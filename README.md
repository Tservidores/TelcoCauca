# Proyecto Integrador TelcoCauca

Sistema distribuido concurrente de monitoreo de infraestructura de telecomunicaciones e IoT.
Programacion Orientada a Objetos 2026.2 - Universidad del Cauca (FIET)
Docente: Paola Andrea Bedoya Toro

## Integrantes
- Catalina Illera
- Jhon Erazo

## Compilacion en Zinjal
- Abrir `TelcoCauca_TrabajoFinalenParejas.zpr`
- Estandar: C++11 (`-std=c++11 -pthread`)
- Enlazado: biblioteca `ws2_32` (Winsock, obligatoria en Windows) y `-pthread`

## Modulos
| Modulo | Contenido | Archivos |
|---|---|---|
| 1. Dominio UML | Asociacion 1:1 Tecnico-Antena, 1:N Torre-Antenas, declaracion adelantada | Tecnico, Antena, Torre |
| 2. Herencia multiple | NodoRedInteligente (DispositivoRed + SensorIoT), operadores `+` y `<<`, ExcepcionNodoRed | DispositivoRed, SensorIoT, NodoRedInteligente, ExcepcionNodoRed |
| 3. Polimorfismo | Clase abstracta, interfaz pura, override, vector polimorfico con guarda nullptr | ITransmisible, DispositivoComunicacion, RouterWiFi, GatewayLoRa, SwitchFibra |
| 4. Multihilo | std::thread sobre funciones miembro, std::ref, mutex + lock_guard, eventos 2027 | Consola, GestorConcurrencia, EventoIngenieria2027 |
| 5. Sockets | Servidor TCP con un hilo por cliente, clientes TCP, telemetria UDP binaria con `#pragma pack`, timeout de 3 s | ServidorCentral, ClienteRemoto, ServidorUDP, ClienteUDP, SerializadorTramas, TramaTelemetria, ExcepcionSocket, ExcepcionRedUDP |

## Puertos
- TCP: 8080 (Servidor Central)
- UDP: 8081 (Telemetria)
- 9090: puerto sin servidor, usado para la prueba de resiliencia
