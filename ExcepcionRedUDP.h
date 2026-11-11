#ifndef EXCEPCIONREDUDP_H
#define EXCEPCIONREDUDP_H
#include <stdexcept>
#include <string>

using namespace std;

class ExcepcionRedUDP : public runtime_error {
private:
	int codigoError;

public:
	ExcepcionRedUDP(string mensaje, int codigoError)
		: runtime_error("[ExcepcionRedUDP] " + mensaje + " (codigo " + to_string(codigoError) + ")") {
		this->codigoError = codigoError;
	}

	int getCodigoError() const {
		return codigoError;
	}
};

#endif
