#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "utilidades.h"

std::string localSearch(const std::list<std::string>& lista,const std::string solucion, int dHam){

std::string aux = solucion; // copia

for(int i = 0; i < aux.size(); ++i){
	
	std::vector<char> otrasOpciones;

	//Las bases a probar
	
	otrosChar(aux[i], otrasOpciones);

		for(char c : otrasOpciones){
			
			std::string nueva_solucion{aux};
			nueva_solucion[i] = c;

			int calidadSolNueva = calidad(dHam,lista,nueva_solucion);

			int calidadSolAux = calidad(dHam,lista,aux);

			if(calidadSolNueva >= calidadSolAux){

				aux = nueva_solucion;
			}
		}
	}

	return aux;
}



#endif
