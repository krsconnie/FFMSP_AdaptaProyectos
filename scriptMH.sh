#!/bin/bash

output_file1="resultadosMH(750).csv"
output_file2="resultadosMH(800).csv"
output_file3="resultadosMH(850).csv"
output_file4="resultadosMH(751).csv"
output_file5="resultadosMH(801).csv"
output_file6="resultadosMH(851).csv"

echo "Archivo,Tiempo (segundos),Calidad" > $output_file1
echo "Archivo,Tiempo (segundos),Calidad" > $output_file2
echo "Archivo,Tiempo (segundos),Calidad" > $output_file3
echo "Archivo,Tiempo (segundos),Calidad" > $output_file4
echo "Archivo,Tiempo (segundos),Calidad" > $output_file5
echo "Archivo,Tiempo (segundos),Calidad" > $output_file6

g++ -o MetaHeuristica G.cpp -std=c++11

for it in {1..6}; do
	for a in 100 200; do
    		for size in 300 600 800; do
			for n in {001..100}; do
  				file_name="${a}-${size}-${n}.txt"
        
        			umbral="0.75"
        			mode="0"

		        	result=$(./MetaHeuristica -i "$file_name" -th "$umbral" "$mode")
       				tiempo=$(echo "$result" | grep "Tiempo usado" | awk '{print $3}')
       				calidad=$(echo "$result" | grep "Calidad de la solución" | awk '{print $5}')
       				echo "$file_name,$tiempo,$calidad" >> $output_file${it}
			done
    		done
	done
	echo "Ejecuciones completadas. Resultados guardados en $output_file{it}"
done