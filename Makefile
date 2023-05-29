#Compilar los dos programas
all: AMBOS

#Compila el main y cliente:
AMBOS:
	g++ main.cpp -o main # Compila main.cpp y crea el ejecutable main
	g++ cliente.cpp -o cliente # Compila main.cpp y crea el ejecutable cliente

#Compila el main

servidor.cpp:
	g++ main.cpp -o main

#Compila el cliente

cliente.cpp:
	g++ cliente.cpp -o cliente

# Limpia los archivos ejecutables
clean: 
	rm main
	rm cliente
