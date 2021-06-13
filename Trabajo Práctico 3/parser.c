#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Nombre del archivo de donde se cargaran los datos
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [ID Máximo] Si esta ok
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	Employee* pEmpleado;
	int retorno;
	char id[256];
	char nombre[256];
	char horasTrabajadas[256];
	char sueldo[256];
	int auxID;
	int flag = 0;
	retorno = -1;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		fscanf(pFile, "%[^,], %[^,], %[^,], %[^\n]\n", id, nombre, horasTrabajadas, sueldo); //Cabeceras

		while(!feof(pFile))
		{
			if(fscanf(pFile, "%[^,], %[^,], %[^,], %[^\n]\n", id, nombre, horasTrabajadas, sueldo) == 4)
			{
				pEmpleado = employee_newParametros(id, nombre, horasTrabajadas, sueldo);

				if(pEmpleado != NULL)
				{
					ll_add(pArrayListEmployee, pEmpleado);
					employee_getId(pEmpleado, &auxID);

					if(flag == 0 || auxID > retorno)
					{
						retorno = auxID; //Retorna el ID máximo encontrado en el archivo
						flag = 1;
					}
				}
			}
		}
	}

    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char* Nombre del archivo de donde se cargaran los datos
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [ID Máximo] Si esta ok
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int auxID;
	int flag = 0;

	Employee* pEmpleado;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		while(!feof(pFile))
		{
			pEmpleado = employee_new();

			if(fread(pEmpleado, sizeof(Employee), 1, pFile) == 1)
			{
				ll_add(pArrayListEmployee, pEmpleado);
				employee_getId(pEmpleado, &auxID);

				if(flag == 0 || auxID > retorno)
				{
					retorno = auxID; //Retorna el ID máximo encontrado en el archivo
					flag = 1;
				}
			}
		}
	}

    return retorno;
}
