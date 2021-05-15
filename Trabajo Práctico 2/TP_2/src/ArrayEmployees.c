
#include "ArrayEmployees.h"

int Employee_GetID()
{
	static int Employee_IdIncremental = 0;
	Employee_IdIncremental++;
	return Employee_IdIncremental;
}

int initEmployees(sEmployee* list, int len)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			list[i].isEmpty = EMPTY;
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

	if(list != NULL && len > 0)
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

int addEmployee(sEmployee* list, int len, int auxIndex)
{
	int retorno = -1;

	if(list != NULL && len > 0 && auxIndex >= 0)
	{
		utn_getString("\nIngrese el nombre del empleado: ", list[auxIndex].name);
		utn_getString("\nIngrese el apellido del empleado: ", list[auxIndex].lastName);
		list[auxIndex].salary = utn_getFloat("\nIngrese el salario del empleado: ", "\nReingrese una cifra válida [hasta 100000]: ", 1, 100000);
		printSectors();
		list[auxIndex].sector = utn_getEntero("\nIngrese el ID del sector de el empleado: ", "\n¡Error! Reingrese un sector válido: ", 1000, 1002);
		list[auxIndex].isEmpty = OCCUPIED;
		list[auxIndex].id = Employee_GetID();
		retorno = 0;
	}

	return retorno;
}

int removeEmployee(sEmployee* list, int len, int id)
{
	int retorno = -2;
	char answer;
	int auxIndex;

	if(list != NULL && len > 0)
	{
		auxIndex = FindEmployeeByID(list, len, id);

		if(auxIndex == -1)
		{
			retorno = -1; //Retorna que el ID no existe
		}
		else
		{
			answer = Confirmar("\n¿Estás seguro de la baja? (s/n): ");
			if(answer == 's')
			{
				list[auxIndex].isEmpty = EMPTY;
				retorno = 0; //Retorna baja exitosa
			}
			else
			{
				retorno = -2; //Retorna baja cancelada
			}
		}
	}
	return retorno;
}

int ModificationMenu()
{
	int option;

	printf("\n Menu de modificaciones \n");
	printf("\n1. Modificar nombre\n");
	printf("\n2. Modificar apellido\n");
	printf("\n3. Modificar salario\n");
	printf("\n4. Modicar sector\n");
	printf("\n5. Volver al menú principal\n");
	option = utn_getEntero("\nElija un opción: ", "\nOpción inválida, ingrese nuevamente: ", 1, 5);

	return option;
}

int ModifyEmployee(sEmployee* list, int len)
{
	int auxID;
	int auxIndex;
	char answer;
	int retorno = -2;
	sEmployee auxEmployee;

	if(list != NULL && len > 0)
	{
		auxID = getInt("\n\nIngrese el ID del empleado que quiere modificar: ");
		auxIndex = FindEmployeeByID(list, len, auxID);

		if(auxIndex == -1)
		{
			retorno = -1; //Retorna que el ID no existe
		}
		else
		{
			switch(ModificationMenu())
			{
				case 1:
					utn_getString("\nIngrese el nuevo nombre: ", auxEmployee.name);
					answer = Confirmar("\n¿Estás seguro de la modificación? (s/n): ");
					if(answer == 's')
					{
						strcpy(list[auxIndex].name, auxEmployee.name);
						retorno = 0; //Retorna modificación exitosa
					}
					else
					{
						retorno = -2; //Retorna modificación cancelada
					}
					break;
				case 2:
					utn_getString("\nIngrese el nuevo apellido: ", auxEmployee.lastName);
					answer = Confirmar("\n¿Estás seguro de la modificación? (s/n): ");
					if(answer == 's')
					{
						strcpy(list[auxIndex].lastName, auxEmployee.lastName);
						retorno = 0; //Retorna modificación exitosa
					}
					else
					{
						retorno = -2; //Retorna modificación cancelada
					}
					break;
				case 3:
					auxEmployee.salary = utn_getFloat("\nIngrese el nuevo salario: ", "\nReingrese una cifra válida [hasta 100000]: ", 1, 100000);
					answer = Confirmar("\n¿Estás seguro de la modificación? (s/n): ");
					if(answer == 's')
					{
						list[auxIndex].salary = auxEmployee.salary;
						retorno = 0; //Retorna modificación exitosa
					}
					else
					{
						retorno = -2; //Retorna modificación cancelada
					}
					break;
				case 4:
					printSectors();
					auxEmployee.sector = utn_getEntero("\nIngrese el ID del nuevo sector: ", "\n¡Error! Reingrese un sector válido: ", 1000, 1002);
					answer = Confirmar("\n¿Estás seguro de la modificación? (s/n): ");
					if(answer == 's')
					{
						list[auxIndex].sector = auxEmployee.sector;
						retorno = 0; //Retorna modificación exitosa
					}
					else
					{
						retorno = -2; //Retorna modificación cancelada
					}
					break;

				case 5:
					retorno = -2; //Retorna modificación cancelada
					break;
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

	if(list != NULL && len > 0)
	{
		switch(order)
		{
			case 0:

				for(i = 0; i < len-1; i++)
				{
					for(j = i+1; j < len; j++)
					{
						if(stricmp(list[i].lastName, list[j].lastName) > 0)
						{
							auxiliar = list[i];
							list[i] = list[j];
							list[j] = auxiliar;
						}
						else if((stricmp(list[i].lastName, list[j].lastName) == 0) && list[i].sector > list[j].sector)
						{
							auxiliar = list[i];
							list[i] = list[j];
							list[j] = auxiliar;
						}
					}
				}
				retorno = 0;
				break;

			case 1:

				for(i = 0; i < len-1; i++)
				{
					for(j = i+1; j < len; j++)
					{
						if(stricmp(list[i].lastName, list[j].lastName) < 0)
						{
							auxiliar = list[i];
							list[i] = list[j];
							list[j] = auxiliar;
						}
						else if((stricmp(list[i].lastName, list[j].lastName) == 0) && list[i].sector < list[j].sector)
						{
							auxiliar = list[i];
							list[i] = list[j];
							list[j] = auxiliar;
						}
					}
				}
				retorno = 0;
				break;
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
	printf("\n| ID: %2d | NOMBRE: %10s | APELLIDO: %10s | SALARIO: %2.2f | SECTOR: %2d |", auxEmployee.id,
																			               auxEmployee.name,
																			               auxEmployee.lastName,
																			               auxEmployee.salary,
																			               auxEmployee.sector);
}

void printSectors()
{
	printf("\n---------------------\n");
	printf("|      SECTORES     |\n");
	printf("---------------------\n");
	printf("|  MARKETING | 1000 |\n");
	printf("---------------------\n");
	printf("|    RRHH    | 1001 |\n");
	printf("---------------------\n");
	printf("|  SISTEMAS  | 1002 |\n");
	printf("---------------------\n");
}

void TestEmployees(sEmployee* list, int len)
{
	char auxName[][51] = {"Oscar", "Fabiana", "Luis", "Ana", "Zara", "Pedro", "Maria", "Victor"};
	char auxLastName[][51] = {"Garcia", "Velarde", "Martinez", "Lopez", "Morales", "Contreras", "Fausto", "Ignacio"};
	float salary[] = {200.50, 500.75, 250.70, 480.60, 900.50, 450.80, 700.50, 650.80};
	int auxSector[] = {1000, 1001, 1002, 1001, 1000, 1001, 1002, 1002};
	int state[] = {OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED, OCCUPIED};

	for(int i = 0; i < len; i++)
	{
		list[i].id = Employee_GetID();
		strcpy(list[i].name, auxName[i]);
		strcpy(list[i].lastName, auxLastName[i]);
		list[i].salary = salary[i];
		list[i].sector = auxSector[i];
		list[i].isEmpty = state[i];
	}
}
