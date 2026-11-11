#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <stdexcept>
#include "GestorConcurrencia.h"
#include "Consola.h"

using namespace std;

void GestorConcurrencia::procesarDispositivo(DispositivoComunicacion* dispositivo, int& contador) {
	// El try-catch va DENTRO del hilo: si una excepcion se escapa del hilo, el programa se cierra
	try {
		validarYTransmitir(dispositivo);

		lock_guard<mutex> bloqueo(mutexBuffer);
		contador++;
		bufferTramas.push_back(dispositivo->serializar());
	}
	catch (const invalid_argument& e) {
		registrarEventoSeguro(string("Error en hilo (argumento invalido): ") + e.what());
	}
	catch (const exception& e) {
		registrarEventoSeguro(string("Error en hilo: ") + e.what());
	}
}

void GestorConcurrencia::procesarEventos(vector<EventoIngenieria2027>& eventos) {
	try {
		for (EventoIngenieria2027 evento : eventos) {
			evento.mostrar();
		}
	}
	catch (const exception& e) {
		registrarEventoSeguro(string("Error en eventos: ") + e.what());
	}
}

void GestorConcurrencia::mostrarBuffer() {
	lock_guard<mutex> bloqueo(mutexBuffer);

	cout << "Buffer compartido (" << bufferTramas.size() << " tramas):" << endl;

	for (string trama : bufferTramas) {
		cout << "  " << trama << endl;
	}
}
