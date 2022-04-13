/*
 ============================================================================
 Name        : TP_1.c
 Author      : 
 Version     : 1.0
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "resoluciones.h"
#include "validaciones.h"
//alt-shift-y   toggle view

int main(void) {

	setbuf(stdout,NULL);

	//variables
	int opcion;
	int banderaSinDatos=0;
	int banderaCalculo=0;
		//1
	float kilometros;
		//2
	float precioAerolineas;
	float precioLatam;
		//3
			//a
	float precioDebitoAerolineas;
	float precioDebitoLatam;
	float precioCreditoAerolineas;
	float precioCreditoLatam;
			//c
	//float bitcoinEnPesos=4606954.55; en función PesosABitcoin
	float bitcoinAerolineas;
	float bitcoinLatam;
			//d
	float precioKmAerolineas;
	float precioKmLatam;
			//e
	float diferenciaPrecios;

	do //menu
	{
		//Menu
		Menu();
		//ingreso de opcion
		opcion=Opcion();

		//menu
		switch(opcion)
		{
			case 1: //kilometros

				kilometros=PedirPositivo("Ingrese los Kilómetros de su vuelo: ","Reingrese los Kilómetros: ");
				printf("Usted ingresó: %.2fkm",kilometros);
				printf("\n\n");

				banderaSinDatos=1;
				break;

			case 2: //precios de vuelos

				if(banderaSinDatos==0)
				{
					printf("	****ERROR***\nUsted NO ingresó los kilometros, por favor reinténtelo.");
					printf("\n\n");
				}
				else
				{
					precioAerolineas=PedirPositivo("Ingrese el precio de Aerolíneas Argentinas: ","Reingrese el precio: ");
					printf("Usted ingresó: $%.2f",precioAerolineas);
					printf("\n\n");

					precioLatam=PedirPositivo("Ingrese el precio de Latam: ","Reingrese el precio: ");
					printf("Usted ingresó: $%.2f",precioLatam);
					printf("\n\n");
				}
				break;

			case 3: //calcular

				//¿Se ingresó datos anteriormente?
				if(banderaSinDatos==0)
				{
					printf("	****ERROR***\nUsted NO ingresó datos, por favor reinténtelo.");
					printf("\n\n");
				}
				else
				{
					//a) Tarjeta de débito (descuento 10%)
					precioDebitoAerolineas=PorcentajeDelPrecio(precioAerolineas,0.9);
					precioDebitoLatam=PorcentajeDelPrecio(precioLatam,0.9);
					//b) Tarjeta de crédito (interés 25%)
					precioCreditoAerolineas=PorcentajeDelPrecio(precioAerolineas,1.25);
					precioCreditoLatam=PorcentajeDelPrecio(precioLatam,1.25);
					//c) Bitcoin (1BTC -> 4606954.55 Pesos Argentinos
					bitcoinAerolineas=PesosABitcoin(precioAerolineas);
					bitcoinLatam=PesosABitcoin(precioLatam);
					//d) Mostrar precio por km (precio unitario)
					precioKmAerolineas=PrecioPorKM(precioAerolineas,kilometros);
					precioKmLatam=PrecioPorKM(precioLatam,kilometros);
					//e) Mostrar diferencia de precio ingresada (Latam - Aerolíneas)
					diferenciaPrecios=DiferenciaPositiva(precioLatam,precioAerolineas);
					//diferenciaPrecios=HacerPositivo(diferenciaPrecios); dentro de DiferenciaPositiva
					banderaCalculo=1;

					printf("\nPrecios y descuentos aplicados, aprete 4 para mostrar. ");
					printf("\n\n");
				}
				break;

			case 4: //mostrar

				if(banderaSinDatos==0||banderaCalculo==0)
				{
					printf("	****ERROR***\nUsted NO ingresó o calculó datos, por favor reinténtelo.");
					printf("\n\n");
				}
				else
				{
					printf("\nKilómetros ingresados: %.2fkm",kilometros);

					printf("\n\nPrecio de Latam: $%.2f",precioAerolineas);
					printf("\na) Precio con tarjeta de débito: $%.2f",precioDebitoAerolineas);
					printf("\nb) Precio con tarjeta de crédito: $%.2f",precioCreditoAerolineas);
					printf("\nc) Precio pagando con bitcoin: %f BTC",bitcoinAerolineas);
					printf("\nd) Precio por kilómetro unitario: $%.2f",precioKmAerolineas);

					printf("\n\nPrecio de Aerolíneas Argentina: $%.2f",precioLatam);
					printf("\na) Precio con tarjeta de débito: $%.2f",precioDebitoLatam);
					printf("\nb) Precio con tarjeta de crédito: $%.2f",precioCreditoLatam);
					printf("\nc) Precio pagando con bitcoin: %f BTC",bitcoinLatam);
					printf("\nd) Precio por kilómetro unitario: $%.2f",precioKmLatam);

					printf("\n\nLa diferencia de precio es: $%.2f",diferenciaPrecios);
					printf("\n\n");
				}
				break;

			case 5: //hardcode de datos
				kilometros=7090;
				precioAerolineas=162965;
				precioLatam=159339;

				banderaSinDatos=1;
				break;

			case 6: //cierra el programa
				printf("\n\nGracias por usar nuestro servicio. Tenga buen día.\n\n");
				break;

			default:
				printf("\n\nOpción inexistente, inténtelo nuevamente.\n\n");
				break;
		}
	}while(opcion!=6);

	return 0;
}
