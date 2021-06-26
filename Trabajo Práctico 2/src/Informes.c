#include "Informes.h"

void MainMenu(int* option)
{
	printf("\n |--------------------------------|");
	printf("\n |      GESTIÓN DE EMPLEADOS      |\n");
	printf(" |--------------------------------|\n");
	printf(" | 1. ALTAS                       |\n");
	printf(" | 2. MODIFICAR EMPLEADO          |\n");
	printf(" | 3. BAJA                        |\n");
	printf(" | 4. INFORMES                    |\n");
	printf(" | 5. SALIR                       |\n");
	printf(" |--------------------------------|\n");
	utn_getNumInt(option, "\nIngresa una opcion: ", "\n\t¡Error! Ingresa una opción del menú.\n", 1, 5);
}

void Reports_Menu(int* option)
{
	printf("\n -------------------------------------------------------------------------------------------");
	printf("\n |                                   INFORMES                                              |\n");
	printf(" -------------------------------------------------------------------------------------------\n");
	printf(" | 1. Listado de los empleados ordenados alfabéticamente por Apellido y Sector.            |\n");
	printf(" | 2. Total y promedio de los salarios, y cuántos empleados superan el salario promedio.   |\n");
	printf(" | 3. Volver al menú principal                                                             |\n");
	printf(" -------------------------------------------------------------------------------------------\n");
	utn_getNumInt(option, "\nIngresa una opcion: ", "\n\t¡Error! Ingresa una opción del menú.\n", 1, 3);
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
			average = auxTotalSalary/quantyEmployees;
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
	int counterHighSalary;
	int option;
	float totalSalary;
	float averageSalary;

	do
	{
		Reports_Menu(&option);

		switch(option)
		{
			case 1:
				utn_getNumInt(&optionOrder, "\nIngrese 0 para ordenar de forma ascendente.\nIngrese 1 para ordenar de forma descendente.\n\nElija una opción de ordenamiento: ",
							"\n¡Error! Ingrese un opción válida 0 (ascedente) o 1 (descendente)\n", 0, 1);
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
				Confirmar(&answer, "\n¿Estás seguro/a? (s/n): ");
				break;
		}

	} while(answer != 's');
}
