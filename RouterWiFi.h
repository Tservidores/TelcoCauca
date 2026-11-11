#ifndef ROUTERWIFI_H
#define ROUTERWIFI_H
#include <iostream>
#include <string>
#include "DispositivoComunicacion.h"

using namespace std;

class RouterWiFi : public DispositivoComunicacion {
private:
	int canalesActivos;
	
public:
	RouterWiFi(string ip, int canalesActivos);
	
	void transmitir() override;
	string serializar() const override;
	
	~RouterWiFi();
};

#endif
