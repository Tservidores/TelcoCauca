#ifndef SERVIDORCENTRAL_H
#define SERVIDORCENTRAL_H
#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

class ServidorCentral {
private:
	int puerto;
	SOCKET socketServidor;

public:
	ServidorCentral(int puerto);

	void iniciar();
	void aceptarClientes(int cantidadClientes);
	void atenderCliente(SOCKET cliente, int numeroCliente);

	~ServidorCentral();
};

#endif
