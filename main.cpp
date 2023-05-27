// first commit
#include <iostream>
#include "tablero.cpp"

using namespace std;

int main(){
    cout << "Hola mundo";
    int option;
    Battleship mybattleship;

    cout << "\n�Como desea generar su tablero?:";
    cout << "\n(1) Aleatoriamente\n(2) Manualmente\nEliga una opcion: ";
    cin >> option;

    if (option == 1){
        mybattleship.GenerarTableroAleatorio();
    } else if (option == 2) {
        mybattleship.GenerarTableroManual();
    } else {
        cout << "\nIngrese una opcion valida";
    }

    bool win = false;
    while(!win){
        int position_x, position_y;
        cout << "\nDisparame\nPosicion x: ";
        cin >> position_x;
        cout << "Posicion y: ";
        cin >> position_y;
        mybattleship.shot(position_x, position_y);

        if (mybattleship.ganar() == 1){
            win = true;
        }
        //system("cls");
        mybattleship.MostrarTablero();
    }
    cout << "\nGANASTE!";
    return 0;
}

