#ifndef utilidades_H
#define utilidades_H


#include <string>
#include <vector>
#include <list>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>

/**
 hammingDist devuelve el valor de la distancia de Hamming entre 2 cadenas dadas
**/

int hammingDist(const std::string &cadena, const std::string &solucion){
    int distancia = 0;
    for(int i = 0; i < solucion.size(); i++){
        if(cadena[i] != solucion[i]){
            distancia++;
        }
    }
    return distancia;
}

int calidad(int dHam,const std::list<std::string> &lista, const std::string &solucion){
    int calidad = 0;
    for(const auto& cadena : lista){	//THE ERROR IS HERE! "lista" is always of max size 100, so it can never grow past it!
		//std::cout<<"Size of lista: "<<lista.size()<<" || Length of cadena: "<<cadena.size()<<std::endl;
        int dif = hammingDist(cadena, solucion);
        if(dif >= dHam){
            calidad++;
        }
    }
	//std::cout<<"calidad: "<<calidad<<std::endl;
    return calidad;
}

//Se cumple la condicion si al menos con uno de los strings de la lista se cumple la dHam?????? *Preguntar
bool evaluateWithHamming(const std::list<std::string> &lista, const std::string &solucion, char c, int dHam){
	std::string aux = solucion + c;
	for(const auto& cadena : lista){
		int dif = hammingDist(cadena,solucion);
		if(dif >= dHam){
			return true;
		}
	}
	return false;
}
 /**
  menosFrecuente evalua todos los string en la posicion
  seleccionada y devuelve el string menos frecuente en 
  dicha posicion
  **/
char menosFrecuente(const std::list<std::string> &lista, int pos){

	int contador[4] = {0,0,0,0};

	for(auto it = lista.begin(); it != lista.end(); it++){

		char a = (*it).at(pos);

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

	int minIndex = std::distance(std::begin(contador),std::min_element(std::begin(contador), std::end(contador)));

	char menosFrec;

		switch(minIndex){

		case 0:
			menosFrec = 'A';
			break;		
	
		case 1:
			menosFrec = 'C';
			break;

		case 2:
			menosFrec = 'G';
			break;

		case 3:
			menosFrec = 'T';
			break;

		default:
			break;
		}

	return menosFrec;
}

//Devuelve un char random de un vector con el alfabeto a usar
char randomChar(std::vector<char> v){

	srand(time(0));

	int pos = rand() % v.size();
	char c = v[pos];

	return c;
}
/** 

Modifica un vector dado (vacio)(al utilizarlo hay que incluir un manejo de excepcion) 
y lo devuelve con las bases menos la que ya esta siendo usada

**/

void otrosChar(char seleccionado, std::vector<char>& otrosChar) {
   
    switch(seleccionado) {
        case 'A':
            otrosChar = {'C', 'G', 'T'};
            break;
        case 'C':
            otrosChar = {'A', 'G', 'T'};
            break;
        case 'G':
            otrosChar = {'A', 'C', 'T'};
            break;
        case 'T':
            otrosChar = {'A', 'C', 'G'};
            break;
        default:
            otrosChar.clear(); // En caso de error, limpiar el vector
            break;
    }
}


#endif 
