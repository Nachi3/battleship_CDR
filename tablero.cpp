#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


using namespace std;

class Battleship{
private:
    // Tamaño del tablero
    static const int SIZE = 15;
    // Tamaño del portaaviones
    static const int PORTAAVIONES_SIZE = 5;
    // Tamaño del buque
    static const int BUQUE_SIZE = 4;
    // Tamaño del submarino
    static const int SUBMARINO_SIZE = 3;
    // Tamaño de la lancha
    static const int LANCHA_SIZE = 1;
    // Variable para el cambio de color
    WORD Attributes = 0;

    char board[SIZE][SIZE];

public:
    Battleship() {
        // Inicializar el tablero con espacios en blanco
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void GenerarTableroAleatorio() {
        srand(time(0));  // Semilla aleatoria basada en el tiempo actual

        // Generar las posiciones aleatorias de los barcos
        GenerarBarco('P', PORTAAVIONES_SIZE);
        GenerarBarco('B', BUQUE_SIZE);
        GenerarBarco('B', BUQUE_SIZE);
        GenerarBarco('S', SUBMARINO_SIZE);
        GenerarBarco('S', SUBMARINO_SIZE);
        GenerarBarco('L', LANCHA_SIZE);
        GenerarBarco('L', LANCHA_SIZE);
        GenerarBarco('L', LANCHA_SIZE);

        // Mostrar el tablero generado
        MostrarTablero();
    }

    void MostrarTablero() {
        //Poner encabezado
        printf("\n    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O\n");
        printf("   ---------------------------------------------\n");
        // Mostrar el tablero en la consola
        for (int i = 0; i < SIZE; i++) {
            printf("%2d|", i);
            for (int j = 0; j < SIZE; j++) {
                // Si la posicion esta vacia dibuja una olita
                if (board[i][j] == ' '){
                    cout << "[" << "~" << "]" ;
                } else {
                    cout << "[" << board[i][j] << "]";
                }
            }
            cout << endl;
        }
    }

private:
    void GenerarBarco(char shipType, int shipSize) {
        // Generar una posición aleatoria para el barco
        int row, col, vert_hor;
        char orientation;
        bool isValid = false;

        // Generar la posicion de la embarcacion de manera aleatoria
        while (!isValid) {
            row = rand() % SIZE;
            col = rand() % SIZE;
            vert_hor = rand() % 2;
            // Gracias a vert_hor se pondra verticalmente u horizontalmente de manera aleatoria
            if (vert_hor == 0) {
                orientation = 'H';
            } else {
                orientation = 'V';
            }
            // Verificar si la posición generada es válida para colocar el barco
            if (EsPosicionValida(row, col, shipSize, 'H') && orientation == 'H') {
                // Colocar el barco en posición horizontal
                for (int i = 0; i < shipSize; i++) {
                    board[row][col + i] = shipType;
                }
                isValid = true;
            } else if (EsPosicionValida(row, col, shipSize, 'V') && orientation == 'V') {
                // Colocar el barco en posición vertical
                for (int i = 0; i < shipSize; i++) {
                    board[row + i][col] = shipType;
                }
                isValid = true;
            }
        }
    }


    bool EsPosicionValida(int row, int col, int shipSize, char orientation) {
        // Verificar si la posición y orientación son válidas para colocar el barco

        // Verificar los límites del tablero
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            return false;
        }

        // Verificar si las casillas necesarias están vacías horizontalmente
        if (orientation == 'H') {
            // Verificar si hay suficientes casillas vacías en posición horizontal
            if (col + shipSize > SIZE) {
                return false;
            }

            for (int i = 0; i < shipSize; i++) {
                if (board[row][col + i] != ' ') {
                    return false;
                }
            }
        } else {
            // Verificar si hay suficientes casillas vacías en posición vertical
            if (row + shipSize > SIZE) {
                return false;
            }

            for (int i = 0; i < shipSize; i++) {
                if (board[row + i][col] != ' ') {
                    return false;
                }
            }
        }

        return true;
    }

};
