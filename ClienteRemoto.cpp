#include <iostream>
#include <string>
#include <stdexcept>
#include <winsock2.h>
#include "ClienteRemoto.h"
#include "ExcepcionSocket.h"
#include "Consola.h"

using namespace std;

ClienteRemoto::ClienteRemoto(string nombre, string ipServidor, int puerto) {
	this->nombre = nombre;
	this->ipServidor = ipServidor;
	this->puerto = puerto;
}

void ClienteRemoto::enviarTrama(string trama) {
	SOCKET cliente = INVALID_SOCKET;

	try {
		// 1. socket(): crea el socket del cliente
		cliente = socket(AF_INET, SOCK_STREAM, 0);
		if (cliente == INVALID_SOCKET) {
			throw ExcepcionSocket(nombre + ": no se pudo crear el socket");
		}

		sockaddr_in direccion = {};
		direccion.sin_family = AF_INET;
		direccion.sin_port = htons(puerto);
		direccion.sin_addr.s_addr = inet_addr(ipServidor.c_str());

		// 2. connect(): se conecta al servidor
		if (connect(cliente, (sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
			throw ExcepcionSocket(nombre + ": no se pudo conectar a " + ipServidor + ":" + to_string(puerto));
		}

		// 3. send(): envia la trama
		if (send(cliente, trama.c_str(), trama.size(), 0) == SOCKET_ERROR) {
			throw ExcepcionSocket(nombre + ": error al enviar la trama");
		}
		registrarEventoSeguro("[" + nombre + "] Trama enviada");

		// 4. recv(): espera la respuesta del servidor
		char buffer[1024];
		int bytesRecibidos = recv(cliente, buffer, sizeof(buffer) - 1, 0);
		if (bytesRecibidos <= 0) {
			throw ExcepcionSocket(nombre + ": el servidor no respondio");
		}

		buffer[bytesRecibidos] = '\0';
		registrarEventoSeguro("[" + nombre + "] Respuesta: " + string(buffer));
	}
	catch (const ExcepcionSocket& e) {
		registrarEventoSeguro(string("[Cliente] ") + e.what());
	}
	catch (const exception& e) {
		registrarEventoSeguro(string("[Cliente] Error: ") + e.what());
	}

	// 5. closesocket(): siempre se cierra el socket al final
	if (cliente != INVALID_SOCKET) {
		closesocket(cliente);
	}
}
