// Clase que crea los tableros de ambos jugadores, y coloca los barcos.
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Battleship{
private:
    // Tamano del tablero
    static const int SIZE = 15;
    // Tamano del portaaviones
    static const int PORTAAVIONES_SIZE = 5;
    // Tamano del buque
    static const int BUQUE_SIZE = 4;
    // Tamano del submarino
    static const int SUBMARINO_SIZE = 3;
    // Tamano de la lancha
    static const int LANCHA_SIZE = 1;

public:
    // Tablero
    char board[SIZE][SIZE];
    // Constructor del tablero, inicializado con espacios

    Battleship() {
        // Inicializar el tablero con espacios en blanco
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = ' ';
            }
        }
    }
    // Generacion de tablero aleatoriamente
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
    }
    // Funcion para imprimir el tablero en consola

    void MostrarTablero() {
        //Poner encabezado
        printf("\n    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14\n");
        printf("   ---------------------------------------------\n");

        // Definicion de Colores de letra
        const string BLACK = "\033[30m";
        const string RED = "\033[31m";
        const string GREEN = "\033[32m";
        const string YELLOW = "\033[33m";
        const string BLUE = "\033[34m";
        const string MAGENTA = "\033[35m";
        const string CYAN = "\033[36m";
        const string WHITE = "\033[37m";
        const string BOLD = "\033[1m";
        const string RESET = "\033[0m";
        // Definicion de colores de fondo
        const string BLUE_BACKGROUND = "\033[44m";
        const string CYAN_BACKGROUND = "\033[46m";
        const string RED_BACKGROUND = "\033[101m";
        const string GRIS_BACKGROUND = "\033[100m";
        const string BLACK_BACKGROUND = "\033[40m";
        // Mostrar el tablero en la consola
        for (int i = 0; i < SIZE; i++) {
            printf("%2d|", i);
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' '){
                    // impresion de mar
                    cout << CYAN <<"[~]" << RESET;
                } else if(board[i][j] == 'X'){
                    cout << WHITE <<"[X]" << RESET;
                } else  {
                    // impresion de los barcos
                    if(board[i][j]=='P'){
                        cout << GREEN << "[P]" << RESET;
                    }else if(board[i][j]=='B'){
                        cout << MAGENTA << "[B]" << RESET;
                    }else if(board[i][j]=='S'){
                        cout << YELLOW << "[S]" << RESET;
                    }else if(board[i][j]=='L'){
                        cout << RED << "[L]" << RESET;
                    }
                }
            }
            cout << endl;
        }
    }

    // Coloca el caracter X en las coordenadas de disparos indicadas
    char shot (int x, int y) {
        if((x>=0 && x<SIZE) && (y>=0 && y<SIZE)) {
            char aux = board[x][y];
            board[x][y] = 'X';
            return aux;
        } else {
            cout << "Ingresa valores validos\n";
            return ' ';
        }
    }

    // Indica si termino el juego, solo si en el tablero solo existe agua o disparos
	int ganar(){
        for(int i = 0; i < SIZE; i++)
            for(int j = 0; j < SIZE; j++)
                if(board[i][j]!=' ' && board[i][j]!='X') return 0;
        return 1;
    	}

private:
    // Funcion que coloca cada barco aleatoriamente
    void GenerarBarco(char shipType, int shipSize) {
        // Generar una posicion aleatoria para el barco
        int row, col, vert_hor;
        char orientation;
        bool isValid = false;

        // Generar la posicion de la embarcacion de manera aleatoria
        while (!isValid) {
            row = rand() % SIZE;
            col = rand() % SIZE;
            vert_hor = rand() % 2;
            // Gracias a vert_hor se pondran verticalmente u horizontalmente de manera aleatoria
            if (vert_hor == 0) {
                orientation = 'H';
            } else {
                orientation = 'V';
            }
            // Verificar si la posicion generada es valida para colocar el barco
            if (EsPosicionValida(row, col, shipSize, 'H') && orientation == 'H') {
                // Colocar el barco en posicion horizontal
                for (int i = 0; i < shipSize; i++) {
                    board[row][col + i] = shipType;
                }
                isValid = true;
            } else if (EsPosicionValida(row, col, shipSize, 'V') && orientation == 'V') {
                // Colocar el barco en posicion vertical
                for (int i = 0; i < shipSize; i++) {
                    board[row + i][col] = shipType;
                }
                isValid = true;
            }
        }
    }
	bool EsPosicionValida(int row, int col, int shipSize, char orientation) {
        // Verificar si la posicion y orientacion son validas para colocar el barco

        // Verificar los limites del tablero
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            return false;
        }
        
        // Verificar si las casillas necesarias estan vacias horizontalmente
        if (orientation == 'H') {
            // Verificar si hay suficientes casillas vacias en posicion horizontal
            if (col + shipSize > SIZE) {
                return false;
            }
            for (int i = 0; i < shipSize; i++) {
                if (board[row][col + i] != ' ') {
                    return false;
                }
            }
        } else {
            // Verificar si hay suficientes casillas vacias en posiciin vertical
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
