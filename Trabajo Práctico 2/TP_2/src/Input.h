
#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * \brief Solicita un número al usuario, valida el rango establecido y lo retorna
 * \param mensaje Es el mensaje a ser mostrado para pedirle un dato al usuario
 * \param mensajeError Es el mensaje mostrado si se ingreso un dato inválido
 * \param minimo Es el número minimo que fue puede ser ingresado
 * \param maximo Es el número máximo que puede ser ingresado
 * \return Número ingresado por el usuario
 *
 */
int utn_getEntero(char[], char[], int, int);

/**
 * \brief Solicita un número al usuario, valida el rango establecido y lo retorna
 * \param mensaje Es el mensaje a ser mostrado para pedirle un dato al usuario
 * \param mensajeError Es el mensaje mostrado si se ingreso un dato inválido
 * \param minimo Es el número minimo que fue puede ser ingresado
 * \param maximo Es el número máximo que puede ser ingresado
 * \return Número ingresado por el usuario
 *
 */
float utn_getFloat(char[], char[], float, float);

/**
 * \brief Solicita un caracter al usuario y lo retorna
 * \param mensaje Es el mensaje a ser mostrado
 * \return El caracter ingresado por el usuario
 *
 */
char utn_getChar(char[]);

/**
 * \brief Solicita un texto al usuario
 * \param mensaje Es el mensaje a ser mostrado
 * \param input Array donde se cargará el texto ingresado
 * \return void
 */

void utn_getString(char mensaje[],char input[]);

/**
 * \brief Solicita un número entero y lo retorna
 * \param mensaje Es el mensaje a ser mostrado
 * \return Número ingresado por el usuario
 *
 */
int getInt(char mensaje[]);

/**
 * \brief Solicita un caracter s/n al usuario, valida la letra y devuelve la respuesta
 * \param confirmarMensaje Es el mensaje a ser mostrado
 * \return Retorna 's' o 'n'
 *
 * */
char Confirmar(char confirmarMensaje[]);

#endif /* INPUT_H_ */
