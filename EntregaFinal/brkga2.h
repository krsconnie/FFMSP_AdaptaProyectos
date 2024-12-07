#ifndef BRKGA_H
#define BRKGA_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <random>
#include <ctime>
#include <algorithm>
#include "utilidades.h"


char mapKeyToChar(double key) { // Asigna a cada character un rango de numeros
    
    if (key < 0.25) return 'A';
    else if (key < 0.5) return 'C';
    else if (key < 0.75) return 'T';
    else return 'G';

}


std::string decodeChromosome(const std::vector<double>& chromosome) {
    
    std::string decoded;
    
    for (double key : chromosome) {
        decoded.push_back(mapKeyToChar(key));
    }
    return decoded;
}


std::vector<double> encoder(const std::string& input){
  
    std::vector<double> encrypted;
    std::mt19937 generator(static_cast<unsigned>(time(nullptr))); // Random number generator with seed

    for (char ch : input){
        if(ch == 'A'){
            std::uniform_real_distribution<double> distA(0.0, 0.25);
            encrypted.push_back(distA(generator));

        }else if (ch == 'C'){
            std::uniform_real_distribution<double> distC(0.26, 0.50);
            encrypted.push_back(distC(generator));

        }else if (ch == 'T'){
            std::uniform_real_distribution<double> distT(0.51, 0.75);
            encrypted.push_back(distT(generator));

        }else if (ch == 'G'){
            std::uniform_real_distribution<double> distG(0.76, 1.0);
            encrypted.push_back(distG(generator));

        }else{
            std::cout <<"Carácter inválido.\n";
            return {};
        }
    }
    return encrypted;
}


/*
createPSol crea la población inical de soluciones de manera randomizada 
int p: hace referencia a la cantidad de soluciones de la población total
int m: es el tamaño o largo de las soluciones
*/

void createPSol(int p, int m, std::list<std::vector<double>>& Pobl) { 
    
    // Semilla para el generador de números aleatorios
    std::srand(std::time(0)); // Usa la hora actual como semilla

    // Limpia la lista por si ya tiene elementos
    Pobl.clear();

    // Generar 'p' cromosomas
    for (int i = 0; i < p; ++i) {
        std::vector<double> chromosome(m); // Cromosoma de tamaño 'm'

        // Generar genes aleatorios en el rango [0, 1)
        for (int j = 0; j < m; ++j) {
            chromosome[j] = static_cast<double>(std::rand()) / RAND_MAX;
        }

        // Agregar el cromosoma a la población
        Pobl.push_back(chromosome);
    }
}



void decodedList(std::list<std::vector<double>>& chromosomes, std::list<std::string>& sols){

    // Iterar sobre cada cromosoma y decodificarlo
    for (const auto& chromosome : chromosomes) {
        std::string decoded = decodeChromosome(chromosome);
        sols.push_back(decoded);
    }

    //chromosomes.clear(); // borrarla para reutilizarla wink wink ;)
}


void codedList(std::list<std::vector<double>>& chromosomes, std::list<std::string>& sols){

    for(const auto& sol : sols){
        std::vector<double> coded = encoder(sol);
        chromosomes.push_back(coded);
    }

}

void calculateQuality(int dHam,std::vector<int>& quality, const std::list<std::string>& list, const std::list<std::string>& sols) { 
    for (const auto& sol : sols) {
        int avgHamDist = 0;
        for(const auto& chain : list){
            avgHamDist += hammingDist(chain, sol);
        }
        avgHamDist = avgHamDist/list.size();
        quality.push_back(avgHamDist);
    }
}

bool stoppinRule(std::vector<int>& quality, int thresholdDiference){
    for(auto& q : quality){
        if(q >=  thresholdDiference){
            return true;
        }
    }
    return false;
}


void preselection(std::vector<int>& quality, std::list<std::string>& sols) {
    // Verificar que quality y sols tienen el mismo tamaño
    //std::cout << "qualityScores: " << quality.size() << " || decodedSolutions: "<< sols.size() << std::endl;
    if (quality.size() != sols.size()) {
        throw std::invalid_argument("quality y sols deben tener el mismo tamaño");
    }

    // Crear un vector de pares (calidad, solución)
    std::vector<std::pair<int, std::string>> pairedSolutions;

    auto it_sols = sols.begin();
    for (size_t i = 0; i < quality.size(); ++i, ++it_sols) {
        pairedSolutions.emplace_back(quality[i], *it_sols);
    }

    // Ordenar las soluciones por calidad de forma descendente
    std::sort(pairedSolutions.begin(), pairedSolutions.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    // Actualizar la lista `sols` con las soluciones ordenadas
    sols.clear();
    for (const auto& pair : pairedSolutions) {
        sols.push_back(pair.second);
    }

    // Limpiar quality, ya que no es necesaria tras la ordenación
    //quality.clear();
}


void sortPobl(int gen, int pElite, int pMutants, int m, 
                std::list<std::vector<double>>& elite, 
                std::list<std::vector<double>>& nonElite, 
                std::list<std::vector<double>>& sols, int dHam, 
                std::list<std::string> inputList){
    gen++;

    if (pElite + pMutants > sols.size()) {
        throw std::invalid_argument("The size of 'sols' is insufficient for pElite and pMutants.");
    }

    auto it = sols.begin();
    
    // Extract elite chromosomes
    for (int i = 0; i < pElite; ++i) {
        elite.push_back(*it);
        ++it;
    }

    // Calculate qualities of elite chromosomes
    std::list<std::string> decodedElite;
    decodedList(elite, decodedElite); // Decode chromosomes to strings
    std::vector<int> qualityScores;
    calculateQuality(dHam, qualityScores, inputList, decodedElite);

    // Pair elite chromosomes with quality scores
    std::vector<std::pair<int, std::vector<double>>> eliteWithScores;
    auto qualIt = qualityScores.begin();
    for (const auto& chromosome : elite) {
        eliteWithScores.emplace_back(*qualIt, chromosome);
        ++qualIt;
    }

    // Sort elite chromosomes by quality score
    std::sort(eliteWithScores.begin(), eliteWithScores.end(), 
              [](const auto& a, const auto& b) { return a.first > b.first; });

    // Update the elite list
    elite.clear();
    for (const auto& pair : eliteWithScores) {
        elite.push_back(pair.second);
    }

    // Extract non-elite chromosomes
    for (int i = 0; i < sols.size() - pElite - pMutants; ++i) {
        nonElite.push_back(*it);
        ++it;
    }

    // Generate mutants if pMutants > 0
    if (pMutants > 0) {
        for (int j = 0; j < pMutants; ++j) {
            std::vector<double> chromosome(m);
            for (int k = 0; k < m; ++k) {
                chromosome[k] = static_cast<double>(std::rand()) / RAND_MAX;
            }
            nonElite.push_back(chromosome);
        }
    }

    sols.clear(); // Clear sols after processing
}

std::vector<double> biasedCrossover(
    const std::vector<double>& eliteParent,
    const std::vector<double>& nonEliteParent,
    double bias
) {
    // Validación de tamaños
    if (eliteParent.size() != nonEliteParent.size()) {
        throw std::invalid_argument("Los padres deben tener el mismo tamaño.");
    }

    std::vector<double> offspring(eliteParent.size());

    // Generador aleatorio moderno
    std::random_device rd;
    std::mt19937 gen(rd()); // Motor Mersenne Twister
    std::uniform_real_distribution<> dis(0.0, 1.0); // Distribución uniforme [0, 1)

    for (size_t i = 0; i < eliteParent.size(); ++i) {
        double prob = dis(gen); // Generar un número aleatorio entre 0 y 1

        // Seleccionar gen del padre élite o no élite
        if (prob < bias) {
            offspring[i] = eliteParent[i];
        } else {
            offspring[i] = nonEliteParent[i];
        }
    }

    return offspring;
}


void newPobl(
    double bias, int pMutants,
    std::list<std::vector<double>>& sols,
    std::list<std::vector<double>>& elite,
    std::list<std::vector<double>>& nonElite
) {
    // Validar entradas
    if (bias < 0.0 || bias > 1.0) {
        throw std::invalid_argument("El parámetro bias debe estar entre 0 y 1.");
    }
    if (elite.empty() || nonElite.empty()) {
        throw std::invalid_argument("Las listas elite y nonElite no deben estar vacías.");
    }

    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distElite(0, elite.size() - 1);
    std::uniform_int_distribution<> distNonElite(0, nonElite.size() - 1);

    // Agregar soluciones élite directamente
    for (const auto& ind : elite) {
        sols.push_back(ind);
    }

    // Generar descendencia para los no élite
    auto itElite = elite.begin();
    auto itNonElite = nonElite.begin();

    for (size_t i = 0; i < nonElite.size() - pMutants; ++i) {
        // Seleccionar padres aleatorios
        std::advance(itElite, distElite(gen));
        std::advance(itNonElite, distNonElite(gen));

        const std::vector<double>& parent1 = *itElite;
        const std::vector<double>& parent2 = *itNonElite;

        // Generar descendencia usando biasedCrossover
        sols.push_back(biasedCrossover(parent1, parent2, bias));

        // Reiniciar iteradores
        itElite = elite.begin();
        itNonElite = nonElite.begin();
    }
}

#endif

