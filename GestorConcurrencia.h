#ifndef GESTORCONCURRENCIA_H
#define GESTORCONCURRENCIA_H
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include "DispositivoComunicacion.h"
#include "EventoIngenieria2027.h"

using namespace std;

class GestorConcurrencia {
private:
	mutex mutexBuffer;
	vector<string> bufferTramas;   // Buffer compartido por todos los hilos

public:
	void supervisarDispositivo(DispositivoComunicacion* dispositivo, int& contador);
	void procesarEventos(vector<EventoIngenieria2027>& eventos);
	void mostrarBuffer();
};

#endif
