#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include "ai.h"
#include "board.h"

#define POPULATION_SIZE 18
#define MUTATION_RATE 0.1

class GeneticAlgorithm {
public:
    vector<AI> population;
    int currentGeneration;
    
    GeneticAlgorithm(); 
    void initializePopulation(); 
    void calculatePopulationFitness(Board& board, char aiMarker, char humanMarker);  
    AI& selectParent();
    void initializeNewIndividual(AI& individual);
    void calculateFitness(Board& board, char aiMarker, char playerMarker);  
    AI rouletteWheelSelection();  
    void crossover(AI& parent1, AI& parent2, AI& offspring);
    void ensureValidChromosome(AI& offspring);
    void mutate(AI& individual); 
    void epoch(Board& board, char aiMarker, char playerMarker); 
};

#endif