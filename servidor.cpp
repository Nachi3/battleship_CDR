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

    string Recibir()
    {
      recv(client, buffer, sizeof(buffer), 0);
      cout << "El cliente dice: " << buffer << endl;
      memset(buffer, 0, sizeof(buffer));
      return "";
    }
    void Enviar()
    {
        cout<<"Escribe el mensaje a enviar: ";
        cin>>this->buffer;
        send(client, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        cout << "Mensaje enviado!" << endl;
    }
    void CerrarSocket()
    {
        close(client);
        cout << "Socket cerrado, cliente desconectado." << endl;
    }
};



int main()
{
  Server *Servidor = new Server();
  while(true)
  {
     Servidor->Recibir();
     Servidor->Enviar();
  }

}

