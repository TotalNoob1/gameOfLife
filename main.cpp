#include <stdio.h>
#include <canvas.hpp>
#include <iostream>
#include <chrono>
#include <thread>
int main() 
{
    std::vector<std::pair<int,int>> alive = {{0,2},{1,1},{1,2},{1,3},{1,2},{2,3}};
    auto background = canvas(alive);
    for (int i = 0; i < 8; i++)
    {
        background.showCanvas();
        background.step(1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    background.showCanvas();
    return 0;
}