#ifndef GENETIC_H
#define GENETIC_H

#include "getInput.h"
#include "brkga2.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::vector<std::string> geneticAlgorithm(const std::list<std::string>& inputList, int length, int populationSize, float mutationProbability, int dHamThreshold){
    bool stopCondition = false;
    std::list<std::vector<double>> initPopulation;                  //Current population
    std::list<std::vector<double>> eliteChromosomes, nonEliteChromosomes;   //Initialize lists for elite and non-elite populations
    std::vector<int> qualityScores;                                 //Then we evaluate the initial fitness
    int gen = 0;

    createPSol(populationSize, length, initPopulation);             //Create the initial population

    std::list<std::string> decodedSolutions;                        //Decode initial solutions to strings
    decodedList(initPopulation, decodedSolutions);

    while (!stopCondition) {
        qualityScores.clear();
        populationSize = decodedSolutions.size();

        calculateQuality(dHamThreshold, qualityScores, inputList, decodedSolutions); //Calculate fitness scores
        stopCondition = stoppinRule(qualityScores, dHamThreshold);                   //Check stopping condition (element in quality scores exceeds the threshold).

        preselection(qualityScores, decodedSolutions);              //Sort by fitness and extract the elite solutions
        
        float eliteProportion = 1 - mutationProbability;
        int eliteSize = populationSize * eliteProportion;           
        int mutantSize = populationSize * mutationProbability;
        if (eliteSize + mutantSize > populationSize) {              //Adjust sizes if they exceed the population size
            eliteSize = populationSize - mutantSize;
        }

        eliteChromosomes.clear();
        nonEliteChromosomes.clear();
        sortPobl(gen, eliteSize, mutantSize, length, eliteChromosomes, nonEliteChromosomes, initPopulation, dHamThreshold, inputList);    //We sort it once more.

        double crossoverBias = 0.5;                                 //We can also modify the crossover bias if necessary

        std::list<std::vector<double>> nextPopulation;              //New population to replace the previous generation
        nextPopulation.insert(nextPopulation.end(), eliteChromosomes.begin(), eliteChromosomes.end()); //Add elite solutions directly to the next generation

        newPobl(crossoverBias, mutantSize, nextPopulation, eliteChromosomes, nonEliteChromosomes);  //Generate offspring and mutated solutions

        // Ensure the next generation has a fixed size
        if (nextPopulation.size() > populationSize) {
            auto it = nextPopulation.begin();
            std::advance(it, populationSize);
            nextPopulation.erase(it, nextPopulation.end());
        }

        decodedSolutions.clear();                                   // Decode the new population into strings
        decodedList(nextPopulation, decodedSolutions);
        initPopulation = nextPopulation;                           // Replace the current generation with the new one
    }

    return std::vector<std::string>(decodedSolutions.begin(), decodedSolutions.end());
}

#endif