/*
 * ArrayPassenger.h
 *
 *  Created on: 29 abr. 2022
 *      Author: alanr
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_
#define MAXCHARS 51

typedef struct{
	char flycode[10];
	int StatusFlight;
	char descStatusFlight[MAXCHARS];
}eFlight;

typedef struct{
	int id; //autoingremental
	char name[MAXCHARS];
	char lastName[MAXCHARS];
	float price;
	char flycode[10]; //LLLL33333 (4letra y 5 num)
	int typePassenger; //documento
	int isEmpty; //TRUE=1, FALSE=0
}ePassenger;

//////////////////////////////////// HARDCODE STRUCT
void hardcodeFlight(eFlight* flights);//DONE
void hardcodePassengers(ePassenger* list, int lenght); //DONE

//////////////////////////////////// ABM
int printPassenger(ePassenger* list, int length, eFlight* flights); //DONE
void printONEPassenger(ePassenger list, eFlight* flights);//DONE
int getValidData(ePassenger* list, int len, eFlight* flights);//DONE
int addPassenger(ePassenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[]);//DONE
int isAny(ePassenger* list, int len); //DONE
int initPassengers(ePassenger* list, int len); //DONE
int findPassengerById(ePassenger* list, int len,int id);//DONE
int removePassenger(ePassenger* list, int len, int id);//DONE
int removePassengerLOGIC(ePassenger* list, int len);//DONE
int searchEmptySpace(ePassenger* list, int len);//DONE
int modifyPassenger(ePassenger* list, int len,eFlight* flights);//DONE

//////////////////////////////////// SORT
//1. Listado de los pasajeros ordenados alfabéticamente por Apellido y Tipo de pasajero.
int sortPassengersBy(ePassenger* list, int len);//DONE
int sortPassengersFLYcode(ePassenger* list, int len, int order);//DONE
int sortPassengersLastname(ePassenger* list, int len, int order);//DONE

//////////////////////////////////// LIST

//2. Total y promedio de los precios de los pasajes, y cuántos pasajeros superan el precio promedio.
float totalPrices(ePassenger* list, int len);
float averagePrices(ePassenger* list, int len);
int surpassAverage(ePassenger* list, int len);
//3. Listado de los pasajeros por Código de vuelo y estados de vuelos ‘ACTIVO’
int activeFlycodes(ePassenger* list, int len,eFlight* flights);

#endif /* ARRAYPASSENGER_H_ */
