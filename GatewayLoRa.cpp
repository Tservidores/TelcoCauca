#include <iostream>
#include <string>
#include "GatewayLoRa.h"
#include "Consola.h"

using namespace std;

GatewayLoRa::GatewayLoRa(string ip, int frecuenciaMHz) : DispositivoComunicacion(ip, "Gateway LoRa") {
	this->frecuenciaMHz = frecuenciaMHz;
}

void GatewayLoRa::transmitir() {
	registrarEventoSeguro("Gateway LoRa transmitiendo a larga distancia. IP: " + ip);
}

string GatewayLoRa::serializar() const {
	return tipo + "|" + ip + "|" + to_string(frecuenciaMHz) + " MHz";
}

GatewayLoRa::~GatewayLoRa() {
	cout << "Destructor de GatewayLoRa " << ip << endl;
}
