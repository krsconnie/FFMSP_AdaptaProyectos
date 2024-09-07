#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
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

    getStrings(nombreArchivo,lista);

    int n = std::stoi(nombreArchivo.substr(0,3)); // Cantidad original de strings
    int m = std::stoi(nombreArchivo.substr(4,3)); // Largo del string 
    std::string solucion[m]; // String solucion 


    std::list<std::string> conjuntoSolucion; 

    // Referencia en contador = A(0), C(1), G(2), T(3)
    int contador[4] = {0,0,0,0}; //Arreglo contador inicializado en 0

    

    std::cout << "Probando... lista con   " << n << "  strings...  de   " << m << "characters cada una..." << std::endl;
    std::cout << "Archivo:" << nombreArchivo << "....."  << std::endl;

    std::list<std::string>::iterator it = lista.begin();
    // Iterador para recorrer los caracteres del string
     for (int i = 0; i < m; i++){
        // Iterador para recorrer la lista de strings
        for( std::list<std::string>::iterator it = lista.begin(); it != lista.end();it++){
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
        // Comparador de la letra con la menor ocurrencia para agregarla al string solucion
        }
    }
   
    return 0;
};