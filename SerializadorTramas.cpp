#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "SerializadorTramas.h"

using namespace std;

// Convierte el nodo en texto separado por "|" para enviarlo por la red
string SerializadorTramas::serializar(const NodoRedInteligente& nodo) {
	string trama = "";

	trama += to_string(nodo.getIdNodo()) + "|";
	trama += nodo.getDireccionIP() + "|";
	trama += nodo.getDireccionMAC() + "|";
	trama += to_string(nodo.getEstadoOperativo()) + "|";
	trama += nodo.getTipoSensor() + "|";
	trama += to_string(nodo.getValorLectura()) + "|";
	trama += to_string(nodo.getPaquetesProcesados());

	return trama;
}

// Separa el texto por "|" y lo vuelve a armar de forma legible
string SerializadorTramas::deserializar(string trama) {
	stringstream separador(trama);
	vector<string> datos;
	string campo;

	while (getline(separador, campo, '|')) {
		datos.push_back(campo);
	}

	if (datos.size() != 7) {
		throw invalid_argument("La trama recibida no es valida");
	}

	string resultado = "Nodo " + datos.at(0)
		+ " | IP: " + datos.at(1)
		+ " | MAC: " + datos.at(2)
		+ " | Sensor: " + datos.at(4) + " = " + datos.at(5)
		+ " | Paquetes: " + datos.at(6);

	return resultado;
}
