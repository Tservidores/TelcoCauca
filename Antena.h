#ifndef ANTENA_H
#define ANTENA_H
#include <iostream>
#include <string>
#include "Tecnico.h"

using namespace std;

class Antena {
private:
	int idAntena;
	double frecuenciaMHz;
	string tecnologia;
	Tecnico* responsableMantenimiento;   // Asociacion 1:1 con Tecnico

public:
	Antena(int idAntena, double frecuenciaMHz, string tecnologia, Tecnico* responsableMantenimiento);

	int getIdAntena() const;
	double getFrecuenciaMHz() const;
	string getTecnologia() const;
	Tecnico* getResponsableMantenimiento() const;

	void asignarTecnico(Tecnico* responsableMantenimiento);

	void mostrarInformacion() const;

	~Antena();
};

#endif
