/*Codigo que implementa la clase Server, este contiene el socket del servidor
y emplea metodos para el envio y recepcion de mensajes*/
#include <iostream>
#include <winsock2.h>
#include <time.h>
#pragma comment(lib, "libws2_32.a")

using namespace std;

class Client{
public:
    WSADATA WSAData; // Para guardar informaci�n de inicializaci�n de sockets
    SOCKET server; // Para definir un tipo de dato y guardar el socket
    SOCKADDR_IN addr; // Para almacenar informaci�n de la ip
    char buffer[1024];
    Client()
    {
        cout<<"Conectando al servidor..."<<endl<<endl;
        // Inicializacion la biblioteca winsock
        WSAStartup(MAKEWORD(2,0), &WSAData);
        /* Creacion del socket del cliente
        ** AF_INET para la conexion entre diferentes hosts (IPv4)
        ** SOCK_STREAM hace referencia al protocolo TCP
        ** 0 referencia al valor del protocolo de internet (IP)*/
        server = socket(AF_INET, SOCK_STREAM, 0);

        // Asignaci�n de la direcci�n IP del servidor al que el cliente desea conectarse
        addr.sin_addr.s_addr = inet_addr("Direcci�n IP aqu�");
        addr.sin_family = AF_INET;
        // Se establece el puerto que el cliente se conectar� al sevidor
        addr.sin_port = htons(5555);
        // Se inicia la conexi�n considerando el socket y la direcci�n ip con su tama�o.
        connect(server, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr));
        cout << "Conectado al Servidor!" << endl;
    }
    void Enviar()
    {
        cout<<"Escribe el mensaje a enviar: ";
        cin>>this->buffer;
        // Se env�an los datos al servidor
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
        closesocket(server);
        WSACleanup();
        cout << "Socket cerrado." << endl << endl;
    }
};


int main()
{
    Client* Cliente = new Client();
    while(true)
    {
        Cliente->Enviar();
        Sleep(1000);
        Cliente->Recibir();
        Sleep(1000);
    }
}
