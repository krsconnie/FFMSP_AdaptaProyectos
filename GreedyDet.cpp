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

    if(argc != 5 or argv[1] == "-i" or argv[3] == "-th" or (umbral > 1 and umbral < 0)){
         std::cerr << "Uso: " << argv[0] << " -i <instancia_problema> -th threshold" << std::endl;
        return EXIT_FAILURE;
    }

    
    std::string nombreArchivo = argv[2];
    std::list<std::string> lista;

    getStrings(nombreArchivo,lista); // Llama a la funcion de la librería getInput.h

    int n = std::stoi(nombreArchivo.substr(0,3)); // Cantidad original de strings 
    int m = std::stoi(nombreArchivo.substr(4,3)); // Largo del string 
    char solucion[m]; // String solucion 

    int dHam = n*umbral; // Distancia de Hamming

    std::list<std::string> conjuntoSolucion; 

    // Referencia en contador = A(0), C(1), G(2), T(3)
    int contador[4] = {0,0,0,0}; //Arreglo contador inicializado en 0

    
    // Flags
    std::cout << "Probando... lista con   " << n << "  strings...  de   " << m << "  characters cada una..." << std::endl;
    std::cout << " Archivo: " << nombreArchivo << "....."  << std::endl;

   
    // Iterador para recorrer los caracteres del string
     for (int i = 0; i < m; i++){
        
        // Iterador para recorrer la lista de strings
        for(std::list<std::string>::iterator it = lista.begin(); it != lista.end();it++){
        
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

        // Comparador de la letra con la menor ocurrencia para agregarla al string solucion
        int minIndex = std::distance(std::begin(contador), std::min_element(std::begin(contador), std::end(contador)));
        // Flag
        std::cout << minIndex << std::endl;
            
            switch(minIndex){
                
                case 0:
                    solucion[i]='A';
                    break;

                case 1:
                    solucion[i]='C';
                    break;

                case 2:
                    solucion[i]='G';
                    break;

                case 3:
                    solucion[i]='T';
                    break;

                default: 
                    break;
        }    

        // Reinicio del contador
        memset(contador, 0, sizeof(contador));

        /* 
        Una vez se itera por un número igual o mayor al umbral
        se compara el string "solution" con los strings de la lista.
        Si cumplen el requisito salen de la lista y se agregan al conjunto solucion.
        */
        if( i >= (dHam - 1)){
            for(std::list<std::string>::iterator it2 = lista.begin(); it2 != lista.end();it2++){
                
                 // Cuenta la distancia de Hamming entre el string de la lista y el string solution
                 int condicion = 0; 

                for (int j = 0; j < dHam ; j++){

                    char a = (*it2).at(j);

                    if (a == solucion[j]){
                        condicion++;
                    }
                 }
            // Si se cumple la condición agregamos el string de la lista
            // al conjunto solucion y despues lo borramos de la lista original.      
            if(condicion == dHam){

            }
            }
        }
    }


   
    return 0;
};