#ifndef SERVIDORUDP_H
#define SERVIDORUDP_H
#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

class ServidorUDP {
private:
	int puerto;
	SOCKET socketUDP;

public:
	ServidorUDP(int puerto);

	void iniciar();
	void escuchar();

	~ServidorUDP();
};

#endif
