#include <iostream>
#include <string>
#include "RouterWiFi.h"
#include "Consola.h"

using namespace std;

RouterWiFi::RouterWiFi(string ip, int canalesActivos) : DispositivoComunicacion(ip, "Router WiFi") {
	this->canalesActivos = canalesActivos;
}

void RouterWiFi::transmitir() {
	registrarEventoSeguro("Router WiFi transmitiendo en banda de 5 GHz. IP: " + ip);
}

string RouterWiFi::serializar() const {
	return tipo + "|" + ip + "|" + to_string(canalesActivos) + " canales";
}

RouterWiFi::~RouterWiFi() {
	cout << "Destructor de RouterWiFi " << ip << endl;
}
