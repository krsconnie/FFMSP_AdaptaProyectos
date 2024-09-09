#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstring>
#include <chrono>
#include <algorithm>
#include "getInput.h"

int main(int argc, char const *argv[]){
    
    float umbral = atof(argv[4]); 

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

   
    // Iterador para recorrer los caracteres del string
    for (int i = 0; i < m; i++){
        
        // Iterador para recorrer la lista de strings
        for(auto it = lista.begin(); it != lista.end(); it++){
        
            char a = (*it).at(i);

            // Switch case para contar las ocurrencias de la n posicion de los strings
            switch(a){
                case 'A':
                    contador[0]++; 
                    break;
                case 'C':
                    contador[1]++;
                    break;
                case 'G':
                    contador[2]++; 
                    break;
                case 'T':
                    contador[3]++; 
                    break;
                default:
                    break;
            }
        }

        // Comparador de la letra con la menor ocurrencia para agregarla al string solución
        int minIndex = std::distance(std::begin(contador), std::min_element(std::begin(contador), std::end(contador)));
        
        switch(minIndex){
            case 0:
                solucion.push_back('A');
                std::cout << "Se agrega A" << std::endl;
                break;
            case 1:
                solucion.push_back('C');
                std::cout << "Se agrega C" << std::endl;
                break;
            case 2:
                solucion.push_back('G');
                std::cout << "Se agrega G" << std::endl;
                break;
            case 3:
                solucion.push_back('T');
                std::cout << "Se agrega T" << std::endl;
                break;
            default: 
                break;
        }    

        // Reinicio del contador
        memset(contador, 0, sizeof(contador));

        if (i >= (dHam - 1)){
            // Utiliza un iterador seguro para borrar elementos mientras iteras
            for(auto it2 = lista.begin(); it2 != lista.end();){
                
                int condicion = 0;

                for (int j = 0; j <= i; j++){
                    char a = (*it2).at(j);
                    if (a == solucion[j]){
                        condicion++;
                    }
                }
            
                if(condicion == dHam){
                    conjuntoSolucion.push_back(*it2);
                    std::cout << "Se agrega línea al conjunto solución" << std::endl;
                    it2 = lista.erase(it2); // Elimina y actualiza el iterador
                    std::cout << "Se borra línea del conjunto original" << std::endl;
                } else {
                    ++it2; // Avanza el iterador si no se elimina
                }
            }
        }
    }

    std::cout << "Línea solución encontrada: " << solucion;
    std::cout << "\nDistancia Hamming designada: " << dHam << "\nCalidad de la solución: " << conjuntoSolucion.size() << std::endl;

    return 0;
}
