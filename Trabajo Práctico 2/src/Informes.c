
#include "Informes.h"

int MainMenu()
{
	int option;

	printf("\n GESTIÓN DE EMPLEADOS \n");
	printf("\n 1. Alta\n");
	printf("\n 2. Modificar empleado\n");
	printf("\n 3. Baja\n");
	printf("\n 4. Informes\n");
	printf("\n 5. Salir\n");
	option = utn_getEntero("\nElija un opción: ", "\nOpción inválida, ingrese nuevamente: ", 1, 5);

	return option;
}

int Reports_Menu()
{
	int option;

	printf("\n\n INFORMES\n");
	printf("\n1. Listado de los empleados ordenados alfabéticamente por Apellido y Sector.\n");
	printf("2. Total y promedio de los salarios, y cuántos empleados superan el salario promedio.\n");
	printf("3. Volver al menú principal\n");
	option = utn_getEntero("\nElija una opción: ","\nOpción inválida, ingrese nuevamente: ", 1, 3);

	return option;
}

float TotalSalary(sEmployee* list, int len)
{
	float totalSalary = 0;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty != EMPTY)
			{
				totalSalary += list[i].salary;
			}
		}
	}

	return totalSalary;
}

float AverageSalary(sEmployee* list, int len)
{
	float average;
	int quantyEmployees = 0;
	float auxTotalSalary = 0;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty != EMPTY)
			{
				quantyEmployees++;
			}
		}

		auxTotalSalary = TotalSalary(list, len);

		if(quantyEmployees > 0)
		{
			average = auxTotalSalary/(float)quantyEmployees;
		}
		else
		{
			average = 0;
		}
	}

	return average;
}

int QuantityEmployeesWithHighSalary(sEmployee* list, int len, float averageSalary)
{
	int counter = 0;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty != EMPTY && list[i].salary > averageSalary)
			{
				counter++;
			}
		}
	}

	return counter;
}

void Reports(sEmployee* list, int len)
{
	char answer;
	int optionOrder;
	float totalSalary;
	float averageSalary;
	int counterHighSalary;

	do
	{
		switch(Reports_Menu())
		{
			case 1:

				optionOrder = utn_getEntero("\nIngrese 0 para ordenar de forma ascendente.\nIngrese 1 para ordenar de forma descendente.\n\nElija una opción de ordenamiento: ",
											"¡Error! Reingrese un opción válida 0 (ascedente) o 1 (descendente): ", 0, 1);
				sortEmployees(list, len, optionOrder);
				printEmployees(list, len);

				break;

			case 2:

				totalSalary = TotalSalary(list, len);
				printf("\nEl salario total es de: %.2f$\n", totalSalary);
				averageSalary = AverageSalary(list, len);
				printf("\nEl salario promedio es de: %.2f$\n", averageSalary);
				counterHighSalary = QuantityEmployeesWithHighSalary(list, len, averageSalary);
				printf("\nLa cantidad de empleados que superan el salario promedio es de: %d empleados\n", counterHighSalary);

				break;

			case 3:
				answer = Confirmar("\n¿Seguro? (s/n): ");
				break;
		}

	} while(answer != 's');
}
