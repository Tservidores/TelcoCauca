#ifndef EXCEPCIONSOCKET_H
#define EXCEPCIONSOCKET_H
#include <stdexcept>
#include <string>

using namespace std;

class ExcepcionSocket : public runtime_error {
public:
	ExcepcionSocket(string mensaje) : runtime_error("[ExcepcionSocket] " + mensaje) {
	}
};

#endif
