/*Codigo que implementa la clase Server, este contiene el socket del servidor
y emplea metodos para el envio y recepcion de mensajes*/
#include <iostream>
#include <winsock2.h>

using namespace std;

class Server{
public:
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    char buffer[1024];
    Server()
    {
        // Inicializacion la biblioteca winsock
        WSAStartup(MAKEWORD(2,0), &WSAData);

        /* Creacion del socket del servidor
        ** AF_INET para la conexion entre diferentes hosts (IPv4)
        ** SOCK_STREAM hace referencia al protocolo TCP
        ** 0 referencia al valor del protocolo de internet (IP)*/
        if((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(5555);

        // Enlace del socket del servidor a una direccion IP y puerto
        bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        // Pone al servidor en modo pasivo, para la escuhca de una conexion entrante
        // El segundo parametro indica la cola de conexiones que puede tener
        listen(server, 3);

        cout << "Escuchando para conexiones entrantes." << endl;
        int clientAddrSize = sizeof(clientAddr);
        // Acepta una conexion entrante y establece el socket del cliente
        if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            cout << "Cliente conectado!" << endl;
        }
    }

    string Recibir()
    {
        // Recibe datos del cliente
        recv(client, buffer, sizeof(buffer), 0);
        cout << "El cliente dice: " << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
        return "";
    }
    void Enviar()
    {
        // Envia datos al cliente
        cout<<"Escribe el mensaje a enviar: ";
        cin>>this->buffer;
        send(client, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        cout << "Mensaje enviado!" << endl;
    }
    void CerrarSocket()
    {
        // Cierra socket del cliente
        closesocket(client);
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

