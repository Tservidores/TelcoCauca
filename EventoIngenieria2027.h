#ifndef EVENTOINGENIERIA2027_H
#define EVENTOINGENIERIA2027_H
#include <iostream>
#include <string>

using namespace std;

class EventoIngenieria2027 {
private:
	string nombre;
	string fecha;
	string lugar;

public:
	EventoIngenieria2027(string nombre, string fecha, string lugar);

	string getNombre() const;
	string getFecha() const;
	string getLugar() const;

	void mostrar() const;
};

#endif
