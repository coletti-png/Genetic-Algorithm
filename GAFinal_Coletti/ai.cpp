#include <algorithm>
#include <cstdlib>
#include "ai.h"
#include "Board.h"
AI::AI() {
    chromosome = vector<int>(9);
    for (int i = 0; i < 9; ++i)
        chromosome[i] = i;
    random_shuffle(chromosome.begin(), chromosome.end());
    fitness = 0;
    totalFitness = 0; 
    generation = 0;
}

void AI::calculateFitness(Board& board, char aiMarker, char playerMarker) {
    board.reset();
    fitness = 0;
    std::vector<int> winningLine; 

    for (int i = 0; i < 9; ++i) {
        if (i % 2 == 0) {  
            if (!board.placeMarker(chromosome[i], aiMarker)) {
                fitness -= 20;  
                continue;
            }
        }
        else {  // Simulate player's move
            int randomMove = rand() % 9;
            while (!board.placeMarker(randomMove, playerMarker)) {
                randomMove = rand() % 9;
            }
        }

        // Check if AI wins
        if (board.checkWin(aiMarker, winningLine)) {  
            fitness += 1000;  
            return;
        }
        if (board.checkWin(playerMarker, winningLine)) {  
            fitness -= 100;  
            return;
        }

        fitness += evaluateIntermediateBoardState(board, aiMarker, playerMarker);
    }

    if (board.isDraw()) {
        fitness += 30;
    }
}

int AI::evaluateIntermediateBoardState(Board& board, char aiMarker, char playerMarker) {
    int score = 0;

    if (board.twoInARow(aiMarker)) {
        score += 50; 
    }

    if (board.twoInARow(playerMarker)) {
        score += 20; 
    }

    return score;
}
void AI::resetFitness() {
    totalFitness = 0; 
}