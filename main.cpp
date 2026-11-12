// PROYECTO INTEGRADOR TelcoCauca - POO C++11 (Zinjal)
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstring>
#include <stdexcept>
#include <functional>
#include <winsock2.h>

#include "Tecnico.h"
#include "Antena.h"
#include "Torre.h"
#include "NodoRedInteligente.h"
#include "ExcepcionNodoRed.h"
#include "DispositivoComunicacion.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
#include "Consola.h"
#include "EventoIngenieria2027.h"
#include "GestorConcurrencia.h"
#include "SerializadorTramas.h"
#include "ServidorCentral.h"
#include "ClienteRemoto.h"
#include "ServidorUDP.h"
#include "ClienteUDP.h"
#include "TramaTelemetria.h"
#include "ExcepcionSocket.h"
#include "ExcepcionRedUDP.h"

using namespace std;

const int PUERTO_TCP = 8080;
const int PUERTO_UDP = 8081;
const int PUERTO_SIN_SERVIDOR = 9090;

void titulo(string texto) {
	cout << endl << "==================================================" << endl;
	cout << "  " << texto << endl;
	cout << "==================================================" << endl;
}


// ---------------- MODULO 1: Tecnicos, Antenas y Torre ----------------
void modulo1() {
	titulo("MODULO 1: Tecnicos, Antenas y Torre");

	Tecnico tecnico1(1, "Carlos Perez", "Infraestructura");
	Tecnico tecnico2(2, "Laura Gomez", "Radiofrecuencia 5G");

	tecnico1.mostrarInformacion();
	tecnico2.mostrarInformacion();

	Antena antena1(101, 850.0, "4G", &tecnico1);
	Antena antena2(102, 3500.0, "5G", &tecnico2);
	Antena antena3(103, 700.0, "4G", nullptr);
	antena3.asignarTecnico(&tecnico1);

	Torre torre(1, "Popayan Centro", 35.0);
	torre.agregarAntena(&antena1);
	torre.agregarAntena(&antena2);
	torre.agregarAntena(&antena3);

	torre.mostrarInformacion();

	cout << endl << "Cambio de turno: Laura reemplaza a Carlos" << endl;
	int cambios = torre.remplazarTecnico(&tecnico1, &tecnico2);
	cout << "Antenas reasignadas: " << cambios << endl;
	torre.mostrarInformacion();
}


// ---------------- MODULO 2: Herencia multiple, operadores y excepciones ----------------
vector<string> modulo2() {
	titulo("MODULO 2: Herencia multiple, operadores y excepciones");

	vector<string> tramas;

	try {
		NodoRedInteligente nodo1("192.168.1.10", "AA:BB:CC:11:22:33", true, "Temperatura", 25.5, 1, 100);
		NodoRedInteligente nodo2("192.168.1.10", "AA:BB:CC:44:55:66", true, "Temperatura", 27.5, 2, 200);

		cout << nodo1;
		cout << nodo2;

		NodoRedInteligente nodo3 = nodo1 + nodo2;
		cout << "Fusion nodo1 + nodo2 (misma IP): " << endl << nodo3;

		tramas.push_back(SerializadorTramas::serializar(nodo1));
		tramas.push_back(SerializadorTramas::serializar(nodo2));
		tramas.push_back(SerializadorTramas::serializar(nodo3));
		cout << "Trama serializada del nodo 1: " << tramas.at(0) << endl;

		cout << endl << "Prueba 1: sumar nodos con IP distinta..." << endl;
		NodoRedInteligente nodoOtraRed("10.0.0.5", "AA:BB:CC:77:88:99", true, "Humedad", 60.0, 3, 50);
		NodoRedInteligente invalido = nodo1 + nodoOtraRed;
	}
	catch (const ExcepcionNodoRed& e) {
		cout << "Excepcion capturada: " << e.what() << endl;
	}
	catch (const exception& e) {
		cout << "Excepcion general capturada: " << e.what() << endl;
	}

	try {
		cout << endl << "Prueba 2: crear un nodo con lectura de 150..." << endl;
		NodoRedInteligente nodoMalo("192.168.1.20", "AA:BB:CC:00:00:01", true, "Temperatura", 150.0, 4, 10);
	}
	catch (const ExcepcionNodoRed& e) {
		cout << "Excepcion capturada: " << e.what() << endl;
	}

	try {
		cout << endl << "Prueba 3: crear un nodo con IP vacia..." << endl;
		NodoRedInteligente nodoSinIP("", "AA:BB:CC:00:00:02", true, "Humedad", 40.0, 5, 10);
	}
	catch (const ExcepcionNodoRed& e) {
		cout << "Excepcion capturada: " << e.what() << endl;
	}

	return tramas;
}


// ---------------- MODULO 3: Polimorfismo ----------------
void modulo3(vector<DispositivoComunicacion*>& dispositivos) {
	titulo("MODULO 3: Polimorfismo y vector con guarda nullptr");

	dispositivos.push_back(new RouterWiFi("192.168.1.1", 12));
	dispositivos.push_back(new GatewayLoRa("192.168.1.2", 868));
	dispositivos.push_back(new SwitchFibra("192.168.1.3", 10));
	dispositivos.push_back(nullptr);   // Puntero nulo a proposito, para probar la guarda

	for (DispositivoComunicacion* dispositivo : dispositivos) {
		try {
			procesarDispositivo(dispositivo);
			cout << "  Serializado: " << dispositivo->serializar() << endl;
		}
		catch (const invalid_argument& e) {
			cout << "Excepcion capturada: " << e.what() << endl;
		}
		catch (const exception& e) {
			cout << "Excepcion general capturada: " << e.what() << endl;
		}
	}
}


// ---------------- MODULO 4: Hilos y mutex ----------------
void modulo4(vector<DispositivoComunicacion*>& dispositivos) {
	titulo("MODULO 4: Hilos en paralelo con mutex");

	GestorConcurrencia gestor;
	int contador = 0;
	vector<thread> hilos;

	// Un hilo por dispositivo. ref() pasa el contador por referencia (sin ref se copiaria)
	for (DispositivoComunicacion* dispositivo : dispositivos) {
		hilos.push_back(thread(&GestorConcurrencia::supervisarDispositivo, &gestor, dispositivo, ref(contador)));
	}

	vector<EventoIngenieria2027> eventos;
	eventos.push_back(EventoIngenieria2027("IEEE PES GTD Latin America 2027 - Generacion, Transmision y Distribucion de Energia", "8-10 marzo 2027", "Medellin, Colombia"));
	eventos.push_back(EventoIngenieria2027("CICI 2027 - IV Congreso Internacional de Ciencia e Ingenieria", "14-16 abril 2027", "Pasto, Colombia"));
	eventos.push_back(EventoIngenieria2027("IEEE Colombian Caribbean Conference (C3) 2027", "Septiembre 2027", "Cartagena, Colombia"));

	thread hiloEventos(&GestorConcurrencia::procesarEventos, &gestor, ref(eventos));

	// join(): esperar a que todos los hilos terminen antes de seguir
	for (int i = 0; i < hilos.size(); i++) {
		hilos[i].join();
	}
	hiloEventos.join();

	cout << "Transmisiones exitosas: " << contador << " de " << dispositivos.size() << endl;
	gestor.mostrarBuffer();
}


// ---------------- MODULO 5: Sockets TCP y UDP ----------------
void modulo5(vector<string>& tramas, vector<DispositivoComunicacion*>& dispositivos) {

	// En Windows es obligatorio iniciar Winsock antes de usar sockets
	WSADATA datosWinsock;
	if (WSAStartup(MAKEWORD(2, 2), &datosWinsock) != 0) {
		cout << "No se pudo iniciar Winsock" << endl;
		return;
	}

	try {
		titulo("MODULO 5.1: Servidor TCP con un hilo por cliente");

		string trama1 = tramas.at(0);
		string trama2 = tramas.at(1);
		string trama3 = tramas.at(2);

		ServidorCentral servidor(PUERTO_TCP);
		servidor.iniciar();
		thread hiloServidor(&ServidorCentral::aceptarClientes, &servidor, 3);

		ClienteRemoto cliente1("Estacion-Popayan", "127.0.0.1", PUERTO_TCP);
		ClienteRemoto cliente2("Estacion-Timbio", "127.0.0.1", PUERTO_TCP);
		ClienteRemoto cliente3("Estacion-Piendamo", "127.0.0.1", PUERTO_TCP);

		thread hiloCliente1(&ClienteRemoto::enviarTrama, &cliente1, trama1);
		thread hiloCliente2(&ClienteRemoto::enviarTrama, &cliente2, trama2);
		thread hiloCliente3(&ClienteRemoto::enviarTrama, &cliente3, trama3);

		hiloCliente1.join();
		hiloCliente2.join();
		hiloCliente3.join();
		hiloServidor.join();

		cout << endl << "Prueba de falla: cliente que se conecta a un puerto sin servidor..." << endl;
		ClienteRemoto clienteCaido("Estacion-Caida", "127.0.0.1", PUERTO_SIN_SERVIDOR);
		clienteCaido.enviarTrama(trama1);


		titulo("MODULO 5.2: Telemetria UDP con #pragma pack");

		cout << "Tamano de la trama: " << sizeof(TramaTelemetria) << " bytes (debe ser 36)" << endl;

		ServidorUDP servidorUDP(PUERTO_UDP);
		servidorUDP.iniciar();
		thread hiloUDP(&ServidorUDP::escuchar, &servidorUDP);

		ClienteUDP clienteUDP("127.0.0.1", PUERTO_UDP);

		for (int i = 0; i < 3; i++) {
			TramaTelemetria trama;
			trama.idEstacion = 501 + i;
			strncpy(trama.tipoDispositivo, dispositivos.at(i)->getTipo().c_str(), 16);
			trama.tipoDispositivo[15] = '\0';
			trama.temperatura = 24.5 + i;
			trama.humedad = 55.0 + i;
			trama.timestamp = time(nullptr);

			clienteUDP.enviarTrama(trama);
			this_thread::sleep_for(chrono::milliseconds(200));
		}

		registrarEventoSeguro("[Cliente UDP] Deja de enviar (simula desconexion)...");
		hiloUDP.join();
	}
	catch (const ExcepcionSocket& e) {
		cout << "Error TCP: " << e.what() << endl;
	}
	catch (const ExcepcionRedUDP& e) {
		cout << "Error UDP: " << e.what() << endl;
	}
	catch (const exception& e) {
		cout << "Error general: " << e.what() << endl;
	}

	WSACleanup();
}


// ---------------- LIBERACION DE MEMORIA ----------------
void liberarMemoria(vector<DispositivoComunicacion*>& dispositivos) {
	titulo("Liberacion de memoria");

	for (int i = 0; i < dispositivos.size(); i++) {
		delete dispositivos[i];
		dispositivos[i] = nullptr;
	}
	dispositivos.clear();

	cout << "Memoria liberada. Elementos en el vector: " << dispositivos.size() << endl;
}


int main() {
	cout << "===================================" << endl;
	cout << "        SISTEMA TELCOCAUCA" << endl;
	cout << "===================================" << endl;

	vector<DispositivoComunicacion*> dispositivos;

	modulo1();
	vector<string> tramas = modulo2();
	modulo3(dispositivos);
	modulo4(dispositivos);
	modulo5(tramas, dispositivos);
	liberarMemoria(dispositivos);

	cout << endl << "        FIN DEL SISTEMA" << endl;
	return 0;
}
