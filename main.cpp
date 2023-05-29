/*Uso de librerias*/
#include <iostream>
#include <limits>
#include <unistd.h>
#include <cstdlib>
#include "tablero.cpp"
#include "Derribos.h"
#include "servidor.cpp"

using namespace std;

int main(){
    std::srand(std::time(nullptr));
    // Creacion del battleship para el cpu
    Battleship mybattleship;
    // Creacion del battleship para el jugador
    Battleship yourbattleship;
    // Generacion tablero aleatorio para cpu y jugador
    mybattleship.GenerarTableroAleatorio();
    sleep(1);
    yourbattleship.GenerarTableroAleatorio();
    //mybattleship.MostrarTablero();
    int PORT;
    cout << "Ingrese el puerto: ";
    cin >> PORT;
    Server *Servidor = new Server(PORT); 
    
    // Tabla de derribos para mostrar al jugador y para que juegue el cpu
    Derribos myDerribo;
    Derribos yourDerribos;
    
    //Primeros mensajes para la generacion de la tabla del jugador, de forma aleatoria o manual
    Servidor->Enviar("Bienvenido a battleship");
    // variables para almacenar la victoria del cpu o del jugador
    bool winserver = false;
    bool winclient = false;
    Servidor->Enviar("Matriz Generada:\n");
    sleep(0.5);
    // Mensaje de comienzo
    Servidor->Enviar("Que comience el juego!");

    // ejecucion del juego mientras nadie haya ganado
    while(winserver==false && winclient==false){
        // Envio de tableros a cliente
        Servidor->EnviarMatriz(myDerribo.derribo);
        Servidor->EnviarMatriz(yourbattleship.board);
        mybattleship.MostrarTablero();
        // Recepcion disparos cliente

        sleep(0.5);
        int position_x = Servidor->RecibirNumero();
        sleep(0.5);
        int position_y = Servidor->RecibirNumero();
        // agregar disparo del cliente al tablero enemigo
        myDerribo.agregar(position_x, position_y, mybattleship.shot(position_x, position_y));
        
        //Disparo aleatorio de cpu
        int x = std::rand() % 15;
        sleep(1);
        int y = std::rand() % 15;
        while(yourDerribos.derribo[x][y]!='0' && (x>=0 && x<15) && (y>=0 && y<15)){
            x = std::rand() % 15;
            sleep(1);
            y = std::rand() % 15;
        }
        // Envio de disparos
        yourDerribos.agregar(x, y, yourbattleship.shot(x, y));
        string numeroString = to_string(x);
        const char* numer = numeroString.c_str();
        sleep(0.5);
        Servidor->Enviar(numer);
        numeroString = to_string(y);
        numer = numeroString.c_str();
        sleep(0.5);
        Servidor->Enviar(numer);
        sleep(1);
        // condicion de victoria, si alguno gana, se cierra el socket
        if (mybattleship.ganar() == 1){
            winserver = true;
            const char* aux = "2";
            Servidor->Enviar(aux);
            Servidor->CerrarSocket();
        } else if (yourbattleship.ganar() == 1){
            winclient = true;
            const char* aux = "1";
            Servidor->Enviar(aux);
            Servidor->CerrarSocket();
        } else {
            const char* aux = "0";
            Servidor->Enviar(aux);
        } 
        
    }

    //Mensaje post finalizacion del socket
    if(winclient==true){
        cout << "\nHa ganado el cliente";
    }else{
        cout << "\nHa ganado el servidor";
    }

    return 0;

}
