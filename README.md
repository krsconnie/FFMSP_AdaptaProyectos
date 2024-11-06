# Far from most String Problem #

Busca encontrar una cadena de caracteres que esté lo más alejada posible de la "cadena más frecuente" dentro de un conjunto dado de cadenas. La "cadena más frecuente" es aquella que tiene la menor distancia de Hamming con las demás cadenas en el conjunto.

Objetivo: 
  
    Crear un algoritmo que genere una cadena que maximice la distancia de Hamming 
    respecto a la cadena más frecuente o a todas las cadenas del conjunto. 
    Esto implica diseñar una solución que no solo identifique la cadena más común, 
    sino que también encuentre una cadena que esté "lejos" en términos de similitud de caracteres.

# LISTA #
# Primera Entrega: 14 de Septiembre #

  Desarrollar una heurística greedy y una heurística greedy aleatorizada. [Listo]

  REQUISITOS MÍNIMOS
    
    - Todos los programas deben correr en Linux
    - El resultado debe ser entregado en la salida estándar (pantalla), y sólo 
      debe ser el valor objetivo o calidad de la solución y el tiempo usado para generarla.
    - El formato de ejecución debe ser el siguiente:

  ![image](https://github.com/user-attachments/assets/47373d13-c02d-475c-a196-c533295d2461)

  ENTREGABLES

    Documentos PDF con  dos páginas con algoritmos en pseudolenguaje y explicación de Greedy 
    y Greedy Aleatorizado desarrollados.
    
    Códigos fuentes, scripts de compilación, bibliotecas o cualquier elementos para lograr programa 
    ejecutable comprimidos en tgz.
    
    Video corto screencast que muestre el funcionamiento del programa en su ambiente de trabajo 
    (no más de 2 minutos).

  ![image](https://github.com/user-attachments/assets/a7d5bc4e-06d8-4c49-b862-36448b327654)

  La tabla de resultados contiene la siguiente información: 

            Media de  greedy determinista (media de los 100 casos de cada configuración de instancia de problema).
            
            Resultados de medias y desviaciones estándar de greedy aleatorizado 
            (también de los 100 casos de cada configuración de instancia de problema).
            
            Sumar esto al reporte PDF antes nombrado con una tabla complementaria (1 página), con su análisis.

# LISTA #
# Segunda Entrega: 18 de Octubre #

Objetivo 

    Busca implementar una Metaheurística de trayectoria o solución única para resolver el Problema FFMS. 

REQUISITOS

      Any-Time Behavior: La metaheurística debe utilizar como criterio de detención el tiempo de ejecución.Este tiempo debe ser especificado en segundos. Adicionalmente la implementación debe permitir análisis any-time behavior. Para lograr esto, es           mandatorio que cada vez que la metaheurística logre una nueva mejor solución, muestre por salida estándar la calidad de la solución, y el tiempo en que la encontró, (desde el inicio del algoritmo).

       Al final de la ejecución (cumplido el tiempo máximo de ejecución) el algoritmo debe  entregar por salida estándar la calidad de la mejor  solución encontrada y el tiempo cuando la encontró.
    
ENTREGABLES

      
    1.Códigos fuentes del proyecto e instrucciones  para poder  compilar/interpretar correctamente la metaheurística.
    2.Manual de uso básico (1 página)
    3.Especificaciones del algoritmo (descripción en pseudolenguaje explicando componentes y funcionamiento) (max 2 páginas)
    4.Video corto screencast que muestre el funcionamiento del programa en su ambiente de trabajo (no más de 2 minutos)

La tabla de resultados contiene:

![image](https://github.com/user-attachments/assets/f070621c-2092-4764-af42-4f239f70d83d)

    Lo mismo que en la primera entrega, pero se agregan 3 datos más:

      1.Media de la mejor solución encontrada en el tiempo determinado.
      2.Desviación estándar de la misma mejor solución encontrada.
      3.Tiempo promedio para obtener esta solución.

RUBRICA:
![image](https://github.com/user-attachments/assets/a31defe4-18e9-497d-b075-605d2af53191)

# Tercera Entrega: 13 de Noviembre #

Objetivo 

    Implementar una Metaheurística Poblacional (Algoritmo Genético) para resolver el FFMSP.

REQUISITOS

    Any-Time Behavior.
    Debe correr en Linux.
    Someter el programa a tuning usando irace en el cluster, con una configuración única.
    Realizar un test de significancia estadística comparando la calidad de su Greedy determinista(Primera entrega),su metaheurística de trayectoria(Segunda entrega),
    y su actual metaheurística poblacional(Tercera entrega). [CD con R]
    
CONSIDERACIONES

    Mismo dataset.
    Los mejores parámetros deben ser de forma automatizada usando irace y el cluster Luthier.
    Budget de 1000 experimentos para Tuning
    Tiempos de 10 segundos y 60 segundos. ( el tuning debe ser a 60 segundos).

ENTREGABLES

    
    1.Códigos fuentes del proyecto e instrucciones  para poder  compilar/interpretar correctamente la metaheurística.
    2.Manual de uso básico (1 página)
    3.Especificaciones del algoritmo (descripción en pseudolenguaje explicando componentes y funcionamiento) (max 2 páginas)
    4.Log de configuración obtenida por irace y análisis de la configuración obtenida
    5.Tabla de resultados comparativa (Greedy/MH de trayectoria/MH poblacional en 10s) y resultados complementarios de la MH poblacional en 60s
    6.Gráfico de Diferencias críticas comparando resultados.
