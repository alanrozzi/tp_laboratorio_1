#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "validaciones.h"
#include "ArrayPassenger.h"

#define QTYPASSENGERS 2000
#define HARDCODE 5

int main(void) {

	setbuf(stdout,NULL);
	int opcion;
	int opcionCUATRO;

	//STRUCTS ARRAYS
	ePassenger passengers[QTYPASSENGERS];
	eFlight flights[4];

	//INNIT
	if(initPassengers(passengers, QTYPASSENGERS)==0)
	{
		printf("\n\tWELCOME\n");
	}
	else
	{
		printf("INICIALIZATION FAILED");
	}

	//HARCODE
	hardcodePassengers(passengers, HARDCODE);
	hardcodeFlight(flights);

	do
	{
		utn_getNumero(&opcion, "\nSelect an option:\n\n1.New passenger\n2.Modify by ID\n3.Unsubscribe by ID\n4.List of informs\n5.Exit\nOption: ", "\n[ERROR]\tNo es una opcion valida, intentelo nuevamente: ", 1, 5, 5);
		switch(opcion)
		{
			//ALTA
			case 1:
				getValidData(passengers, QTYPASSENGERS, flights);
				break;

			//MODIFICAR
			case 2:
				if(isAny(passengers, QTYPASSENGERS)>0)
				{
					modifyPassenger(passengers, QTYPASSENGERS, flights);
				}
				else
				{
					printf("There's no data, please subscribe a passenger");
				}
				break;

			//BAJA
			case 3:
				if(isAny(passengers, QTYPASSENGERS)>0)
				{
					removePassengerLOGIC(passengers, QTYPASSENGERS);
				}
				else
				{
					printf("There's no data, please subscribe a passenger");
				}
				break;

			//INFORMAR
			case 4:

				if(isAny(passengers, QTYPASSENGERS)>0)
				{
					utn_getNumero(&opcionCUATRO, "\n1. List of passengers in certain order...\n2. Total and average of FLY prices, and how many passengers pass this average.\n3. List if passengers by FLYcode ACTIVES.\n4.List all passengers\n5.Exit\nOption: ", "\n[ERROR]\tINVALID NUMBER, TRY AGAIN: ", 1, 5, 3);

					switch(opcionCUATRO)
					{
					case 1:
						//1. Listado de los pasajeros ordenados alfabéticamente por Apellido y Tipo de pasajero.
						sortPassengersBy(passengers, QTYPASSENGERS);
						printPassenger(passengers, QTYPASSENGERS, flights);
						break;
					case 2:
						//2. Total y promedio de los precios de los pasajes, y cuántos pasajeros superan el precio promedio.
						printf("\nTOTAL prices: %.2f",totalPrices(passengers, QTYPASSENGERS));
						printf("\nPrices average: %.2f",averagePrices(passengers, QTYPASSENGERS));
						printf("\nCount of passengers that pass the average: %d\n",surpassAverage(passengers, QTYPASSENGERS));
						break;
					case 3:
						//3. Listado de los pasajeros por Código de vuelo y estados de vuelos ‘ACTIVO’
						activeFlycodes(passengers, QTYPASSENGERS, flights);
						break;
					case 4:
						printPassenger(passengers, QTYPASSENGERS, flights);
						break;
					}
				}
				else
				{
					printf("There's no data, please subscribe a passenger");
				}
		}
	}while(opcion!=5);
}
