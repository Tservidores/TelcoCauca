#include <iostream>
#include <string>
#include <vector>
#include "Torre.h"
#include "Antena.h"

using namespace std;

Torre::Torre(int idTorre, string ubicacion, double alturaMetros) {
	this->idTorre = idTorre;
	this->ubicacion = ubicacion;
	this->alturaMetros = alturaMetros;
}

void Torre::agregarAntena(Antena* antena) {
	if (antena != nullptr) {
		listaAntenas.push_back(antena);
	}
}

int Torre::contarAntenas() const {
	return listaAntenas.size();
}

int Torre::contarAntenas5G() const {
	int contador = 0;

	for (Antena* antena : listaAntenas) {
		if (antena->getTecnologia() == "5G") {
			contador++;
		}
	}

	return contador;
}

void Torre::mostrarInformacion() const {
	cout << "Torre " << idTorre << " | " << ubicacion << " | " << alturaMetros << " metros" << endl;
	cout << "Antenas instaladas: " << contarAntenas() << " (5G: " << contarAntenas5G() << ")" << endl;

	for (Antena* antena : listaAntenas) {
		antena->mostrarInformacion();
	}
}

// La torre NO borra las antenas (asociacion), solo vacia su lista
Torre::~Torre() {
	listaAntenas.clear();
}
