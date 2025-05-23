#include <canvas.hpp>
#include <iostream>
#include <string>
#include <algorithm>

void setNeighbors(std::vector<cell *> *aliveCells,std::vector<cell *> * deadCells,std::vector<cell *> *allCell,int upDown)
{
    for(auto cel : *aliveCells)
    {
        auto neighbors = cel->getNeighbors();
        auto places = cel->getPlace();
        auto pos = places.first;
        for(auto neighbor : neighbors)
        {
            int relX = neighbor.first.first;
            int relY = neighbor.first.second;
            int i = relX + places.second;
            if (relY > 0)
            {
                i += upDown;
            }
            else if (relY < 0)
            {
                i -= upDown;
            }
            pos.first += relX;
            pos.second += relY;
            std::pair<int,int> oppisote = {neighbor.first.first * -1, neighbor.first.second * -1};
            if ((*allCell)[i] == nullptr)
            {
                auto deadCell = new cell(false,pos);
                (*allCell)[i] = deadCell;
                deadCell->setPlace(pos,i);
                cel->setNeighbor(deadCell,neighbor.first);
                deadCell->setNeighbor(cel,oppisote);
                (*deadCells).push_back(deadCell);
                deadCell->addAliveNeighbor();

            }
            else if((*allCell)[i]->getStatus())
            {
                cel->setNeighbor((*allCell)[i],neighbor.first);
                (*allCell)[i]->addAliveNeighbor();
            }
            else
            {
                cel->setNeighbor((*allCell)[i],neighbor.first);
                (*allCell)[i]->setNeighbor(cel,oppisote);
                (*allCell)[i]->addAliveNeighbor();
            }
            pos = places.first;   
        }
    }
}

canvas::canvas(std::vector<std::pair<int,int>> aliveCellsPos)
{   
    for(auto coors : aliveCellsPos)
    {
        int xAxis = coors.first+1;//adding on to both x and y axis to ensure they will not start on the x or y axis
        int yAxis = coors.second+1;
        if(xAxis > currentDim.first)
        {
            currentDim.first = xAxis;
        }
        if(yAxis > currentDim.second)
        {
            currentDim.second = yAxis;
        }

        auto newCell = new cell(true,{xAxis,yAxis});
        allAliveCells.push_back(newCell);
    }
    currentDim.first += 2;// adding 2 to a buffer layer to ensure they are not on the edge
    currentDim.second += 2;

    for (int i = 0; i < (currentDim.first*currentDim.second); i++)
    {
        allCells.push_back(nullptr);//Blank canvas
        if (i % currentDim.first == i)//consider just making this a fuction that checks dimisions
        {
            bishopRight = i + 2;
            bishopLeft = i;
            upDown = i + 1;
        }
        
    }
    for (auto cell : allAliveCells)//Places the cell into the array 
    {
        auto pos = cell->getPlace();
        int x = pos.first.first;
        int y = pos.first.second;
        int i =0;
        if (x == y)
        {
            i = x * bishopRight;
        }
        else
        {
            i = (x > y) ? y * bishopRight + x - y : x * bishopRight + (y - x)* upDown ;
        }
        allCells[i] = cell;
        cell->setPlace(pos.first,i);
    }
    setNeighbors(&allAliveCells,&allDeadCells,&allCells,upDown);
    
    
}

void canvas::showCanvas()
{
    std::vector<std::string> lines;
    std::string line ="";

    for (int i = 0; i < currentDim.first * currentDim.second; i++)
    {
        if (allCells[i] == nullptr)
        {
            line.push_back('0');
        }
        else if (!(allCells[i]->getStatus()))
        {
            line.push_back('0');
        }
        else
        {
            line.push_back('1');
        }
        if ((i+1) % currentDim.first == 0)
        {
            lines.push_back(line);
            line = "";
        }
    }
    for(int i = lines.size() - 1; i >= 0; i--)
    {
        std::cout<<lines[i]<<std::endl;
    }
}
//Could store the amount of alive neighbor so I don't have to count them over and over
void canvas::step(int steps)//TODO Add delete dead cells with no alive neighbors
{
    for (int i = 0; i < steps; i++)
    {

        for(auto cel : allAliveCells)
        {
            int alive = cel->getaliveNeighbors();
            //Rule 1 Each cell with one or no neighbors dies
            //Rule 2 Each cell with four or more neighbors dies
            if (alive <= 1 || alive >= 4)
            {
                newDeadCells.push_back(cel);
            }
            //Rule 3 Each cell with two or three neighbor lives 
            
        }
        for(auto cel : allDeadCells)
        {
            int alive = cel->getaliveNeighbors();
            if (alive == 3)
            {
                newAliveCells.push_back(cel);
            }
        }
        for(auto newCell : newAliveCells)
        {
            newCell->setStatus(true);
            auto it = std::remove(allDeadCells.begin(),allDeadCells.end(),newCell);
            if(it != allDeadCells.end())
            {
                allDeadCells.erase(it);
            }
            allAliveCells.push_back(newCell);
            
        }
        for(auto newCell : newDeadCells)
        {
            newCell->setStatus(false);
            for(auto cel : newCell->getNeighbors())
            {
                auto neigh = cel.second;
                neigh->removeAliveNeighbor();
            }
            auto it = std::remove(allAliveCells.begin(),allAliveCells.end(),newCell);
            if(it != allAliveCells.end())
            {
                allAliveCells.erase(it);
            }
            allDeadCells.push_back(newCell);
        }
        setNeighbors(&newAliveCells,&allDeadCells,&allCells,upDown);
        newAliveCells.clear();
        newDeadCells.clear();
        //going to have to resize the canvases;
    }
}