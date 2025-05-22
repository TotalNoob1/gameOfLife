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
std::pair<int,int> cell::getPlace()
{
    return place;
}
void cell::setStatus(bool status,int x, int y)
{
    alive = status;
    place = {x,y};
}