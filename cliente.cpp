#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace std;

class Client{
public:
    //WSADATA WSAData;
    int server;
    struct sockaddr_in address;
    char buffer[1024];
    char board[15][15];
    Client()
    {
        memset(buffer, 0, sizeof(buffer));
        cout<<"Conectando al servidor..."<<endl<<endl;
        //WSAStartup(MAKEWORD(2,0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);
        //address.sin_addr.s_addr = inet_pton(AF_INET, "192.168.1.197", &address.sin_addr);
        address.sin_family = AF_INET;
        address.sin_port = htons(5555);
        inet_pton(AF_INET, "172.18.242.229", &address.sin_addr);
        connect(server, (struct sockaddr*)&address, sizeof(address));
        cout << "Conectado al Servidor!" << endl;
    }
    void Enviar()
    {
        //cout<<"Escribe el mensaje a enviar: ";
        memset(buffer, 0, sizeof(buffer));
        cin>>this->buffer;
        send(server, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        cout << "Mensaje enviado!" << endl;
    }
    char Recibir()
    {
        memset(buffer, 0, sizeof(buffer));
        recv(server, buffer, sizeof(buffer), 0);
        cout << "El cliente dice: " << buffer << endl;
        char temp = buffer[0];
        memset(buffer, 0, sizeof(buffer));
        return temp;
    }

    int RecibirNumero() {
        memset(buffer, 0, sizeof(buffer));
        recv(server, buffer, sizeof(buffer), 0);
        int numero = atoi(buffer); // Convertir el mensaje recibido a un entero
        memset(buffer, 0, sizeof(buffer));
        return numero;
    }

    void CerrarSocket()
    {
       close(server);
       //WSACleanup();
       cout << "Socket cerrado." << endl << endl;
    }
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
    Client* Cliente = new Client();
    Cliente->Recibir();
    Cliente->Recibir();
    Cliente->Enviar();
    Cliente->Recibir();
    Cliente->Recibir();
    while(true)
    {
        char board[15][15];
        char boardcpu[15][15];
        //system("clear");
        Cliente->RecibirMatriz(boardcpu);
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


        Cliente->RecibirMatriz(board);
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
        cout << "\nDisparame\nPosicion x: ";
        Cliente->Enviar();
        cout << "Posicion y: ";
        Cliente->Enviar();
        cout << "La cpu disparo en " << endl;
        cout << "x : " ;
        int  numrecv = Cliente->RecibirNumero();
        cout << numrecv;
        cout << "\ny : ";        
        numrecv = Cliente->RecibirNumero();
        cout << numrecv;
        sleep(2);
        
    }
}
