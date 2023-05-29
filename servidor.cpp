/* odigo que implementa la clase Server, esta contiene el socket del servidor
y emplea métodos para el envio y recepción de mensajes*/
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace std;

class Server{
public:
    // Definicion de variables
    int server, client; int opt = 1;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];
    Server()
    {
        memset(buffer, 0, sizeof(buffer));
        // Creando el socket
        if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forzar la conexión del socket al puerto 8080
        if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                       &opt, sizeof(opt))){
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(5555);

        // Establecer la conexion
        bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        // socket en escucha por alguna conexion entrante
        listen(server, 0);

        cout << "Escuchando para conexiones entrantes." << endl;
        int clientAddrSize = sizeof(clientAddr);
        if((client = accept(server, (struct sockaddr*)&clientAddr, (socklen_t*)&clientAddrSize)) < 0)
        {
            cout << "Cliente conectado!" << endl;
        }
    }

    char Recibir()
    {
        memset(buffer, 0, sizeof(buffer));
        recv(client, buffer, sizeof(buffer), 0);
        cout << "El cliente dice: " << buffer << endl;
        char temp = buffer[0];
        memset(buffer, 0, sizeof(buffer));
        return temp;
    }

    int RecibirNumero() {
        memset(buffer, 0, sizeof(buffer));
        recv(client, buffer, sizeof(buffer), 0);
        int numero = atoi(buffer); // Convertir el mensaje recibido a un entero
        memset(buffer, 0, sizeof(buffer));
        return numero;
    }

    void Enviar(const char* mensaje)
    {
        memset(buffer, 0, sizeof(buffer));
        send(client, mensaje, strlen(mensaje), 0);
        cout << "Mensaje enviado al cliente." << endl;
        memset(buffer, 0, sizeof(buffer));
    }

    void EnviarMatriz(char board[][15]) {
        memset(buffer, 0, sizeof(buffer));
        // Convertir la matriz a una cadena de caracteres
        std::string mensaje;
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                mensaje += board[i][j];
            }
        }
        int index = 0;
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                cout << mensaje[index] << " ";
                index++;
            }
            cout << endl;
        }
        // Enviar el mensaje al cliente
        send(client, mensaje.c_str(), mensaje.length(), 0);
        //memset(board, 0, sizeof(char) * 15 * 15);
        cout << "Matriz enviada al cliente." << endl;
    }

    void CerrarSocket()
    {
        close(client);
        cout << "Socket cerrado, cliente desconectado." << endl;
    }
};


/*
int main()
{
  Server *Servidor = new Server();
  while(true)
  {
     Servidor->Recibir();
     Servidor->Enviar();
  }

}
*/
