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
/// Precio por kilómetro recorrido de viaje.
/// @param x precio total
/// @param y kilómetros totales
/// @return precio del kilómetro
float PrecioPorKM(float x, float y);

/// @brief
/// Hace la diferencia de dos números, su módulo
/// @param x primer numero
/// @param y segundo número
/// @return diferencia de ambos números de forma positiva.
float DiferenciaPositiva(float x,float y);

#endif /* RESOLUCIONES_H_ */
