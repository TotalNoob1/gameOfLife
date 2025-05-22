#include <utility>
#include <vector>
#include <map>
class cell
{
    private:
        bool alive;
        int onLeftOrRightBorder = 0;// 0 = no border -1 = left 1 = right TODO:: should replace these with basic bool if it on the border
        int onTopOrBottomBorder = 0;// 0 = no border -1 = bottom 1 = top
        cell *topLeft = nullptr;
        cell *top = nullptr;
        cell *topRight = nullptr;
        cell *left = nullptr;
        cell *right = nullptr;
        cell *bottomLeft = nullptr;
        cell *bottom = nullptr;
        cell *bottomRight = nullptr;
        std::map<std::pair<int,int>,cell*> neigbors = {
            {{-1,1},topLeft},
            {{0,1}, top},
            {{1,1}, topRight},
            {{-1,0}, left},
            {{1,0}, right},
            {{-1,-1},bottomLeft},
            {{0,-1}, bottom},
            {{1,-1}, bottomRight}
        };
        int arrayLocation = 0;
        std::pair<int,int> place;
    public:
        cell();
        cell(bool isAlive,std::pair<int,int> position);
        void setNeighbor(cell *neighbor,std::pair<int,int> loc);
        cell *checkNeigbor(std::pair<int,int> loc);
        std::vector<std::pair<std::pair<int,int>,cell*>> getNeighbors();
        bool getStatus();
        std::pair<std::pair<int,int>,int> getPlace();
        void setStatus(bool status);// The pos is on a grid. i is on the array.
        void setPlace(std::pair<int,int> pos, int i);
};