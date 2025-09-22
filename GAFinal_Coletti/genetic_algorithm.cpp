#include "genetic_algorithm.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set> 
#include <numeric>
GeneticAlgorithm::GeneticAlgorithm() {
    population = std::vector<AI>(POPULATION_SIZE);
    currentGeneration = 1;
}

void GeneticAlgorithm::calculateFitness(Board& board, char aiMarker, char playerMarker) {
    for (auto& individual : population) {
        individual.calculateFitness(board, aiMarker, playerMarker
        );
    }
}

AI GeneticAlgorithm::rouletteWheelSelection() {
    int totalFitness = 0;
    for (auto& individual : population) {
        totalFitness += individual.fitness;
    }

    int spin = rand() % totalFitness;
    int partialSum = 0;
    for (auto& individual : population) {
        partialSum += individual.fitness;
        if (partialSum >= spin) return individual;
    }
    return population[0]; 
}

void GeneticAlgorithm::crossover(AI& parent1, AI& parent2, AI& offspring) {
    int crossoverPoint = rand() % 9;
    for (int i = 0; i < 9; i++) {
        if (i < crossoverPoint) {
            offspring.chromosome[i] = parent1.chromosome[i];
        }
        else {
            offspring.chromosome[i] = parent2.chromosome[i];
        }
    }
    offspring.generation = currentGeneration;
}

void GeneticAlgorithm::calculatePopulationFitness(Board& board, char aiMarker, char humanMarker) {
    for (AI& individual : population) {
        individual.calculateFitness(board, aiMarker, humanMarker );
    }
}

void GeneticAlgorithm::initializePopulation() {
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        for (int j = 0; j < 9; ++j) {
            population[i].chromosome[j] = j;
        }
        std::random_shuffle(population[i].chromosome.begin(), population[i].chromosome.end());
        population[i].generation = currentGeneration;
    }
}


void GeneticAlgorithm::ensureValidChromosome(AI& offspring) {
    std::set<int> usedMoves;
    for (int i = 0; i < 9; i++) {
        if (usedMoves.find(offspring.chromosome[i]) != usedMoves.end()) {
            offspring.chromosome[i] = rand() % 9;
        }
        usedMoves.insert(offspring.chromosome[i]);
    }
}

void GeneticAlgorithm::mutate(AI& individual) {
    if ((rand() / (float)RAND_MAX) < 0.2) {  
        int index1 = rand() % 9;
        int index2 = rand() % 9;
        std::swap(individual.chromosome[index1], individual.chromosome[index2]);
    }
}

AI& GeneticAlgorithm::selectParent() {
    int totalFitness = std::accumulate(population.begin(), population.end(), 0,
        [](int sum, AI& individual) {
            return sum + individual.fitness;
        }
    );

    int selection = rand() % totalFitness;
    int runningSum = 0;

    for (AI& individual : population) {
        runningSum += individual.fitness;
        if (runningSum >= selection) {
            return individual;
        }
    }
    return population[0]; 
}
void GeneticAlgorithm::initializeNewIndividual(AI& individual) {
    
    for (int i = 0; i < 9; ++i) {
        individual.chromosome[i] = i;
    }

    std::random_shuffle(individual.chromosome.begin(), individual.chromosome.end());

    individual.fitness = 0;
    individual.generation = currentGeneration;
}
void GeneticAlgorithm::epoch(Board& board, char aiMarker, char playerMarker) {
    calculatePopulationFitness(board, aiMarker, playerMarker);

    std::sort(population.begin(), population.end(), [](AI& a, AI& b) {
        return a.fitness > b.fitness;
        });

    AI bestAI = population[0];
    bestAI.generation = currentGeneration;  

    // Create a new population
    std::vector<AI> newPopulation(POPULATION_SIZE);

    newPopulation[0] = bestAI;

    for (int i = 1; i < POPULATION_SIZE; ++i) {
        if (rand() % 100 < 5) {  
            initializeNewIndividual(newPopulation[i]);
        }
        else {
            AI& parent1 = selectParent();
            AI& parent2 = selectParent();
            AI offspring;
            crossover(parent1, parent2, offspring);
            mutate(offspring);
            ensureValidChromosome(offspring);
            offspring.generation = currentGeneration; 
            newPopulation[i] = offspring;
        }
    }
        population = newPopulation;

        currentGeneration++;


    
}