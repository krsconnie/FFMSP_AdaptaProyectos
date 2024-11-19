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

// Mapea un valor [0, 1) a un carácter ('A', 'C', 'T', 'G') basado en rangos específicos.
char mapKeyToChar(double key) { 
    if (key < 0.25) return 'A';
    else if (key < 0.5) return 'C';
    else if (key < 0.75) return 'T';
    else return 'G';
}

// Decodifica un cromosoma (vector de valores [0, 1)) a una cadena de caracteres ('A', 'C', 'T', 'G').
std::string decodeChromosome(const std::vector<double>& chromosome) {
    std::string decoded;
    for (double key : chromosome) {
        decoded.push_back(mapKeyToChar(key));
    }
    return decoded;
}

// Codifica una cadena de caracteres ('A', 'C', 'T', 'G') a un vector de valores aleatorios en subrangos específicos.
std::vector<double> encoder(const std::string& input) {
    std::vector<double> encrypted;
    mt19937 generator(static_cast<unsigned>(time(nullptr))); // Generador aleatorio

    for (char ch : input) {
        if (ch == 'A') {
            uniform_real_distribution<double> distA(0.0, 0.25);
            encrypted.push_back(distA(generator));
        } else if (ch == 'C') {
            uniform_real_distribution<double> distC(0.26, 0.50);
            encrypted.push_back(distC(generator));
        } else if (ch == 'T') {
            uniform_real_distribution<double> distT(0.51, 0.75);
            encrypted.push_back(distT(generator));
        } else if (ch == 'G') {
            uniform_real_distribution<double> distG(0.76, 1.0);
            encrypted.push_back(distG(generator));
        } else {
            std::cout << "Carácter inválido.\n";
            return {};
        }
    }
    return encrypted;
}

// Genera una población inicial de soluciones aleatorias.
// p: Número de soluciones a generar.
// m: Longitud de cada solución (cromosoma).
void createPSol(int p, int m, std::list<std::vector<double>>& Pobl) { 
    std::srand(std::time(0)); // Semilla aleatoria
    Pobl.clear();

    for (int i = 0; i < p; ++i) {
        std::vector<double> chromosome(m);
        for (int j = 0; j < m; ++j) {
            chromosome[j] = static_cast<double>(std::rand()) / RAND_MAX;
        }
        Pobl.push_back(chromosome);
    }
}

// Decodifica una lista de cromosomas en una lista de soluciones (cadenas de caracteres).
void decodedList(std::list<std::vector<double>>& chromosomes, std::list<std::string>& sols) {
    for (const auto& chromosome : chromosomes) {
        sols.push_back(decodeChromosome(chromosome));
    }
    chromosomes.clear(); // Limpia la lista para reutilizar.
}

// Codifica una lista de soluciones en una lista de cromosomas.
void codedList(std::list<std::vector<double>>& chromosomes, std::list<std::string>& sols) {
    for (const auto& sol : sols) {
        chromosomes.push_back(encoder(sol));
    }
}

// Calcula las calidades de un conjunto de soluciones.
// dHam: Distancia de Hamming.
// quality: Vector donde se almacenarán las calidades.
// list: Conjunto de referencias para calcular calidad.
// sols: Soluciones a evaluar.
void calculateQuality(int dHam, std::vector<int>& quality, 
                      const std::list<std::string>& list, const std::list<std::string>& sols) { 
    for (const auto& sol : sols) {
        int qualitySol = calidad(dHam, list, sol);
        quality.push_back(qualitySol);
    }
}

// Comprueba si alguna calidad supera el umbral definido.
bool stoppinRule(std::vector<int>& quality, int thresholdDiference) {
    for (auto& q : quality) {
        if (q >= thresholdDiference) {
            return true;
        }
    }
    return false;
}

// Ordena soluciones por calidad en orden descendente.
void preselection(std::vector<int>& quality, std::list<std::string>& sols) {
    std::list<std::string> sortedsols;
    std::vector<int> numeros = quality;

    for (int i = 0; i < sols.size(); ++i) {
        auto it = std::max_element(numeros.begin(), numeros.end());
        int posicion = std::distance(numeros.begin(), it);
        auto solIt = sols.begin();
        std::advance(solIt, posicion);

        sortedsols.push_back(*solIt);
        numeros[posicion] = -1; // Evitar duplicados.
    }

    quality.clear();
    sols.swap(sortedsols);
}

// Divide la población en élite, no élite, y mutantes.
void sortPobl(int gen, int pElite, int pMutants, std::list<std::vector<double>>& elite, 
              std::list<std::vector<double>>& nonElite, std::list<std::string>& sols) { 
    std::srand(std::time(0)); // Semilla
    gen++;
    auto it = sols.begin();

    for (int i = 0; i < pElite; ++i) {
        elite.push_back(*it);
        ++it;
    }

    for (int i = pElite; i < sols.size() - pMutants; ++i) {
        nonElite.push_back(*it);
        ++it;
    }

    for (int j = 0; j < pMutants; ++j) {
        std::vector<double> chromosome(elite.front().size());
        for (auto& gene : chromosome) {
            gene = static_cast<double>(std::rand()) / RAND_MAX;
        }
        nonElite.push_back(chromosome);
    }

    sols.clear();
}

// Realiza un cruce sesgado entre dos cromosomas.
std::vector<double> biasedCrossover(const std::vector<double>& eliteParent, 
                                    const std::vector<double>& nonEliteParent, 
                                    double bias) {
    std::vector<double> offspring(eliteParent.size());
    std::srand(std::time(0));

    for (size_t i = 0; i < eliteParent.size(); ++i) {
        double prob = static_cast<double>(std::rand()) / RAND_MAX;
        offspring[i] = (prob < bias) ? eliteParent[i] : nonEliteParent[i];
    }
    return offspring;
}

// Genera una nueva población cruzando soluciones élite y no élite.
void newPobl(int bias, int pMutants, std::list<std::string>& sols,
             std::list<std::vector<double>>& elite, std::list<std::vector<double>>& nonElite) {
    std::srand(std::time(0));

    for (const auto& eliteSol : elite) {
        sols.push_back(eliteSol);
    }

    for (size_t i = 0; i < nonElite.size() - pMutants; ++i) {
        auto itElite = elite.begin();
        auto itNonElite = nonElite.begin();

        std::advance(itElite, rand() % elite.size());
        std::advance(itNonElite, rand() % nonElite.size());

        sols.push_back(biasedCrossover(*itElite, *itNonElite, bias));
    }
}

#endif
