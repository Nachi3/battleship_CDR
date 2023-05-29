// Definicion de la clase derribos, esta almacena los disparos de cada jugador
#include "Derribos.h"

using namespace std;
// Constructor
Derribos::Derribos() {
    for(int i=0; i<SIZE_TABLE; i++){
        for(int j=0; j<SIZE_TABLE; j++){
            derribo[i][j] = '0';
        }
    }
}
// Agrega un disparo a la matriz de derribos (X o la letra del barco)
char Derribos::agregar(int position_x, int position_y, char ship){
    if (ship=='P'){
        portaaviones_hundidos += 1;
    } else if (ship=='B'){
        buques_hundidos += 1;
    } else if (ship=='S'){
        submarinos_hundidos += 1;
    } else if (ship=='L'){
        lanchas_hundidos += 1;
    }

    if (ship=='0' || ship=='X'){
        derribo[position_x][position_y] = 'X';
        return 'X';
    } else {
        derribo[position_x][position_y] = ship;
        return ship;
    }
}
// Imprime la matriz de derribos
void Derribos::imprimir(){
    for(int i=0; i<SIZE_TABLE; i++){
        for(int j=0; j<SIZE_TABLE; j++){
            cout << "[" << derribo[i][j] << "]";
        }
    cout << endl;
    }
}
// Imprime cuantos barcos estan hundidos
void Derribos::imprimir_barcos_hundidos(){
    cout << "Portaaviones hundidos: " << portaaviones_hundidos/PORTAAVIONES_SIZE << endl;
    cout << "Buques hundidos: " << buques_hundidos/BUQUE_SIZE << endl;
    cout << "Submarinos hundidos: " << submarinos_hundidos/SUBMARINO_SIZE << endl;
    cout << "Lanchas hundidas: " << lanchas_hundidos/LANCHA_SIZE << endl;
}

// funciones getters
int Derribos::getPortaavionesNum(){
    return PORTAAVIONES_NUM;
}

int Derribos::getBuquesNum(){
    return BUQUE_NUM;
}

int Derribos::getSubmarinosNum(){
    return SUBMARINO_NUM;
}

int Derribos::getLanchasNum(){
    return LANCHAS_NUM;
}

int Derribos::getPortaavionesSize(){
    return PORTAAVIONES_SIZE;
}

int Derribos::getBuquesSize(){
    return BUQUE_SIZE;
}

int Derribos::getSubmarinosSize(){
    return SUBMARINO_SIZE;
}

int Derribos::getLanchasSize(){
    return LANCHA_SIZE;
}
