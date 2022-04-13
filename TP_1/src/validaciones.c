/*
 * validaciones.c
 *
 *  Created on: 9 abr. 2022
 *      Author: alanr
 */

#include <stdio.h>
#include <stdlib.h>
#include "resoluciones.h"

float PedirPositivo(char mensaje[],char error[])
{
    float numero;

    printf("%s",mensaje);
    scanf("%f", &numero);

    while(numero < 1)
    {
        printf("%s",error);
        scanf("%f", &numero);
    }

    return numero;
}

float HacerPositivo(float x)
{
	if(x<0)
	{
		x*=(-1);
	}

	return x;
}

int Opcion()
{
	int option;

	scanf("%d",&option);

	return option;
}


void Menu()
{
	printf("	*** MENU ***");
	printf("\n\n1. Ingresar Kilómetros: ");
	printf("\n2. Ingresar Precio de Vuelos: (Aerolíneas y Latam)");
	printf("\n3. Calcular todos los costos: ");
	printf("\n4. Informar Resultados");
	printf("\n5. Carga forzada de datos");
	printf("\n\n6. Salir.");
	printf("\n\n");
}
