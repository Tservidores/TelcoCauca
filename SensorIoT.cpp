#include <iostream>
#include <string>
#include "SensorIoT.h"
#include "ExcepcionNodoRed.h"

using namespace std;

SensorIoT::SensorIoT(string tipoSensor, double valorLectura) {
	this->tipoSensor = tipoSensor;
	this->valorLectura = valorLectura;

	if (this->valorLectura < -50.0 || this->valorLectura > 100.0) {
		throw ExcepcionNodoRed("Lectura del sensor fuera de rango [-50, 100]");
	}
}

string SensorIoT::getTipoSensor() const {
	return tipoSensor;
}

double SensorIoT::getValorLectura() const {
	return valorLectura;
}

SensorIoT::~SensorIoT() {
}
