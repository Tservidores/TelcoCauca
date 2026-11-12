#include <iostream>
#include <string>
#include "Antena.h"

using namespace std;

Antena::Antena(int idAntena, double frecuenciaMHz, string tecnologia, Tecnico* responsableMantenimiento) {
	this->idAntena = idAntena;
	this->frecuenciaMHz = frecuenciaMHz;
	this->tecnologia = tecnologia;
	this->responsableMantenimiento = responsableMantenimiento;
}

int Antena::getIdAntena() const {
	return idAntena;
}

double Antena::getFrecuenciaMHz() const {
	return frecuenciaMHz;
}

string Antena::getTecnologia() const {
	return tecnologia;
}

Tecnico* Antena::getResponsableMantenimiento() const {
	return responsableMantenimiento;
}

void Antena::asignarTecnico(Tecnico* responsableMantenimiento) {
	this->responsableMantenimiento = responsableMantenimiento;
}

void Antena::mostrarInformacion() const {
	cout << "  Antena " << idAntena << " | " << tecnologia
		<< " | " << frecuenciaMHz << " MHz | Responsable: ";

	if (responsableMantenimiento != nullptr) {
		cout << responsableMantenimiento->getNombre() << endl;
	}
	else {
		cout << "Sin asignar" << endl;
	}
}

// La antena NO borra al tecnico: es una asociacion, el tecnico existe por su cuenta
Antena::~Antena() {
}
