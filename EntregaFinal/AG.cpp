#ifndef GENETIC_H
#define GENETIC_H

#include "getInput.h"
#include "utilidades.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

//La inicialización crea una población inicial de tamaño "populationSize", cada solución de largo "largo" generada de manera aleatoria
//según los caracteres base.
std::vector<std::string> initializePopulation(int largo, int populationSize) {
    std::vector<std::string> population;
    std::vector<char> bases = {'A', 'C', 'G', 'T'};
    for (int i = 0; i < populationSize; i++) {
        std::string solution;
        for (int j = 0; j < largo+1; j++) {
            solution.push_back(bases[rand()%4]);
        }
        population.push_back(solution);
    }
    return population;
}

//Operador de cruzamiento
//Aquí elegí un cruzamiento segmentado, ya que al seccionar los strings de ambos padres en partes iguales y
//concatenarlas en el offspring el algoritmo es más rápido y los hijos preservan más info estructural de los padres.
std::string crossover(const std::string& parent1, const std::string& parent2) {
    int point = rand() % parent1.size();
    return parent1.substr(0, point) + parent2.substr(point);
}

//Operador de mutación. No lo ocupamos ya que el algoritmo es determinista, pero lo dejo escrito en caso de necesitarlo.
//La mutación puede mutar un caracter al mismo caracter original. Una implementación que verifique que el caracter mutado
//sea distinto podría resultar mucho más costosa temporalmente en strings largos como los que utilizamos.
//Queremos que esta implementación sea mejor que las anteriores!!!
void mutate(std::string& solution, float probRandom) {
    std::vector<char> bases = {'A', 'C', 'G', 'T'};
    float dice;
    for (int i=0; i<solution.size(); i++){
        dice = static_cast<float>(rand()) / RAND_MAX;
        if (dice < probRandom) {
            solution[i] = bases[rand() % 4];
        }
    }
}

bool stoppinRule(std::vector<int>& quality, int thresholdDiference) {
    for (auto& q : quality) {
        //std::cout << "Checking quality: " << q << " against threshold: " << thresholdDiference << std::endl;
        if (q >= thresholdDiference) {
            return true;
        }
    }
    return false;
}

bool compareFitnessScores(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){
    return a.second > b.second;
}

//Algoritmo genético principal
//En contraste con Greedy, geneticAlgorithm ya no tiene float umbral, en cambio, ahora necesita los parámetros:
//populationSize parar definir el tamaño de la población inicial y dHam (distancia de Hamming) para definir mínimos de calidad.
std::vector<std::string> geneticAlgorithm(std::list<std::string>& lista, int largo, int populationSize, float probRandom, int dHam){
    srand(time(0));

    int initPopFitness;
    bool stop = false;
    std::vector<std::string> eliteSolutions, newPopulation;
    std::vector<std::pair<std::string, int>> fitnessScores;
    std::vector<int> eliteFitness, newFitness;

    std::vector<std::string> population = initializePopulation(largo, populationSize);

    while(!stop || newPopulation.size() < populationSize){
        int bestFitness = -1;
        std::string bestSolution;
        for (const std::string& solution : population) {
            initPopFitness = calidad(dHam, lista, solution);
            fitnessScores.emplace_back(solution, initPopFitness);
        }
        std::sort(fitnessScores.begin(), fitnessScores.end(), compareFitnessScores);

        //Seleccionar la mejor solución de la generación actual.
        std::string parent1, parent2, child;
        newPopulation.push_back(fitnessScores[0].first);                //Mantener la mejor solución
        newPopulation.push_back(fitnessScores[1].first);
        parent1 = fitnessScores[rand() % populationSize].first;
        parent2 = fitnessScores[rand() % populationSize].first;
        child = crossover(parent1, parent2);

        newPopulation.push_back(child);
        int childFitness = calidad(dHam, lista, child);
        //std::cout<<"Child fitness: "<<childFitness<<std::endl;
        newFitness.push_back(childFitness);
        for(int i=0; i<newFitness.size(); i++){
            if(bestFitness<newFitness[i]){
                bestFitness = newFitness[i];
                bestSolution = newPopulation[i];
            }
        }

        eliteSolutions.push_back(bestSolution); //Añadir la mejor solución al conjunto de soluciones iniciales para MH_p+MH_t.
        std::cout<<"Best Fitness: "<<bestFitness<<" added to Elite Fitness."<<std::endl;
        eliteFitness.push_back(bestFitness);

        stop = stoppinRule(eliteFitness, dHam);
        std::cout<<stop<<std::endl;
        if(stop){
            std::cout<<"Break!"<<std::endl;
            break;
        }

        population = newPopulation;             //Reemplazar población.
    }
    return eliteSolutions;
}
#endif
