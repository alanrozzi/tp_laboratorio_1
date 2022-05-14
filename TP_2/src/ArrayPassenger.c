/*
 * “ArrayPassenger.c
 *
 *  Created on: 29 abr. 2022
 *      Author: alanr
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "validaciones.h"
#include "ArrayPassenger.h"

///////////////////////////////////////////////// ID AUTOINCREMENTAL

static int ePassenger_GetID(void);
static int ePassenger_GetID(void) {
	static int ePassenger_idIncremental = 10006; //hardcode 5 ids.
	return ePassenger_idIncremental++;
}

///////////////////////////////////////////////// HARDCODE STRUCT

void hardcodeFlight(eFlight* flights)
	{
		char flycode[][10] = {"LAER-3753", "SERT-7245", "MTRG-2960", "MTQG-2966"};
		int StatusFlight[]= {1, 2, 3, 2};
		char descStatusFlight[][51] = {"ACTIVE", "CANCELED", "LATE", "CANCELED"};
		//recorro la estructura para setear
		for(int i=0; i<4; i++)
		{
			strcpy(flights[i].flycode, flycode[i]);
			flights[i].StatusFlight=StatusFlight[i];
			strcpy(flights[i].descStatusFlight, descStatusFlight[i]);
		}
	}

void hardcodePassengers(ePassenger* list, int lenght)
{
	int id[] = {10001, 10002, 10003, 10004, 10005};
	char name[][51] = {"Brenda", "Paloma", "Ezequiel", "Cristian", "Ariel"};
	char lastName[][51] = {"Merida", "Albedo", "Merida", "Lobos", "Palaso"};
	float price[] = {120000, 150000.5, 200000, 145000.7, 130000.5};
	char flycode[][10] = {"LAER-3753", "SERT-7245", "LAER-3753", "SERT-7245", "MTQG-2966"};
	int typePassenger[] = {39175783, 38135284, 12349031, 86752484, 93671763};

	for(int i=0; i<lenght; i++)
	{
		list[i].id=id[i];
		strcpy(list[i].name,name[i]);
		strcpy(list[i].lastName,lastName[i]);
		list[i].price=price[i];
		strcpy(list[i].flycode,flycode[i]);
		list[i].typePassenger=typePassenger[i];

		list[i].isEmpty=0;
	}
	//printf("\tHARDCODE\n\n");
}

////////////////////////////////////////////////////////////////////ABM

/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initPassengers(ePassenger* list, int len)
{
	int retorno=-1;
	int i;
	//list are the passengers
	if(list!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			//its empty, true
			list[i].isEmpty=1;
		}
		retorno=0;
	}
	return retorno;
}

/// @brief Counts how many passenger are in the program.
///
/// @param list passenger
/// @param len int
/// @return if -1 ERROR else the counter of passengers.
int isAny(ePassenger* list, int len)
{
	int counter=0;
	if(list!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty==0)
			{
				counter++;
			}
		}
		return counter;
	}
	return -1;
}

/** \brief add in a existing list of passengers the values received as parameters
* in the first empty position
* \param list passenger*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param price float
* \param typePassenger int
* \param flycode[] char
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*/
int addPassenger(ePassenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[])
{
	int retorno=-1;
	int i;

	if(list!=NULL && len>0 && id>0 && name!=NULL && lastName!=NULL && price>0 && typePassenger>0 && flycode!=NULL)
	{
		for (i=0;i<len;i++)
		{
			if(list[i].isEmpty==1)
			{
				list[i].id=id;
				strcpy(list[i].name,name);
				strcpy(list[i].lastName,lastName);
				list[i].price=price;
				list[i].typePassenger=typePassenger;
				strcpy(list[i].flycode,flycode);
				list[i].isEmpty=0;
				break;
			}
		}
		retorno=0;
	}
	return retorno;
}

int getValidData(ePassenger* list, int len, eFlight* flights)
{
	int retorno=-1;

	if(list!=NULL && len>0)
	{
		int id;
		char name[51];
		char lastName[51];
		float price;
		int typePassenger;
		char flycode[10];
		int caseFlycode;

		//SET UNIQUE ID - STATIC AUTOINCREMENTAL
		id = ePassenger_GetID();

		//NAME
		printf("\nEnter name's passenger: ");
		while(utn_getString(name, sizeof(name))!=0)
		{
			printf("\nERROR, NOT A NAME, Try again: ");
		}

		//LASTNAME
		printf("Enter lastname's passenger: ");
		while(utn_getString(lastName, sizeof(lastName))!=0)
		{
			printf("\nERROR, NOT A LASTNAME, Try again: ");
		}

		//PRICE
		utn_getNumeroFlotante(&price, "Enter flight price: ", "\nERROR, INVALID, Try again: ", 1000, 500000, 5);

		//DNI
		utn_getNumero(&typePassenger, "Enter passangers DNI: ", "\nERROR, INVALID, Try again: ", 10000000, 50000000, 5);

		//FLYCODE
		utn_getNumero(&caseFlycode, "Enter FLYCODE:\n1. 'LAER-3753'\n2. 'SERT-7245'\n3. 'MTRG-2960'\n4. 'MTQG-2966'\nOption: ", "\nERROR, INVALID, Try again: ", 1, 4, 5);
		switch(caseFlycode)
		{
		case 1:
			strcpy(flycode,flights[0].flycode);
			break;
		case 2:
			strcpy(flycode,flights[1].flycode);
			break;
		case 3:
			strcpy(flycode,flights[2].flycode);
			break;
		case 4:
			strcpy(flycode,flights[3].flycode);
			break;
		}

		if(addPassenger(list, len, id, name, lastName, price, typePassenger, flycode)==0)
		{
			printf("\tVALID DATA\n\tGoing back to menu...\n");
		}
		retorno=0;
	}
	return retorno;
}

/** \brief find a Passenger by Id en returns the index position in array.
*
* \param list Passenger*
* \param len int
* \param id int
* \return Return passenger index position or (-1) if [Invalid length or
NULL pointer received or passenger not found]
*
*/
int findPassengerById(ePassenger* list, int len,int id)
{
	if (list!=NULL && len>0)
	{
		for (int i=0; i<len; i++)
		{
			if (list[i].id==id && list[i].isEmpty==0)
			{
				return i; //retorna el indice buscado
				break;
			}
		}
	}
	return -1;
}

/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
*
* \param list Passenger*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*
*/
int removePassenger(ePassenger* list, int len, int id)
{
	if(list != NULL && len > 0)
	{
		if(findPassengerById(list, len, id)==-1)
		{
			return 0;
		}
		return 1;
	}
	return -1;
}

/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
*
* \param list Passenger*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*/
int removePassengerLOGIC(ePassenger* list, int len)
{
	int idAux;
	int IndexAux;
	char confirm;

	if( list != NULL && len > 0)
	{

		utn_getNumero(&idAux, "\nEnter ID to unsubscribe: ", "\nERROR INVALID NUMBER FOR ID, TRY AGAIN ", 10000, 12000, 5);
		while(removePassenger(list, len, idAux)==0)
		{
			utn_getNumero(&idAux, "\n|DOES NOT EXIST|\n Enter valid ID to unsubscribe: ", "\nERROR INVALID NUMBER FOR ID, TRY AGAIN ", 10000, 12000, 5);
		}

		//busco el indice del ID
		IndexAux=findPassengerById(list, len, idAux);
		utn_getCaracter(&confirm, "\nYou want to unsubscribe this ID? 'y' to continue, else to cancel", "NOT A VALID LETTER TRY AGAIN: ", 'a', 'z', 3);
		confirm=toupper(confirm);
		if(confirm=='Y')
		{
			list[IndexAux].isEmpty=1;
			printf("\n\t[UNSUBSCRIBED]\n\n");
		}
		else
		{
			printf("\n\t[CANCELLED, GOING BACK TO MENU]\n\n");
		}
		return 1;
	}
	return -1;
}

/**
* \brief Select between two options of order
*
* \param list Passenger*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortPassengersBy(ePassenger* list, int len)
{
	int selectedWay;
	int selectedOrder;

	if (list != NULL && len > 0)
	{
		utn_getNumero(&selectedWay, "\nEnter de way you want to order Passengers.\n1. By FLYcode and Status.\n2. By lastname and DNI\nOption: ", "INVALID NUMBER, Try again:", 1, 2, 5);
		switch(selectedWay)
		{
		case 1: //ORDER BY FLYCODE
			utn_getNumero(&selectedOrder, "\nEnter the order.\n1. UP.\n2. DOWN\nOption: ", "INVALID NUMBER, Try again: ", 1, 2, 5);
				sortPassengersFLYcode(list, len, selectedOrder);
			printf("\n\tOrder complete.\n");
			break;
		case 2: //ORDER BY LASTNAME
			utn_getNumero(&selectedOrder, "\nEnter the order.\n1. UP.\n2. DOWN\nOption: ", "INVALID NUMBER, Try again: ", 1, 2, 5);
				sortPassengersLastname(list, len, selectedOrder);
			printf("\n\tORDER COMPLETE.\n");
			break;
		}
		return 0;
	}
	return -1;
}

/** \brief Sort the elements in the array of passengers BY FLYCODE, the argument order
indicate UP or DOWN order
*
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP by - [2] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortPassengersFLYcode(ePassenger* list, int len, int order)
{
	int i, j;
	ePassenger listAux;
	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (list != NULL && len > 0)
	{
		switch (order)
		{
		case 1:
			for (i = 0; i < len - 1; i++) {
				for (j = i + 1; j < len; j++) {
					//NOT AN EMPTY SPACE
					if (list[i].isEmpty==0  && list[j].isEmpty==0) {
						//CRITERIO DE ORDENAMIENTO
						if (strcmp(list[i].flycode,list[j].flycode)>0) {
							listAux = list[i];
							list[i] = list[j];
							list[j] = listAux;
						}
					}
				}
			}
			return 0;
			break;
		case 2:
			for (i = 0; i < len - 1; i++) {
				for (j = i + 1; j < len; j++) {
					//NOT AN EMPTY SPACE
					if (list[i].isEmpty==0 && list[j].isEmpty==0) {
						//CRITERIO DE ORDENAMIENTO
						if (strcmp(list[i].flycode,list[j].flycode)<0) {
							listAux = list[i];
							list[i] = list[j];
							list[j] = listAux;
						}
					}
				}
			}
			return 0;
			break;
		}
	}
	return -1;
}


/** \brief Sort the elements in the array of passengers BY LASTNAME AND DNI, the argument order
indicate UP or DOWN order
*
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP by - [2] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortPassengersLastname(ePassenger* list, int len, int order)
{
	int i, j;
	ePassenger listAux;
	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (list != NULL && len > 0)
	{
		switch (order)
		{
		case 1:
			for (i = 0; i < len - 1; i++) {
				for (j = i + 1; j < len; j++) {
					//NOT AN EMPTY SPACE
					if (list[i].isEmpty==0  && list[j].isEmpty==0) {
						//CRITERIO DE ORDENAMIENTO
						if (strcmp(list[i].lastName,list[j].lastName)>0) {
							listAux = list[i];
							list[i] = list[j];
							list[j] = listAux;
						}
						else
						{	//SI FALLA EL PRIMER CRITERIO
							if (strcmp(list[i].lastName,list[j].lastName)==0) {
								if (list[i].typePassenger>list[j].typePassenger) {
									listAux = list[i];
									list[i] = list[j];
									list[j] = listAux;
								}
							}
						}
					}
				}
			}
			return 0;
			break;
		case 2:
			for (i = 0; i < len - 1; i++) {
				for (j = i + 1; j < len; j++) {
					//NOT AN EMPTY SPACE
					if (list[i].isEmpty==0 && list[j].isEmpty==0) {
						//CRITERIO DE ORDENAMIENTO
						if (strcmp(list[i].flycode,list[j].flycode)<0) {
							listAux = list[i];
							list[i] = list[j];
							list[j] = listAux;
						}
						else
						{	//SI FALLA EL PRIMER CRITERIO
							if (strcmp(list[i].lastName,list[j].lastName)==0) {
								if (list[i].typePassenger<list[j].typePassenger) {
									listAux = list[i];
									list[i] = list[j];
									list[j] = listAux;
								}
							}
						}
					}
				}
			}
			return 0;
			break;
		}
	}
	return -1;
}


/**
* \brief print the content of passengers array
*
* \param list Passenger*
* \param length int
* \return int
*
*/
int printPassenger(ePassenger* list, int length, eFlight* flights)
{
	if(list!=NULL && length>0)
	{
		printf("| [ID] |      Document|        Name|      Lastname|       Price|   FLYcode|    STATUS|\n");
		for(int i=0;i<length;i++)
		{
			if(list[i].isEmpty==0)
			{
				printf("\n|%-6d",list[i].id);
				printf("|%14d",list[i].typePassenger);
				printf("|%12s",list[i].name);
				printf("|%14s",list[i].lastName);
				printf("|%12.2f",list[i].price);
				for(int j=0;j<4;j++)
				{
					if(strcmp(list[i].flycode,flights[j].flycode)==0)
					{
						printf("|%10s",list[i].flycode);
						printf("|%10s|",flights[j].descStatusFlight);
					}
				}

			}
		}
		printf("\n\n\t============================\n");
		return 0;
	}
	return -1;
}

/**
 * @brief print ONE passenger
 *
 * @param list Passenger*
 * @param length int
 * @param flights eFlight*
 * @return
 */
void printONEPassenger(ePassenger list, eFlight* flights)
{
	printf("\n|%-6d",list.id);
	printf("|%14d",list.typePassenger);
	printf("|%12s",list.name);
	printf("|%14s",list.lastName);
	printf("|%12.2f",list.price);
	for(int i=0;i<4;i++)
	{
		if(strcmp(list.flycode,flights[i].flycode)==0)
		{
			printf("|%10s",list.flycode);
			printf("|%10s|",flights[i].descStatusFlight);
		}
	}
}

/** \brief find a empty space in the array and returns the index position.
*
* \param list Passenger*
* \param len int
* \return Return the empty space index position or (-1) if [Invalid length or
NULL pointer received or empty not found]
*
*/
int searchEmptySpace(ePassenger* list, int len)
{
	int i;
	int index=-1; //error
	if(list!=NULL && len>0)
	{
		for (i=0;i<len;i++)
		{
			if(list[i].isEmpty==1)
			{
				//Return the empty space index
				index=i;
				break;
			}
		}
	}
	return index;
}

/**
 * @brief Search an ID that the usser wants to modify, for each camp
*
* @param list Passenger*
* @param len int
* @return Return the empty space index position or (-1) if [Invalid length or NULL pointer received or empty not found]
*/
int modifyPassenger(ePassenger* list, int len, eFlight* flights)
{
	int idAux;
	int index;
	int option;
	int caseFlycode;

	if(list!=NULL && len>0)
	{
		//GET AND SEARCH ID
		utn_getNumero(&idAux, "\nEnter ID to modify: ", "\nERROR INVALID NUMBER FOR AN ID, TRY AGAIN: ", 10000, 12000, 5);
		//GET AND SEARCH INDEX FROM THE ID
		index=findPassengerById(list, len, idAux);
		if(index==-1)
		{
			printf("\nID DOES NOT EXIST");
		}
		else
		{

			do
			{
				printf("\tMODIFY:\n\n");
				printf("| [ID] |      Document|        Name|      Lastname|       Price|   FLYcode|    STATUS|\n");
				printONEPassenger(list[index],flights);
				utn_getNumero(&option, "\n\nSELECT WHAT YOU WANT TO MODIFY:\n1. Name\n2. Lastname\n3. Price\n4. FLYcode\n5. Document\n6.None\nOption: ", "\nERROR INVALID OPTION, TRY AGAIN: ", 1, 6, 5);
				switch(option)
				{
					case 1:
						//NAME
						printf("\nEnter NEW name's passenger: ");
						while(utn_getString(list[index].name, sizeof(list[index].name))!=0)
						{
							printf("\nERROR, NOT A NAME, Try again: ");
						}
						break;

					case 2:
						//LASTNAME
						printf("\nEnter NEW lastname's passenger: ");
						while(utn_getString(list[index].lastName, sizeof(list[index].lastName))!=0)
						{
							printf("\nERROR, NOT A LASTNAME, Try again: ");
						}
						break;
					case 3:
						//PRICE
						utn_getNumeroFlotante(&list[index].price, "\nEnter NEW flight price: ", "\nERROR, INVALID, Try again: ", 1000, 500000, 5);
						break;
					case 4:
						//FLYCODE
						utn_getNumero(&caseFlycode, "\nSelect FLYCODE:\n1. 'LAER-3753'\n2. 'SERT-7245'\n3. 'MTRG-2960'\n4. 'MTQG-2966'\nOption: ", "\nERROR, INVALID, Try again: ", 1, 4, 5);
						switch(caseFlycode)
						{
							case 1:
								strcpy(list[index].flycode,flights[0].flycode);
								break;
							case 2:
								strcpy(list[index].flycode,flights[1].flycode);
								break;
							case 3:
								strcpy(list[index].flycode,flights[2].flycode);
								break;
							case 4:
								strcpy(list[index].flycode,flights[3].flycode);
								break;
						}
						break;
					case 5:
						//DNI
						utn_getNumero(&list[index].typePassenger, "Enter passangers DNI: ", "\nERROR, INVALID, Try again: ", 10000000, 50000000, 5);
						break;
					case 6:
						printf("\nEXIT MODIFY\n");
						break;
				}
			}while(option!=6);
		}
		return 0;
	}
	return -1;
}

/// @brief Acumule all prices into a total.
///
/// @param list Passenger*
/// @param len int
/// @return return the total price or -1 if error
float totalPrices(ePassenger* list, int len)
{
	float acumPrices=0;

	if(list!=NULL && len>0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty==0)
			{
				acumPrices+=list[i].price;
			}
		}
		return acumPrices;
	}
	return -1;
}

/// @brief make an average from total prices
///
/// @param list Passenger*
/// @param len int
/// @return return the average price, 0 if no data or -1 if error
float averagePrices(ePassenger* list, int len)
{
	float total;
	int counter;
	float average;

	if(list!=NULL && len>0)
	{

		if(isAny(list, len)!=-1)
		{
			total=totalPrices(list, len);
			counter=isAny(list, len);

			average=(float)total/counter;
			return average;
		}
		else
		{
			printf("\nNO DATA\n");
			return 0;
		}
	}
	return -1;
}

/// @brief count all prices who pass the average price.
///
/// @param list Passenger*
/// @param len int
/// @return return the counter  or -1 if error
int surpassAverage(ePassenger* list, int len)
{
	float average;
	int passCounter=0;

	if(list!=NULL && len>0)
	{
		average=averagePrices(list, len);
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty==0 && list[i].price>average)
			{
				passCounter++;
			}
		}
		return passCounter;
	}
	return -1;
}

//3. Listado de los pasajeros por Código de vuelo y estados de vuelos ‘ACTIVO’

/// @brief print all the active codes
///
/// @param list Passenger*
/// @param len int
/// @return return 0 if ok  or -1 if error
int activeFlycodes(ePassenger* list, int len, eFlight* flights)
{
	if(list!=NULL && len>0)
	{
		printf("\n| [ID] |      Document|        Name|      Lastname|       Price|   FLYcode|    STATUS|\n");
		for(int i=0; i<len; i++) //flycode
		{
			if(strcmp(list[i].flycode,flights[0].flycode)==0)
			{
				printONEPassenger(list[i], flights);
			}
		}
		printf("\n");
		return 0;
	}
	return -1;
}
