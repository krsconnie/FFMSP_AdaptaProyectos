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
#include <iomanip> // Para imprimir tiempos con precisión

// Evaluar si un carácter es válido basado en el umbral
bool evaluate(const std::list<std::string> &lista, const std::string &solucion, char x, int dHam)
{
    std::string aux = solucion + x; // Construir la solución parcial con el nuevo carácter
    for (const auto &cadena : lista)
    {
        int dif = 0;
        // Calcular la distancia de Hamming entre la solución parcial y cada cadena en la lista
        for (int j = 0; j < aux.size(); j++)
        {
            if (aux[j] != cadena[j])
            {
                dif++;
            }
        }
        // Si la distancia de Hamming es mayor o igual a dHam, es válido
        if (dif >= dHam)
        {
            return true;
        }
    }
    return false; // Si no se cumple, el carácter no es válido
}

// Función de búsqueda local para mejorar la solución
void busquedaLocal(std::string &solucion, const std::list<std::string> &lista, int dHam, int m)
{
    bool hayMejora = true;
    std::vector<char> bases = {'A', 'C', 'G', 'T'};
    std::list<std::string> conjuntoSolucion;

    while (hayMejora)
    {
        hayMejora = false;

        // Para cada posición en la solución
        for (int i = 0; i < m; i++)
        {
            char originalChar = solucion[i]; // Guardar el carácter original

            // Probar cambiar por cada base posible ('A', 'C', 'G', 'T')
            for (char base : bases)
            {
                if (base == originalChar)
                    continue; // Si es el mismo carácter, no lo cambies

                solucion[i] = base; // Modificar la solución

                // Evaluar la nueva solución
                conjuntoSolucion.clear();
                for (const auto &cadena : lista)
                {
                    int condicion = 0;
                    for (int j = 0; j <= i; j++)
                    {
                        if (cadena[j] != solucion[j])
                        {
                            condicion++;
                        }
                    }

                    if (condicion >= dHam)
                    {
                        conjuntoSolucion.push_back(cadena); // Agregar las que cumplen con dHam
                    }
                }

                // Si la nueva solución mejora, mantener el cambio
                if (conjuntoSolucion.size() > lista.size() / 2)
                { // Mejora local: más de la mitad cumple
                    hayMejora = true;
                    break;
                }
                else
                {
                    // Revertir el cambio si no mejora
                    solucion[i] = originalChar;
                }
            }

            if (hayMejora)
            {
                break; // Salir del ciclo si se encontró una mejora
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    float umbral = atof(argv[4]);     // Umbral para la distancia de Hamming
    float mode = atof(argv[5]);       // Porcentaje de randomizado
    int maxTime = std::stoi(argv[6]); // Tiempo máximo en segundos

    if (argc != 7 || std::string(argv[1]) != "-i" || std::string(argv[3]) != "-th" || (umbral <= 1 || umbral >= 0) || (mode <= 1 && mode >= 0))
    {
        std::cerr << "Uso: " << argv[0] << " -i <instancia_problema> -th threshold < 0 / 1 > \n 0 = Greedy Determinista \n 0.numero = Porcentaje randomizado para Greedy aleatorizado" << std::endl;
        std::cerr << "Adicionalmente: <tiempo_en_segundos> como tiempo máximo de ejecución." << std::endl;
        return EXIT_FAILURE;
    }

    std::string nombreArchivo = argv[2];
    std::list<std::string> lista;
    getStrings(nombreArchivo, lista); // Llama a la función de la librería getInput.h

    int n = std::stoi(nombreArchivo.substr(0, 3)); // Cantidad original de strings
    int m = std::stoi(nombreArchivo.substr(4, 3)); // Largo del string
    int dHam = m * umbral;                         // Distancia de Hamming

    std::string bestSolucion = ""; // Mejor solución
    int bestCalidad = 0;           // Calidad de la mejor solución encontrada
    double bestTiempo = 0;         // Tiempo en que se encontró la mejor solución

    auto startGeneral = std::chrono::high_resolution_clock::now();
    bool tiempoMaxAlcanzado = false;

    while (!tiempoMaxAlcanzado)
    {
        std::string solucion = ""; // Solución para esta iteración
        std::list<std::string> conjuntoSolucion;
        std::list<std::string> listaTemp = lista; // Copia de la lista original

        int contador[4] = {0, 0, 0, 0}; // Arreglo contador inicializado en 0
        double tiempo = 0;

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<char> bases = {'A', 'C', 'G', 'T'}; // Posibles caracteres para elegir
        float dado = 0;

        // *** Fase de Construcción ***
        for (int i = 0; i < m; i++)
        {
            dado = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            if (dado > mode)
            {
                for (auto it = listaTemp.begin(); it != listaTemp.end(); it++)
                {
                    char a = (*it).at(i);
                    switch (a)
                    {
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

                std::map<char, bool> validChars;
                for (char base : bases)
                {
                    validChars[base] = evaluate(listaTemp, solucion, base, dHam);
                }

                std::vector<char> candidatos;
                for (const auto &kv : validChars)
                {
                    if (kv.second)
                    {
                        candidatos.push_back(kv.first);
                    }
                }

                char selectedChar;
                if (!candidatos.empty())
                {
                    selectedChar = candidatos[rand() % candidatos.size()];
                }
                else
                {
                    int minIndex = std::distance(std::begin(contador), std::min_element(std::begin(contador), std::end(contador)));
                    switch (minIndex)
                    {
                    case 0:
                        selectedChar = 'A';
                        break;
                    case 1:
                        selectedChar = 'C';
                        break;
                    case 2:
                        selectedChar = 'G';
                        break;
                    case 3:
                        selectedChar = 'T';
                        break;
                    default:
                        break;
                    }
                }

                solucion.push_back(selectedChar);
                memset(contador, 0, sizeof(contador));

                if (i >= (dHam - 1))
                {
                    for (auto it2 = listaTemp.begin(); it2 != listaTemp.end();)
                    {
                        int condicion = 0;
                        for (int j = 0; j <= i; j++)
                        {
                            if ((*it2)[j] != solucion[j])
                            {
                                condicion++;
                            }
                        }

                        if (condicion >= dHam)
                        {
                            conjuntoSolucion.push_back(*it2);
                            it2 = listaTemp.erase(it2);
                        }
                        else
                        {
                            ++it2;
                        }
                    }
                }
            }
            else if (mode >= dado)
            {
                int generadorAleatorio = rand() % 4;
                solucion.push_back(bases[generadorAleatorio]);
            }
        }

        // *** Fase de Mejora Local ***
        busquedaLocal(solucion, lista, dHam, m);

        auto end = std::chrono::high_resolution_clock::now();
        tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        tiempo *= (1e-9);

        // Si la nueva solución es mejor, actualiza la mejor solución
        if (conjuntoSolucion.size() > bestCalidad)
        {
            bestSolucion = solucion;
            bestCalidad = conjuntoSolucion.size();
            bestTiempo = tiempo; // Tiempo de la mejor solución

            // Mostrar la calidad y el tiempo de la nueva mejor solución
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - startGeneral).count();
            std::cout << "Nueva mejor solución: Calidad = " << bestCalidad << ", Tiempo = " << elapsed * 1e-9 << " segundos" << std::endl;
        }

        // Verificar si el tiempo máximo ha sido alcanzado
        auto totalTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startGeneral).count();
        if (totalTime >= maxTime)
        {
            tiempoMaxAlcanzado = true;
        }
    }

    // Mostrar la mejor solución encontrada al final
    std::cout << "Mejor solución encontrada: Calidad = " << bestCalidad << ", Tiempo cuando se encontró = " << bestTiempo << " segundos" << std::endl;

    return 0;
}
