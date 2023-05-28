/*Codigo que implementa la clase Cliente, este contiene el socket del servidor
y emplea metodos para el envio y recepcion de mensajes*/
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace std;

class Client{
public:
    // Definicion de variables
    int server;
    struct sockaddr_in address;
    char buffer[1024];
    Client()
    {
        cout<<"Conectando al servidor..."<<endl<<endl;
        /* Creacion del socket del cliente
        ** AF_INET para la conexion entre diferentes hosts (IPv4)
        ** SOCK_STREAM hace referencia al protocolo TCP
        ** 0 referencia al valor del protocolo de internet (IP)*/
        server = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_port = htons(5555);
        inet_pton(AF_INET, "192.168.56.1", &address.sin_addr);
        connect(server, (struct sockaddr*)&address, sizeof(address));
        cout << "Conectado al Servidor!" << endl;
    }
    void Enviar()
    {
    	// Se envían los datos al servidor
        cout<<"Escribe el mensaje a enviar: ";
        cin>>this->buffer;
        send(server, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        cout << "Mensaje enviado!" << endl;
    }
    void Recibir()
    {
    	// Se recibe los datos del servidor
        recv(server, buffer, sizeof(buffer), 0);
        cout << "El servidor dice: " << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
    }
    void CerrarSocket()
    {
       // Cierra socket del servidor
       close(server);
       cout << "Socket cerrado." << endl << endl;
    }
};


int main(int argc, char const* argv[])
{
    Client* Cliente = new Client();
    while(true)
    {
        Cliente->Enviar();
        //Sleep(1000);
        Cliente->Recibir();
        //Sleep(1000);
    }
}
