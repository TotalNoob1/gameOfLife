#include <canvas.hpp>
#include <iostream>
#include <string>
#include <algorithm>

std::pair<int,int> relativeLocation(int x, int y)
{
    std::pair<int,int> temp;
    if (x < 0)
    {
        temp.first = -1;
    }
    else if (x > 0)
    {
        temp.first = 1;
    }
    else
    {
        temp.first = 0;
    }
    if (y < 0)
    {
        temp.second = -1;
    }
    else if (y > 0)
    {
        temp.second = 1;
    }
    else
    {
        temp.second = 0;
    }
    return temp;
}
void createLinks(cell *prev)
{

}

canvas::canvas(std::vector<std::pair<int,int>> aliveCells)
{   
    std::pair<int,int> finding = {0,0};
    if (find(aliveCells.begin(),aliveCells.end(),finding) != aliveCells.end())
    {
        auto temp = new cell(true,{0,0});
        start = *temp;
        orgin = &start;
    }
    else
    {
        auto temp = new cell(false,{0,0});
        start = *temp;
        orgin = &start;
    }
    
    bool done = false;
    for(auto coors : aliveCells)
    {
        cell *prev = orgin;
        int layers = 0;
        int xAxis = coors.first;
        int yAxis = coors.second;
        int x = 0;
        int y = 0;

        while (xAxis != 0 && yAxis != 0)
        {
            std::pair<int,int> loc = relativeLocation(xAxis,yAxis);
            xAxis -= loc.first;
            yAxis -= loc.second;
            x += loc.first;
            y += loc.second;
            if (prev->checkNeigbor(loc) == nullptr)
            {
                if (yAxis == 0 && xAxis == 0)
                {

                    auto next = new cell(true,{x,y});//going to have to delete
                    allAliveCells.push_back(next);
                    allCells.push_back(next);
                    prev->setNeighbor(next,loc);
                    done = true;

                }
                else
                {
                    auto next = new cell(false,{x,y});
                    allCells.push_back(next);
                    prev->setNeighbor(next,loc);
                    prev = next;
                }
            }
            else
            {
                prev = prev->checkNeigbor(loc);//Add A set back neighbor, along with a way to chain the neighbors
            }
            layers++;


        }
        if (xAxis == 0 && !done)
        {
            while (yAxis != 0)
            {
                std::pair<int,int> loc = relativeLocation(xAxis,yAxis);
                yAxis -= loc.second;
                y += loc.second;
                if (prev->checkNeigbor(loc) == nullptr)
                {
                    if (yAxis == 0)
                    {
                        auto next = new cell(true,{x,y});
                        allAliveCells.push_back(next);
                        allCells.push_back(next);
                        prev->setNeighbor(next,loc);
                    }
                    else
                    {
                        auto next = new cell(false,{x,y});
                        allCells.push_back(next);
                        prev->setNeighbor(next,loc);
                        prev = next;

                    }
                }
                else
                {
                    prev = prev->checkNeigbor(loc);
                }
            }
            layers++;

            
        }
        else if (yAxis == 0 && !done)
        {
            while (xAxis != 0)
            {
                std::pair<int,int> loc = relativeLocation(xAxis,yAxis);
                xAxis -= loc.first;
                x += loc.first;
                if (prev->checkNeigbor(loc) == nullptr)
                {
                    if (xAxis == 0)
                    {
                        auto next = new cell(true,{x,y});
                        allAliveCells.push_back(next);
                        allCells.push_back(next);
                        prev->setNeighbor(next,loc);
                    }
                    else
                    {
                        auto next = new cell(false,{x,y});
                        allCells.push_back(next);
                        prev->setNeighbor(next,loc);
                        prev = next;
                    }
                }
                else
                {
                    prev = prev->checkNeigbor(loc);
                }
            }
            layers++;
        }
        if(layers> layer)
        {
            layer = layers;
        }
        done = false;
        
    }
}
void canvas::showCanvas()
{
    std::cout <<layer<< std::endl;
    //auto dims = getDim(orgin,{0,0,0,0},0);
    //printf("%d\n%d\n", dims[0],dims[1]);
    //printf("%d\n%d\n", dims[2],dims[3]);
}
