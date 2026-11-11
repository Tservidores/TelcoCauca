#ifndef CLIENTEUDP_H
#define CLIENTEUDP_H
#include <iostream>
#include <string>
#include "TramaTelemetria.h"

using namespace std;

class ClienteUDP {
private:
	string ipServidor;
	int puerto;

public:
	ClienteUDP(string ipServidor, int puerto);

	void enviarTrama(TramaTelemetria trama);
};

#endif
