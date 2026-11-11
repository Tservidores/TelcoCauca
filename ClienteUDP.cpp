#include <iostream>
#include <string>
#include <winsock2.h>
#include "ClienteUDP.h"
#include "ExcepcionRedUDP.h"
#include "Consola.h"

using namespace std;

ClienteUDP::ClienteUDP(string ipServidor, int puerto) {
	this->ipServidor = ipServidor;
	this->puerto = puerto;
}

void ClienteUDP::enviarTrama(TramaTelemetria trama) {
	SOCKET cliente = socket(AF_INET, SOCK_DGRAM, 0);
	if (cliente == INVALID_SOCKET) {
		throw ExcepcionRedUDP("No se pudo crear el socket del cliente UDP", WSAGetLastError());
	}

	sockaddr_in destino = {};
	destino.sin_family = AF_INET;
	destino.sin_port = htons(puerto);
	destino.sin_addr.s_addr = inet_addr(ipServidor.c_str());

	// sendto(): envia la estructura completa como bytes, sin conectarse antes
	int bytes = sendto(cliente, (char*)&trama, sizeof(trama), 0, (sockaddr*)&destino, sizeof(destino));

	closesocket(cliente);

	if (bytes == SOCKET_ERROR) {
		throw ExcepcionRedUDP("Error en sendto()", WSAGetLastError());
	}

	registrarEventoSeguro("[Cliente UDP] Trama de la estacion " + to_string(trama.idEstacion)
						  + " enviada (" + to_string(bytes) + " bytes)");
}
