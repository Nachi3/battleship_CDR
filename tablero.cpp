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
    // Variable para el cambio de color
    //WORD Attributes = 0;

public:

    char board[SIZE][SIZE];

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
        //MostrarTablero();
    }

    void GenerarTableroManual() {
        // Solicitar al usuario que ingrese las posiciones de los barcos manualmente
        ColocarBarcoManual('P', PORTAAVIONES_SIZE);
        ColocarBarcoManual('B', BUQUE_SIZE);
        ColocarBarcoManual('B', BUQUE_SIZE);
        ColocarBarcoManual('S', SUBMARINO_SIZE);
        ColocarBarcoManual('S', SUBMARINO_SIZE);
        ColocarBarcoManual('L', LANCHA_SIZE);
        ColocarBarcoManual('L', LANCHA_SIZE);
        ColocarBarcoManual('L', LANCHA_SIZE);

        // Mostrar el tablero generado
        //system("cls"); //MostrarTablero();
    }

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

    // Indicar si en el tablero solo existe agua o disparos
	int ganar(){
        for(int i = 0; i < SIZE; i++)
            for(int j = 0; j < SIZE; j++)
                if(board[i][j]!=' ' && board[i][j]!='X') return 0;
        return 1;
    }

private:
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
                // Colocar el barco en posici�n horizontal
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

    void ColocarBarcoManual(char shipType, int shipSize) {
        // Solicitar al usuario que ingrese la posicion del barco manualmente
        cout << "\nColocando barco de tipo " << shipType << " (tamano: " << shipSize << ")" << endl;

        bool isValid = false;
        while (!isValid) {
            int row, col;
            char orientation;

            cout << "Ingrese la fila (0-" << SIZE - 1 << "): ";
            cin >> row;
            cout << "Ingrese la columna (0-" << SIZE - 1 << "): ";
            cin >> col;

            while (true && shipSize!=1) { // Las lanchas no piden orientacion
                cout << "Ingrese la orientacion (H para horizontal, V para vertical): ";
                cin >> orientation;
                orientation = toupper(orientation); // Convertir a mayúscula
                if (orientation == 'H' || orientation == 'V') {
                    break; // Sale del bucle si la orientacion es valida
                } else {
                    cout << "\nOrientacion no valida. Por favor, ingrese H para horizontal o V para vertical.\n" << endl;
                }
            }

            if (EsPosicionValida(row, col, shipSize, orientation)) {
                if (orientation == 'H') {
                    // Colocar el barco en posicion horizontal
                    for (int i = 0; i < shipSize; i++) {
                        board[row][col + i] = shipType;
                    }
                } else {
                    // Colocar el barco en posicion vertical
                    for (int i = 0; i < shipSize; i++) {
                        board[row + i][col] = shipType;
                    }
                }
                isValid = true;
            } else {
                cout << "La posicion no es valida. Intente nuevamente." << endl;
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
