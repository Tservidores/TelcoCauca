#ifndef DISPOSITIVORED_H
#define DISPOSITIVORED_H
#include <iostream>
#include <string>

using namespace std;

class DispositivoRed {
protected:
	string direccionIP;
	string direccionMAC;
	bool estadoOperativo;

public:
	DispositivoRed(string direccionIP, string direccionMAC, bool estadoOperativo);

	string getDireccionIP() const;
	string getDireccionMAC() const;
	bool getEstadoOperativo() const;

	virtual ~DispositivoRed();
};

#endif
