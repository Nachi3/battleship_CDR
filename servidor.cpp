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
    struct sockaddr_in serverAddr, clientAddr; // variable de direcciones
    char buffer[1024];
    Server(int PORT)
    {
        memset(buffer, 0, sizeof(buffer));
        /*
        ** AF_INET para la conexion entre diferentes hosts (IPv4)
        ** SOCK_STREAM hace referencia al protocolo TCP
        ** 0 referencia al valor del protocolo de internet (IP)*/
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
        // Acepta conexiones en todas las interfaces de red disponibles
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);

        // Establecer la conexion
        bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        // socket en escucha por alguna conexion entrante
        listen(server, 0);
        cout << "Escuchando para conexiones entrantes." << endl;
        int clientAddrSize = sizeof(clientAddr);
        // Conexion con un jugador
        if((client = accept(server, (struct sockaddr*)&clientAddr, (socklen_t*)&clientAddrSize)) < 0)
        {
            cout << "Cliente conectado!" << endl;
        }
    }
    // Funcion para recibir mensajes del cliente
    char Recibir()
    {
        memset(buffer, 0, sizeof(buffer));
        recv(client, buffer, sizeof(buffer), 0);
        cout << "El cliente dice: " << buffer << endl;
        // Transformacion del mensaje a char
        char temp = buffer[0];
        memset(buffer, 0, sizeof(buffer));
        return temp;
    }
    // Funcion para recibir un entero del cliente
    int RecibirNumero() {
        memset(buffer, 0, sizeof(buffer));
        recv(client, buffer, sizeof(buffer), 0);
        int numero = atoi(buffer); // Convertir el mensaje recibido a un entero
        memset(buffer, 0, sizeof(buffer));
        return numero;
    }
    // Funcion para enviar mensajes al cliente
    void Enviar(const char* mensaje)
    {
        memset(buffer, 0, sizeof(buffer));
        send(client, mensaje, strlen(mensaje), 0);
        cout << "Mensaje enviado al cliente." << endl;
        memset(buffer, 0, sizeof(buffer));
    }
    // funcion para enviar la matriz al cliente
    void EnviarMatriz(char board[][15]) {
        memset(buffer, 0, sizeof(buffer));
        // Convertir la matriz a una cadena de caracteres
        std::string mensaje;
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                mensaje += board[i][j];
            }
        }
        // Enviar el mensaje al cliente
        send(client, mensaje.c_str(), mensaje.length(), 0);
        //memset(board, 0, sizeof(char) * 15 * 15);
        cout << "Matriz enviada al cliente." << endl;
    }
    // Funcion para cerrar el socket
    void CerrarSocket()
    {
        close(client);
        cout << "Socket cerrado, cliente desconectado." << endl;
    }
};

