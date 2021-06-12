#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "utn.h"

Employee* employee_new()
{
	Employee* pEmpleado = NULL;
	pEmpleado = (Employee*)malloc(sizeof(Employee));
	return pEmpleado;
}

Employee* employee_newParametros(char* idStr, char* nombreStr, char* horasTrabajadasStr, char* sueldoStr)
{
	int id;
	int horasTrabajadas;
	int sueldo;

	Employee* pEmpleado = employee_new();

	if(pEmpleado != NULL &&  idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		id = atoi(idStr);
		horasTrabajadas = atoi(horasTrabajadasStr);
		sueldo = atoi(sueldoStr);

		if(employee_setId(pEmpleado, id) == -1 ||
		   employee_setNombre(pEmpleado, nombreStr) == -1 ||
		   employee_setSueldo(pEmpleado, sueldo) == -1 ||
		   employee_setHorasTrabajadas(pEmpleado, horasTrabajadas) == -1)
		{
			employee_delete(pEmpleado);
		}
	}
	else
	{
		employee_delete(pEmpleado);
	}

	return pEmpleado;
}

void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
		this = NULL;
	}
}

int employee_setId(Employee* this, int id)
{
    int estado = -1;
    if(this != NULL && id >= 0)
    {
        this->id = id;
        estado = 0;
    }

    return estado;
}

int employee_getId(Employee* this, int* id)
{
	int estado = -1;
	if(this != NULL && id >= 0)
	{
		*id = this->id;
		estado = 0;
	}

	return estado;
}

int employee_setNombre(Employee* this, char* nombre)
{
    int estado = -1;
    if(this != NULL && nombre != NULL && strlen(nombre) < 128)
    {
    	AcomodarString(nombre);
    	strncpy(this->nombre, nombre, sizeof(this->nombre));
    	estado = 0;
    }

    return estado;
}

int employee_getNombre(Employee* this, char* nombre)
{
    int estado = -1;
    if(this != NULL && nombre != NULL)
    {
    	strcpy(nombre, this->nombre);
    	estado = 0;
    }

    return estado;
}

int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int estado = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
		this->horasTrabajadas = horasTrabajadas;
		estado = 0;
	}

	return estado;
}

int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas)
{
	int estado = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
		*horasTrabajadas = this->horasTrabajadas;
		estado = 0;
	}

	return estado;
}

int employee_setSueldo(Employee* this, int sueldo)
{
	int estado = -1;
	if(this != NULL && sueldo >= 0)
	{
		this->sueldo = sueldo;
		estado = 0;
	}

	return estado;
}

int employee_getSueldo(Employee* this, int* sueldo)
{
	int estado = -1;
	if(this != NULL && sueldo >= 0)
	{
		*sueldo = this->sueldo;
		estado = 0;
	}

	return estado;
}

int employee_CargarDatos(Employee* pEmpleado)
{
	int auxSueldo;
	int auxHoras;
	char auxNombre[128];
	int estado = -1;

	if(pEmpleado != NULL)
	{
		if(utn_getString(auxNombre, "\nIngrese el nombre: ", "\n\t = | ¡Error! Ingrese un nombre válido | =\n", 128, 5) == 0 &&
		   utn_getNumEnteroV2(&auxSueldo, "\nIngrese el sueldo: ", "\n\t = | ¡Error! Ingrese un sueldo válido | =\n\n", 0, 5) == 0 &&
		   utn_getNumEnteroV2(&auxHoras, "\nIngrese las horas trabajadas: ", "\n\t = | ¡Error! Ingrese una cifra válida | =\n\n", 1, 5) == 0)
		{
			employee_setNombre(pEmpleado, auxNombre);
			employee_setSueldo(pEmpleado, auxSueldo);
			employee_setHorasTrabajadas(pEmpleado, auxHoras);
			estado = 0;
		}
		else
		{
			printf("\n\t ¡Error! Se ingresaron datos inválidos\n\n");
		}
	}

	return estado;
}

Employee* employee_BuscarPorID(LinkedList* pArrayListEmployee, int idBuscar)
{
	Employee* pEmpleado;
	Employee* pAux;
	int auxID;
	int len;

	pEmpleado = NULL;

	if(pArrayListEmployee != NULL && idBuscar > 0)
	{
		len = ll_len(pArrayListEmployee);

		for(int i = 0; i < len; i++)
		{
			pAux = (Employee*)ll_get(pArrayListEmployee, i);

			if(employee_getId(pAux, &auxID) == 0 && auxID == idBuscar)
			{
				pEmpleado = pAux;
				break;
			}
		}
	}

	return pEmpleado;
}

int employee_CompararPorNombre(void* empleado1, void* empleado2)
{
	int ordenamiento;
	Employee* auxEmpleado1;
	Employee* auxEmpleado2;
	char nombre1[128];
	char nombre2[128];

	ordenamiento = -1;

	if(empleado1 != NULL && empleado2 != NULL)
	{
		auxEmpleado1 = (Employee*)empleado1;
		auxEmpleado2 = (Employee*)empleado2;

		employee_getNombre(auxEmpleado1, nombre1);
		employee_getNombre(auxEmpleado2, nombre2);

		ordenamiento = stricmp(nombre1, nombre2);
	}

	return ordenamiento;
}

int employee_CompararPorID(void* empleado1, void* empleado2)
{
	int ordenamiento = 0;
	Employee* auxEmpleado1;
	Employee* auxEmpleado2;
	int id1;
	int id2;

	if(empleado1 != NULL && empleado2 != NULL)
	{
		auxEmpleado1 = (Employee*)empleado1;
		auxEmpleado2 = (Employee*)empleado2;

		employee_getId(auxEmpleado1, &id1);
		employee_getId(auxEmpleado2, &id2);

		if(id1 > id2)
		{
			ordenamiento = 1;
		}
		else
		{
			if(id1 < id2)
			{
				ordenamiento = -1;
			}
		}

	}

	return ordenamiento;
}

int employee_CompararPorSueldo(void* empleado1, void* empleado2)
{
	int ordenamiento = 0;
	Employee* auxEmpleado1;
	Employee* auxEmpleado2;
	int sueldo1;
	int sueldo2;

	if(empleado1 != NULL && empleado2 != NULL)
	{
		auxEmpleado1 = (Employee*)empleado1;
		auxEmpleado2 = (Employee*)empleado2;

		employee_getSueldo(auxEmpleado1, &sueldo1);
		employee_getSueldo(auxEmpleado2, &sueldo2);

		if(sueldo1 > sueldo2)
		{
			ordenamiento = 1;
		}
		else
		{
			if(sueldo1 < sueldo2)
			{
				ordenamiento = -1;
			}
		}
	}

	return ordenamiento;
}

int employee_CompararPorHoras(void* empleado1, void* empleado2)
{
	int ordenamiento = 0;
	Employee* auxEmpleado1;
	Employee* auxEmpleado2;
	int horas1;
	int horas2;

	auxEmpleado1 = (Employee*)empleado1;
	auxEmpleado2 = (Employee*)empleado2;


	if(auxEmpleado1 != NULL && auxEmpleado2 != NULL)
	{

		employee_getHorasTrabajadas(auxEmpleado1, &horas1);
		employee_getHorasTrabajadas(auxEmpleado2, &horas2);

		if(horas1 > horas2)
		{
			ordenamiento = 1;
		}
		else
		{
			if(horas1 < horas2)
			{
				ordenamiento = -1;
			}
		}
	}

	return ordenamiento;
}

