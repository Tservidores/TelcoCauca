#ifndef NODOREDINTELIGENTE_H
#define NODOREDINTELIGENTE_H
#include <iostream>
#include <string>
#include "DispositivoRed.h"
#include "SensorIoT.h"

using namespace std;

// Herencia multiple: hereda de DispositivoRed y de SensorIoT al mismo tiempo
class NodoRedInteligente : public DispositivoRed, public SensorIoT {
private:
	int idNodo;
	int paquetesProcesados;

public:
	NodoRedInteligente(string direccionIP, string direccionMAC, bool estadoOperativo,
					   string tipoSensor, double valorLectura, int idNodo, int paquetesProcesados);

	int getIdNodo() const;
	int getPaquetesProcesados() const;

	NodoRedInteligente operator+(const NodoRedInteligente& otro) const;

	friend ostream& operator<<(ostream& os, const NodoRedInteligente& nodo);

	~NodoRedInteligente();
};

#endif
