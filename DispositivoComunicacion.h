#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H
#include <iostream>
#include <string>
#include "ITransmisible.h"

using namespace std;

// Clase abstracta: tiene un metodo virtual puro, por eso no se pueden crear objetos de ella
class DispositivoComunicacion : public ITransmisible {
protected:
	string ip;
	string tipo;

public:
	DispositivoComunicacion(string ip, string tipo);

	virtual void transmitir() = 0;

	string getIp() const;
	string getTipo() const;

	// Destructor virtual obligatorio: asi el delete llama tambien al destructor de la clase hija
	virtual ~DispositivoComunicacion() = default;
};

void validarYTransmitir(DispositivoComunicacion* dispositivo);

#endif
