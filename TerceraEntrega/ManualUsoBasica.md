# Manual de Uso Básico: BRKGA para FFMSP

## 1.REQUISITOS PREVIOS

  -Tener instalados los paquetes de g++ y c++. Para usuarios de Debian/Ubuntu esto puede realizarse mediante el comando:

        $sudo apt install c++
        $sudo apt install g++

## 2.COMPILACIÓN

  - Crea el archivo donde descomprimirás el archivo .zip usando:

        $mkdir BRKGA
  
  (GRASP es una sugerencia, puede escoger el nombre de su preferencia)

  - Una vez los archivos estén en la carpeta, asegurate de descomprimir el dataset en la misma carpeta.
  - Para compilar el programa use los siguientes comandos:

        $cd BRKGA
        $g++ a.cpp -o <nombre del ejecutable>

  ## 3.EJECUCIÓN

  - Para ejecutar el programa, use los siguientes comandos:

         $./<nombre del ejecutable> -i <instancia_problema> -th <umbral> -t <tiempo_max> -pi <población inicial>
          -pE <poblacion elite> -pM <poblacion mutantes> -b <bias>

   #### Parámetros:

    <instancia_problema>: La ruta al archivo de texto con la instancia a probar. Este archivo debe contener la lista de strings sobre la cual se realizará la búsqueda.

    <umbral>: El umbral (threshold) que se utilizará para calcular la distancia de Hamming y determinar el nivel de similitud entre strings.

    <tiempo_max>: El tiempo máximo de ejecución en segundos para el algoritmo (positivo, no puede ser 0).

    <poblacion inicial>: Cantidad de soluciones producidas al inicio del algoritmo.

    <poblacion elite>: Cantidad de soluciones que serán consideradas como elite.

    <poblacion mutantes>: Cantidad de soluciones aleatorias que se agregan a cada generación para salir de un máximo local.
    
    <bias>: Porcentaje de obtencion de un genoma del padre elite.
    
   #### Ejemplo de ejecución

    $ ./<nombre del ejecutable> -i 100-300-001.txt -th 0.7 -t 10 -pi 100 -pE 20 -pM 5 -b 0.7 
