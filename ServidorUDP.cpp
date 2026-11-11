#include <iostream>
#include <string>
#include <winsock2.h>
#include "ServidorUDP.h"
#include "TramaTelemetria.h"
#include "ExcepcionRedUDP.h"
#include "Consola.h"

using namespace std;

ServidorUDP::ServidorUDP(int puerto) {
	this->puerto = puerto;
	this->socketUDP = INVALID_SOCKET;
}

void ServidorUDP::iniciar() {
	// SOCK_DGRAM = UDP (no usa listen ni accept)
	socketUDP = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketUDP == INVALID_SOCKET) {
		throw ExcepcionRedUDP("No se pudo crear el socket UDP", WSAGetLastError());
	}

	sockaddr_in direccion = {};
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = INADDR_ANY;
	direccion.sin_port = htons(puerto);

	if (bind(socketUDP, (sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
		throw ExcepcionRedUDP("Error en bind() UDP", WSAGetLastError());
	}

	// Timeout de 3 segundos: si no llega nada, recvfrom deja de esperar
	DWORD tiempo = 3000;
	setsockopt(socketUDP, SOL_SOCKET, SO_RCVTIMEO, (char*)&tiempo, sizeof(tiempo));

	registrarEventoSeguro("[Servidor UDP] Esperando telemetria en el puerto " + to_string(puerto));
}

void ServidorUDP::escuchar() {
	int tramasRecibidas = 0;

	try {
		while (true) {
			TramaTelemetria trama;
			sockaddr_in cliente;
			int longitud = sizeof(cliente);

			int bytes = recvfrom(socketUDP, (char*)&trama, sizeof(trama), 0, (sockaddr*)&cliente, &longitud);

			if (bytes == SOCKET_ERROR) {
				int codigo = WSAGetLastError();
				if (codigo == WSAETIMEDOUT) {
					throw ExcepcionRedUDP("TIMEOUT: no llegaron mas datagramas", codigo);
				}
				throw ExcepcionRedUDP("Error en recvfrom()", codigo);
			}

			tramasRecibidas++;
			registrarEventoSeguro("[Servidor UDP] Estacion " + to_string(trama.idEstacion)
								  + " (" + string(trama.tipoDispositivo) + ") Temperatura: "
								  + to_string(trama.temperatura) + " | Humedad: " + to_string(trama.humedad));
		}
	}
	catch (const ExcepcionRedUDP& e) {
		registrarEventoSeguro(string("[Servidor UDP] ") + e.what());
		registrarEventoSeguro("[Servidor UDP] Tramas recibidas: " + to_string(tramasRecibidas)
							  + ". El sistema sigue funcionando.");
	}
	catch (const exception& e) {
		registrarEventoSeguro(string("[Servidor UDP] Error: ") + e.what());
	}
}

ServidorUDP::~ServidorUDP() {
	if (socketUDP != INVALID_SOCKET) {
		closesocket(socketUDP);
	}
}
