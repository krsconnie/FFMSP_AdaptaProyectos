#!/bin/bash

# Archivos de salida CSV
output_file1="resultados(751).csv"
output_file2="resultados(801).csv"
output_file3="resultados(851).csv"

# Inicializar los archivos CSV con los encabezados
echo "Archivo,Tiempo Greedy (segundos),Calidad Greedy,Tiempo Mejor Solución (segundos),Calidad Mejor Solución" > "$output_file1"
echo "Archivo,Tiempo Greedy (segundos),Calidad Greedy,Tiempo Mejor Solución (segundos),Calidad Mejor Solución" > "$output_file2"
echo "Archivo,Tiempo Greedy (segundos),Calidad Greedy,Tiempo Mejor Solución (segundos),Calidad Mejor Solución" > "$output_file3"


# Compilar el programa
g++ -o programa G.cpp -std=c++11

# Array para manejar los archivos de salida
output_files=("$output_file1" "$output_file2" "$output_file3" "$output_file4" "$output_file5" "$output_file6")

# Función para ejecutar y extraer los resultados
function ejecutar_y_guardar {
    local umbral="$1"
    local mode="$2"
    local output_file="$3"

    for a in 100 200; do
        for size in 300 600 800; do
            for tiempo_max in 1 2 4; do
                for n in $(seq -w 1 100); do

                    # Construir el nombre del archivo
                    file_name="${a}-${size}-${n}.txt"

                    # Ejecutar el programa con los parámetros correspondientes
                    result=$(./programa -i "$file_name" -th "$umbral" "$mode" "$tiempo_max")

                   # Extraer la calidad y el tiempo de la solución Greedy
                    greedy_output=$(echo "$result" | sed -n '1p')
                    greedy_quality=$(echo "$greedy_output" | awk '{print $1}')
                    greedy_time=$(echo "$greedy_output" | awk '{print $2}')

                    # Extraer la calidad y el tiempo de la mejor solución final
                    best_output=$(echo "$result" | sed -n '2p')
                    best_quality=$(echo "$best_output" | awk '{print $1}')
                    best_time=$(echo "$best_output" | awk '{print $2}')

                    # Guardar los resultados en el archivo de salida correspondiente
                    echo "$file_name,$greedy_time,$greedy_quality,$best_time,$best_quality" >> "$output_file"
                done
            done
        done
    done
}

# Ejecutar para diferentes combinaciones de mode
ejecutar_y_guardar "0.75" "1" "$output_file1"
echo "Ejecuciones completadas para el archivo $output_file1"
ejecutar_y_guardar "0.80" "1" "$output_file2"
echo "Ejecuciones completadas para el archivo $output_file2"
ejecutar_y_guardar "0.85" "1" "$output_file3"
echo "Ejecuciones completadas para el archivo $output_file3"

echo "Todas las ejecuciones se han completado."
