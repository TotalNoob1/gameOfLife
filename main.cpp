#include <stdio.h>
#include <canvas.hpp>

int main() 
{
    std::vector<std::pair<int,int>> alive = {{1,1},{3,1},{2,1},{4,0},{0,4}};
    auto background = canvas(alive);
    background.showCanvas();

    return 0;
}