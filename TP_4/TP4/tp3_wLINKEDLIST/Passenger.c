#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "Controller.h"
///////////////////////////////////////////////// SET ID
/**
 * @brief Lee el archivo donde se ubica el id y lo devuelve
 *
 * @return -1 si hubo error o el id autoincrementado
 */
int id_readAndSet()
{
	FILE* fileID = fopen("counter.txt", "r");
	int id;
	int retorno=-1;
	if(fileID!=NULL)
	{
		fscanf(fileID, "%d\n", &id);
		retorno=id;

		fclose(fileID);
	}
	return retorno;
}

/**
 * @brief Obtiene el Id previamente leido y lo autoincrementa, guardandolo nuevamente
 *
 * @param id
 * @return Retorna 0 si OK y -1 si hubo error
 */
int id_write(int *id)
{
	FILE* fileID = fopen("counter.txt", "w");
	int retorno=-1;

	if(fileID!=NULL)
	{
		(*id)++;
		fprintf(fileID, "%d",*id);
		retorno=0;
		fclose(fileID);
	}
	return retorno;
}
///////////////////////////////////////////////// MENUS
void menuPrincipal()
{
	printf("\n\t[MENU]\n\n"
		  "1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n"
		  "2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).\n"
		  "3. Alta de pasajero\n"
		  "4. Modificar datos de pasajero\n"
		  "5. Baja de pasajero.\n"
		  "6. Listar pasajeros.\n"
		  "7. Ordenar pasajeros.\n"
		  "8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n"
		  "9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).\n"
		  "10. Salir\n");
}

void menuFlycodes()
{
	printf("\n[FLYCODES]\n"
		  "1. 'BA2491A'\n"
		  "2. 'IB0800A'\n"
		  "3. 'MM0987B'\n"
		  "4. 'TU6789B'\n"
		  "5. 'GU2345F'\n"
		  "6. 'HY4567D'\n"
		  "7. 'FR5678G'\n"
		  "8. 'BR3456J'\n");
}

void menuTypePassengers()
{
	printf("\n[TYPE OF PASSENGER]\n"
			"1. First Class\n"
			"2. Executive Class\n"
			"3. Economy Class\n");
}

void menuModificar()
{
	printf("\n[MODIFICAR]\n"
		  "1. Nombre.\n"
		  "2. Apellido.\n"
		  "3. Precio.\n"
		  "4. Flycode.\n"
		  "5. Tipo de pasajero.\n"
		  "6. Salir de modificar.\n");
}

void menuOrdenar()
{
	printf("\n\t[ORDENAR]\n\n"
		  "1. Ordenar por orden ascendente [A-Z].\n"
		  "2. Ordenar por orden descendente [Z-A].\n"
		  "3. Ordenar por id ascendente [1-10...].\n"
		  "4. Salir de ordenar.\n");
}
//////////////////////////////////////////////CONSTRUCTORES Y DESTRUCTORES
/**
 * @brief Crea un nuevo pasajero de forma dinamica, sin inicializar
 *
 * @return Retorna puntero al pasajero o NULL si hubo error
 */
Passenger* Passenger_new()
{
	Passenger* this = NULL;
	this=(Passenger*) malloc(sizeof(Passenger));
	return this;
}
/**
 * @brief Crea un nuevo pasajero dinamico con char de parametros
 *
 * @param idStr
 * @param nameStr
 * @param lastnameStr
 * @param priceStr
 * @param flycodeStr
 * @param typePassengerStr
 * @param statusFlightStr
 * @return Retorna puntero al pasajero o NULL si hubo error
 */
Passenger* Passenger_newParametros(char* idStr,char* nameStr,char* lastnameStr,char* priceStr,char* flycodeStr,char* typePassengerStr,char* statusFlightStr)
{
	Passenger* this = Passenger_new();

	if(this != NULL && idStr != NULL && nameStr != NULL && lastnameStr != NULL && priceStr != NULL && flycodeStr != NULL && typePassengerStr != NULL && statusFlightStr != NULL)
	{
		if( Passenger_setId(this,atoi(idStr)) == -1 ||
			Passenger_setNombre(this,nameStr) == -1 ||
			Passenger_setCodigoVuelo(this,flycodeStr) == -1 ||
			Passenger_setApellido(this,lastnameStr) == -1 ||
			Passenger_setTipoPasajero(this,Passenger_tipoPasajeroTO_INT(typePassengerStr)) == -1 ||
			Passenger_setPrecio(this,atof(priceStr)) == -1 ||
			Passenger_setEstadoVuelo(this,Passenger_estadoVueloTO_INT(statusFlightStr)) == -1)
		{
			Passenger_delete(this);
			this = NULL;
		}
	}
	return this;
}

/**
 * @brief Crea un nuevo pasajero dinamico con parametros segun sus tipos correspondientes, facilita el pedido de datos
 *
 * @param id
 * @param name
 * @param lastname
 * @param price
 * @param flycode
 * @param typePassenger
 * @param statusFlight
 * @return Retorna puntero al pasajero o NULL si hubo error
 */
Passenger* Passenger_newParametrosNOSTRING(int id,char* name,char* lastname,float price,char* flycode,int typePassenger,int statusFlight)
{
	Passenger* this = NULL;
	this = Passenger_new();

	if(this != NULL && id >0 && name != NULL && lastname != NULL && price >0 && flycode != NULL && typePassenger >0 && statusFlight >0)
	{
		if( Passenger_setId(this,id) == -1 ||
			Passenger_setNombre(this,name) == -1 ||
			Passenger_setCodigoVuelo(this,flycode) == -1 ||
			Passenger_setApellido(this,lastname) == -1 ||
			Passenger_setTipoPasajero(this,typePassenger) == -1 ||
			Passenger_setPrecio(this,price) == -1 ||
			Passenger_setEstadoVuelo(this, statusFlight) == -1)
		{
			Passenger_delete(this);
			this = NULL;
		}
	}
	return this;
}

/**
 * @brief Borra/libera de memoria el pasajero
 *
 * @param this
 */
void Passenger_delete(Passenger* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////GETTERS Y SETTERS

/**
 * @brief Coloca el id del pasajero
 *
 * @param this
 * @param id
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_setId(Passenger* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >=0)
	{
		retorno = 0;
		this->id =id;
	}
	return retorno;
}

/**
 * @brief Obtiene el id del pasajero
 *
 * @param this
 * @param id
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_getId(Passenger* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id !=NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}

/**
 * @brief Coloca el nombre del pasajero
 *
 * @param this
 * @param nombre
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_setNombre(Passenger* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL )
	{
		retorno = 0;
		strcpy(this->nombre, nombre);
	}
	return retorno;
}

/**
 * @brief Obtiene el nombre del pasajero
 *
 * @param this
 * @param nombre
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_getNombre(Passenger* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL )
	{
		retorno = 0;
		strcpy(nombre, this->nombre);
	}
	return retorno;
}

/**
 * @brief Coloca el apellido del pasajero
 *
 * @param this
 * @param apellido
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_setApellido(Passenger* this,char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL )
	{
		retorno = 0;
		strcpy(this->apellido, apellido);
	}
	return retorno;
}

/**
 * @brief Coloca el apellido del pasajero
 *
 * @param this
 * @param apellido
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_getApellido(Passenger* this,char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL )
	{
		retorno = 0;
		strcpy(apellido,this->apellido);
	}
	return retorno;
}

/**
 * @brief Coloca el codigo de vuelo del pasajero
 *
 * @param this
 * @param codigoVuelo
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo)
{
	int retorno = -1;
	if(this != NULL && codigoVuelo != NULL )
	{
		retorno = 0;
		strcpy(this->codigoVuelo, codigoVuelo);
	}
	return retorno;
}
/**
 * @brief Obtiene el codigo de vuelo del pasajero
 *
 * @param this
 * @param codigoVuelo
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo)
{
	int retorno = -1;
	if(this != NULL && codigoVuelo != NULL )
	{
		retorno = 0;
		strcpy(codigoVuelo, this->codigoVuelo);
	}
	return retorno;
}

/**
 * @brief Coloca el tipo de pasajero como ID entero
 *
 * @param this
 * @param tipoPasajero
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero)
{
	int retorno = -1;
	if(this != NULL && tipoPasajero >0)
	{
		retorno = 0;
		this->tipoPasajero= tipoPasajero;
	}
	return retorno;
}

/**
 * @brief Obtiene el tipo de pasajero como ID entero
 *
 * @param this
 * @param tipoPasajero
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero)
{
	int retorno = -1;
	if(this != NULL && tipoPasajero != NULL)
	{
		retorno = 0;
		*tipoPasajero=this->tipoPasajero;
	}
	return retorno;
}

/**
 * @brief Coloca el precio del vuelo del pasajero
 *
 * @param this
 * @param precio
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_setPrecio(Passenger* this,float precio)
{
	int retorno = -1;
	if(this != NULL && precio >=0)
	{
		retorno = 0;
		this->precio=precio;
	}
	return retorno;
}

/**
 * @brief Obtiene el precio del vuelo del pasajero
 *
 * @param this
 * @param precio
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_getPrecio(Passenger* this,float* precio)
{
	int retorno = -1;
	if(this != NULL && precio >=0)
	{
		retorno = 0;
		*precio=this->precio;
	}
	return retorno;
}

/**
 * @brief Coloca el estado de vuelo del pasajero como ID entero
 *
 * @param this
 * @param estadoVuelo
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo)
{
	int retorno = -1;
	if(this != NULL && estadoVuelo>=0)
	{
		retorno = 0;
		this->estadoVuelo=estadoVuelo;
	}
	return retorno;
}

/**
 * @brief Obtiene el estado de vuelo del pasajero como ID entero
 *
 * @param this
 * @param estadoVuelo
 * @return Retorna 0 si es correcto o -1 en caso de error
 */
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo)
{
	int retorno = -1;
	if(this != NULL && estadoVuelo != NULL )
	{
		retorno = 0;
		*estadoVuelo=this->estadoVuelo;
	}
	return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////// CONVERTIDORES

/**
 * @brief Copia el string segun el tipo y devuelve el numero indicado
 * 			1 - FirstClass
 * 			2 - ExecutiveClass
 * 			3 - EconomyClass
 * @param tipoPasajero
 * @return Retorna el tipo de pasajero o -1 si hubo error
 */
int Passenger_tipoPasajeroTO_INT(char* tipoPasajero)
{
	int retorno = -1;
	if(tipoPasajero != NULL)
	{
		if(strcmp(tipoPasajero, "FirstClass")==0)
		{
			retorno = 1;
		}
		else
		{
			if(strcmp(tipoPasajero, "ExecutiveClass")==0)
			{
				retorno = 2;
			}
			else
			{
				if(strcmp(tipoPasajero, "EconomyClass")==0)
				{
					retorno = 3;
				}
			}
		}
	}
	return retorno;
}
/**
 * @brief Copia el tipo (entero) segun el tipo de pasajero y devuelve la descricion
 * 			1 - FirstClass
 * 			2 - ExecutiveClass
 * 			3 - EconomyClass
 * @param tipo
 * @param tipoPasajero
 * @return Retorna 0 si OK y -1 si hubo error
 */
int Passenger_tipoPasajeroTO_STRING(int tipo, char* tipoPasajero)
{
	int retorno = -1;
	if(tipo >0 && tipoPasajero != NULL)
	{
		switch(tipo)
		{
		case 1:
			strcpy(tipoPasajero, "FirstClass");
			break;
		case 2:
			strcpy(tipoPasajero, "ExecutiveClass");
			break;
		case 3:
			strcpy(tipoPasajero, "EconomyClass");
			break;
		}
		retorno =0;
	}
	return retorno;
}

/**
 * @brief Copia el string segun el estado de vuelo y devuelve el numero indicado
 * 			1 - En Vuelo
 * 			2 - Aterrizado
 * 			3 - En Horario
 * 			4 - Demorado
 * @param tipo
 * @param tipoPasajero
 * @return Retorna el numero del estado del vuelo o -1 si hubo error.
 */
int Passenger_estadoVueloTO_INT(char* estadoVuelo)
{
	int retorno = -1;
	if(estadoVuelo != NULL)
	{
		if(strcmp(estadoVuelo, "En Vuelo")==0)
		{
			retorno = 1;
		}
		else
		{
			if(strcmp(estadoVuelo, "Aterrizado")==0)
			{
				retorno = 2;
			}
			else
			{
				if(strcmp(estadoVuelo, "En Horario")==0)
				{
					retorno = 3;
				}
				else
				{
					if(strcmp(estadoVuelo, "Demorado")==0)
					{
						retorno = 4;
					}
				}
			}
		}
	}
	return retorno;
}

/**
 * @brief Copia el estado (entero) del vuelo y devuelve su descricion
 * 			1 - En Vuelo
 * 			2 - Aterrizado
 * 			3 - En Horario
 * 			4 - Demorado
 * @param tipo
 * @param tipoPasajero
 * @return Retorna 0 si OK y -1 si hubo error.
 */
int Passenger_estadoVueloTO_STRING(int estado, char* estadoVuelo)
{
	int retorno = -1;
	if(estado >0 && estadoVuelo != NULL)
	{
		switch(estado)
		{
		case 1:
			strcpy(estadoVuelo, "En Vuelo");
			break;
		case 2:
			strcpy(estadoVuelo, "Aterrizado");
			break;
		case 3:
			strcpy(estadoVuelo, "En Horario");
			break;
		case 4:
			strcpy(estadoVuelo, "Demorado");
			break;
		}
		retorno =0;
	}
	return retorno;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////// ABM
/**
 * @brief Imprime un pasajero
 *
 * @param this
 */
void Passenger_printfOne(Passenger* this)
{
    int auxId;
    char auxName[51];
    char lastname[51];
    float auxPrice;
    char auxFlyCode[51];
    int auxTypePassenger;
    char auxTypePassengerChar[51];
    int auxStatusFlight;
    char auxStatusFlightChar[51];
    if(this!=NULL)
    {
        if(Passenger_getId(this, &auxId)==0 &&
        	Passenger_getNombre(this, auxName)==0 &&
			Passenger_getApellido(this, lastname)==0 &&
			Passenger_getPrecio(this, &auxPrice)==0 &&
			Passenger_getCodigoVuelo(this, auxFlyCode)==0 &&
			Passenger_getTipoPasajero(this, &auxTypePassenger)==0 &&
			Passenger_getEstadoVuelo(this, &auxStatusFlight)==0)
        {
        	Passenger_tipoPasajeroTO_STRING(auxTypePassenger, auxTypePassengerChar);
        	Passenger_estadoVueloTO_STRING(auxStatusFlight, auxStatusFlightChar);
			printf("|%5d|%-17s|%-17s|%11.2f|%10s|%-17s|%-11s|\n",auxId,auxName,lastname,auxPrice, auxFlyCode, auxTypePassengerChar, auxStatusFlightChar);
        }
    }
}

/**
 * @brief Da el alta de un pasajero ingresado
 *
 * @param pArrayListPassenger
 * @return retorna 0 si OK y -1 si hubo error
 */
int Passenger_alta(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	Passenger* auxPassenger = NULL;

	int id;
	char name[51];
	char lastname[51];
	float price;
	int flycode;
	char flycodeChar[10];
	int typePassenger;
	int statusFlight;

	if(pArrayListPassenger!=NULL)
	{
		//SET UNIQUE ID - AUTOINCREMENTAL CON ARCHIVO TXT
		id = id_readAndSet();

		//NAME
		if(utn_getNombre(name, sizeof(name), "\nIngrese el nombre del pasajero: ", "\nERROR, NO ES UN NOMBRE, Try again: ", 5)==-1)
		{
			printf("\nERROR EN ALTA: 'NOMBRE'\n");
		}

		//LASTNAME
		if(utn_getNombre(lastname, sizeof(lastname), "Ingrese el apellido del pasajero: ", "\nERROR, NO ES UN APELLIDO, Try again: ", 5)==-1)
		{
			printf("\nERROR EN ALTA: 'APELLIDO'\n");
		}

		//PRICE
		if(utn_getNumeroFlotante(&price, "Ingrese el precio del vuelo: ", "\nERROR, INVALIDO, Try again: ", 10000, 500000, 5)==-1)
		{
			printf("\nERROR EN ALTA: 'PRECIO'\n");
		}

		//FLYCODE
		menuFlycodes();
		if(utn_getNumero(&flycode, "Opcion: ", "\nERROR, INVALID), Try again: ", 1, 8, 5)==-1)
		{
			printf("\nERROR EN ALTA: 'FLYCODE'\n");
		}
		else
		{
			Passengers_setFlycodebyID(flycode, flycodeChar);
		}

		//TYPE PASSENGER
		menuTypePassengers();
		if(utn_getNumero(&typePassenger, "Number: ", "\nERROR, INVALID, Try again: ", 1, 3, 5)==-1)
		{
			printf("\nERROR EN ALTA: 'TYPE PASSENGER'\n");
		}

		//SET STATUS FLIGHT by FLYCODE
		if(Passenger_setStatusFlightbyFLYCODE(flycodeChar, &statusFlight)<0)
		{
			printf("\nERROR EN ALTA: 'SET STATUS FLIGHT'\n");
		}

		//UNA VEZ PEDIDOS LOS DATOS LO CARGO AL ARRAY DINAMICO
		auxPassenger = Passenger_newParametrosNOSTRING(id, name, lastname, price, flycodeChar, typePassenger, statusFlight);

		//LO AGREGO A LA LISTA DINAMICA
		if(auxPassenger!=NULL)
		{
			ll_add(pArrayListPassenger, auxPassenger);
			retorno=0;
			id_write(&id);
		}
	}
	return retorno;
}

/**
 * @brief Retorna el id del codigo de vuelo segun su descripcion
 *
 * @param idFlycode
 * @param flycodeChar
 * @return -1 si hubo error, y mayor a 0 si OK.
 */
int Passengers_setFlycodebyID(int idFlycode, char* flycodeChar)
{
	int retorno = -1;
	if(idFlycode>0 && flycodeChar!=NULL)
	{
		retorno=0;
		switch(idFlycode)
		{
		case 1:
			strcpy(flycodeChar, "BA2491A");
			retorno=1;
			break;
		case 2:
			strcpy(flycodeChar, "IB0800A");
			retorno=2;
			break;
		case 3:
			strcpy(flycodeChar, "MM0987B");
			retorno=3;
			break;
		case 4:
			strcpy(flycodeChar, "TU6789B");
			retorno=4;
			break;
		case 5:
			strcpy(flycodeChar, "GU2345F");
			retorno=5;
			break;
		case 6:
			strcpy(flycodeChar, "HY4567D");
			retorno=6;
			break;
		case 7:
			strcpy(flycodeChar, "FR5678G");
			retorno=7;
			break;
		case 8:
			strcpy(flycodeChar, "BR3456J");
			retorno=8;
			break;
		}
	}
	return retorno;
}

/**
 * @brief Coloca el ID del estado del vuelo segun el codigo de vuelo ingresado.
 *
 * @param flycodeChar
 * @param statusFlight
 * @return mayor a 0 si OK y -1 si hubo error.
 */
int Passenger_setStatusFlightbyFLYCODE(char* flycodeChar, int* statusFlight)
{
	int retorno = -1;
	if(flycodeChar!=NULL && statusFlight!=NULL)
	{
		retorno=0;
		//"En Vuelo"
		if(strcmp(flycodeChar, "GU2345F")==0)
		{
			*statusFlight=1;
			retorno=1;
		}
		else
		{
			//"Aterrizado"
			if(strcmp(flycodeChar, "BA2491A")==0 || strcmp(flycodeChar, "IB0800A")==0 || strcmp(flycodeChar, "TU6789B")==0)
			{
				*statusFlight=2;
				retorno=2;
			}
			else
			{
				//"En Horario"
				if(strcmp(flycodeChar, "MM0987B")==0 || strcmp(flycodeChar, "FR5678G")==0)
				{
					*statusFlight=3;
					retorno=3;
				}
				else
				{
					//"Demorado"
					if(strcmp(flycodeChar, "HY4567D")==0 || strcmp(flycodeChar, "BR3456J")==0)
					{
						*statusFlight=4;
						retorno=4;
					}
				}
			}
		}
	}
	return retorno;
}

/**
 * @brief Modifica mediante la opcion que se ingrese a un pasajero
 *
 * @param pArrayListPassenger
 * @return -1 si hubo error y 0 si OK
 */
int Passenger_modificarPasajero(LinkedList* pArrayListPassenger)
{
	Passenger* auxPassenger;
	int retorno=-1;
	int idAux;
	int indexEncontrado;
	int opcion;

	char name[51];
	char lastname[51];
	float price;
	int flycode;
	char flycodeChar[10];
	int statusFlight;
	int typePassenger;

	if(pArrayListPassenger!=NULL)
	{
		controller_ListPassenger(pArrayListPassenger);
		auxPassenger=Passenger_new();
		utn_getNumero(&idAux, "Ingrese el ID a modificar: ", "ERROR, ID no valido, reintente: ", 1, 10000, 3);

		indexEncontrado=Passenger_buscarID(pArrayListPassenger, idAux);
		if(indexEncontrado!=-1)
		{
			auxPassenger=(Passenger*)ll_get(pArrayListPassenger, indexEncontrado);
			menuModificar();
			if(utn_getNumero(&opcion, "Opcion: ", "Opcion NO VALIDA, reintente: ", 1, 6, 3)==0)
			{

				switch(opcion)
				{
				case 1:
					//NAME
					if(utn_getNombre(name, sizeof(name), "\nIngrese NUEVO nombre: ", "\nERROR, NO CORRESPONDE, Try again: ", 5)==0)
					{
						if(Passenger_setNombre(auxPassenger, name)==0)
						{
							retorno=0;
							printf("\nMODIFICACION: 'NOMBRE', EXITO.\n");
						}
					}
					break;
				case 2:
					//LASTNAME
					if(utn_getNombre(lastname, sizeof(lastname), "\nIngrese NUEVO apellido: ", "\nERROR, NO CORRESPONDE, Try again: ", 5)==0)
					{
						if(Passenger_setApellido(auxPassenger, lastname)==0)
						{
							retorno=0;
							printf("\nMODIFICACION: 'APELLIDO', EXITO.\n");
						}
					}
					break;
				case 3:
					//PRICE
					if(utn_getNumeroFlotante(&price, "\nIngrese NUEVO precio de vuelo: ", "\nERROR, NO CORRESPONDE, Try again: ", 1000, 500000, 5)==0)
					{
						if(Passenger_setPrecio(auxPassenger, price)==0)
						{
							retorno=0;
							printf("\nMODIFICACION: 'PRECIO', EXITO.\n");
						}
					}
					break;
				case 4:
					//FLYCODE
					menuFlycodes();
					if(utn_getNumero(&flycode, "Opcion: ", "\nERROR, NO CORRESPONDE, Try again: ", 1, 8, 3)==0)
					{
						if(Passengers_setFlycodebyID(flycode, flycodeChar)>0)
						{
							if(Passenger_setCodigoVuelo(auxPassenger, flycodeChar)==0)
							{
								retorno=0;
								printf("\nMODIFICACION: 'FLYCODE', EXITO.\n");
							}
						}
					}
					//STATUS FLIGHT by FLYCODE
					if(Passenger_setStatusFlightbyFLYCODE(flycodeChar, &statusFlight)>0)
					{
						Passenger_setEstadoVuelo(auxPassenger, statusFlight);
					}
					break;
				case 5:
					//TYPE PASSENGER
					menuTypePassengers();
					if(utn_getNumero(&typePassenger, "Opcion: ", "\nERROR, INVALID, Try again: ", 1, 3, 5)==0)
					{
						if(Passenger_setTipoPasajero(auxPassenger, typePassenger)==0)
						{
							retorno=0;
							printf("\nMODIFICACION: 'TYPE PASSENGER', EXITO.\n");
						}
					}
					break;
				case 6:
					retorno=0;
					printf("\nSaliendo de modificar...\n");
					break;
				}
			}
		}
		else
		{
			printf("\nERROR; NO SE ENCONTRO ID\n");
		}
	}
	return retorno;
}

/**
 * @brief Recorre la lista dinamica en busca de un id que se ingrese y devuelve su posicion
 *
 * @param pArrayListPassenger
 * @param id
 * @return Retorna el indice o -1 si hubo error
 */
int Passenger_buscarID(LinkedList* pArrayListPassenger, int id)
{
	int retorno=-1;
	Passenger* auxPassenger=NULL;
	int len = ll_len(pArrayListPassenger);
	int idGet;

	if(pArrayListPassenger!=NULL)
	{
		for(int i=0;i<len;i++)//1
		{
			auxPassenger=(Passenger*)ll_get(pArrayListPassenger, i);//i-1
			Passenger_getId(auxPassenger, &idGet);

			if(idGet==id)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

/**
 * @brief Daa de baja fisica a un ID que se seleccione
 *
 * @param pArrayListPassenger
 * @return 0 si OK y -1 si hubo error.
 */
int Passenger_baja(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	Passenger* auxPassenger;
	int idAux;
	int indexEncontrado;
	char respuesta;

	if(pArrayListPassenger!=NULL)
	{
		controller_ListPassenger(pArrayListPassenger);
		utn_getNumero(&idAux, "\nIngrese el ID a borrar: ", "ERROR, ID no valido, reintente: ", 1, 10000, 3);
		indexEncontrado=Passenger_buscarID(pArrayListPassenger, idAux);
		if(indexEncontrado!=-1)
		{
			utn_getCaracterMAYUS(&respuesta, "\nDesea borrar?:\n[S] para continuar, otro para cancelar: ", "ERROR, Opcion no valida, reintente: ", 'A', 'Z', 5);
			if(respuesta=='S')
			{
				auxPassenger=(Passenger*)ll_get(pArrayListPassenger, indexEncontrado);
				if(auxPassenger!=NULL)
				{
					ll_remove(pArrayListPassenger, indexEncontrado);
					retorno=0;
				}
			}
		}
		else
		{
			printf("\nERROR; NO SE ENCONTRO ID\n");
		}
	}
	return retorno;
}

/**
 * @brief Devuelve el modo de ordenar a los pasajeros por su nombre y apellido
 * Modo de ordenar:
 * 		//A-Z por nombre y apellido = 1;
 *		//Z-A por nombre y apellido = -1;
 * @param pPassengerA
 * @param pPassengerB
 * @return modo de ordenar, 0 si no se pudo obtener los campos o -2 si hubo error.
 */
int Passenger_sortNombreApellido(void* pPassengerA, void* pPassengerB)
{
	int retorno=-2;
	Passenger* passengerA;
	Passenger* passengerB;

	char nombreA[51];
	char nombreB[51];
	char apellidoA[51];
	char apellidoB[51];

	if(pPassengerA!=NULL && pPassengerB!=NULL)
	{
		passengerA=pPassengerA;
		passengerB=pPassengerB;
		retorno=0;
		if((Passenger_getNombre(passengerA, nombreA)==0) &&
			(Passenger_getNombre(passengerB, nombreB)==0) &&
			(Passenger_getApellido(passengerA, apellidoA)==0) &&
			(Passenger_getApellido(passengerB, apellidoB)==0))
		{
			//A-Z nombre
			if(strcmp(nombreA,nombreB)>0)
			{
				retorno=1;
			}
			//Z-A nombre
			if(strcmp(nombreA,nombreB)<0)
			{
				retorno=-1;
			}
			//IGUAL nombre
			if(strcmp(nombreA,nombreB)==0)
			{
				//A-Z apellido
				if(strcmp(apellidoA,apellidoB)>0)
				{
					retorno=1;
				}
				//Z-A apellido
				if(strcmp(apellidoA,apellidoB)<0)
				{
					retorno=-1;
				}
			}
		}
	}
	return retorno;
}

/**
 * @brief Devuelve el modo de ordenar a los pasajeros por su ID
 * Modo de ordenar:
 * 		//ID ascendente = 1;
 *		//ID descendente = -1;
 * @param pPassengerA
 * @param pPassengerB
 * @return modo de ordenar, 0 si no se pudo obtener los campos o -2 si hubo error.
 */
int Passenger_sortID(void* pPassengerA, void* pPassengerB)
{
	int retorno=-2;
	Passenger* passengerA;
	Passenger* passengerB;

	int idA, idB;

	if(pPassengerA!=NULL && pPassengerB!=NULL)
	{
		passengerA=pPassengerA;
		passengerB=pPassengerB;
		retorno=0;
		if((Passenger_getId(passengerA, &idA)==0) &&
			(Passenger_getId(passengerB, &idB)==0))
		{
			if(idA > idB)
			{
				retorno=1;
			}
			if(idA < idB)
			{
				retorno=-1;
			}
		}
	}
	return retorno;
}
