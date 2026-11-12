#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <stdexcept>
#include <winsock2.h>
#include "ServidorCentral.h"
#include "SerializadorTramas.h"
#include "ExcepcionSocket.h"
#include "Consola.h"

using namespace std;

ServidorCentral::ServidorCentral(int puerto) {
	this->puerto = puerto;
	this->socketServidor = INVALID_SOCKET;
}

void ServidorCentral::iniciar() {
	// 1. socket(): crea el socket TCP
	socketServidor = socket(AF_INET, SOCK_STREAM, 0);
	if (socketServidor == INVALID_SOCKET) {
		throw ExcepcionSocket("No se pudo crear el socket del servidor");
	}

	sockaddr_in direccion = {};
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = INADDR_ANY;
	direccion.sin_port = htons(puerto);

	// 2. bind(): une el socket con el puerto
	if (bind(socketServidor, (sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
		throw ExcepcionSocket("Error en bind() del puerto " + to_string(puerto));
	}

	// 3. listen(): el servidor empieza a escuchar
	if (listen(socketServidor, 5) == SOCKET_ERROR) {
		throw ExcepcionSocket("Error en listen()");
	}

	registrarEventoSeguro("[Servidor TCP] Escuchando en el puerto " + to_string(puerto));
}

void ServidorCentral::aceptarClientes(int cantidadClientes) {
	vector<thread> hilosClientes;

	try {
		for (int i = 1; i <= cantidadClientes; i++) {
			// 4. accept(): espera un cliente y devuelve un socket nuevo solo para el
			SOCKET cliente = accept(socketServidor, nullptr, nullptr);
			if (cliente == INVALID_SOCKET) {
				throw ExcepcionSocket("Error en accept()");
			}

			registrarEventoSeguro("[Servidor TCP] Cliente " + to_string(i) + " conectado");

			// Un hilo nuevo para atender a cada cliente
			hilosClientes.push_back(thread(&ServidorCentral::atenderCliente, this, cliente, i));
		}
	}
	catch (const ExcepcionSocket& e) {
		registrarEventoSeguro(string("[Servidor TCP] ") + e.what());
	}

	for (int i = 0; i < hilosClientes.size(); i++) {
		hilosClientes[i].join();
	}
}

void ServidorCentral::atenderCliente(SOCKET cliente, int numeroCliente) {
	try {
		char buffer[1024];

		int bytesRecibidos = recv(cliente, buffer, sizeof(buffer) - 1, 0);

		if (bytesRecibidos == SOCKET_ERROR) {
			throw ExcepcionSocket("Error en recv() con el cliente " + to_string(numeroCliente));
		}
		if (bytesRecibidos == 0) {
			throw ExcepcionSocket("El cliente " + to_string(numeroCliente) + " cerro la conexion");
		}

		buffer[bytesRecibidos] = '\0';

		registrarEventoSeguro("[Servidor TCP] Trama recibida del cliente " + to_string(numeroCliente)
							  + ": " + string(buffer));
		registrarEventoSeguro("[Servidor TCP] Deserializada: " + SerializadorTramas::deserializar(buffer));

		string respuesta = "ACK - trama recibida por el servidor";
		send(cliente, respuesta.c_str(), respuesta.size(), 0);
	}
	catch (const ExcepcionSocket& e) {
		registrarEventoSeguro(string("[Servidor TCP] ") + e.what());
	}
	catch (const exception& e) {
		registrarEventoSeguro(string("[Servidor TCP] Error: ") + e.what());
	}

	closesocket(cliente);
}

ServidorCentral::~ServidorCentral() {
	if (socketServidor != INVALID_SOCKET) {
		closesocket(socketServidor);
	}
}
