#ifndef UTN_H_
#define UTN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

/**
* \brief Solicita un string al usuario, luego de verificarlo devuelve el resultado.
* \param input Puntero al espacio de memoria donde se dejara el resultado de la funcion
* \param mensaje Es el mensaje a ser mostrado
* \param mensajeError Es el mensaje de error a ser mostrado
* \param longitud Es la longitud máxima del string
* \param reintentos Es el número de intentos en caso de error
 * \return (0) Si OK.
 * 		  (-1) si hay ERROR.
*/
int utn_getString(char* input, char* mensaje, char* mensajeError, int longitud, int reintentos);

/**
 * \brief Acomoda la cadena en forma de nombre, las primeras letras en mayúsculas y las demás en minúsculas
 * \param cadena Puntero al string a ser analizado
 * \return (0) Si se acomodo la cadena - (-1) En caso de error
 */
int AcomodarString(char* cadena);

/**
 * \brief Solicita un caracter 's' o 'n' al usuario, valida la letra y devuelve la respuesta
 * \param confirmarMensaje Es el mensaje a ser mostrado
 * \return (-1) En caso de error - (0) Si respondio bien
 */
int Confirmar(char* respuesta, char* confirmarMensaje);

/**
 * \brief Solicita Un numero entero al usuario con reintentos, lo verifica y lo copia en el puntero pResultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser una opcion valida
 * \param minimo Rango mínimo permitido
 * \param maximo Rango máximo permitido
 * \param reintentos Es la cantidad de reintentos
 * \return (0) Si OK.
 * 		  (-1) si hay ERROR.
 */
int utn_getNumEntero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

/**
 * \brief Solicita Un numero entero al usuario con reintentos y sin rango máximo, lo verifica y lo copia en pResultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser una opcion valida
 * \param reintentos Es la cantidad de reintentos
 * \return (0) Si OK.
 * 		  (-1) si hay ERROR.
 */
int utn_getNumEnteroV2(int* pResultado, char* mensaje, char* mensajeError, int minimo, int reintentos);

/**
 * \brief Solicita Un numero entero al usuario, lo verifica y lo copia en el puntero pResultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser una opcion valida
 * \param minimo Rango mínimo permitido
 * \param maximo Rango máximo permitido
 * \return (0) Si OK.
 * 		  (-1) si hay ERROR.
 */
int utn_getNumInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo);

/**
 * \brief Solicita Un numero entero al usuario sin rango máximo, lo verifica y lo copia en el puntero pResultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser una opcion valida
 * \param minimo Rango mínimo permitido
 * \return (0) Si OK.
 * 		  (-1) si hay ERROR.
 */
int utn_getNumIntSM(int* pResultado, char* mensaje, char* mensajeError, int minimo);

/**
 * \brief Solicita Un numero entero al usuario, lo verifica y lo copia en el puntero pResultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un operando valido
 * \param minimo Rango mínimo permitido
 * \param maximo Rango máximo permitido
 * \param reintentos Es la cantidad de reintentos
 * \return (0) Si OK.
 * 		  (-1) si hay ERROR.
 */
int utn_getFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);

/**
 * \brief Solicita Un texto alfanumerico al usuario, lo verifica y lo copia en el puntero pResultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del texto
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return (0) Si OK.
 * 		  (-1) si hay ERROR.
 */
int utn_getAlfaNumerico(char* input, char* mensaje, char* mensajeError, int longitud, int reintentos);

#endif /* UTN_H_ */
