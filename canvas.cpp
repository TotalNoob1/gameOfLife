#include <canvas.hpp>
#include <iostream>
#include <string>
#include <algorithm>

void canvas::setNeighbors(std::map<std::pair<int,int>, cell *> *aliveCells)
{
    for(auto cel : *aliveCells)
    {
        auto neighbors = cel.second->getNeighbors();
        auto places = cel.second->getPlace();//change get place to remove the i
        auto pos = places.first;
        for(auto neighbor : neighbors)
        {
            int relX = neighbor.first.first;
            int relY = neighbor.first.second;
            pos.first += relX;
            pos.second += relY;
            std::pair<int,int> oppisote = {neighbor.first.first * -1, neighbor.first.second * -1};
            auto search = allCells.find(pos);
            if (search == allCells.end())
            {
            auto deadCell = new cell(false,pos);
            if (pos.first < 0)
            {
                if (pos.first < currentDim[1])
                {
                    currentDim[1] = pos.first;
                }
            }
            else if (pos.first > currentDim[0])
            {
                currentDim[0] = pos.first;  
            }
            if (pos.second < 0)
            {
                if (pos.second < currentDim[3])
                {
                    currentDim[3] = pos.second;
                } 
            }
            else if (pos.second > currentDim[2])
            {
                currentDim[2] = pos.second;
            }
                allCells.insert({pos,deadCell});
                deadCell->setPlace(pos,0);
                cel.second->setNeighbor(deadCell,neighbor.first);
                deadCell->setNeighbor(cel.second,oppisote);
                allDeadCells.insert({pos,deadCell});
                deadCell->addAliveNeighbor();
            }
            else if((*search).second->getStatus())
            {
                cel.second->setNeighbor((*search).second,neighbor.first);
                (*search).second->addAliveNeighbor();
            }
            else
            {
                cel.second->setNeighbor((*search).second,neighbor.first);
                (*search).second->setNeighbor(cel.second,oppisote);
                (*search).second->addAliveNeighbor();
            }
            pos = places.first;   
        }
    }
}

canvas::canvas(std::vector<std::pair<int,int>> aliveCellsPos)
{   
    for(auto coors : aliveCellsPos)
    {
        int xAxis = coors.first;//adding on to both x and y axis to ensure they will not start on the x or y axis
        int yAxis = coors.second;
        if (xAxis < 0)
        {
            if (xAxis < currentDim[1])
            {
                currentDim[1] = xAxis;
            }
        }
        else if (xAxis > currentDim[0])
        {
            currentDim[0] = xAxis;
        }
        if (yAxis < 0)
        {
            if (yAxis < currentDim[3])
            {
                currentDim[3] = yAxis;
            } 
        }
        else if (yAxis > currentDim[2])
        {
            currentDim[2] = yAxis;
        }
        auto newCell = new cell(true,{xAxis,yAxis});
        allAliveCells.insert({{xAxis,yAxis},newCell});
        allCells.insert({{xAxis,yAxis},newCell});
    }
    setNeighbors(&allAliveCells);
}

void canvas::showCanvas()
{
    std::vector<std::string> lines;//honsetly this might be where that box array should go
    std::string line ="";
    for (int y = currentDim[3]; y < currentDim[2]; y++)
    {
        for (int i = currentDim[1]; i < currentDim[0]; i++)
        {
            line.append(" ");
        }
        lines.push_back(line);
        line ="";
    }
    for (auto alive : allAliveCells)
    {
        auto coors = alive.first;
        lines[coors.second-currentDim[3]][coors.first-currentDim[1]] = '0';
    }
    for(int i = lines.size() - 1; i >= 0; i--)
    {
        std::cout<<lines[i]<<std::endl;
    }

    

    // for (int i = 0; i < currentDim.first * currentDim.second; i++)
    // {
    //     if (allCells[i] == nullptr)
    //     {
    //         line.push_back('0');
    //     }
    //     else if (!(allCells[i]->getStatus()))
    //     {
    //         line.push_back('0');
    //     }
    //     else
    //     {
    //         line.push_back('1');
    //     }
    //     if ((i+1) % currentDim.first == 0)
    //     {
    //         lines.push_back(line);
    //         line = "";
    //     }
    // }

}
//Could store the amount of alive neighbor so I don't have to count them over and over
void canvas::step(int steps)//TODO Add delete dead cells with no alive neighbors
{
    for (int i = 0; i < steps; i++)
    {

        for(auto cel : allAliveCells)
        {
            int alive = cel.second->getaliveNeighbors();
            //Rule 1 Each cell with one or no neighbors dies
            //Rule 2 Each cell with four or more neighbors dies
            if (alive <= 1 || alive >= 4)
            {
                newDeadCells.insert({cel.first,cel.second});
            }
            //Rule 3 Each cell with two or three neighbor lives 
        }
        for(auto cel : allDeadCells)
        {
            int alive = cel.second->getaliveNeighbors();
            if (alive == 3)
            {
                newAliveCells.insert({cel.first,cel.second});
            }
        }
        for(auto newCell : newAliveCells)
        {
            newCell.second->setStatus(true);
            auto it = std::find(allDeadCells.begin(),allDeadCells.end(),newCell);
            if(it != allDeadCells.end())
            {
                allDeadCells.erase(it);
            }
            allAliveCells.insert({newCell.first,newCell.second});
            
        }
        for(auto newCell : newDeadCells)
        {
            newCell.second->setStatus(false);
            for(auto cel : newCell.second->getNeighbors())
            {
                auto neigh = cel.second;
                neigh->removeAliveNeighbor();
            }
            auto it = std::find(allAliveCells.begin(),allAliveCells.end(),newCell);
            if(it != allAliveCells.end())
            {
                allAliveCells.erase(it);
            }
            allDeadCells.insert({newCell.first,newCell.second});
        }
        setNeighbors(&newAliveCells);
        newAliveCells.clear();
        newDeadCells.clear();
    }
}