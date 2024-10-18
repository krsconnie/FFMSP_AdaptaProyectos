#ifndef GREEDY_H
#define GREEDY_H

#include "getInput.h"
#include "utilidades.h"
#include <map>

std::string greedy(std::list<std::string> &lista, int largo, float umbral,float probRandom){
 
 srand(time(0));
 int dHam = largo * umbral;
 std::vector<char> v = {'A','C','G','T'};
 std::list<std::string> conjuntoSolucion; 
 std::string solucion;

 float dado = 0;
 
 for (int i = 0; i < largo; i++){
	
	dado = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
 	char selectedChar;

 	if(dado <= probRandom){
 	
 		selectedChar = randomChar(v);
 	
 	} else {

 		// Evaluar cada carácter ('A', 'C', 'G', 'T') para ver si es válido
            std::map<char, bool> validChars;
            
            for (char base : v) {
            
                validChars[base] = evaluateWithHamming(lista, solucion, base, dHam); // Verifica si agregar el carácter es válido
            }

            // Crear un vector de caracteres válidos
            std::vector<char> candidatos;
            for (const auto& kv : validChars) {
                
                if (kv.second) {
                    candidatos.push_back(kv.first); // Agregar caracteres válidos a la lista de candidatos
                }
            }

            // Seleccionar carácter según la frecuencia o al azar si hay varios válidos
            
            if (!candidatos.empty()) {
                selectedChar = candidatos[rand() % candidatos.size()]; // Selección aleatoria de los válidos
 			} else {
 				selectedChar = menosFrecuente(lista, i);
 			}
 		}

 		solucion.push_back(selectedChar);

 		if (i >= (dHam - 1)){

 			for(auto it2 = lista.begin(); it2 != lista.end();){
                    
                int condicion;
                hammingDist(*it2,solucion);


                if(condicion >= dHam){
                    
                	conjuntoSolucion.push_back(*it2);   
                	it2 = lista.erase(it2);
                    
                } else {
                	++it2;
                }  
            }
 		}
	}
	
	return solucion;
}

#endif