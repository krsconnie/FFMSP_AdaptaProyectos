#ifndef GRASP_H
#define GRASP_H

#include "utilidades.h"
#include "AG.cpp"
#include "localSearch.h"
#include <chrono>
#include <iostream>

void sortSolucionesElite(std::vector<std::pair<std::string, int>>& solucionesElite) {
    std::sort(solucionesElite.begin(), solucionesElite.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });
}

//IMPLEMENTACIÓN MH_p+MH_t//
void mhp_mht(std::list<std::string>& lista, int largo, float umbral, int maxTime, float probRandom, int populationSize) {
    auto start = std::chrono::steady_clock::now();
    int dHam = largo * umbral;

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

        sortSolucionesElite(solucionesElite);

        std::vector<std::string> poblacionAG = geneticAlgorithm(aux, largo, populationSize, probRandom, dHam); 
        std::cout<<"Size Población AG: "<<poblacionAG.size()<<std::endl;     
        std::string solucion;
        int calidad_solucion;
        for(int i=0; i<poblacionAG.size(); i++){
            solucion = localSearch(lista, poblacionAG[i], dHam);    //Local Search is applied to all initial solutions and then the best one is chosen.
            calidad_solucion = calidad(dHam, lista, solucion);
            solucionesElite.emplace_back(solucion, calidad_solucion);
        }

        if (solucionesElite[0].second > best_metric){
            best_metric = solucionesElite[0].second;
            best_time = elapsed_seconds.count(); // Update time when the new best solution is found
        }

        std::cout << "Mejor solución final: Calidad = " << solucionesElite[0].second << ", Tiempo cuando se encontró = " << best_time << " segundos" << std::endl;
    }
}

int main(int argc, char const *argv[]) {
    srand(time(0));

    if (argc != 8 || std::string(argv[1]) != "-i" || std::string(argv[3]) != "-th") {
        std::cerr << "Uso: " << argv[0] << " -i <instancia_problema> -th threshold <[0,...,1]> <tiempo Máximo> <probabilidad de mutación> <tamaño de población inicial>\n" << std::endl;
        return EXIT_FAILURE;
    }

    float umbral = atof(argv[4]);       //Umbral para la distancia de Hamming
    int maxTime = atoi(argv[5]);        //Tiempo máximo de ejecución
    float probRandom = atof(argv[6]);
    int populationSize = atoi(argv[7]); //Tamaño de la población inicial

    if (umbral <= 0.0 || umbral >= 1.0 || probRandom <= 0.0 || probRandom >= 1.0 || maxTime <= 0) {
        std::cerr << "Error: El umbral debe estar entre 0 y 1 (exclusivo), el mode entre 0 y 1 (inclusivo), la probabilidad de mutación entre 0 y 1 (exclusivo) y el tiempo debe ser positivo" << std::endl;
        return EXIT_FAILURE;
    }

    std::string nombreArchivo = argv[2];
    std::list<std::string> lista;
    getStrings(nombreArchivo, lista);                       //Obtener los strings de entrada

    int m = std::stoi(nombreArchivo.substr(4, 3));          //Largo del string
    //std::cout<<m<<std::endl; //El largo del archivo ingresado por consola normalmente, es 300. ¿Por qué la calidad SIEMPRE da 100 y no mejora en cada generación?
    mhp_mht(lista, m, umbral, maxTime, probRandom, populationSize);     //Ejecutar MH_p+MH_t; EDITAR PARAMETROS.

    return 0;
}

#endif