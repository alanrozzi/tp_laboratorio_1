/*
 * validaciones.h
 *
 *  Created on: 30 abr. 2022
 *      Author: alanr
 */

#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_

#include "ArrayPassenger.h"

int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getString(char* pResultado, int len);
int myGets(char* pCadena, int longitud);

#endif /* VALIDACIONES_H_ */
