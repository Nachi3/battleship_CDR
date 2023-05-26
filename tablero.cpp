#include <iostream>
#include <cstdlib>
#include <ctime>
// #include <windows.h>


using namespace std;

class Battleship{
private:
    // Tama�o del tablero
    static const int SIZE = 15;
    // Tama�o del portaaviones
    static const int PORTAAVIONES_SIZE = 5;
    // Tama�o del buque
    static const int BUQUE_SIZE = 4;
    // Tama�o del submarino
    static const int SUBMARINO_SIZE = 3;
    // Tama�o de la lancha
    static const int LANCHA_SIZE = 1;
    // Variable para el cambio de color
    //WORD Attributes = 0;

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

    void GenerarTableroManual() {
        // Solicitar al usuario que ingrese las posiciones de los barcos manualmente
        MostrarTablero();
        ColocarBarcoManual('P', PORTAAVIONES_SIZE);
        system("cls"); MostrarTablero();
        ColocarBarcoManual('B', BUQUE_SIZE);
        system("cls"); MostrarTablero();
        ColocarBarcoManual('B', BUQUE_SIZE);
        system("cls"); MostrarTablero();
        ColocarBarcoManual('S', SUBMARINO_SIZE);
        system("cls"); MostrarTablero();
        ColocarBarcoManual('S', SUBMARINO_SIZE);
        system("cls"); MostrarTablero();
        ColocarBarcoManual('L', LANCHA_SIZE);
        system("cls"); MostrarTablero();
        ColocarBarcoManual('L', LANCHA_SIZE);
        system("cls"); MostrarTablero();
        ColocarBarcoManual('L', LANCHA_SIZE);

        // Mostrar el tablero generado
        system("cls"); MostrarTablero();
    }
    
    void MostrarTablero() {
        //Poner encabezado
        printf("\n    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O\n");
        printf("   ---------------------------------------------\n");
        // Mostrar el tablero en la consola
        for (int i = 0; i < SIZE; i++) {
            printf("%2d|", i);
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' '){
                    // impresion de mar
                    cout << "[~]";
                } else {
                    cout << "[";
                    // Impresion de barcos.
                    // SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                    cout << board[i][j];
                    //ResetConsoleColour(Attributes);
                    cout << "]";
                }
            }
            cout << endl;
        }
    }
    
    // Coloca el car�cter X en las coordenadas de disparos indicadas
    void shot (int x, int y) {
		if((x>=0 && x<SIZE) && (y>=0 && y<SIZE)) {
            board[x][y] = 'X';
        } else {
            cout << "Ingresa valores validos\n";
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
        // Generar una posici�n aleatoria para el barco
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
            // Verificar si la posici�n generada es v�lida para colocar el barco
            if (EsPosicionValida(row, col, shipSize, 'H') && orientation == 'H') {
                // Colocar el barco en posici�n horizontal
                for (int i = 0; i < shipSize; i++) {
                    board[row][col + i] = shipType;
                }
                isValid = true;
            } else if (EsPosicionValida(row, col, shipSize, 'V') && orientation == 'V') {
                // Colocar el barco en posici�n vertical
                for (int i = 0; i < shipSize; i++) {
                    board[row + i][col] = shipType;
                }
                isValid = true;
            }
        }
    }

    void ColocarBarcoManual(char shipType, int shipSize) {
        // Solicitar al usuario que ingrese la posici�n del barco manualmente
        cout << "\nColocando barco de tipo " << shipType << " (tama�o: " << shipSize << ")" << endl;

        bool isValid = false;
        while (!isValid) {
            int row, col;
            char orientation;

            cout << "Ingrese la fila (0-" << SIZE - 1 << "): ";
            cin >> row;
            cout << "Ingrese la columna (0-" << SIZE - 1 << "): ";
            cin >> col;
            cout << "Ingrese la orientaci�n (H para horizontal, V para vertical): ";
            cin >> orientation;

            if (EsPosicionValida(row, col, shipSize, orientation)) {
                if (orientation == 'H') {
                    // Colocar el barco en posici�n horizontal
                    for (int i = 0; i < shipSize; i++) {
                        board[row][col + i] = shipType;
                    }
                } else {
                    // Colocar el barco en posici�n vertical
                    for (int i = 0; i < shipSize; i++) {
                        board[row + i][col] = shipType;
                    }
                }
                isValid = true;
            } else {
                cout << "La posici�n no es v�lida. Intente nuevamente." << endl;
            }
        }
    }
    
    bool EsPosicionValida(int row, int col, int shipSize, char orientation) {
        // Verificar si la posici�n y orientaci�n son v�lidas para colocar el barco

        // Verificar los l�mites del tablero
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            return false;
        }

        // Verificar si las casillas necesarias est�n vac�as horizontalmente
        if (orientation == 'H') {
            // Verificar si hay suficientes casillas vac�as en posici�n horizontal
            if (col + shipSize > SIZE) {
                return false;
            }

            for (int i = 0; i < shipSize; i++) {
                if (board[row][col + i] != ' ') {
                    return false;
                }
            }
        } else {
            // Verificar si hay suficientes casillas vac�as en posici�n vertical
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
/*
    void SetConsoleColour(WORD* Attributes, DWORD Colour) {
        // M�todo para cambiar el color del Foreground o el Background de la consola
        CONSOLE_SCREEN_BUFFER_INFO Info;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &Info);
        *Attributes = Info.wAttributes;
        SetConsoleTextAttribute(hStdout, Colour);
    }

    void ResetConsoleColour(WORD Attributes) {
        // M�todo para reestablecer el color del Foreground o el Background de la consola
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
    }*/
};
