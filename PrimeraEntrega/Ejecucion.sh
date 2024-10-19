#!/bin/bash

# Archivo de salida CSV
output_file1="resultados(750).csv"
output_file2="resultados(800).csv"
output_file3="resultados(850).csv"
output_file4="resultados(751).csv"
output_file5="resultados(801).csv"
output_file6="resultados(851).csv"

# Inicializar el archivo CSV con los encabezados
echo "Archivo,Tiempo (segundos),Calidad" > $output_file1
echo "Archivo,Tiempo (segundos),Calidad" > $output_file2
echo "Archivo,Tiempo (segundos),Calidad" > $output_file3
echo "Archivo,Tiempo (segundos),Calidad" > $output_file4
echo "Archivo,Tiempo (segundos),Calidad" > $output_file5
echo "Archivo,Tiempo (segundos),Calidad" > $output_file6

# Compilar el programa (asumiendo que el archivo fuente es "programa.cpp")
g++ -o programa Greedy.cpp -std=c++11

for a in 100 200; do
	# Iterar sobre las diferentes combinaciones de tamaño de instancia
    for size in 300 600 800; do
		# Iterar sobre los valores de n (de 1 a 100)
		for n in {001..100}; do
  
        	# Construir el nombre del archivo
        	file_name="${a}-${size}-${n}.txt"
        
        	# Ejecutar el programa con los parámetros correspondientes
        	# Se asume que el programa recibe los parámetros de la forma:
        	# ./programa -i <nombre_archivo> -th <umbral> <mode>
        
        	# Umbral y modo son valores arbitrarios que debes ajustar según tus necesidades
        	umbral="0.75"
        	mode="0"

        	# Capturar el tiempo de ejecución y la salida del programa
        	result=$(./programa -i "$file_name" -th "$umbral" "$mode")
        
        	# Extraer el tiempo y calidad de la salida del programa usando grep y awk
        	tiempo=$(echo "$result" | grep "Tiempo usado" | awk '{print $3}')
        	calidad=$(echo "$result" | grep "Calidad de la solución" | awk '{print $5}')
        
        	# Escribir los resultados en el archivo CSV
        	echo "$file_name,$tiempo,$calidad" >> $output_file1
    	done
	done
done

echo "Ejecuciones completadas. Resultados guardados en $output_file1"

for a in 100 200; do
	# Iterar sobre las diferentes combinaciones de tamaño de instancia
    for size in 300 600 800; do
		# Iterar sobre los valores de n (de 1 a 100)
		for n in {001..100}; do
  
        	# Construir el nombre del archivo
        	file_name="${a}-${size}-${n}.txt"
        
        	# Ejecutar el programa con los parámetros correspondientes
        	# Se asume que el programa recibe los parámetros de la forma:
        	# ./programa -i <nombre_archivo> -th <umbral> <mode>
        
        	# Umbral y modo son valores arbitrarios que debes ajustar según tus necesidades
        	umbral="0.80"
        	mode="0"

        	# Capturar el tiempo de ejecución y la salida del programa
        	result=$(./programa -i "$file_name" -th "$umbral" "$mode")
        
        	# Extraer el tiempo y calidad de la salida del programa usando grep y awk
        	tiempo=$(echo "$result" | grep "Tiempo usado" | awk '{print $3}')
        	calidad=$(echo "$result" | grep "Calidad de la solución" | awk '{print $5}')
        
        	# Escribir los resultados en el archivo CSV
        	echo "$file_name,$tiempo,$calidad" >> $output_file2
    	done
	done
done

echo "Ejecuciones completadas. Resultados guardados en $output_file2"

for a in 100 200; do
	# Iterar sobre las diferentes combinaciones de tamaño de instancia
    for size in 300 600 800; do
		# Iterar sobre los valores de n (de 1 a 100)
		for n in {001..100}; do
  
        	# Construir el nombre del archivo
        	file_name="${a}-${size}-${n}.txt"
        
        	# Ejecutar el programa con los parámetros correspondientes
        	# Se asume que el programa recibe los parámetros de la forma:
        	# ./programa -i <nombre_archivo> -th <umbral> <mode>
        
        	# Umbral y modo son valores arbitrarios que debes ajustar según tus necesidades
        	umbral="0.85"
        	mode="0"

        	# Capturar el tiempo de ejecución y la salida del programa
        	result=$(./programa -i "$file_name" -th "$umbral" "$mode")
        
        	# Extraer el tiempo y calidad de la salida del programa usando grep y awk
        	tiempo=$(echo "$result" | grep "Tiempo usado" | awk '{print $3}')
        	calidad=$(echo "$result" | grep "Calidad de la solución" | awk '{print $5}')
        
        	# Escribir los resultados en el archivo CSV
        	echo "$file_name,$tiempo,$calidad" >> $output_file3
    	done
	done
done

echo "Ejecuciones completadas. Resultados guardados en $output_file3"

for a in 100 200; do
	# Iterar sobre las diferentes combinaciones de tamaño de instancia
    for size in 300 600 800; do
		# Iterar sobre los valores de n (de 1 a 100)
		for n in {001..100}; do
  
        	# Construir el nombre del archivo
        	file_name="${a}-${size}-${n}.txt"
        
        	# Ejecutar el programa con los parámetros correspondientes
        	# Se asume que el programa recibe los parámetros de la forma:
        	# ./programa -i <nombre_archivo> -th <umbral> <mode>
        
        	# Umbral y modo son valores arbitrarios que debes ajustar según tus necesidades
        	umbral="0.75"
        	mode="1"

        	# Capturar el tiempo de ejecución y la salida del programa
        	result=$(./programa -i "$file_name" -th "$umbral" "$mode")
        
        	# Extraer el tiempo y calidad de la salida del programa usando grep y awk
        	tiempo=$(echo "$result" | grep "Tiempo usado" | awk '{print $3}')
        	calidad=$(echo "$result" | grep "Calidad de la solución" | awk '{print $5}')
        
        	# Escribir los resultados en el archivo CSV
        	echo "$file_name,$tiempo,$calidad" >> $output_file4
    	done
	done
done

echo "Ejecuciones completadas. Resultados guardados en $output_file4"

for a in 100 200; do
	# Iterar sobre las diferentes combinaciones de tamaño de instancia
    for size in 300 600 800; do
		# Iterar sobre los valores de n (de 1 a 100)
		for n in {001..100}; do
  
        	# Construir el nombre del archivo
        	file_name="${a}-${size}-${n}.txt"
        
        	# Ejecutar el programa con los parámetros correspondientes
        	# Se asume que el programa recibe los parámetros de la forma:
        	# ./programa -i <nombre_archivo> -th <umbral> <mode>
        
        	# Umbral y modo son valores arbitrarios que debes ajustar según tus necesidades
        	umbral="0.80"
        	mode="1"

        	# Capturar el tiempo de ejecución y la salida del programa
        	result=$(./programa -i "$file_name" -th "$umbral" "$mode")
        
        	# Extraer el tiempo y calidad de la salida del programa usando grep y awk
        	tiempo=$(echo "$result" | grep "Tiempo usado" | awk '{print $3}')
        	calidad=$(echo "$result" | grep "Calidad de la solución" | awk '{print $5}')
        
        	# Escribir los resultados en el archivo CSV
        	echo "$file_name,$tiempo,$calidad" >> $output_file5
    	done
	done
done

echo "Ejecuciones completadas. Resultados guardados en $output_file5"

for a in 100 200; do
	# Iterar sobre las diferentes combinaciones de tamaño de instancia
    for size in 300 600 800; do
		# Iterar sobre los valores de n (de 1 a 100)
		for n in {001..100}; do
  
        	# Construir el nombre del archivo
        	file_name="${a}-${size}-${n}.txt"
        
        	# Ejecutar el programa con los parámetros correspondientes
        	# Se asume que el programa recibe los parámetros de la forma:
        	# ./programa -i <nombre_archivo> -th <umbral> <mode>
        
        	# Umbral y modo son valores arbitrarios que debes ajustar según tus necesidades
        	umbral="0.85"
        	mode="1"

        	# Capturar el tiempo de ejecución y la salida del programa
        	result=$(./programa -i "$file_name" -th "$umbral" "$mode")
        
        	# Extraer el tiempo y calidad de la salida del programa usando grep y awk
        	tiempo=$(echo "$result" | grep "Tiempo usado" | awk '{print $3}')
        	calidad=$(echo "$result" | grep "Calidad de la solución" | awk '{print $5}')
        
        	# Escribir los resultados en el archivo CSV
        	echo "$file_name,$tiempo,$calidad" >> $output_file6
    	done
	done
done

echo "Ejecuciones completadas. Resultados guardados en $output_file6"
