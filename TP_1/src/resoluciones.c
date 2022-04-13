/*
 * resoluciones.c
 *
 *  Created on: 9 abr. 2022
 *      Author: alanr
 */

#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"

float PorcentajeDelPrecio(float x, float y)
{
	float precioPorcentaje;

	precioPorcentaje=x*y;

	return precioPorcentaje;
}

float PesosABitcoin(float x)
{
	float conversion;
	float bitcoinEnPesos=4606954.55;

	conversion=x/bitcoinEnPesos;

	return conversion;
}

float PrecioPorKM(float x, float y)
{
	float precioKM;

	precioKM=x/y;

	return precioKM;
}

float DiferenciaPositiva(float x,float y)
{
	float difpos;

	difpos=x-y;

	if(difpos<0)
	{
		difpos*=(-1);
	}

	return difpos;
}
