#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>

/*
getStrings abre el archivo en cuestión, copia cada línea del texto (hasta un salto de línea)
en una variable tipo string y la inserta en una lista de la STL (doblemente enlazada).
*/

void getStrings(const std::string& nombreArchivo, std::list<std::string>& lista) {
    std::ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        std::cerr << "Error al leer el archivo: " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {

        linea.erase(std::remove(linea.begin(), linea.end(),'\n'),linea.end());
        lista.push_back(linea);

    }
}
