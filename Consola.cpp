#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "Consola.h"

using namespace std;

mutex mutexConsola;

// Todos los hilos imprimen por aqui para que los mensajes no se mezclen
void registrarEventoSeguro(string mensaje) {
	// lock_guard (RAII): bloquea el mutex aqui y lo libera solo al salir de la funcion
	lock_guard<mutex> bloqueo(mutexConsola);
	cout << "[Hilo " << this_thread::get_id() << "] " << mensaje << endl;
}
