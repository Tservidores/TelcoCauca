#ifndef EXCEPCIONNODORED_H
#define EXCEPCIONNODORED_H
#include <stdexcept>
#include <string>

using namespace std;

class ExcepcionNodoRed : public runtime_error {
public:
	// El constructor de la clase padre (runtime_error) solo se puede llamar con ":"
	ExcepcionNodoRed(string mensaje) : runtime_error("[ExcepcionNodoRed] " + mensaje) {
	}
};

#endif
