#include <iostream>
#include <string>
#include "EventoIngenieria2027.h"
#include "Consola.h"

using namespace std;

EventoIngenieria2027::EventoIngenieria2027(string nombre, string fecha, string lugar) {
	this->nombre = nombre;
	this->fecha = fecha;
	this->lugar = lugar;
}

string EventoIngenieria2027::getNombre() const {
	return nombre;
}

string EventoIngenieria2027::getFecha() const {
	return fecha;
}

string EventoIngenieria2027::getLugar() const {
	return lugar;
}

void EventoIngenieria2027::mostrar() const {
	registrarEventoSeguro("Evento 2027: " + nombre + " | " + fecha + " | " + lugar);
}
