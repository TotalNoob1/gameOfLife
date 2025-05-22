#include <canvas.hpp>
#include <iostream>
#include <string>
#include <algorithm>

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
    for(auto cel : allAliveCells)
    {
        auto neighbors = cel->getNeighbors();
        auto places = cel->getPlace();
        auto pos = places.first;
        for(auto neighbor : neighbors)
        {
            int relX = neighbor.first.first;
            int relY = neighbor.first.second;
            int i = relX + places.second;
            if (relY > 0 )
            {
                i += upDown;
            }
            else if (relY < 0)
            {
                i -= upDown;
            }
            pos.first += relX;
            pos.second += relY;
            if (allCells[i] == nullptr)
            {
                auto deadCell = new cell(false,pos);
                allCells[i] = deadCell;
                deadCell->setPlace(pos,i);
                cel->setNeighbor(deadCell,neighbor.first);
            }
            else
            {
                cel->setNeighbor(allCells[i],neighbor.first);
            }
            pos = places.first;   
        }
    }
    
    
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
