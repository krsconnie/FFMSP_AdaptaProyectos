#ifndef GENETIC_H
#define GENETIC_H

#include "getInput.h"
#include "brkga2.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::vector<std::string> geneticAlgorithm(const std::list<std::string>& inputList, int length, int populationSize, float mutationProbability, int dHamThreshold) {
    std::list<std::vector<double>> initPopulation;
    createPSol(populationSize, length, initPopulation);             //We create the initial population

    std::list<std::string> decodedSolutions;                        //Decode initial solutions to strings
    decodedList(initPopulation, decodedSolutions);

    std::vector<int> qualityScores;                                 //We evaluate the initial fitness
    calculateQuality(dHamThreshold, qualityScores, inputList, decodedSolutions);
    preselection(qualityScores, decodedSolutions);                  //Sort by fitness and extract the elite solutions
                                                                    //Up to here, we're doing great!

    float eliteProportion = 1 - mutationProbability;
    std::list<std::vector<double>> eliteChromosomes, nonEliteChromosomes;   //Prepare lists for elite and non-elite populations
    int eliteSize = populationSize*eliteProportion;                           //20% elite since we decided to make it deterministic (0% of mutation). We can modify this if necessary.
    int mutantSize = populationSize * mutationProbability;

    sortPobl(0, eliteSize, mutantSize, length, eliteChromosomes, nonEliteChromosomes, initPopulation);    //We sort it once more.
    
    double crossoverBias = 0.7;                                     //We can also modify the crossover bias if necessary
    newPobl(crossoverBias, mutantSize, initPopulation, eliteChromosomes, nonEliteChromosomes);  //Generate new population
    
    decodedSolutions.clear();                                       //Decode and return solutions
    decodedList(initPopulation, decodedSolutions);
    
    return std::vector<std::string>(decodedSolutions.begin(), decodedSolutions.end());
}
#endif