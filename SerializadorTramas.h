#ifndef SERIALIZADORTRAMAS_H
#define SERIALIZADORTRAMAS_H
#include <iostream>
#include <string>
#include "NodoRedInteligente.h"

using namespace std;

class SerializadorTramas {
public:
	static string serializar(const NodoRedInteligente& nodo);
	static string deserializar(string trama);
};

#endif
