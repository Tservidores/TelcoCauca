#ifndef TECNICO_H
#define TECNICO_H
#include <iostream>
#include <string>

using namespace std;

class Tecnico {
private:
	int idTecnico;
	string nombre;
	string especialidad;

public:
	Tecnico(int idTecnico, string nombre, string especialidad);

	int getIdTecnico() const;
	string getNombre() const;
	string getEspecialidad() const;

	void setIdTecnico(int idTecnico);
	void setNombre(string nombre);
	void setEspecialidad(string especialidad);

	void mostrarInformacion() const;

	~Tecnico();
};

#endif
