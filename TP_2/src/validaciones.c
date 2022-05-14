/*
 * validaciones.c
 *
 *  Created on: 30 abr. 2022
 *      Author: alanr
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ArrayPassenger.h"
#include "validaciones.h"

static int esNumerica(char* cadena, int limite);
static int getInt(int* pResultado);
static int esFlotante(char* cadena, int limite);
static int getFloat(float* pResultado);


/**
 * @brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en una cadena un maximo de 'longitud-1' caracteres.
 *
 * @param cadena  Puntero al espacio de memoria donde se copiara la cadena obtenida
 * @param longitud Define el tamanio de cadena
 * @return Retorna 0 si obtuvo la cadena o -1 si no.
 */
int myGets(char* pCadena, int longitud)
{
	int retorno=-1;
	char bufferString[4096]; //*********
	if (pCadena!=NULL && longitud>0)
	{
		fflush(stdin); //borro
		if(fgets(bufferString,sizeof(bufferString),stdin)!=NULL)
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1]=='\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1]='\0';
			}
			if(strnlen(bufferString,sizeof(bufferString))<=longitud)
			{
				strncpy(pCadena,bufferString,longitud);
				retorno=0;
			}
		}
	}
	return retorno;
}


/**
 * @brief Obtener un numero entero desde la terminal
 *
 * @param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * @return retorna 0 (exito) si se obtiene un numero entero y -1 (error) si no
 */
static int getInt(int* pResultado)
{
    int retorno=-1;
    char bufferString[1000];
    if(	pResultado != NULL &&
    	myGets(bufferString,sizeof(bufferString)) == 0 &&
    	esNumerica(bufferString,sizeof(bufferString)))
	{
		retorno=0;
		*pResultado = atoi(bufferString) ;

	}
    return retorno;
}

/**
 * @brief Indica si la cadena que encontro es numerica, que haya numeros
 *
 * @param cadena Cadena de caracteres a ser analizada
 * @return Retorna 1 si la cadena es numerica y 0 si no lo es. Si retorna -1 hay un error de parametro
 */
static int esNumerica(char* cadena, int limite)
{
	int retorno=-1; //error
	int i=0;

	if(cadena!=NULL && limite>0)
	{
		retorno=1;//verdadero
		for(i=0;i<limite && cadena[i]!='\0';i++)
		{
			if(i==0 && (cadena[i]=='+'||cadena[i]=='-'))
			{
				continue;
			}
			if(cadena[i]>'9' || cadena[i]<'0')
			{
				retorno=0; //falso
				break;
			}
			//continue
		}
		//break
	}
	return retorno;
}


/**
 * @brief Solicita un numero al usuario, luego de verificarlo devuelve el resultado
 *
 * @param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * @param mensaje Es el mensaje a ser mostrado
 * @param mensajeError Es el mensaje de Error a ser mostrado
 * @param minimo Es el numero minimo a ser aceptado
 * @param maximo Es el numero maximo a ser aceptado
 * @param reintentos
 * @return retorna 0 si se obtuvo el numero o -1 si no
 */
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno=-1; //carga error
	int bufferInt;

	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&minimo<=maximo&&reintentos>=0)
	{
		do
		{
			printf("%s",mensaje);

			if( getInt(&bufferInt)==0 &&
				bufferInt>=minimo &&
				bufferInt<=maximo)
			{
				*pResultado=bufferInt;
				retorno=0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos>=0);
	}
	return retorno;
}


/**
 * \brief Verifica si la cadena ingresada es flotante
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int getFloat(float* pResultado)
{
    int retorno=-1;
    char bufferString[1000];
    if(	pResultado != NULL &&
    	myGets(bufferString,sizeof(bufferString)) == 0 &&
		esFlotante(bufferString,sizeof(bufferString)))
	{
		retorno=0;
		*pResultado = atof(bufferString) ;
	}
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es flotante
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (vardadero) si la cadena es flotante y 0 (falso) si no lo es
 *
 */
static int esFlotante(char* cadena, int limite)
{
	//error
	int retorno=-1;
	int i=0;
	if(cadena!=NULL && limite>0)
	{
		//verdadero
		retorno=1;
		for(i=0;i<limite && cadena[i]!='\0';i++)
		{
			if(i==0 && (cadena[i]=='+'||cadena[i]=='-'))
			{
				continue;
			}
			if((cadena[i]>'9' || cadena[i]<'0') && cadena[i]!='.')
			{
				//falso
				retorno=0;
				break;
			}
			//continue
		}
		//break
	}
	return retorno;
}

/**
 * \brief Solicita un numero flotante al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el numero maximo a ser aceptado
 * \param maximo Es el minimo minimo a ser aceptado
 * \return Retorna 0 si se obtuvo el numero flotante y -1 si no
 *
 */
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno=-1; //carga error
	float bufferFloat;
	if(pResultado!=NULL&&mensaje!=NULL&&mensajeError!=NULL&&minimo<=maximo&&reintentos>=0)
	{
		do
		{
			printf("%s",mensaje);

			if(getFloat(&bufferFloat)==0 &&
					bufferFloat>=minimo &&
					bufferFloat<=maximo)
			{
				*pResultado=bufferFloat;
				retorno=0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos>=0);
	}
	return retorno;
}

/**
 * \brief Solicita un caracter  al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es la letra maximo a ser aceptado
 * \param maximo Es la letra minimo a ser aceptado
 * \return Retorna 0 si se obtuvo el caracter y -1 si no
 *
 */
int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos)
{
	int retorno=-1;
	char bufferChar;

	if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			scanf("%c",&bufferChar);

			if(bufferChar>=minimo && bufferChar<=maximo)
			{
				*pResultado=bufferChar; // guarda el puntero a resultado si es perfecto
				retorno=0;
				break; //exito
			}
			else //salio mal
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos>=0);
	}
	return retorno;
}

/**
 * \brief Solicita un string  al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es la letra maximo a ser aceptado
 * \param maximo Es la letra minimo a ser aceptado
 * \return Retorna 0 si se obtuvo el string y -1 si no
 */
int utn_getString(char* pResultado, int len)
{
	int retorno = -1;
	int esLetra = 1;
	char buffer[4096];

	if(pResultado!=NULL && len>0)
	{
		myGets(buffer, len);
		for(int i=0;i<strlen(buffer);i++)
		{
			if(isalpha(buffer[i])==0 || buffer[i]=='\0')
			{
				if(buffer[i]!=' ')
				{
					esLetra=0;
					retorno = -2;
					break;
				}
			}
		}
		if(esLetra==1)
		{
			buffer[0]=toupper(buffer[0]);
			for(int i=0;i<strlen(buffer);i++)
			{
				if(buffer[i]==' ')
				{
					buffer[i+1]=toupper(buffer[i+1]);
				}
			}
			strncpy(pResultado,buffer,len);
			retorno = 0;
		}
	}
	return retorno;
}
