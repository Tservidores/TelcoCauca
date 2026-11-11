#include <iostream>
#include <string>
#include <stdexcept>
#include "DispositivoComunicacion.h"

using namespace std;

DispositivoComunicacion::DispositivoComunicacion(string ip, string tipo) {
	this->ip = ip;
	this->tipo = tipo;
}

string DispositivoComunicacion::getIp() const {
	return ip;
}

string DispositivoComunicacion::getTipo() const {
	return tipo;
}

void validarYTransmitir(DispositivoComunicacion* dispositivo) {
	// Guarda defensiva: revisar el puntero ANTES de usar ->
	if (dispositivo == nullptr) {
		throw invalid_argument("Puntero nulo detectado");
	}

	dispositivo->transmitir();
}
