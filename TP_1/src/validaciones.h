/*
 * validaciones.h
 *
 *  Created on: 9 abr. 2022
 *      Author: alanr
 */

#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_

/// @brief
/// Función para validar que sea un número positivo y no se ingrese negativos.
/// @param mensaje
/// Se coloca el mensaje de lo que se necesita ingresar.
/// @param error
/// Si hubo un error entonces si no es un número positivo y lo informa.
/// @return retorna el numero positivo
float PedirPositivo(char mensaje[],char error[]);

/// @brief
/// Hace positivo un número flotante.
/// @param x
/// Número flotante que se ingresa;
/// @return
/// Retorna el flotante que ingresó, positivo.
float HacerPositivo(float x);

/// @brief
/// Opcion para el menu
/// @return Retorna la opcion.
int Opcion();

/// @brief
/// Menu del TP1
void Menu();


#endif /* VALIDACIONES_H_ */
