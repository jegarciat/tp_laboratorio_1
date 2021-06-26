/*
 ============================================================================
 Programa    : Trabajo practico 2 - Laboratorio I
 Autor       : Jorge García
 Legajo      : 111263
 División    : 1°C
 ============================================================================
*/

#include "ArrayEmployees.h"
#include "Informes.h"

int main(void) {

	sEmployee listEmployees[QTY_EMPLOYEES];
	sEmployee auxEmployee;

	char answer;
	int auxID;
	int option;

	setbuf(stdout, NULL);

	initEmployees(listEmployees, QTY_EMPLOYEES);

	//TestEmployees(listEmployees, 8);

	do
	{
		MainMenu(&option);

		switch(option)
		{
			case 1:
				auxEmployee = Employee_RequestData(listEmployees, QTY_EMPLOYEES);
				if(addEmployee(listEmployees, QTY_EMPLOYEES, auxEmployee.id, auxEmployee.name, auxEmployee.lastName, auxEmployee.salary, auxEmployee.sector) != -1)
				{
					printf("\n\t[REGISTRO EXITOSO]\n");
					printEmployee(auxEmployee);
				}
				else
				{
					printf("\n\t[NO SE HA PODIDO REGISTRAR EL EMPLEADO CORRECTAMENTE]\n");
				}
				break;

			case 2:
				sortEmployeesByID(listEmployees, QTY_EMPLOYEES);
				if((printEmployees(listEmployees, QTY_EMPLOYEES)) != -1)
				{
					ModifyEmployee(listEmployees, QTY_EMPLOYEES);
				}
				else
				{
					printf("\n\t[NO HAY EMPLEADOS A MODIFICAR]\n");
				}
				break;

			case 3:
				sortEmployeesByID(listEmployees, QTY_EMPLOYEES);
				if((printEmployees(listEmployees, QTY_EMPLOYEES)) != -1)
				{
					utn_getNumIntSM(&auxID, "\nIngrese el ID del empleado que quiere dar de baja: ", "\n\t¡Error! Ingresa un ID válido.\n", 0);

					if(removeEmployee(listEmployees, QTY_EMPLOYEES, auxID) != -1)
					{
						printf("\n\t[BAJA EXITOSA]\n");
					}
				}
				else
				{
					printf("\n\t[NO HAY EMPLEADOS A DAR DE BAJA]\n");
				}
				break;

			case 4:
				sortEmployeesByID(listEmployees, QTY_EMPLOYEES);
				if((printEmployees(listEmployees, QTY_EMPLOYEES)) != -1)
				{
					Reports(listEmployees, QTY_EMPLOYEES);
				}
				else
				{
					printf("\n\t[NO HAY EMPLEADOS PARA HACER LOS INFORMES]\n");
				}
				break;

			case 5:
				Confirmar(&answer, "\n¿Estás seguro/a? (s/n): ");
				break;
		}

	} while(answer != 's');

	printf("\n\t[SALISTE DEL PROGRAMA]\n");

	return EXIT_SUCCESS;
}
