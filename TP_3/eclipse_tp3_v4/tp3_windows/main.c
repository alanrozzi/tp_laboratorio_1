#include <stdio.h>
#include <stdlib.h>

#include "utn.h"
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "Controller.h"

/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
    10. Salir

    NOTA: Previamente se cargo dos pasajeros (1001 y 1002)
    se dio de baja a 1002 por lo que el nuevo pasajero
    tendra ID = 1003.
*****************************************************/
int main()
{
	setbuf(stdout,NULL);
	int option = 0;
    LinkedList* listaPasajeros = ll_newLinkedList();

    //Verificadores
    int load=0;
    int save=0;

    if(listaPasajeros!=NULL)
    {
    	do{
    		menuPrincipal();
			utn_getNumero(&option,"Opcion: ","\n[ERROR] Opcion no valida, intentelo de nuevo.\nOpcion: ",1,10,3);
			switch(option)
			{
				case 1:
					//1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
					if(load==0)
					{
						controller_loadFromText("data.csv",listaPasajeros);
						load=1;
					}
					else
					{
						printf("\n\t[ARCHIVO CARGADO PREVIAMENTE]");
					}
					break;
				case 2:
					//2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario)
					if(load==0)
					{
						controller_loadFromBinary("data.bin", listaPasajeros);
						load=1;
					}
					else
					{
						printf("\n\t[ARCHIVO CARGADO PREVIAMENTE]");
					}
					break;
				case 3:
					//3. Alta de pasajero
					controller_addPassenger(listaPasajeros);
					break;
				case 4:
					//4. Modificar datos de pasajero
					if(ll_len(listaPasajeros)==0)
					{
						printf("\t[NO EXISTEN DATOS, CARGUE O AGREGUE PASAJEROS]");
					}
					else
					{
						controller_editPassenger(listaPasajeros);
					}
					break;
				case 5:
					//5. Baja de pasajero
					if(ll_len(listaPasajeros)==0)
					{
						printf("\t[NO EXISTEN DATOS, CARGUE O AGREGUE PASAJEROS]");
					}
					else
					{
						controller_removePassenger(listaPasajeros);
					}
					break;
				case 6:
					//6. Listar pasajeros
					if(ll_len(listaPasajeros)==0)
					{
						printf("\t[NO EXISTEN DATOS, CARGUE O AGREGUE PASAJEROS]");
					}
					else
					{
						controller_ListPassenger(listaPasajeros);
					}
					break;
				case 7:
					//7. Ordenar pasajeros
					if(ll_len(listaPasajeros)==0)
					{
						printf("\t[NO EXISTEN DATOS, CARGUE O AGREGUE PASAJEROS]");
					}
					else
					{
						controller_sortPassenger(listaPasajeros);
					}
					break;
				case 8:
				case 9:
					if(load==1)
					{
						//8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
						controller_saveAsText("data.csv" , listaPasajeros);
						//9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
						controller_saveAsBinary("data.bin" , listaPasajeros);
						save=1;
					}
					else
					{
						printf("\n\t[ARCHIVO NO LEIDO, Por favor lea [1, 2] los archivos antes de continuar.]");
					}
					break;
				case 10:
					if(save==1)
					{
						printf("\n\t[EXIT]\n");
						ll_deleteLinkedList(listaPasajeros);
						option=11;
					}
					else
					{
						printf("\n\t[NO SE PUEDE SALIR, POR FAVOR CARGUE Y GUARDE EL ARCHIVO]\n");
					}
					break;
			}
		}while(option != 11);
    }
    else
    {
    	printf("\n\t[INICIALIZACION FALLIDA]\n");
    }

    return 0;
}

