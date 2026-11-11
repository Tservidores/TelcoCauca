#ifndef ITRANSMISIBLE_H
#define ITRANSMISIBLE_H
#include <iostream>
#include <string>

using namespace std;

// Interfaz pura: solo metodos virtuales puros (= 0) y ningun atributo
class ITransmisible {
public:
	virtual string serializar() const = 0;

	virtual ~ITransmisible() = default;
};

#endif
