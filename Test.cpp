#include "greedy.h"
#include "utilidades.h"
#include "getInput.h"

int main(int argc, char const *argv[]) {

     srand(time(0));

    // Verificar el número de argumentos
    if (argc != 6 || std::string(argv[1]) != "-i" || std::string(argv[3]) != "-th") {
        std::cerr << "Uso: " << argv[0] << " -i <instancia_problema> -th threshold < 0 / 1 > \n"
                  << " 0 = Greedy Determinista \n 0.numero = Porcentaje randomizado para Greedy aleatorizado" << std::endl;
        return EXIT_FAILURE;
    }

    // Convertir y validar los valores de umbral y mode
    float umbral = atof(argv[4]); // Umbral para la distancia de Hamming
    float mode = atof(argv[5]);   // Porcentaje de randomización

    // Verificar que el umbral esté entre 0 y 1 (exclusivo), y el modo entre 0 y 1 (inclusivo)
    if (umbral <= 0 || umbral >= 1 || mode < 0 || mode > 1) {
        std::cerr << "Error: El umbral debe estar entre 0 y 1 (exclusivo), y el mode debe estar entre 0 y 1 (inclusivo)." << std::endl;
        return EXIT_FAILURE;
    }

    std::string nombreArchivo = argv[2];
    std::list<std::string> lista;

    getStrings(nombreArchivo, lista); // Llama a la función de la librería getInput.h

    int n = std::stoi(nombreArchivo.substr(0,3)); // Cantidad original de strings 
    int m = std::stoi(nombreArchivo.substr(4,3)); // Largo del string 
    std::string solucion = greedy(lista,m,umbral,mode); // String solución 

    int dHam = m*umbral;

    std::list<std::string> aux;
    getStrings(nombreArchivo,aux);
    int metrica = calidad(dHam,aux,solucion);
    std::cout << metrica << " de la sol: " << solucion;

}