#ifndef SENSORIOT_H
#define SENSORIOT_H
#include <iostream>
#include <string>

using namespace std;

class SensorIoT {
protected:
	string tipoSensor;
	double valorLectura;

public:
	SensorIoT(string tipoSensor, double valorLectura);

	string getTipoSensor() const;
	double getValorLectura() const;

	virtual ~SensorIoT();
};

#endif
