# JUEGO BATTLESHIP - CLIENTE SERVIDOR

Battleship es un juego de estrategia que se juega entre dos jugadores, uno contra uno, donde la idea principal es derribar todas las naves del contincante disparando en una coordenada de un tablero de 15x 15. Los turnos se van alternando, un disparo cada uno. Este juego está implementado en C++, y trata de la comunicación cliente servidor para poder batallar.

## Características
- El tablero es de 15x15
- Las naves son un Portaavion, dos buques, dos submarinos y tres lanchas.
- Los disparos se representan el tablero con un carácter de X.
- Se va mostrando los disparos y naves hundidas.

## Archivos usados
1. *main.cpp:* Es el archivo principal, donde se incializa el programa y se lleva a cabo el control del juego.
2. *servidor.cpp:* Sirve para conectar con el cliente, batallar mantiendo el estado del juego y funcionando automáticamente, enviando actualizaciones y realizando disparos.
3. *cliente.cpp:* Envía las acciones al servidor estableciendo la conexión necesaria, mandando disparos ingresados por teclado.
4. *tablero.cpp:* Archivo usado para representar un tablero con coordenadas.
5. *derribos.cpp y derribos.h:* En este archivo se registrar las naves hundidas y los disparos que se han hecho.

## Cómo jugar

Este es un juego de red local y se ejecuta en la terminal de linux. Los pasos para jugar son los siguientes:

1. Se descarga el juego del repositorio donde se encuentra, usando el comando 'git clone https://github.com/Nachi3/battleship_CDR.git'
2. Se debe compilar y ejecutar el programa.
3. Luego de que se genere aleatoriamente, ya se puede ingresar las coordenadas de los disparos por teclado.
4. Una vez hundidos todos los barcos del contrincantes se decide el ganador con un mensaje, y ya se puede cerrar el juego.
