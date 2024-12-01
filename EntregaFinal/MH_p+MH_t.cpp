#ifndef GRASP_H
#define GRASP_H

#include "utilidades.h"
#include "AG.cpp"
#include "localSearch.h"
#include <chrono>
#include <iostream>

//IMPLEMENTACIÓN MH_p+MH_t//
void mhp_mht(std::list<std::string>& lista, int largo, float umbral, int maxTime, int populationSize) {
    auto start = std::chrono::steady_clock::now();
    int dHam = largo * umbral;
    float probRandom = 0;

    std::list<std::string> aux = lista;
    std::vector<std::pair<std::string, int>> solucionesElite;
    int best_metric = -1;
    double best_time = 0;

    while (true) {
        auto current = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = current - start;
        if (elapsed_seconds.count() >= maxTime) {
            break;
        }

        std::vector<std::string> solucionesIniciales = geneticAlgorithm(aux, largo, populationSize, probRandom, dHam);  //The problem's here!!!
        if (solucionesIniciales.empty()) {
            std::cerr << "Error: geneticAlgorithm returned an empty vector!" << std::endl;
         return;
        }
        
        std::string solucion;
        int calidad_solucion;
        for(int i=0; i<solucionesIniciales.size(); i++){
            solucion = localSearch(lista, solucionesIniciales[i], dHam);                                //Local Search es aplicado a todas las soluciones iniciales y luego se elige la mejor de estas.
            calidad_solucion = calidad(dHam, lista, solucion);
            solucionesElite.emplace_back(solucion, calidad_solucion);
        }

        std::sort(solucionesElite.begin(), solucionesElite.end(), compareFitnessScores);

        // Mostrar la mejor solución al final
        std::cout << "Mejor solución final: Calidad = " << solucionesElite[0].second << ", Tiempo cuando se encontró = " << best_time << " segundos" << std::endl;
    }
}

int main(int argc, char const *argv[]) {
    srand(time(0));

    if (argc != 7 || std::string(argv[1]) != "-i" || std::string(argv[3]) != "-th") {
        std::cerr << "Uso: " << argv[0] << " -i <instancia_problema> -th threshold <[0,...,1]> <tiempo Máximo> <tamaño de población inicial>\n" << std::endl;
        return EXIT_FAILURE;
    }

    float umbral = atof(argv[4]); //Umbral para la distancia de Hamming
    int maxTime = atoi(argv[5]);  //Tiempo máximo de ejecución
    int populationSize = atoi(argv[6]); //Tamaño de la población inicial

    if (umbral <= 0 || umbral >= 1 || maxTime <= 0) {
        std::cerr << "Error: El umbral debe estar entre 0 y 1 (exclusivo), el mode entre 0 y 1 (inclusivo) y el tiempo debe ser positivo" << std::endl;
        return EXIT_FAILURE;
    }

    std::string nombreArchivo = argv[2];
    std::list<std::string> lista;
    getStrings(nombreArchivo, lista);                       //Obtener los strings de entrada

    int m = std::stoi(nombreArchivo.substr(4, 3));          //Largo del string
    mhp_mht(lista, m, umbral, maxTime, populationSize);     //Ejecutar MH_p+MH_t; EDITAR PARAMETROS.

    return 0;
}

#endif