/*
 * Calculadora.c
 *
 *      Trabajo Práctico 1
 *      Author: Jorge García
 */

#include "Calculadora.h"

float utn_getFloat(char mensaje[])
{
    float numero;
    printf("%s", mensaje);
    scanf("%f",&numero);
    return numero;
}

int utn_getEntero(char mensaje[], char mensajeError[], int minimo, int maximo)
{
	int numero;

	printf("%s", mensaje);
	scanf("%d", &numero);

	while(numero < minimo || numero > maximo)
	{
		printf("%s", mensajeError);
		scanf("%d", &numero);
	}
	return numero;
}

float utn_Sumar(float operando1, float operando2)
{
    float suma;
    suma = operando1+operando2;
    return suma;
}

float utn_Restar(float operando1, float operando2)
{
	float resta;
	resta = operando1-operando2;
	return resta;
}

float utn_Multiplicar(float operando1, float operando2)
{
    float multiplicacion;
    multiplicacion = operando1*operando2;
    return multiplicacion;
}

float utn_Dividir(float operando1, float operando2)
{
	float division;
	division = operando1/operando2;
	return division;
}

long int utn_Factorial(int operando)
{
	long int factorial;
	int retorno;
	int i;

	factorial = 1;

	if(operando < 0)
	{
		retorno = -1;
	}
	else if(operando > 12)
	{
		retorno = -2;
	}
	else if (operando == 0)
	{
		retorno = factorial;
	}
	else
	{
		for(i = operando; i > 0; i--)
		{
			factorial = factorial*i;
		}
		retorno = factorial;
	}

	return retorno;
}

void utn_MostrarFactorial(long int factorial1, long int factorial2)
{
	switch(factorial1)
	{
		case -1:
			printf("\n e) El factorial de A es: No existe el factorial de un número negativo \n");
			break;

		case -2:
			printf("\n e) El factorial de A es: El resultado desborda lo permitido por el programa (hasta el 12!) \n");
			break;

		default:
			printf("\n e) El factorial de A es: %ld \n", factorial1);
			break;
	}
	switch(factorial2)
	{
		case -1:
			printf("    y el factorial de B es: No existe el factorial de un número negativo");
			break;

		case -2:
			printf("    y el factorial de B es: El resultado desborda lo permitido por el programa (hasta el 12!)");
			break;

		default:
			printf("    y el factorial de B es: %ld", factorial2);
			break;
	}
}

void utn_MostrarFloat(char mensaje[], float resultado)
{
	fflush(stdin);
	printf("%s%.2f",mensaje,resultado);
}
