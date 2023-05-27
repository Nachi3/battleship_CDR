#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Derribos{
private:
    // Tamanio del portaaviones
    static const int PORTAAVIONES_SIZE = 5;
    // Tamanio del buque
    static const int BUQUE_SIZE = 4;
    // Tamanio del submarino
    static const int SUBMARINO_SIZE = 3;
    // Tamanio de la lancha
    static const int LANCHA_SIZE = 1;

    // Tamaño de la matriz
    static const int SIZE_TABLE = 15;

    // Numero de portaaviones
    static const int PORTAAVIONES_NUM = 1*PORTAAVIONES_SIZE;
    // Numero de Buques
    static const int BUQUE_NUM = 2*BUQUE_SIZE;
    // Numero de Submarinoss
    static const int SUBMARINO_NUM = 2*SUBMARINO_SIZE;
    // Numero de Lanchas
    static const int LANCHAS_NUM = 3*LANCHA_SIZE;

public:
    // Una matriz que almacena todos los disparos realizados por la CPU
    char  derribo[SIZE_TABLE][SIZE_TABLE];
    // Variable que almacena la cant de barcos que fueron disparados
    int portaaviones_hundidos = 0;
    int buques_hundidos = 0;
    int submarinos_hundidos = 0;
    int lanchas_hundidos = 0;


    // Inicializa los derribos con 0s
    Derribos(){
        for(int i=0; i<SIZE_TABLE; i++){
            for(int j=0; j<SIZE_TABLE; j++){
                derribo[i][j] = '~';
            }
        }
    }

    // Suma 1 a la cantidad de barcos hundidos
    char agregar(int position_x, int position_y, char ship){
        if (ship=='P'){
            portaaviones_hundidos += 1;
        } else if (ship=='B'){
            buques_hundidos += 1;
        } else if (ship=='S'){
            submarinos_hundidos += 1;
        } else if (ship=='L'){
            lanchas_hundidos += 1;
        }

        // Reemplaza la posicion en donde se disparo por la letra del barco
        // o por una "X"
        if (ship=='~' || ship=='X'){
            derribo[position_x][position_y] = 'X';
            return 'X';
        } else {
            derribo[position_x][position_y] = ship;
            return ship;
        }

    }

    // Impresion de la matriz de derribos
    void imprimir(){
        for(int i=0; i<SIZE_TABLE; i++){
            for(int j=0; j<SIZE_TABLE; j++){
                cout << "[" << derribo[i][j] << "]";
            }
        cout << endl;
        }
    }

    // Impresion de la cantidad de barcos hundidos
    void imprimir_barcos_hundidos(){
        cout << "Portaaviones hundidos: " << portaaviones_hundidos/PORTAAVIONES_SIZE << endl;
        cout << "Buques hundidos: " << buques_hundidos/BUQUE_SIZE << endl;
        cout << "Submarinos hundidos: " << submarinos_hundidos/SUBMARINO_SIZE << endl;
        cout << "Lanchas hundidas: " << lanchas_hundidos/LANCHA_SIZE << endl;
    }

};

/*int main(){
    // Creacion de la matriz derribo
    Derribos derribo;

    cout << endl;
    derribo.agregar(0, 0, 'S');
    derribo.agregar(0, 1, 'S');
    derribo.agregar(0, 2, 'S');
    derribo.imprimir_barcos_hundidos();
    derribo.imprimir();

    return 0;
}*/
