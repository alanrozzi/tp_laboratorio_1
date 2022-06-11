#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utn.h"
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "Controller.h"

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger)
{
	FILE* pArchivo;
	int retorno=-1;
	if(path!=NULL && pArrayListPassenger!=NULL)
	{
		pArchivo = fopen(path, "r");
		if(pArchivo!=NULL)
		{
			if(parser_PassengerFromText(pArchivo, pArrayListPassenger)==0)
			{
				retorno=0;
				fclose(pArchivo);
				printf("\n\t[ARCHIVO TEXTO LEIDO CON EXITO]\n");
			}
			else
			{
				printf("\n\t[ERROR, ARCHIVO NO EXISTENTE]\n");
			}
		}
	}
    return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger)
{
	FILE* pArchivoBIN;
	int retorno=-1;
	if(path!=NULL && pArrayListPassenger!=NULL)
	{
		pArchivoBIN = fopen(path, "rb");
		if(pArchivoBIN!=NULL)
		{
			if(parser_PassengerFromBinary(pArchivoBIN, pArrayListPassenger)==0)
			{
				retorno=0;
				fclose(pArchivoBIN);
				printf("\n\t[ARCHIVO BINARIO GUARDADO CON EXITO]\n");
			}
			else
			{
				printf("\n\t[ERROR, ARCHIVO NO EXISTENTE]\n");
			}
		}

	}
	return retorno;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger) ////////////////////////////////////////////////////////////////////////////MODIFICAAAAAAAAAR
{
	int retorno=-1;
	if(pArrayListPassenger!=NULL)
	{
		if(Passenger_alta(pArrayListPassenger)==0)
		{
			retorno=0;
			printf("\n\t[PASAJERO CARGADO CON EXITO]\n");
		}
		else
		{
			printf("\n\t[ERROR EN LA CARGA]\n");
		}
	}
	return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	if(pArrayListPassenger!=NULL)
	{
		if(Passenger_modificarPasajero(pArrayListPassenger)==0)
		{
			retorno=0;
			printf("\n\t[PASAJERO MODIFICADO CON EXITO]\n");
		}
		else
		{
			printf("\n\t[ERROR EN LA MODIFICACION]\n");
		}
	}

	return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	if(pArrayListPassenger!=NULL)
	{
		if(Passenger_baja(pArrayListPassenger)==0)
		{
			retorno=0;
			printf("\n\t[PASAJERO DADO DE BAJA CON EXITO]\n");
		}
		else
		{
			printf("\n\t[ERROR EN LA BAJA]\n");
		}
	}
	return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	Passenger* auxPassenger=NULL;
	int len = ll_len(pArrayListPassenger);
	int i;

	printf("\n|  ID |NOMBRE		|APELLIDO	  |	PRECIO|	  FLYCODE|TYPE PASSENGER   |STATUS     |\n");
	printf("================================================================================================\n");
	if(pArrayListPassenger!=NULL)
	{
		for(i=0;i<len;i++)
		{
			auxPassenger=ll_get(pArrayListPassenger, i);
			if(auxPassenger!=NULL)
			{
				Passenger_printfOne(auxPassenger);
				retorno=0;
			}
		}
	}
    return retorno;
}


/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
    int retorno=-1;
    int opcion;

    if(pArrayListPassenger!=NULL)
    {
        do
        {
        	menuOrdenar();
        	utn_getNumero(&opcion, "Option: ", "\nERROR, INVALID, Try again: ", 1, 4, 3);
            switch(opcion)
            {
            case 1:
                ll_sort(pArrayListPassenger, Passenger_sortNombreApellido, 1);
                printf("[ORDEN EXITOSO]\n");
                controller_ListPassenger(pArrayListPassenger);
                retorno=0;
                break;
            case 2:
                ll_sort(pArrayListPassenger, Passenger_sortNombreApellido, -1);
                printf("[ORDEN EXITOSO]\n");
                controller_ListPassenger(pArrayListPassenger);
                retorno=0;
                break;
            case 3:
                ll_sort(pArrayListPassenger, Passenger_sortID, 1);
                printf("[ORDEN EXITOSO]\n");
                controller_ListPassenger(pArrayListPassenger);
                retorno=0;
                break;
            case 4:
                printf("\n[SALIENDO DE ORDENAR]\n");
                retorno=0;
                break;
            }
        }
        while(opcion!=4);
    }
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	FILE* pArchivo;
	Passenger* auxPassenger = Passenger_new();

	int len;
	int auxId;
	char auxName[51];
	char auxLastname[51];
	float auxPrice;
	char auxFlyCode[51];
	int auxTypePassenger;
	char auxTypePassengerChar[51];
	int auxStatusFlight;
	char auxStatusFlightChar[51];

	if(path!=NULL && pArrayListPassenger!=NULL)
	{
		len = ll_len(pArrayListPassenger);
		pArchivo=fopen(path,"w");

		if(pArchivo!=NULL)
		{
			fprintf(pArchivo, "id,name,lastname,price,flycode,typePassenger,statusFlight\n");
			for(int i=0; i<len; i++)
			{
				auxPassenger = ll_get(pArrayListPassenger, i);

				if(Passenger_getId(auxPassenger,&auxId)==0 &&
				   Passenger_getNombre(auxPassenger, auxName)==0 &&
				   Passenger_getApellido(auxPassenger, auxLastname)==0 &&
				   Passenger_getPrecio(auxPassenger, &auxPrice)==0 &&
				   Passenger_getCodigoVuelo(auxPassenger, auxFlyCode)==0 &&
				   Passenger_getTipoPasajero(auxPassenger, &auxTypePassenger)==0 &&
				   Passenger_getEstadoVuelo(auxPassenger, &auxStatusFlight)==0)
				{
					Passenger_tipoPasajeroTO_STRING(auxTypePassenger, auxTypePassengerChar);
					Passenger_estadoVueloTO_STRING(auxStatusFlight, auxStatusFlightChar);

					fprintf(pArchivo, "%d,%s,%s,%.2f,%s,%s,%s\n",auxId,auxName,auxLastname,auxPrice,auxFlyCode,auxTypePassengerChar,auxStatusFlightChar);
				}
				else
				{
					printf("\n\t[ARCHIVO TEXTO ERRONEO]\n");
					break;
				}
			}
			fclose(pArchivo);
			retorno=0;
			printf("\n\t[ARCHIVO TEXTO GUARDADO EXITOSAMENTE]\n");
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno=-1;

	FILE* pArchivoBIN;
	Passenger* auxPassengerBIN;
	int len = ll_len(pArrayListPassenger);

	if(path!=NULL && pArrayListPassenger!=NULL)
	{
		pArchivoBIN=fopen(path,"wb");
		if(pArchivoBIN!=NULL)
		{
			for(int i=0; i<len; i++)
			{
				auxPassengerBIN = ll_get(pArrayListPassenger, i);
				fwrite(auxPassengerBIN, sizeof(Passenger), 1, pArchivoBIN);
			}
			retorno=0;
			fclose(pArchivoBIN);
			printf("\n\t[ARCHIVO BINARIO GUARDADO EXITOSAMENTE]\n");
		}
		else
		{
			printf("\n\t[ARCHIVO BINARIO ERRONEO]\n");
		}
	}
	return retorno;
}
