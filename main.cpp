#include <stdio.h>
#include <canvas.hpp>
#include <iostream>
int main() 
{
    std::vector<std::pair<int,int>> alive = {{1,1},{2,1},{3,1},{2,2}};
    auto background = canvas(alive);
    for (int i = 0; i < 50; i++)
    {
        background.showCanvas();
        background.step(1);
    }
    background.showCanvas();
    return 0;
}