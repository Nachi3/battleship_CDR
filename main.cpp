// first commit
#include <iostream>
#include <windows.h>
#include "tablero.cpp"

using namespace std;

int main(){
    cout << "Hola mundo";
    int option = 2;
    Battleship mybattleship;

    cout << "\n¿Como desea generar su tablero?:";
    cout << "\n(1) Aleatoriamente\n(2) Manualmente\nEliga una opcion: ";

    while(option != 1) {
        cin >> option;
        if (option == 1){
            mybattleship.GenerarTableroAleatorio();
        } else {
            cout << "\nIngrese una opcion valida: ";
        }
    }

    return 0;
}

