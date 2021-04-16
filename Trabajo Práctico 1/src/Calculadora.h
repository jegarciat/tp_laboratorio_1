/*
 * Calculadora.h
 *
 *      Trabajo Práctico 1
 *      Author: Jorge García 1°C
 */

#ifndef CALCULADORA_H_
#define CALCULADORA_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Solicita un número y lo retorna
 * \param mensaje Es el mensaje a ser mostrado
 * \return Retorna el número ingresado
 */

float utn_getFloat(char mensaje[]);

/**
 * \brief Solicita un número al usuario, valida el rango establecido y lo retorna
 * \param mensaje Es el mensaje a ser mostrado para pedirle un dato al usuario
 * \param mensajeError Es el mensaje mostrado si se ingreso un dato inválido
 * \param minimo Es el número minimo que puede ser ingresado
 * \param maximo Es el número máximo que puede ser ingresado
 * \return Retorna el número ingresado
 */

int utn_getEntero(char mensaje[], char mensajeError[], int minimo, int maximo);

/**
 * \brief Recibe dos números float y los suma
 * \param operando1 Primer operando
 * \param operando2 Segundo operando
 * \return Retorna el resultado de la suma
 */

float utn_Sumar(float operando1, float operando2);

/**
 * \brief Recibe dos números float y los suma
 * \param operando1 Primer operando
 * \param operando2 Segundo operando
 * \return Retorna el resultado de la suma
 */

float utn_Restar(float operando1, float operando2);

/**
 * \brief Recibe dos números float y los suma
 * \param operando1 Primer operando
 * \param operando2 Segundo operando
 * \return Retorna el resultado de la multiplicación
 */

float utn_Multiplicar(float operando1, float operando2);

/**
 * \brief Recibe dos números float y los divide
 * \param operando1 Primer operando
 * \param operando2 Segundo operando
 * \return Retorna el resultado de la división
 */

float utn_Dividir(float operando1, float operando2);

/**
 * \brief Recibe un entero, valida si es un número negativo, el rango permitido, y calcula su factorial.
 * \param int operando Operando a ser calculado
 * \return [-1]: Si el número es negativo
 * 		   [-2]: Si el número sobrepasa el rango permitido
 * 		   [Factorial] El resultado del factorial
 */

long int utn_Factorial(int operando);

/**
 * \brief Recibe un texto y un número y los muestra.
 * \param char mensaje Mensaje a ser mostrado
 * \param float resultado Número a ser mostrado, en este caso, el resultado de las operaciones.
 */

void utn_MostrarFloat(char mensaje[], float resultado);

/**
 * \brief Recibe el factorial de los dos operandos y muestra distintos mensajes según el resultado
 * \param long int factorial1 Resultado del factorial del primer operando
 * \param long int factorial2 Resultado del factorial del segundo operando
 */

void utn_MostrarFactorial(long int factorial1, long int factorial2);

#endif /* CALCULADORA_H_ */
