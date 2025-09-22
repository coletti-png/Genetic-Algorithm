#ifndef BOARD_H
#define BOARD_H

#include <vector>
using namespace std;

class Board {
public:
    vector<char> board;

    Board();  
    void display(int lastMoveIndex, char lastMoveMarker, const std::vector<int>& winningLine);
    bool isEmpty(int index) const;
    void removeMarker(int index);
    bool placeMarker(int position, char marker);
    bool twoInARow(char marker);

    bool checkWin(char marker, std::vector<int>& winningLine);

          
    bool isDraw();                      
    void reset();                        
};

#endif