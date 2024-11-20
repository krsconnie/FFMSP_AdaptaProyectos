#include "utilidades.h"
#include "getInput.h"
#include "brkga.h"
#include <chrono>

int main(int argc, char const *argv[]) {

    srand(time(0));

    if (argc != 15 || 
        std::string(argv[1]) != "-i" || 
        std::string(argv[3]) != "-th" || 
        std::string(argv[5]) != "-t" || 
        std::string(argv[7]) != "-pi" || 
        std::string(argv[9]) != "-pE" || 
        std::string(argv[11]) != "-pM" || 
        std::string(argv[13]) != "-b") {

        std::cerr << "Uso: " << argv[0] 
                  << " -i <instancia_problema> -th <umbral> -t <tiempo_max> "
                  << "-pi <pobl_inicial> -pE <pobl_elite> -pM <pobl_mutantes> -b <bias>\n";
        return EXIT_FAILURE;
    }

    float umbral = atof(argv[4]);
    int maxTime = atoi(argv[6]);
    int poblacion_inicial = atoi(argv[8]);
    int poblacion_Elite = atoi(argv[10]);
    int poblacion_Mutantes = atoi(argv[12]);
    double bias = std::stod(argv[14]);

    if (umbral <= 0 || umbral >= 1 || bias <= 0 || bias >= 1 || maxTime <= 0 || poblacion_inicial <= 0 
        || poblacion_Elite <= 0 || poblacion_Mutantes < 0 || 
        poblacion_inicial - poblacion_Elite - poblacion_Mutantes <= 0) {
           
        std::cerr << "Error: El umbral y el porcentaje_genElite deben estar entre 0 y 1 (exclusivo).\n"
                  << "El tiempo, población inicial y población élite deben ser positivos.\n"
                  << "La población mutantes debe ser >= 0 y el total de la población debe ser suficiente.\n";
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
    std::cout << "Tiempo transcurrido: " << elapsed_seconds.count() 
              << " segundos de " << maxTime << " permitidos.\n";

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
            std::cout << "aaaaa\n";
            break;
    }
     
    codedList(poblacionDouble, poblacionString);

    if (elapsed_seconds.count() >= maxTime) {
            tiempo = tiempoIteracion;
            std::cout << "aaaaa\n";
            break;
    }
     
    sortPobl(gen, poblacion_Elite, poblacion_Mutantes, m, elite, nonElite, poblacionDouble);
    
    if (elapsed_seconds.count() >= maxTime) {
            tiempo = tiempoIteracion;
            std::cout << "aaaaa\n";
            break;
    }

    newPobl(bias, poblacion_Mutantes, poblacionDouble, elite, nonElite);

    if (calidad[indice] > best_metric) {
        best_metric = calidad[indice];
        auto itPoblacionStrings = poblacionString.begin();
        std::advance(itPoblacionStrings, indice);
        solucion = *itPoblacionStrings;
        tiempoIteracion = elapsed_seconds.count();

        std::cout << "Nueva mejor calidad: " << best_metric 
                  << " encontrada en " << elapsed_seconds.count() << " segundos.\n";
    }

}
    
    if (stop) {
        auto itPoblacionStrings = poblacionString.begin();
        std::advance(itPoblacionStrings, indice);
        best_metric = calidad[indice];
        solucion = *itPoblacionStrings;
    }

   

    std::cout << "Mejor solución: " << solucion << "\n";
    std::cout << "Tiempo total: " << tiempo << " segundos\n";
    std::cout << "Mejor métrica: " << best_metric << "\n";

    return 0;
}