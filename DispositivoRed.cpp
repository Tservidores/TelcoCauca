#include <iostream>
#include <string>
#include "DispositivoRed.h"
#include "ExcepcionNodoRed.h"

using namespace std;

DispositivoRed::DispositivoRed(string direccionIP, string direccionMAC, bool estadoOperativo) {
	this->direccionIP = direccionIP;
	this->direccionMAC = direccionMAC;
	this->estadoOperativo = estadoOperativo;

	if (this->direccionIP.empty()) {
		throw ExcepcionNodoRed("La direccion IP no puede estar vacia");
	}
}

string DispositivoRed::getDireccionIP() const {
	return direccionIP;
}

string DispositivoRed::getDireccionMAC() const {
	return direccionMAC;
}

bool DispositivoRed::getEstadoOperativo() const {
	return estadoOperativo;
}

DispositivoRed::~DispositivoRed() {
}
