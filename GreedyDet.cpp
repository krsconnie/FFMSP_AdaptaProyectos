#include "getInput.h"
#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

// Evaluar si un carácter es válido basado en el umbral 
bool evaluate(const std::list<std::string> &lista, const std::string &solucion, char x, int dHam) {
    std::string aux = solucion + x; // Construir la solución parcial con el nuevo carácter
    for (const auto& cadena : lista) {
        int dif = 0;
        // Calcular la distancia de Hamming entre la solución parcial y cada cadena en la lista
        for (int j = 0; j < aux.size(); j++) {
            if (aux[j] != cadena[j]) {
                dif++;
            }
        }
        // Si la distancia de Hamming es mayor o igual a dHam, es válido
        if (dif >= dHam) {
            return true;
        }
    }
    return false; // Si no se cumple, el carácter no es válido
}

int main(int argc, char const *argv[]) {

    float umbral = atof(argv[4]); // Umbral para la distancia de Hamming

    if(argc != 5 || std::string(argv[1]) != "-i" || std::string(argv[3]) != "-th" || (umbral > 1 || umbral < 0)){
        std::cerr << "Uso: " << argv[0] << " -i <instancia_problema> -th threshold" << std::endl;
        return EXIT_FAILURE;
    }

    std::string nombreArchivo = argv[2];
    std::list<std::string> lista;

    getStrings(nombreArchivo, lista); // Llama a la función de la librería getInput.h

    int n = std::stoi(nombreArchivo.substr(0,3)); // Cantidad original de strings 
    int m = std::stoi(nombreArchivo.substr(4,3)); // Largo del string 
    std::string solucion = ""; // String solución 

    int dHam = m * umbral; // Distancia de Hamming

    std::list<std::string> conjuntoSolucion; 

    // Referencia en contador = A(0), C(1), G(2), T(3)
    int contador[4] = {0,0,0,0}; // Arreglo contador inicializado en 0

    double tiempo = 0;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<char> bases = {'A', 'C', 'G', 'T'}; // Posibles caracteres para elegir

    for (int i = 0; i < m; i++){
        for(auto it = lista.begin(); it != lista.end(); it++){
            char a = (*it).at(i);
            switch(a){
                case 'A': contador[0]++; break;
                case 'C': contador[1]++; break;
                case 'G': contador[2]++; break;
                case 'T': contador[3]++; break;
                default: break;
            }
        }

        // Evaluar cada carácter ('A', 'C', 'G', 'T') para ver si es válido
        std::map<char, bool> validChars;
        for (char base : bases) {
            validChars[base] = evaluate(lista, solucion, base, dHam); // Verifica si agregar el carácter es válido
        }

        // Crear un vector de caracteres válidos
        std::vector<char> candidatos;
        for (const auto& kv : validChars) {
            if (kv.second) {
                candidatos.push_back(kv.first); // Agregar caracteres válidos a la lista de candidatos
            }
        }

        // Seleccionar carácter según la frecuencia o al azar si hay varios válidos
        char selectedChar;
        if (!candidatos.empty()) {
            selectedChar = candidatos[rand() % candidatos.size()]; // Selección aleatoria de los válidos
        } else {
            // Si no hay válidos, elige el de menor frecuencia
            int minIndex = std::distance(std::begin(contador), std::min_element(std::begin(contador), std::end(contador)));
            switch(minIndex){
                case 0: selectedChar = 'A'; break;
                case 1: selectedChar = 'C'; break;
                case 2: selectedChar = 'G'; break;
                case 3: selectedChar = 'T'; break;
                default: break;
            }
        }

        solucion.push_back(selectedChar); // Agregar el carácter seleccionado a la solución

        // Reinicio del contador
        memset(contador, 0, sizeof(contador));

        // Eliminar las cadenas que ya no cumplen con la distancia de Hamming
        if (i >= (dHam - 1)){
            for(auto it2 = lista.begin(); it2 != lista.end();){
                int condicion = 0;
                for (int j = 0; j <= i; j++){
                    char a = (*it2).at(j);
                    if (a == solucion[j]){
                        condicion++;
                    }
                }
                if(condicion >= dHam){
                    conjuntoSolucion.push_back(*it2);
                    it2 = lista.erase(it2);
                } else {
                    ++it2;
                }
                condicion = 0;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    tiempo *= (1e-9);

    std::cout << "Tamaño de la solución: " << solucion.size() << " // Línea solución encontrada: " << solucion;
    std::cout << "\nDistancia Hamming designada: " << dHam << "\nCalidad de la solución: " << conjuntoSolucion.size() << "\nConjunto original queda con: " << lista.size()  << std::endl;
    std::cout << "Tiempo usado: " << tiempo << " segundos" << std::endl;
    
    return 0;
}
