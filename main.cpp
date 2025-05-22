#include <stdio.h>
#include <canvas.hpp>

void zeros(int xAxis, int yAxis,std::vector<std::vector<cell>> &empty)
{
    for(int i=0; i<yAxis; i++)
    {
        std::vector<cell> temp;
        for(int j=0; j<xAxis; j++)//there should be something checking for links
        {
            cell tempCell(false,{i,j});
            temp.push_back(tempCell);
        }
        empty.push_back(temp);
    }
}
void step(std::vector<std::vector<int>> &canvas)
{
    
}
void showCanvas(std::vector<std::vector<cell>> canvas)
{
    for(auto i : canvas)
    {
        for(auto j : i)
        {
            if(j.getStatus() == false)
            {
                printf("0");
            }
            else
            {
                printf("1");
            }
        }
            printf("\n");

    }
}
int main() 
{
    std::vector<std::pair<int,int>> alive = {{1,1},{-1,-1},{2,1}};
    auto background = canvas(alive);
    background.showCanvas();

    return 0;
}