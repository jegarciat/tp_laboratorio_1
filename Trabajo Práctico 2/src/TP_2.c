/*
 ============================================================================
 Programa    : Trabajo practico 2 - Laboratorio I/Programación I
 Autor       : Jorge García
 Legajo      : 111263
 División    : 1°C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayEmployees.h"
#include "Informes.h"

int main(void) {

	sEmployee employees[QTY_EMPLOYEES];

	char answer;
	int auxIndex;
	int auxAdd;
	int auxID;
	int auxRemove;
	int modifyEmployee;

	setbuf(stdout, NULL);

	initEmployees(employees, QTY_EMPLOYEES);

	//TestEmployees(employees, 8);

	do
	{
		switch(MainMenu())
		{
			case 1:
				auxIndex = Employees_SearchFree(employees, QTY_EMPLOYEES);
				if(auxIndex == -1)
				{
					printf("\n\t[NO HAY ESPACIO DISPONIBLE]\n");
				}
				else
				{
					auxAdd = addEmployee(employees, QTY_EMPLOYEES, auxIndex);
					if(auxAdd != -1)
					{
						printf("\n\t[REGISTRO EXITOSO]\n");
					}
					else
					{
						printf("\n[NO SE HA PODIDO INGRESAR EL EMPLEADO CORRECTAMENTE]\n");
					}
				}
				break;

			case 2:
				if((printEmployees(employees, QTY_EMPLOYEES)) != -1)
				{
					modifyEmployee = ModifyEmployee(employees, QTY_EMPLOYEES);
					switch(modifyEmployee)
					{
						case 0:
							printf("\n\t[MODIFICACIÓN EXITOSA]\n");
							break;

						case -1:
							printf("\n\t[EL ID INGRESADO NO EXISTE]\n");
							break;

						case -2:
							printf("\n\t[MODIFICACIÓN CANCELADA]\n");
							break;
					}
				}
				else
				{
					printf("\n[DEBE REGISTRAR AL MENOS UN EMPLEADO]\n");
				}
				break;

			case 3:
				if((printEmployees(employees, QTY_EMPLOYEES)) != -1)
				{
					auxID = getInt("\n\nIngrese el ID del empleado que quiere dar de baja: ");
					auxRemove = removeEmployee(employees, QTY_EMPLOYEES, auxID);

					switch(auxRemove)
					{
						case 0:
							printf("\n\t[BAJA EXITOSA]\n");
						break;

						case -1:
							printf("\n\t[EL ID INGRESADO NO EXISTE]\n");
						break;

						case -2:
							printf("\n\t[BAJA CANCELADA]\n");
						break;
					}

				}
				else
				{
					printf("\n[DEBE REGISTRAR AL MENOS UN EMPLEADO]\n");
				}
				break;

			case 4:
				if((printEmployees(employees, QTY_EMPLOYEES)) != -1)
				{
					Reports(employees, QTY_EMPLOYEES);
				}
				else
				{
					printf("\n[DEBE REGISTRAR AL MENOS UN EMPLEADO]\n");
				}
				break;

			case 5:
				answer = Confirmar("\n¿Desea salir? (s/n): ");
				break;
		}

	} while(answer != 's');

	printf("\n\t[SALISTE DEL PROGRAMA]\n");

	return EXIT_SUCCESS;
}
