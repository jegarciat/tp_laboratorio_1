#include "ArrayEmployees.h"

/**
 * \brief Increases the base employee ID by 1 and returns it.
* \return int (-1) if Error [Invalid length or NULL pointer] - (Last ID + 1) if Ok
 */
static int GetID(sEmployee* list, int len)
{
	int maxID;
	int auxID = -1;

	if(list != NULL && len > 0)
	{
		auxID = 0;
		for(int i = 0; i < len; i++)
		{
			if(i == 0 || list[i].id > maxID)
			{
				maxID = list[i].id;
			}
		}
	}

	auxID = maxID + 1;

	return auxID;
}

int initEmployees(sEmployee* list, int len)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			list[i].isEmpty = EMPTY;
			list[i].id = 0;
		}
		retorno = 0;
	}

	return retorno;
}

int Employees_SearchFree(sEmployee* list, int len)
{
    int index = -1;

    if(list != NULL && len > 0)
    {
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == EMPTY)
			{
				index = i;
				break;
			}
		}
    }
    return index;
}

int FindEmployeeByID(sEmployee* list, int len, int id)
{
	int index = -1;

	if(list != NULL && len > 0 && id > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == OCCUPIED && list[i].id == id)
			{
				index = i;
				break;
			}
		}
	}

	return index;
}

sEmployee Employee_RequestData(sEmployee* list, int len)
{
	sEmployee auxEmployee;
	int flag = -1;

	if(utn_getString(auxEmployee.name, "\nIngresa el nombre del empleado: ", "\n\t = | ¡Error! Ingrese un nombre válido (máx 50 caracteres)| =\n", 51, 20) == 0 &&
	  utn_getString(auxEmployee.lastName, "\nIngresa el apellido del empleado: ", "\n\t = | ¡Error! Ingrese un apellido válido (máx 50 caracteres)| =\n", 51, 20) == 0 &&
	  utn_getFlotante(&auxEmployee.salary, "\nIngresa el salario del empleado: ", "\n\t = | ¡Error! Ingrese un salario válido | =\n", 1, 999999, 20) == 0)
	{
		printSectors();
		if(utn_getNumEntero(&auxEmployee.sector, "\nIngresa el ID del sector: ", "\n\t = | ¡Error! Ingrese ID válido | =\n", 1, 3, 20) == 0)
		{
			auxEmployee.id = GetID(list, len);
			flag = 0;
		}
	}

	if(flag == -1)
	{
		printf("\n\t[SE INGRESARON DATOS INVÁLIDOS] ");
	}

	return auxEmployee;
}

int addEmployee(sEmployee* list, int len, int id, char name[], char lastName[], float salary, int sector)
{
	int returnAux = -1;
	int auxIndex;
	int lenName = strlen(name);
	int lenLastName = strlen(lastName);

	if(list != NULL && id > 0 && lenName > 0 && lenName < 51 &&  lenLastName > 0 && lenLastName < 51 && salary >= 0 && sector > 0 && sector <= 3)
	{
		auxIndex = Employees_SearchFree(list, len);
		if(auxIndex == -1)
		{
			printf("\n\t[NO HAY ESPACIO DISPONIBLE]");
		}
		else
		{
			list[auxIndex].id = id;
			strcpy(list[auxIndex].name, name);
			strcpy(list[auxIndex].lastName, lastName);
			list[auxIndex].salary = salary;
			list[auxIndex].sector = sector;
			list[auxIndex].isEmpty = OCCUPIED;
			returnAux = 0;
		}
	}

	return returnAux;
}

void printSectors()
{
	printf("\n |----------------------|\n");
	printf(" |       SECTORES       |\n");
	printf(" |----------------------|\n");
	printf(" |  MARKETING   | ID: 1 |\n");
	printf(" |----------------------|\n");
	printf(" |     RRHH     | ID: 2 |\n");
	printf(" |----------------------|\n");
	printf(" |   SISTEMAS   | ID: 3 |\n");
	printf(" |----------------------|\n");
}

int removeEmployee(sEmployee* list, int len, int id)
{
	int retorno = -1;
	char answer;
	int auxIndex;

	if(list != NULL && len > 0)
	{
		auxIndex = FindEmployeeByID(list, len, id);

		if(auxIndex == -1)
		{
			printf("\n\t[EL ID INGRESADO NO EXISTE]\n");
		}
		else
		{
			printf("\n EMPLEADO A DAR DE BAJA  \n");
			printEmployee(list[auxIndex]);
			Confirmar(&answer, "\n¿Estás seguro/a de la baja? (s/n): ");
			if(answer == 's')
			{
				list[auxIndex].isEmpty = EMPTY;
				retorno = 0; //Retorna baja exitosa
			}
			else
			{
				printf("\n\t[BAJA CANCELADA]\n");
			}
		}
	}

	return retorno;
}

void ModificationMenu(int* option)
{
	printf("\n ----------------------------------");
	printf("\n |    OPCIONES DE MODIFICACION    |\n");
	printf(" ----------------------------------\n");
	printf(" | 1. Modificar nombre            |\n");
	printf(" | 2. Modificar apellido          |\n");
	printf(" | 3. Modificar salario           |\n");
	printf(" | 4. Modificar sector            |\n");
	printf(" | 5. Volver al menú principal    |\n");
	printf(" ----------------------------------\n");

	utn_getNumInt(option, "\nIngresa una opcion: ", "\n\t¡Error! Ingresa una opción del menú.\n", 1, 5);
}

void ModifyEmployee(sEmployee* list, int len)
{
	int auxID;
	int auxIndex;
	char exit;
	int option;

	if(list != NULL && len > 0)
	{
		utn_getNumIntSM(&auxID, "\nIngrese el ID del empleado que quiere modificar: ", "\n\t¡Error! Ingresa un ID válido.\n", 0);
		auxIndex = FindEmployeeByID(list, len, auxID);
		if(auxIndex == -1)
		{
			printf("\n\t[EL ID INGRESADO NO EXISTE]\n");
		}
		else
		{
			do
			{
				printf("\n EMPLEADO A MODIFICAR  \n");
				printEmployee(list[auxIndex]);
				ModificationMenu(&option);

				switch(option)
				{
					case 1:
						if(Edit_Name(list, auxIndex) == 0)
						{
							printf("\n\t[MODIFICACIÓN EXITOSA]\n");
							printEmployee(list[auxIndex]);
							Confirmar(&exit, "\n¿Desea volver al menú principal? (s/n): ");
						}
						break;

					case 2:
						if(Edit_LastName(list, auxIndex) == 0)
						{
							printf("\n\t[MODIFICACIÓN EXITOSA]\n");
							printEmployee(list[auxIndex]);
							Confirmar(&exit, "\n¿Desea volver al menú principal? (s/n): ");
						}
						break;

					case 3:
						if(Edit_Salary(list, auxIndex) == 0)
						{
							printf("\n\t[MODIFICACIÓN EXITOSA]\n");
							printEmployee(list[auxIndex]);
							Confirmar(&exit, "\n¿Desea volver al menú principal? (s/n): ");
						}
						break;

					case 4:
						if(Edit_Sector(list, auxIndex) == 0)
						{
							printf("\n\t[MODIFICACIÓN EXITOSA]\n");
							printEmployee(list[auxIndex]);
							Confirmar(&exit, "\n¿Desea volver al menú principal? (s/n): ");
						}
						break;

					case 5:
						Confirmar(&exit, "\n¿Estás seguro/a de volver al menú principal? (s/n): ");
						break;
				}

			} while(exit != 's');
		}
	}
}

int Edit_Name(sEmployee* list, int indexEdit)
{
	char auxName[51];
	char answer;
	int retorno = -1;

	if(list != NULL && indexEdit >= 0)
	{
		if(utn_getString(auxName, "\nIngresa el nuevo nombre del empleado: ", "\n\t = | ¡Error! Ingrese un nombre válido (máx 50 caracteres)| =\n", 51, 5) == 0)
		{
			Confirmar(&answer, "\n¿Estás seguro/a de la modificación? (s/n): ");
			if(answer == 's')
			{
				strcpy(list[indexEdit].name, auxName);
				retorno = 0;
			}
			else
			{
				printf("\n\t[MODIFICACIÓN CANCELADA]\n");
			}
		}
		else
		{
			printf("\n\tNo se pudo modificar el empleado ¡Se acabaron los intentos!\n");
		}
	}

	return retorno;
}

int Edit_LastName(sEmployee* list, int indexEdit)
{
	char auxLastName[51];
	char answer;
	int retorno = -1;

	if(list != NULL && indexEdit >= 0)
	{
		if(utn_getString(auxLastName, "\nIngresa el nuevo apellido del empleado: ", "\n\t = | ¡Error! Ingrese un apellido válido (máx 50 caracteres)| =\n", 51, 5) == 0)
		{
			Confirmar(&answer, "\n¿Estás seguro/a de la modificación? (s/n): ");
			if(answer == 's')
			{
				strcpy(list[indexEdit].lastName, auxLastName);
				retorno = 0;
			}
			else
			{
				printf("\n\t[MODIFICACIÓN CANCELADA]\n");
			}
		}
		else
		{
			printf("\n\tNo se pudo modificar el empleado ¡Se acabaron los intentos!\n");
		}
	}

	return retorno;
}

int Edit_Salary(sEmployee* list, int indexEdit)
{
	float auxSalary;
	char answer;
	int retorno = -1;

	if(list != NULL && indexEdit >= 0)
	{
		if(utn_getFlotante(&auxSalary, "\nIngresa el nuevo salario del empleado: ", "\n\t = | ¡Error! Ingrese un salario válido | =\n", 1, 999999, 5) == 0)
		{
			Confirmar(&answer, "\n¿Estás seguro/a de la modificación? (s/n): ");
			if(answer == 's')
			{
				list[indexEdit].salary = auxSalary;
				retorno = 0;
			}
			else
			{
				printf("\n\t[MODIFICACIÓN CANCELADA]\n");
			}
		}
		else
		{
			printf("\n\tNo se pudo modificar el empleado ¡Se acabaron los intentos!\n");
		}
	}

	return retorno;
}

int Edit_Sector(sEmployee* list, int indexEdit)
{
	int auxSector;
	char answer;
	int retorno = -1;

	if(list != NULL && indexEdit >= 0)
	{
		printSectors();
		if(utn_getNumEntero(&auxSector, "\nIngresa el ID del nuevo el sector: ", "\n\t = | ¡Error! Ingrese un sector válido | =\n", 1, 3, 5) == 0)
		{
			Confirmar(&answer, "\n¿Estás seguro/a de la modificación? (s/n): ");
			if(answer == 's')
			{
				list[indexEdit].sector = auxSector;
				retorno = 0;
			}
			else
			{
				printf("\n\t[MODIFICACIÓN CANCELADA]\n");
			}
		}
		else
		{
			printf("\n\tNo se pudo modificar el empleado ¡Se acabaron los intentos!\n");
		}
	}

	return retorno;
}

int sortEmployeesByID(sEmployee* list, int len)
{
	int retorno = -1;
	sEmployee auxiliar;

	if(list != NULL && len > 0)
	{
		retorno = 0;

		for(int i = 0; i < len-1; i++)
		{
			for(int j = i+1; j < len; j++)
			{
				if(list[i].id > list[j].id)
				{
					auxiliar = list[i];
					list[i] = list[j];
					list[j] = auxiliar;
				}
			}
		}
	}

	return retorno;
}

int sortEmployees(sEmployee* list, int len, int order)
{
	sEmployee auxiliar;
	int i;
	int j;
	int retorno = -1;

	if(list != NULL && len > 0 && (order == 0 || order == 1))
	{
		retorno = 0;

		if(order == 0)
		{
			for(i = 0; i < len-1; i++)
			{
				for(j = i+1; j < len; j++)
				{
					if(stricmp(list[i].lastName, list[j].lastName) > 0 ||
					  (stricmp(list[i].lastName, list[j].lastName) == 0 && list[i].sector > list[j].sector))
					{
						auxiliar = list[i];
						list[i] = list[j];
						list[j] = auxiliar;
					}
				}
			}
		}
		else
		{
			for(i = 0; i < len-1; i++)
			{
				for(j = i+1; j < len; j++)
				{
					if(stricmp(list[i].lastName, list[j].lastName) < 0 ||
					  (stricmp(list[i].lastName, list[j].lastName) == 0 && list[i].sector < list[j].sector))
					{
						auxiliar = list[i];
						list[i] = list[j];
						list[j] = auxiliar;
					}
				}
			}
		}
	}

	return retorno;
}

int printEmployees(sEmployee* list, int len)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty != EMPTY)
			{
				printEmployee(list[i]);
				retorno = 0;
			}
		}
	}

	return retorno;
}

void printEmployee(sEmployee auxEmployee)
{
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("| ID: %2d | NOMBRE: %20s | APELLIDO: %18s | SALARIO: %12.2f | SECTOR: %2d |", auxEmployee.id,
																			              auxEmployee.name,
																			              auxEmployee.lastName,
																			              auxEmployee.salary,
																			              auxEmployee.sector);
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
}

void TestEmployees(sEmployee* list, int len)
{
	char auxName[][51] = {"Oscar", "Fabiana", "Luis", "Ana", "Zara", "Pedro", "Maria", "Victor"};
	char auxLastName[][51] = {"Garcia", "Velarde", "Morales", "Lopez", "Morales", "Contreras", "Fausto", "Ignacio"};
	float salary[] = {2000.50, 5000.75, 2500.70, 4800.60, 9000.50, 4500.80, 7500.50, 6750.80};
	int auxSector[] = {1, 2, 3, 1, 1, 2, 3, 3};
	int state[] = {OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED};

	for(int i = 0; i < len; i++)
	{
		list[i].id = GetID(list, len);
		strcpy(list[i].name, auxName[i]);
		strcpy(list[i].lastName, auxLastName[i]);
		list[i].salary = salary[i];
		list[i].sector = auxSector[i];
		list[i].isEmpty = state[i];
	}
}
