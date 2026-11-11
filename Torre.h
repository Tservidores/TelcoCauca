#ifndef TORRE_H
#define TORRE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Declaracion adelantada: evita la inclusion ciclica. El #include "Antena.h" va en Torre.cpp
class Antena;

class Torre {
private:
	int idTorre;
	string ubicacion;
	double alturaMetros;
	vector<Antena*> listaAntenas;   // Asociacion 1:N con Antena

public:
	Torre(int idTorre, string ubicacion, double alturaMetros);

	void agregarAntena(Antena* antena);
	int contarAntenas() const;
	int contarAntenas5G() const;

	void mostrarInformacion() const;

	~Torre();
};

#endif
