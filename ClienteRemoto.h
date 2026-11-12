#ifndef CLIENTEREMOTO_H
#define CLIENTEREMOTO_H
#include <iostream>
#include <string>

using namespace std;

class ClienteRemoto {
private:
	string nombre;
	string ipServidor;
	int puerto;

public:
	ClienteRemoto(string nombre, string ipServidor, int puerto);

	void enviarTrama(string trama);
};

#endif
