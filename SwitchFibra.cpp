#include <iostream>
#include <string>
#include "SwitchFibra.h"
#include "Consola.h"

using namespace std;

SwitchFibra::SwitchFibra(string ip, int velocidadGbps) : DispositivoComunicacion(ip, "Switch Fibra") {
	this->velocidadGbps = velocidadGbps;
}

void SwitchFibra::transmitir() {
	registrarEventoSeguro("Switch de Fibra transmitiendo por fibra optica. IP: " + ip);
}

string SwitchFibra::serializar() const {
	return tipo + "|" + ip + "|" + to_string(velocidadGbps) + " Gbps";
}

SwitchFibra::~SwitchFibra() {
	cout << "Destructor de SwitchFibra " << ip << endl;
}
