#include <iostream>
#include <string>
#include "NodoRedInteligente.h"
#include "ExcepcionNodoRed.h"

using namespace std;

// Los constructores de las dos clases padre se llaman en la lista de inicializacion (con ":")
NodoRedInteligente::NodoRedInteligente(string direccionIP, string direccionMAC, bool estadoOperativo,
									   string tipoSensor, double valorLectura, int idNodo, int paquetesProcesados)
	: DispositivoRed(direccionIP, direccionMAC, estadoOperativo), SensorIoT(tipoSensor, valorLectura) {

	this->idNodo = idNodo;
	this->paquetesProcesados = paquetesProcesados;
}

int NodoRedInteligente::getIdNodo() const {
	return idNodo;
}

int NodoRedInteligente::getPaquetesProcesados() const {
	return paquetesProcesados;
}

NodoRedInteligente NodoRedInteligente::operator+(const NodoRedInteligente& otro) const {
	if (this->estadoOperativo == false || otro.estadoOperativo == false) {
		throw ExcepcionNodoRed("No se puede sumar la carga de un nodo inactivo");
	}

	int cargaTotal = this->paquetesProcesados + otro.paquetesProcesados;

	NodoRedInteligente resultado(this->direccionIP, this->direccionMAC, this->estadoOperativo,
								 this->tipoSensor, this->valorLectura, this->idNodo, cargaTotal);
	return resultado;
}

ostream& operator<<(ostream& os, const NodoRedInteligente& nodo) {
	os << "Nodo " << nodo.idNodo
		<< " | IP: " << nodo.direccionIP
		<< " | MAC: " << nodo.direccionMAC
		<< " | Estado: " << (nodo.estadoOperativo ? "Activo" : "Inactivo")
		<< " | Sensor: " << nodo.tipoSensor << " = " << nodo.valorLectura
		<< " | Paquetes: " << nodo.paquetesProcesados << endl;
	return os;
}

NodoRedInteligente::~NodoRedInteligente() {
}
