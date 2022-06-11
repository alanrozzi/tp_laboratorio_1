#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "Controller.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	Passenger* pAuxPassenger = Passenger_new();
	int retorno=-1;
	char id[1024];
	char name[1024];
	char lastname[1024];
	char price[1024];
	char flycode[1024];
	char typePassenger[1024];
	char statusFlight[1024];

	if(pFile!=NULL && pArrayListPassenger!=NULL)
	{
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id,name,lastname,price,flycode,typePassenger,statusFlight);
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id,name,lastname,price,flycode,typePassenger,statusFlight)==7)
			{
				pAuxPassenger = Passenger_newParametros(id, name, lastname, price, flycode, typePassenger, statusFlight);

				if(pAuxPassenger!=NULL)
				{
					ll_add(pArrayListPassenger, pAuxPassenger);
					retorno=0;
				}
			}
		}while(!feof(pFile));
	}
	return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	Passenger* pAuxPassenger = NULL;

	if(pFile!=NULL && pArrayListPassenger!=NULL)
	{
		do
		{
			pAuxPassenger = Passenger_new();
			if(pAuxPassenger!=NULL)
			{
				if(fread(pAuxPassenger, sizeof(Passenger),1,pFile)==1)
				{
					ll_add(pArrayListPassenger, pAuxPassenger);
					retorno=0;
				}
			}
		}while(!feof(pFile));
	}
	return retorno;
}
