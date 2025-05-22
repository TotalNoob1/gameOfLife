
#include <cell.hpp>

class canvas
{
    private:
        cell start;
        std::vector<cell *> allAliveCells;
        std::vector<cell *> allCells;
        cell *orgin;
        int layer;
        std::pair<int,int> currentDim;
    public:
        canvas(std::vector<std::pair<int,int>> aliveCells);
        void showCanvas();
};


