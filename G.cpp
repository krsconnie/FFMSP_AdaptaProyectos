#ifndef GRASP_H
#define GRASP_H

#include "utilidades.h"
#include "greedy.h"
#include "localSearch.h"
#include <chrono>
#include <iostream>
// Función métrica adaptada
int calcularMetrica(const std::list<std::string>& lista, const std::string& solucion, int dHam) {
    return calidad(dHam, lista, solucion);
}

void grasp(std::list<std::string>& lista, int largo, float umbral, float probRandom, int maxTime) {
    auto start = std::chrono::steady_clock::now();
    int dHam = largo * umbral;

    std::list<std::string> aux = lista;
    std::string best_solution;
    int best_metric = -1;
    double best_time = 0;

    while (true) {
        auto current = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = current - start;
        if (elapsed_seconds.count() >= maxTime) {
            break;
        }

        // Generar solución inicial con Greedy aleatorizado
        std::string solucion = greedy(aux, largo, umbral, probRandom);

        // Búsqueda local para mejorar la solución
        solucion = localSearch(lista, solucion, dHam);

        // Evaluar la calidad de la nueva solución
        int calidad_solucion = calcularMetrica(lista, solucion, dHam);

        // Si la nueva solución es mejor, actualizar la mejor solución
        if (calidad_solucion > best_metric) {
            best_solution = solucion;
            best_metric = calidad_solucion;
            best_time = elapsed_seconds.count();

            // Mostrar la nueva mejor solución
            std::cout << "Nueva mejor solución: Calidad = " << best_metric
                      << ", Tiempo = " << best_time << " segundos" << std::endl;
        }
    }

    // Mostrar la mejor solución al final
    std::cout << "Mejor solución final: Calidad = " << best_metric
              << ", Tiempo cuando se encontró = " << best_time << " segundos" << std::endl;
}

int main(int argc, char const *argv[]) {
    srand(time(0));

    if (argc != 7 || std::string(argv[1]) != "-i" || std::string(argv[3]) != "-th") {
        std::cerr << "Uso: " << argv[0] << " -i <instancia_problema> -th threshold <[0,...,1]>  <tiempo Máximo>\n" << std::endl;
        return EXIT_FAILURE;
    }

    float umbral = atof(argv[4]); // Umbral para la distancia de Hamming
    float mode = atof(argv[5]);   // Porcentaje de randomización
    int maxTime = atoi(argv[6]);  // Tiempo máximo de ejecución

    if (umbral <= 0 || umbral >= 1 || mode < 0 || mode > 1 || maxTime <= 0) {
        std::cerr << "Error: El umbral debe estar entre 0 y 1 (exclusivo), el mode entre 0 y 1 (inclusivo) y el tiempo debe ser positivo" << std::endl;
        return EXIT_FAILURE;
    }

    std::string nombreArchivo = argv[2];
    std::list<std::string> lista;
    getStrings(nombreArchivo, lista);  // Obtener los strings de entrada

    int m = std::stoi(nombreArchivo.substr(4, 3));  // Largo del string
    grasp(lista, m, umbral, mode, maxTime);         // Ejecutar GRASP

    return 0;
}

#endif

