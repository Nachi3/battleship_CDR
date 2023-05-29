// first commit
#include <iostream>
#include <limits>
#include <unistd.h>
#include "tablero.cpp"
#include "Derribos.h"
//#include "Mapadecalor.cpp"
#include "servidor.cpp"

using namespace std;

//void target(Battleship& myBattleship, int x, int y, char letra, Derribos& myDerribos, MapaCalor& myMapaCalor);

int main(){
    Battleship mybattleship;
    Battleship yourbattleship;
    mybattleship.GenerarTableroAleatorio();
    //mybattleship.MostrarTablero();
    Server *Servidor = new Server(); 
    Derribos myDerribo;
    Derribos yourDerribos;
    //MapaCalor myMapaCalor;

    Servidor->Enviar("¿Como desea generar su tablero?:");
    Servidor->Enviar("\n(1) Aleatoriamente\n(2) Manualmente\nEliga una opcion: ");
    char temp = Servidor->Recibir();
    int option = temp - '0';
    while (option!=1 && option!=2) {
        cout << "Opción inválida. Por favor, elija '1' o '2': ";
        temp = Servidor->Recibir();
        int option = temp - '0';
    }

    if (option == 1){
        yourbattleship.GenerarTableroAleatorio();
    } else {
        yourbattleship.GenerarTableroManual();
    }
    bool winserver = false;
    bool winclient = false;
    Servidor->Enviar("Matriz Generada:\n");
    sleep(0.5);
    Servidor->Enviar("Que comience el juego!");

    while(winserver==false && winclient==false){
        // Envio de tableros a cliente

        Servidor->EnviarMatriz(myDerribo.derribo);
        Servidor->EnviarMatriz(yourbattleship.board);
        mybattleship.MostrarTablero();
        // Recepcion disparos cliente
        int position_x = Servidor->RecibirNumero();
        int position_y = Servidor->RecibirNumero();
        myDerribo.agregar(position_x, position_y, mybattleship.shot(position_x, position_y));
        
        //Disparo de cpu
        int x = rand() % 15;
        int y = rand() % 15;
        while(yourDerribos.derribo[x][y]!='0' && x>=0 && y<15){
            x = rand() % 15;
            y = rand() % 15;
        }
        yourDerribos.agregar(x, y, yourbattleship.shot(x, y));
        string numeroString = to_string(x);
        sleep(0.5);
        Servidor->Enviar(numeroString.c_str());
        numeroString = to_string(y);
        sleep(0.5);
        Servidor->Enviar(numeroString.c_str());
        
        // condicion de victoria
        if (mybattleship.ganar() == 1){
            winserver = true;
            Servidor->CerrarSocket();
        } else if (yourbattleship.ganar() == 1){
            winclient = true;
            Servidor->CerrarSocket();
        } 
        //mybattleship.MostrarTablero();
    }
    if(winclient==true){
        cout << "\nGANASTE!";
    }else{
        cout << "\nPERDISTE!";
    }
    Servidor->CerrarSocket();
    return 0;

}

/*
    //myMapaCalor.Imprimir();
    myMapaCalor.mapahunt(myDerribo);
    //myMapaCalor.Imprimir();
    //myDerribo.imprimir();

    while(mybattleship.ganar()==0){
        MapaCalor myMapaCalor;
        myMapaCalor.mapahunt(myDerribo);
        int mayor=myMapaCalor.m[0][0];
        int x=0,y=0;
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                if(mayor<myMapaCalor.m[i][j]){
                    mayor=myMapaCalor.m[i][j];
                }
            }
        }
        myMapaCalor.Imprimir();
        //sleep(2);
        myDerribo.imprimir();
        cout<<endl;
        while(mayor!=myMapaCalor.m[x][y]){
            x=rand() % 15;
            y=rand() % 15;
        }

        char letra=myDerribo.agregar(x,y,mybattleship.shot(x,y));

        if(letra!='X' && letra!='0'){
            target(mybattleship,x,y,letra,myDerribo,myMapaCalor);
        }

        myDerribo.imprimir();
    }

    cout << "you win" << endl;
*/

/*
void target(Battleship& myBattleship, int x, int y, char letra, Derribos& myDerribos, MapaCalor& myMapaCalor){
        if(letra!='X' && letra!=' '){
            int num,tamano;
            if(letra=='P'){
                num=myDerribos.portaaviones_hundidos;
                tamano=myDerribos.getPortaavionesSize();
            }else if(letra=='B'){
                num=myDerribos.buques_hundidos;
                tamano=myDerribos.getBuquesSize();
                if (num>=tamano){
                    num = num % 4;
                }
            }else if(letra=='S'){
                num=myDerribos.submarinos_hundidos;
                tamano=myDerribos.getSubmarinosSize();
                if (num>=tamano){
                    num = num % 3;
                }
            }else{
                num=myDerribos.lanchas_hundidos;
                tamano=myDerribos.getLanchasSize();
                if (num>=tamano){
                    num = num % 1;
                }
            }
            while(num<tamano){
                MapaCalor myMapaCalor;
                myMapaCalor.mapatarget(x,y,letra,myDerribos,15);
                int mayor=myMapaCalor.m[0][0];
                for(int i=0;i<15;i++){
                    for(int j=0;j<15;j++){
                        if(mayor<myMapaCalor.m[i][j]){
                            mayor=myMapaCalor.m[i][j];
                        }
                    }
                }
                while(mayor!=myMapaCalor.m[x][y]){
                    x=rand() % 15;
                    y=rand() % 15;
                }
                int hit=myDerribos.agregar(x,y,myBattleship.shot(x,y));
                if(letra!=hit && hit!='X'){
                    target(myBattleship,x,y,hit,myDerribos,myMapaCalor);
                }
                if(letra=='P'){
                    num=myDerribos.portaaviones_hundidos;
                }else if(letra=='B'){
                    num=myDerribos.buques_hundidos;
                }else if(letra=='S'){
                    num=myDerribos.submarinos_hundidos;
                }else{
                    num=myDerribos.lanchas_hundidos;
                }
            }
        }
        
}
*/
