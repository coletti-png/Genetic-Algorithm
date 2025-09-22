#include <iostream>
#include "board.h"
#include "genetic_algorithm.h"
#include "ai.h"

using namespace std;

int main() {
    srand(time(0));
    std::vector<int> winningLine;
    Board board;
    GeneticAlgorithm ga;
    char humanMarker = 'X';
    char aiMarker = 'O';

    int generations = 1000;
    for (int i = 0; i < generations; ++i) {
        ga.epoch(board, aiMarker, humanMarker);
    }

    AI bestAI = *max_element(ga.population.begin(), ga.population.end(), [](AI& a, AI& b) {
        return a.fitness < b.fitness;
        });

    int humanWins = 0, aiWins = 0, draws = 0;

    for (int game = 0; game < 10; ++game) {
        int lastMoveIndex = -1;
        char lastMoveMarker = ' ';
        bool humanTurn = false;
        board.reset();

        cout << "\nStarting Game " << game + 1 << "...\n";
        

        int aiMoveIndex = 0; 

        while (true) {

            if (humanTurn) {
              
                int move;
                cout << "Enter your move (0-8): ";
                cin >> move;
                if (board.placeMarker(move, humanMarker)) {
                    lastMoveIndex = move;     
                    lastMoveMarker = humanMarker;
                    humanTurn = false;
                    board.display(lastMoveIndex, lastMoveMarker, winningLine);
                    cout << "Human made a move.\n";
                    if (board.checkWin(humanMarker, winningLine)) {
                        cout << "You win this game!\n";
                        ++humanWins;
                        board.display(lastMoveIndex, lastMoveMarker, winningLine);
                        bestAI.calculateFitness(board, aiMarker, humanMarker);
                        break;
                    }
                    else if (board.isDraw()) {
                        cout << "It's a draw!\n";
                        board.display(lastMoveIndex, lastMoveMarker, {});
                        ++draws;
                        bestAI.calculateFitness(board, aiMarker, humanMarker);
                        break;
                    }
                }
                else {
                    cout << "Invalid move. Try again.\n";
                }
            }
            else {
                
                bool aiMoved = false;
               
                int attempts = 0;
                while (attempts < 9 && !aiMoved) {
                    int move = bestAI.chromosome[aiMoveIndex];
                    aiMoveIndex = (aiMoveIndex + 1) % 9;
                    attempts++;
                    if (board.placeMarker(move, aiMarker)) {
                        lastMoveIndex = move;      
                        lastMoveMarker = aiMarker; 
                        aiMoved = true;
                        humanTurn = true;
                        
                        std::cout << "AI's current fitness: " << bestAI.fitness << "\n";
                        std::cout << "AI's generation: " << bestAI.generation << "\n";
                    
                        board.display(lastMoveIndex, lastMoveMarker, winningLine);
                       
                      
                        cout << "AI made a move.\n";
                        if (board.checkWin(aiMarker, winningLine)) {
                            cout << "AI wins this game!\n";
                            ++aiWins;
                            board.display(lastMoveIndex, lastMoveMarker, winningLine);
                            bestAI.calculateFitness(board, aiMarker, humanMarker);
                            break;
                        }
                        else if (board.isDraw()) {
                            cout << "It's a draw!\n";
                            board.display(lastMoveIndex, lastMoveMarker, {});
                            ++draws;
                            bestAI.calculateFitness(board, aiMarker, humanMarker);
                            break;
                        }
                    }
                }
            }

            
            
        }
    }

    cout << "\nBest of 10 series results:\n";
    cout << "Human Wins: " << humanWins << "\n";
    cout << "AI Wins: " << aiWins << "\n";
    cout << "Draws: " << draws << "\n";
    cout << "\nAI's Final Fitness Score: " << aiWins + draws << "/10 " << "\n";
    return 0;
}