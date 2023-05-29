// uso de librerias
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace std;

class Client{
public:
    //Creacion de variables a utilizar
    int server;
    struct sockaddr_in address;
    char buffer[1024];
    char board[15][15];
    // conexion a puerto del servidor
    Client(int PORT, char *IP)
    {
        // reset del buffer
        memset(buffer, 0, sizeof(buffer));
        cout<<"Conectando al servidor..."<<endl<<endl;
        // conexion a un puerto y servidor
        server = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_port = htons(PORT);
        inet_pton(AF_INET, IP, &address.sin_addr);
        // conexion al servidor
        if(connect(server, (struct sockaddr*)&address, sizeof(address)) < 0){
            cout << "No se logro conexion al Servidor!" << endl;
        }else{
            cout << "Conectado al Servidor!" << endl;
        }
        
    }
    // funcion para enviar mensajes al servidor
    void Enviar()
    {
        // reset de buffer
        memset(buffer, 0, sizeof(buffer));
        cin>>this->buffer;
        send(server, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer)); 
    }
    // Funcion para recibir mensajes del servidor
    char Recibir()
    {
        // reset del buffer
        memset(buffer, 0, sizeof(buffer));
        recv(server, buffer, sizeof(buffer), 0);
        cout << "El servidor dice: " << buffer << endl;
        char temp = buffer[0];
        memset(buffer, 0, sizeof(buffer));
        return temp;
    }

    //Funcion para transformar el mensaje entrante en un entero
    int RecibirNumero() {
        memset(buffer, 0, sizeof(buffer));
        recv(server, buffer, sizeof(buffer), 0);
        int numero = atoi(buffer); // Convertir el mensaje recibido a un entero
        memset(buffer, 0, sizeof(buffer));
        return numero;
    }

    // Cerrar socket del cliente
    void CerrarSocket()
    {
       close(server);
       cout << "Socket cerrado." << endl << endl;
    }
    //Funcion para recibir los tableros del battleship
    void RecibirMatriz(char board[][15]) {
        memset(board, 0, sizeof(char) * 15 * 15);
        char mensaje[15 * 15];
        recv(server, mensaje, sizeof(char) * 15 * 15, 0);
        // Convertir el mensaje recibido en una matriz de caracteres
        int k = 0;
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                board[i][j] = mensaje[k++];
            }
        }
    }
};



int main(int argc, char const* argv[])
{
    // Creacion de socket cliente y envio y recepcion de priemeros mensajes con el servidor
    cout << "Ingrese IP servidor (con puntos): ";
    char ipserv[20];
    cin >> ipserv;
    cout << "Ingrese el Puerto del servidor: ";
    int puerto;
    cin >> puerto;
    Client* Cliente = new Client(puerto, ipserv);
    Cliente->Recibir();
    Cliente->Recibir();
    Cliente->Recibir();
    // Proceso de jugado
    while(true)
    {
        // Variables que almacenan el tablero del jugador y los disparos realizados a la CPU
        char board[15][15];
        char boardcpu[15][15];
        // Recepcion de matriz de la cpu
        cout << "TABLERO CPU" << endl;
        Cliente->RecibirMatriz(boardcpu);
        // Impresion de tablero
        printf("\n    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14\n");
        printf("   ---------------------------------------------\n");
        for(int i=0; i<15; i++){
            printf("%2d|", i);
            for(int j=0; j<15; j++){
                if (boardcpu[i][j]=='0'){
                    cout << "[" << "~" << "]";
                }else{
                    cout << "[" << boardcpu[i][j] << "]";
                }
                
            }
            cout << endl;
        }

        cout << "\nTABLERO Jugador" << endl;
        Cliente->RecibirMatriz(board);
        // Impresion de tablero
        printf("\n    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14\n");
        printf("   ---------------------------------------------\n");
        for(int i=0; i<15; i++){
            printf("%2d|", i);
            for(int j=0; j<15; j++){
                if (board[i][j]==' '){
                    cout << "[" << "~" << "]";
                }else{
                    cout << "[" << board[i][j] << "]";
                }
                
            }
            cout << endl;
        }
        // Disparo del jugador
        cout << "\nDisparame\nPosicion x: ";
        sleep(0.5);
        Cliente->Enviar();
        cout << "Posicion y: ";
        sleep(0.5);
        Cliente->Enviar();
        
        // Recepcion del disparo de la CPU
        cout << "La cpu disparo en " << endl;
        cout << "x : " ;
        sleep(0.5);
        int  numrecv = Cliente->RecibirNumero();
        cout << numrecv;
        cout << "\ny : ";
        sleep(0.5);        
        numrecv = Cliente->RecibirNumero();
        cout << numrecv;
        sleep(1);
        int finalize = Cliente->RecibirNumero();
        //cout << finalize << endl;
        system("clear");
        if (finalize == 1){
            cout << "Felicidades, ganaste";
            Cliente->CerrarSocket();
        } else if(finalize==2){
            cout << "Lastima, la cpu gano";
            Cliente->CerrarSocket();
        }
    }
}
