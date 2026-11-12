#ifndef GATEWAYLORA_H
#define GATEWAYLORA_H
#include <iostream>
#include <string>
#include "DispositivoComunicacion.h"

using namespace std;

class GatewayLoRa : public DispositivoComunicacion {
private:
	int frecuenciaMHz;
	
public:
	GatewayLoRa(string ip, int frecuenciaMHz);
	
	void transmitir() override;
	string serializar() const override;
	
	~GatewayLoRa();
};

#endif
