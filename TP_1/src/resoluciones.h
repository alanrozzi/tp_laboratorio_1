/*
 * resoluciones.h
 *
 *  Created on: 9 abr. 2022
 *      Author: alanr
 */

#ifndef RESOLUCIONES_H_
#define RESOLUCIONES_H_

/// @brief
/// Agrega impuesto o descuenta en el mismo precio.
/// @param x parametro que recibe el precio para agregarle o descontarle dinero.
/// @param y Impuesto o descuento.
/// @return retorna el precio total con el porcentaje.
float PorcentajeDelPrecio(float x, float y);

/// @brief
/// Conversor de pesos a Bitcoin.
/// @param x Pesos a convertir
/// @return Pesos ya convertidos
float PesosABitcoin(float x);

/// @brief
/// Precio por kil�metro recorrido de viaje.
/// @param x precio total
/// @param y kil�metros totales
/// @return precio del kil�metro
float PrecioPorKM(float x, float y);

/// @brief
/// Hace la diferencia de dos n�meros, su m�dulo
/// @param x primer numero
/// @param y segundo n�mero
/// @return diferencia de ambos n�meros de forma positiva.
float DiferenciaPositiva(float x,float y);

#endif /* RESOLUCIONES_H_ */
