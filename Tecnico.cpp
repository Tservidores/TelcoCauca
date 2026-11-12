#include <iostream>
#include <string>
#include "Tecnico.h"

using namespace std;

Tecnico::Tecnico(int idTecnico, string nombre, string especialidad) {
	this->idTecnico = idTecnico;
	this->nombre = nombre;
	this->especialidad = especialidad;
}

int Tecnico::getIdTecnico() const {
	return idTecnico;
}

string Tecnico::getNombre() const {
	return nombre;
}

string Tecnico::getEspecialidad() const {
	return especialidad;
}

void Tecnico::setIdTecnico(int idTecnico) {
	this->idTecnico = idTecnico;
}

void Tecnico::setNombre(string nombre) {
	this->nombre = nombre;
}

void Tecnico::setEspecialidad(string especialidad) {
	this->especialidad = especialidad;
}

void Tecnico::mostrarInformacion() const {
	cout << "Tecnico " << idTecnico << ": " << nombre
		<< " | Especialidad: " << especialidad << endl;
}

Tecnico::~Tecnico() {
}
