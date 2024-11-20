#include "utilidades.h"
#include "getInput.h"
#include "brkga.h"
#include <chrono>

int main(int argc, char const *argv[]) {

    srand(time(0));

    if (argc != 15 || 
        std::string(argv[1]) != "-i" || 
        std::string(argv[3]) != "-th" || 
        std::string(argv[5]) != "-t") {

        std::cerr << "Uso: " << argv[0] 
                  << " -i <instancia_problema> -th <umbral> -t <tiempo_max>\n";
        return EXIT_FAILURE;
    }

    float umbral = atof(argv[4]);
    int maxTime = atoi(argv[6]);
    int poblacion_inicial = 100;
    int poblacion_Elite = 15;
    int poblacion_Mutantes = 5 ;
    double bias = 0.5;

    if (umbral <= 0 || umbral >= 1 || maxTime <= 0) {
           
        std::cerr << "Error: El umbral debe estar entre 0 y 1 (exclusivo).\n"
                  << "El tiempo debe ser positivo.\n";
        return EXIT_FAILURE;
    }

    std::string nombreArchivo = argv[2];
    int m = std::stoi(nombreArchivo.substr(4, 3));

    std::list<std::string> lista;
    getStrings(nombreArchivo, lista);

    std::list<std::vector<double>> poblacionDouble;
    std::list<std::string> poblacionString;
    std::vector<int> calidad;

    std::list<std::vector<double>> elite;
    std::list<std::vector<double>> nonElite;

    std::string solucion = "";
    int dHam = m * umbral;
    int best_metric = -1;

    double tiempo = 0;
    double tiempoIteracion = 0;
    int indice = 0;  // Inicialización necesaria para `stoppinRule`
    int gen = 0;
    bool stop = false;

    auto start = std::chrono::steady_clock::now();

    createPSol(poblacion_inicial, m, poblacionDouble);
    decodedList(poblacionDouble, poblacionString);

    while (true) {
     auto current = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = current - start;
        tiempo = elapsed_seconds.count();

        if (elapsed_seconds.count() >= maxTime) {
            tiempo = tiempoIteracion;
            std::cout << "aaaaa\n";
            break;
        }

    // Depuración: imprime el tiempo transcurrido en cada iteración
    // std::cout << "Tiempo transcurrido: " << elapsed_seconds.count() 
    //       << " segundos de " << maxTime << " permitidos.\n";

    if(stop) break;

    calidad.clear();
    calculateQuality(dHam, calidad, lista, poblacionString);

    stop = stoppinRule(calidad, dHam, indice);
    if (stop) {
        std::cout << "Regla de parada activada: calidad suficiente alcanzada.\n";
        auto itPoblacionStrings = poblacionString.begin();
        std::advance(itPoblacionStrings, indice);
        solucion = *itPoblacionStrings;
        break;
    }

    preselection(calidad, poblacionString);

    if (elapsed_seconds.count() >= maxTime) {
            tiempo = tiempoIteracion;
            break;
    }
     
    codedList(poblacionDouble, poblacionString);

    if (elapsed_seconds.count() >= maxTime) {
            tiempo = tiempoIteracion;
            break;
    }
     
    sortPobl(gen, poblacion_Elite, poblacion_Mutantes, m, elite, nonElite, poblacionDouble);
    
    if (elapsed_seconds.count() >= maxTime) {
            tiempo = tiempoIteracion;
            break;
    }

    newPobl(bias, poblacion_Mutantes, poblacionDouble, elite, nonElite);

    if (elapsed_seconds.count() >= maxTime) {
            tiempo = tiempoIteracion;
            break;
    }

    if (calidad[indice] > best_metric) {
        best_metric = calidad[indice];
        auto itPoblacionStrings = poblacionString.begin();
        std::advance(itPoblacionStrings, indice);
        solucion = *itPoblacionStrings;
        tiempoIteracion = elapsed_seconds.count();
    }
       

    tiempoIteracion = elapsed_seconds.count();
}
    
    if (stop) {
        auto itPoblacionStrings = poblacionString.begin();
        std::advance(itPoblacionStrings, indice);
        best_metric = (calidad[indice])*-1;
        solucion = *itPoblacionStrings;
    }

   
    std::cout << "Mejor métrica: " << best_metric << "\n";

    return 0;
}

