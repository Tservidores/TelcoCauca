#ifndef SWITCHFIBRA_H
#define SWITCHFIBRA_H
#include <iostream>
#include <string>
#include "DispositivoComunicacion.h"

using namespace std;

class SwitchFibra : public DispositivoComunicacion {
private:
	int velocidadGbps;
	
public:
	SwitchFibra(string ip, int velocidadGbps);
	
	void transmitir() override;
	string serializar() const override;
	
	~SwitchFibra();
};

#endif
