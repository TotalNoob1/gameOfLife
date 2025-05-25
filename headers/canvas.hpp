
#include <cell.hpp>

class canvas
{
    private:
        cell start;
        std::map<std::pair<int,int>, cell *> allAliveCells;
        std::map<std::pair<int,int>, cell *> allDeadCells;
        std::map<std::pair<int,int>, cell *> newAliveCells;
        std::map<std::pair<int,int>, cell *> newDeadCells;  
        std::map<std::pair<int,int>, cell *> allCells;
        cell *orgin;
        std::vector<int> currentDim = {0,0,0,0};// {x,-x,y,-y}
        int bishopRight = 0;// up and to the right
        int bishopLeft = 0;// up and to the left
        int upDown = 0;
        //Moving left and right will just need to go by one
    public:
        canvas(std::vector<std::pair<int,int>> aliveCells);
        void showCanvas();
        void setNeighbors(std::map<std::pair<int,int>, cell *> *aliveCells);
        void step(int steps);
};


