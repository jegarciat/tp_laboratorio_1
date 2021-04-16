/*
 =======================================================================================================
 Programa    : Trabajo practico 1 - Laboratorio I/Programación I
 Autor       : Jorge García
 División    : 1°C
 Enunciado   :  Hacer una calculadora. Para ello el programa iniciará y contará con un menú de opciones:
			 1. Ingresar 1er operando (A=x)
			 2. Ingresar 2do operando (B=y)
			 3. Calcular todas las operaciones
				a) Calcular la suma (A+B)
				b) Calcular la resta (A-B)
				c) Calcular la division (A/B)
				d) Calcular la multiplicacion (A*B)
				e) Calcular el factorial (A!)
			 4. Informar resultados
				a) “El resultado de A+B es: r”
				b) “El resultado de A-B es: r”
				c) “El resultado de A/B es: r” o “No es posible dividir por cero”
				d) “El resultado de A*B es: r”
				e) “El factorial de A es: r1 y El factorial de B es: r2”
			 5. Salir
 =======================================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Calculadora.h"

#define FALSE 0
#define TRUE 1

int main(void) {

	float operador1;
	float operador2;
	float suma;
	float resta;
	float division;
	float multiplicacion;
	int primerIngresoNum1;
	int primerIngresoNum2;
	int calculosRealizados;
	int opcion;
	int contadorDeCalculos;
	long int factorialNum1;
	long int factorialNum2;

	contadorDeCalculos = 0;

	primerIngresoNum1 = FALSE;
	primerIngresoNum2 = FALSE;
	calculosRealizados = FALSE;

	setbuf(stdout, NULL);

	do
	{
		if(primerIngresoNum1 == FALSE)
		{
			printf("=======================================\n");
			printf(" 1. Ingresar 1er operando (A=x)");
		}
		else
		{
			printf("=======================================\n");
			printf(" 1. Ingresar 1er operando (A = %.2f)", operador1);
		}
		if(primerIngresoNum2 == FALSE)
		{
			printf("\n 2. Ingresar 2do operando (B=y)");
		}
		else
		{
			printf("\n 2. Ingresar 2do operando (B = %.2f)", operador2);
		}
		opcion = utn_getEntero("\n 3. Calcular todas las operaciones\n"
				"    a) Calcular la suma (A+B)\n"
				"    b) Calcular la resta (A-B)\n"
				"    c) Calcular la division (A/B)\n"
				"    d) Calcular la division (A/B)\n"
				"    e) Calcular el factorial (A!)\n"
				" 4. Informar resultados\n"
				" 5. Salir\n"
				"======================================="
				"\n Elija una opcion: ", "\n [ESCOGA UNA OPCIÓN VÁLIDA]: ", 1, 5);

		switch(opcion)
		{
			case 1:
				operador1 = utn_getFloat("\n Ingresa el 1er operando: ");
				primerIngresoNum1 = TRUE;
				system("cls");
				break;

			case 2:
				operador2 = utn_getFloat("\n Ingresa el 2do operando: ");
				primerIngresoNum2 = TRUE;
				system("cls");
				break;

			case 3:
				if(primerIngresoNum1 == TRUE && primerIngresoNum2 == TRUE && calculosRealizados == FALSE)
				{
					suma = utn_Sumar(operador1, operador2);
					resta = utn_Restar(operador1, operador2);
					multiplicacion = utn_Multiplicar(operador1, operador2);
					division = utn_Dividir(operador1, operador2);
					factorialNum1 = utn_Factorial((int)operador1);
					factorialNum2 = utn_Factorial((int)operador2);

					printf("\n Calculando...\n");
					system("pause");
					system("cls");
					printf("\n\t[CÁLCULOS REALIZADOS]\n");
					system("pause");
					calculosRealizados = TRUE;
					contadorDeCalculos++;
					system("cls");
				}
				else
				{
					if(contadorDeCalculos > 0)
					{
						printf("\n[Si ingresaste un operando nuevo debes calcular nuevamente]\n\n");
						contadorDeCalculos = 0;
						calculosRealizados = FALSE;
						system("pause");
						system("cls");
					}
					else
					{
						printf("\n[DEBES INGRESAR PRIMERO LOS DOS OPERANDOS]\n\n");
						system("pause");
						system("cls");
					}
				}
				break;

			case 4:
				if(calculosRealizados == TRUE)
				{
					utn_MostrarFloat("\n a) El resultado de (A+B) es: ", suma);
					utn_MostrarFloat("\n b) El resultado de (A-B) es: ", resta);
					if(operador2 != 0)
					{
						utn_MostrarFloat("\n c) El resultado de (A/B) es: ", division);
					}
					else
					{
						printf("\n c) El resultado de (A/B) es: No se puede dividir entre 0");
					}
					utn_MostrarFloat("\n d) El resultado de (A*B) es: ", multiplicacion);
					utn_MostrarFactorial(factorialNum1, factorialNum2);
					printf("\n\n");

					primerIngresoNum1 = FALSE;
					primerIngresoNum2 = FALSE;
					calculosRealizados = FALSE;

					system("pause");
					system("cls");
				}
				else
				{
						printf("\n\t[DEBES CALCULAR PRIMERO]\n");
						system("pause");
						system("cls");
				}
				break;

			case 5:
				printf("\n\t[QUE TENGA UN BUEN DIA]\n\n");
				system("pause");
				break;
		}

	} while(opcion != 5);

	return EXIT_SUCCESS;
}

