#ifndef TRAMATELEMETRIA_H
#define TRAMATELEMETRIA_H
#include <cstdint>

// #pragma pack(1): el compilador NO agrega bytes de relleno, la trama mide exactamente 36 bytes
#pragma pack(push, 1)
struct TramaTelemetria {
	uint32_t idEstacion;         // 4 bytes
	char tipoDispositivo[16];    // 16 bytes
	float temperatura;           // 4 bytes
	float humedad;               // 4 bytes
	uint64_t timestamp;          // 8 bytes
};
#pragma pack(pop)

#endif
