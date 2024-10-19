# Manual de Uso Básico: Grasp para FFMSP

## 1.REQUISITOS PREVIOS

  -Tener instalados los paquetes de g++ y c++. Para usuarios de Debian/Ubuntu esto puede realizarse mediante el comando:

        $sudo apt install c++
        $sudo apt install g++

## 2.COMPILACIÓN

  - Crea el archivo donde descomprimirás el archivo .zip usando:

        $mkdir GRASP
  
  (GRASP es una sugerencia, puede escoger el nombre de su preferencia)

  - Una vez los archivos estén en la carpeta, asegurate de descomprimir el dataset en la misma carpeta.
  - Para compilar el programa use los siguientes comandos:

        $cd GRASP
        $g++ G.cpp -o <nombre del ejecutable>

  ## 3.EJECUCIÓN

  - Para ejecutar el programa, use los siguientes comandos:

         $./<nombre del ejecutable> -i <instancia_problema> -th <umbral> <porcentaje_random> <tiempo_max>

   #### Parámetros:

    -i: La ruta al archivo de texto con la instancia a probar. Este archivo debe contener la lista de strings sobre la cual se realizará la búsqueda.

    -th: El umbral (threshold) que se utilizará para calcular la distancia de Hamming y determinar el nivel de similitud entre strings.

    <porcentaje_random>: El coeficiente de aleatorización para el algoritmo greedy, un valor en el rango [0, 1]. Un valor de 0 significa un algoritmo completamente determinista, mientras que un valor mayor a 0 introduce aleatoriedad.

    <tiempo_max>: El tiempo máximo de ejecución en segundos para el algoritmo (positivo, no puede ser 0).

   #### Ejemplo de ejecución

    $ ./grasp -i 100-300-001.txt -th 0.5 0.3 60

  100-300-001.txt: Archivo con los datos del problema.
  
  0.5: Umbral de Hamming, que determina el porcentaje de posiciones diferentes permitidas entre el string candidato y los strings en la lista.
  
  0.3: Porcentaje de aleatoriedad para la selección greedy.
  
  60: Tiempo máximo de ejecución en segundos.
