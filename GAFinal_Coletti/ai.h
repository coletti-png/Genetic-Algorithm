#ifndef AI_H
#define AI_H

#include <vector>
#include "board.h"

using namespace std;

class AI {
public:
    vector<int> chromosome; 
    int fitness;            
    int totalFitness;       
    int generation;
    AI();  
    void calculateFitness(Board& board, char aiMarker, char playerMarker);
    int evaluateIntermediateBoardState(Board& board, char aiMarker, char playerMarker);

    void resetFitness();  
};

#endif


