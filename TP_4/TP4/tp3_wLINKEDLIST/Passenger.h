#ifndef PASSENGER_H_
#define PASSENGER_H_

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	char codigoVuelo[10];
	int tipoPasajero;
	int estadoVuelo;

}Passenger;
/////////////////////////////////////////////////////////////CONSTRUCTORES Y DESTRUCTORES
Passenger* Passenger_new();
Passenger* Passenger_newParametros(char* idStr,char* nameStr,char* lastnameStr,char* priceStr,char* flycodeStr,char* typePassengerStr,char* statusFlightStr);
Passenger* Passenger_newParametrosNOSTRING(int id,char* name,char* lastname,float price,char* flycode,int typePassenger,int statusFlight);
void Passenger_delete(Passenger* this);

/////////////////////////////////////////////////////////////SETTERS Y GETTERS
int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this,int* id);
//---------
int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);
//---------
int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);
//---------
int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);
//---------
int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);
//---------
int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);
//---------
int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo);
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo);

/////////////////////////////////////////////////////////////CONVERTIDORES

int Passenger_tipoPasajeroTO_INT(char* tipoPasajero);
int Passenger_tipoPasajeroTO_STRING(int tipo, char* tipoPasajero);

int Passenger_estadoVueloTO_INT(char* estadoVuelo);
int Passenger_estadoVueloTO_STRING(int estado, char* estadoVuelo);

///////////////////////////////////////////////////////////// ID
int id_readAndSet();
int id_write(int *id);

///////////////////////////////////////////////////////////// MENUS
void menuPrincipal();
void menuFlycodes();
void menuTypePassengers();
void menuOrdenar();

///////////////////////////////////////////////////////////// ABM
void Passenger_printfOne(Passenger* this);
int Passenger_alta(LinkedList* pArrayListPassenger);
int Passengers_setFlycodebyID(int idFlycode, char* flycodeChar);
int Passenger_setStatusFlightbyFLYCODE(char* flycodeChar, int* statusFlight);
int Passenger_modificarPasajero(LinkedList* pArrayListPassenger);
int Passenger_buscarID(LinkedList* pArrayListPassenger, int id);
int Passenger_baja(LinkedList* pArrayListPassenger);
int Passenger_sortNombreApellido(void* pPassengerA, void* pPassengerB);
int Passenger_sortID(void* pPassengerA, void* pPassengerB);

#endif /* PASSENGER_H_ */
