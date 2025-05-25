#include <cell.hpp>
#include <iostream>

cell::cell()
{
}

cell::cell(bool isAlive,std::pair<int,int> pos)
{
    alive = isAlive;
    place =pos;
}
void cell::setNeighbor(cell *neighbor, std::pair<int,int> loc)
{
    neigbors[loc] = neighbor;
}
cell* cell::checkNeigbor(std::pair<int,int> loc)
{
    return neigbors.at(loc);
}
std::vector<std::pair<std::pair<int,int>,cell*>> cell::getNeighbors()
{
    std::vector<std::pair<std::pair<int,int>,cell*>> temp;
    for (auto neigh : neigbors)
    {
        temp.push_back({neigh.first, neigh.second});
    }
    return temp;
}
bool cell::getStatus()
{
    return alive;
}
std::pair<std::pair<int,int>,int> cell::getPlace()
{
    return {place,arrayLocation};
}
void cell::setStatus(bool status)
{
    alive = status;
}
void cell::setPlace(std::pair<int,int> pos, int i)
{
    place = pos;
    arrayLocation = i;
} 
int cell::getaliveNeighbors()
{
    return aliveNeighbors;
}
void cell::addAliveNeighbor()
{
    aliveNeighbors++;
}
void cell::removeAliveNeighbor()
{
    aliveNeighbors--;
}
cell::~cell()
{
    if (this != nullptr)
    {
        std::vector<std::pair<int,int>> change;
        for(auto i : neigbors)
        {
            if(i.second != nullptr)
            {
                change.push_back(i.first);
            }
        }
        for(auto i : change)
        {
            neigbors[i] = nullptr;
        }
        neigbors.~map();
        delete topLeft;
        delete topRight;
        delete top;
        delete left;
        delete right;
        delete bottomLeft;
        delete bottom;
        delete bottomRight;
    }
}