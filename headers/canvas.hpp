
#include <cell.hpp>

class canvas
{
    private:
        cell start;
        std::vector<cell *> allAliveCells;//consider changing these to bst or some other data struct to make deleting and inserting faster
        std::vector<cell *> allDeadCells;
        std::vector<cell *> newAliveCells;
        std::vector<cell *> newDeadCells;  
        std::vector<cell *> allCells;
        cell *orgin;
        std::pair<int,int> currentDim = {0,0};// {x,y}
        int bishopRight = 0;// up and to the right
        int bishopLeft = 0;// up and to the left
        int upDown = 0;
        //Moving left and right will just need to go by one
    public:
        canvas(std::vector<std::pair<int,int>> aliveCells);
        void showCanvas();
        void step(int steps);
};


