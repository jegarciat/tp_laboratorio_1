#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"
#include "parser.h"
#include "utn.h"

static int controller_IdIncremental = 0;

static int controller_ObtenerID()
{
	return controller_IdIncremental += 1;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	int estado;
	int parser;
	estado = -1;

	pArchivo = fopen(path, "r");

	if(pArchivo != NULL && pArrayListEmployee != NULL)
	{
		parser = parser_EmployeeFromText(pArchivo, pArrayListEmployee);

		if(parser != -1)
		{
			printf("\n\t¡Datos cargados correctamente!\n");
			if(controller_IdIncremental == 0)
			{
				controller_IdIncremental += parser;
				//printf("\nControl de ID mayor: %d\n", controller_IdIncremental);
				EscribirArchivoID();
			}

			estado = 0;
		}
	}
	else
	{
		printf("\n\n¡El archivo no se pudo abrir o no existe!\n");
	}

	fclose(pArchivo);

    return estado;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	int estado;
	int parser;
	estado = -1;

	pArchivo = fopen(path, "rb");

	if(pArchivo != NULL && pArrayListEmployee != NULL)
	{
		parser = parser_EmployeeFromBinary(pArchivo, pArrayListEmployee);

		if(parser != -1)
		{
			printf("\n\t¡Datos cargados correctamente!\n");
			if(controller_IdIncremental == 0)
			{
				controller_IdIncremental += parser;
				//printf("\nControl de ID mayor: %d\n", controller_IdIncremental);
				EscribirArchivoID();
			}

			estado = 0;
		}
	}
	else
	{
		printf("\n\n¡El archivo no se pudo abrir o no existe!\n");
	}

	fclose(pArchivo);

    return estado;
}

int EscribirArchivoID()
{
	FILE* pArchivo_ID;
	int estado = -1;

	pArchivo_ID = fopen("ID_Maximo.csv","w");

	if(pArchivo_ID != NULL)
	{
		fprintf(pArchivo_ID, "%d", controller_IdIncremental);
		fclose(pArchivo_ID);
		estado = 0;
	}

	return estado;
}

int LeerArchivoID()
{
	FILE* pArchivo_ID;
	int estado = -1;
	char idMax[256];

	pArchivo_ID = fopen("ID_Maximo.csv","r");

	if(pArchivo_ID != NULL)
	{
		fscanf(pArchivo_ID, "%s\n", idMax);
		controller_IdIncremental = atoi(idMax);
		fclose(pArchivo_ID);
		estado = 0;
	}

	return estado;
}


/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pEmpleado;
	int auxID;
	int estado;
	char respuesta;
	estado = -1;

	if(controller_IdIncremental == 0)
	{
		LeerArchivoID();
		//printf("\n[ID leido de ID_Maximo]: %d\n", controller_IdIncremental); // Printf de control
	}

	if(pArrayListEmployee != NULL)
	{
		pEmpleado = employee_new();

		if(pEmpleado == NULL)
		{
			printf("\n\t¡No hay memoria disponible!\n");
		}
		else
		{
			if(employee_CargarDatos(pEmpleado) == 0)
			{
				Confirmar(&respuesta, "\n¿Estás seguro de añadir este empleado? (s/n): ");

				if(respuesta == 's' && pEmpleado != NULL)
				{
					auxID = controller_ObtenerID();
					employee_setId(pEmpleado, auxID);
					ll_add(pArrayListEmployee, pEmpleado);
					printf("\n\t¡ALTA EXITOSA!\n");

					estado = 0;
				}
				else
				{
					employee_delete(pEmpleado);
					printf("\n\t[ALTA CANCELADA]\n");
				}
			}
		}
	}
	else
	{
		printf("\n\t¡La lista no existe!\n");
	}

    return estado;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pEmpleado;
	int auxID;
	int estado;
	int indexEdit;
	int opcion;
	estado = -1;

	if(pArrayListEmployee != NULL && !ll_isEmpty(pArrayListEmployee))
	{
		controller_ListEmployee(pArrayListEmployee);

		utn_getNumIntSM(&auxID, "\nIngrese el ID del empleado a modificar: ", "\n\t = | ¡Error! Ingrese un ID válido | =\n", 1);

		pEmpleado = employee_BuscarPorID(pArrayListEmployee, auxID);
		indexEdit = ll_indexOf(pArrayListEmployee, pEmpleado);

		if(pEmpleado == NULL)
		{
			printf("\n\t¡El ID ingresado no existe!\n");
		}
		else
		{
			printf("\n\t EMPLEADO A MODIFICAR ");
			controller_MostrarEmpleado(pArrayListEmployee, indexEdit);

			MenuEditarEmpleado(&opcion);

			switch (opcion)
			{
				case 1:
					printf("\n[MODIFICACION DEL NOMBRE]\n");
					if(Edit_Nombre(pArrayListEmployee, auxID, indexEdit) == 0)
					{
						printf("\n\t¡MODIFICACIÓN EXITOSA!\n");
						controller_MostrarEmpleado(pArrayListEmployee, indexEdit);
					}
					break;

				case 2:
					printf("\n[MODIFICACION DE HORAS TRABAJADAS]\n");
					if(Edit_Horas(pArrayListEmployee, auxID, indexEdit) == 0)
					{
						printf("\n\t¡MODIFICACIÓN EXITOSA!\n");
						controller_MostrarEmpleado(pArrayListEmployee, indexEdit);
					}
					break;

				case 3:
					printf("\n[MODIFICACIÓN DEL SUELDO]\n");
					if(Edit_Sueldo(pArrayListEmployee, auxID, indexEdit) == 0)
					{
						printf("\n\t¡MODIFICACIÓN EXITOSA!\n");
						controller_MostrarEmpleado(pArrayListEmployee, indexEdit);
					}
					break;
			}

			estado = 0;
		}
	}
	else
	{
		printf("\n\t¡No hay empleados cargados en la lista!\n");
	}

    return estado;
}

int Edit_Nombre(LinkedList* pArrayListEmployee, int idEdit, int indexEdit)
{
	Employee* pEmpleado;
	char auxNombre[128];
	char respuesta;
	int estado = -1;

	pEmpleado = employee_BuscarPorID(pArrayListEmployee, idEdit);
	indexEdit = ll_indexOf(pArrayListEmployee, pEmpleado);

	if(pEmpleado != NULL)
	{
		if(utn_getString(auxNombre, "\nIngrese el nuevo nombre del empleado: ", "\n\t = | ¡Error! Ingrese un nombre válido | =\n", 128, 5) == 0)
		{
			Confirmar(&respuesta, "\n¿Estás seguro/a de la modificación? (s/n): ");

			if(respuesta == 's')
			{
				employee_setNombre(pEmpleado, auxNombre);
				estado = 0;
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
	else
	{
		printf("\n\tError: Edit_Nombre\n");
	}

	return estado;
}

int Edit_Horas(LinkedList* pArrayListEmployee, int idEdit, int indexEdit)
{
	Employee* pEmpleado;
	int auxHoras;
	char respuesta;
	int estado = -1;

	pEmpleado = employee_BuscarPorID(pArrayListEmployee, idEdit);
	indexEdit = ll_indexOf(pArrayListEmployee, pEmpleado);

	if(pEmpleado != NULL)
	{
		if(utn_getNumEnteroV2(&auxHoras, "\nIngrese las horas trabajadas del empleado: ", "\n\t = | ¡Error! Ingrese una cifra válida | =\n\n", 1, 5) == 0)
		{
			Confirmar(&respuesta, "\n¿Estás seguro/a de la modificación? (s/n): ");

			if(respuesta == 's')
			{
				employee_setHorasTrabajadas(pEmpleado, auxHoras);
				estado = 0;
			}
			else
			{
				printf("\n\t[MODIFICACIÓN CANCELADA]\n");
			}
		}
		else
		{
			printf("\n\tnNo se pudo modificar el empleado ¡Se acabaron los intentos!\n");
		}
	}
	else
	{
		printf("\n\tError: Edit_Horas\n");
	}

	return estado;
}

int Edit_Sueldo(LinkedList* pArrayListEmployee, int idEdit, int indexEdit)
{
	Employee* pEmpleado;
	int auxSueldo;
	char respuesta;
	int estado = -1;

	pEmpleado = employee_BuscarPorID(pArrayListEmployee, idEdit);
	indexEdit = ll_indexOf(pArrayListEmployee, pEmpleado);

	if(pEmpleado != NULL)
	{
		if(utn_getNumEnteroV2(&auxSueldo, "\nIngrese el sueldo del empleado: ", "\n\t = | ¡Error! Ingrese un sueldo válido | =\n\n", 1, 5) == 0)
		{
			Confirmar(&respuesta, "\n¿Estás seguro/a de la modificación? (s/n): ");

			if(respuesta == 's')
			{
				employee_setSueldo(pEmpleado, auxSueldo);
				estado = 0;
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
	else
	{
		printf("\n\tError: Edit_Sueldo\n");
	}

	return estado;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pEmpleado;
	int auxID;
	int estado;
	int indexBaja;
	char respuesta;
	estado = -1;

	if(pArrayListEmployee != NULL && !ll_isEmpty(pArrayListEmployee))
	{
		controller_ListEmployee(pArrayListEmployee);

		utn_getNumIntSM(&auxID, "\nIngrese el ID a dar de baja: ", "\n\t = | ¡Error! Ingrese un ID válido | =\n", 1);

		pEmpleado = employee_BuscarPorID(pArrayListEmployee, auxID);
		indexBaja = ll_indexOf(pArrayListEmployee, pEmpleado);

		if(pEmpleado == NULL)
		{
			printf("\n\t¡El ID ingresado no existe!\n");
		}
		else
		{
			printf("\n\t EMPLEADO A DAR DE BAJA ");
			controller_MostrarEmpleado(pArrayListEmployee, indexBaja);

			Confirmar(&respuesta, "\n¿Estás seguro de la baja? (s/n): ");

			if(respuesta == 's')
			{
				employee_delete(pEmpleado);
				ll_remove(pArrayListEmployee, indexBaja);
				printf("\n\t¡BAJA EXITOSA!\n");
			}
			else
			{
				printf("\n\t[BAJA CANCELADA]\n");
			}

			estado = 0;
		}
	}
	else
	{
		printf("\n\t¡No hay empleados cargados en la lista!\n");
	}

    return estado;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int estado = -1;
	int len;

	if(pArrayListEmployee != NULL && !ll_isEmpty(pArrayListEmployee))
	{
		len = ll_len(pArrayListEmployee);

		estado = 0;

		for(int i = 0; i < len; i++)
		{
			controller_MostrarEmpleado(pArrayListEmployee, i);
		}
	}
	else
	{
		printf("\n\t¡No hay empleados cargados en la lista!\n");
	}

    return estado;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	LinkedList* clone;
	int estado = -1;
	int opcion;

	if(pArrayListEmployee != NULL && !ll_isEmpty(pArrayListEmployee))
	{
		clone = ll_clone(pArrayListEmployee);

		MenuOrdenamiento(&opcion);

		switch (opcion)
		{
			case 1:
				printf("\nOrdenamiento por nombre\n");
				if(OrdenamientoPorNombre(clone) == 0)
				{
					controller_ListEmployee(clone);
				}
				break;

			case 2:
				printf("\nOrdenamiento por ID\n");
				if(OrdenamientoPorID(clone) == 0)
				{
					controller_ListEmployee(clone);
				}
				break;

			case 3:
				printf("\nOrdenamiento por sueldo\n");
				if(OrdenamientoPorSueldo(clone) == 0)
				{
					controller_ListEmployee(clone);
				}
				break;

			case 4:
				printf("\nOrdenamiento por horas trabajadas\n");
				if(OrdenamientoPorHorasTrabajadas(clone) == 0)
				{
					controller_ListEmployee(clone);
				}
				break;
		}

		ll_deleteLinkedList(clone);
		estado = 0;
	}
	else
	{
		printf("\n\t¡No hay empleados cargados en la lista!\n");
	}

    return estado;
}

int OrdenamientoPorNombre(LinkedList* auxList)
{
	int orden;
	int estado = -1;

	if(auxList != NULL)
	{
		if(utn_getNumEntero(&orden, "\nIngresa [1] para ordenar de forma ascendente\nIngresa [0] para ordenar de forma descendente\n\nIngrese acá: ", "\n\t= | ¡Opción inválida! | =\n", 0, 1, 5) == 0)
		{
			if(orden == 1)
			{
				ll_sort(auxList, employee_CompararPorNombre, orden);
				estado = 0;
				printf("\nLista ordenada de forma ascendente por nombre:");
			}
			else
			{
				ll_sort(auxList, employee_CompararPorNombre, orden);
				estado = 0;
				printf("\nLista ordenada de forma descendente por nombre:");
			}
		}
		else
		{
			printf("\n\t¡No acertaste una! Te devolvemos al menú principal \n");
		}
	}

	return estado;
}

int OrdenamientoPorID(LinkedList* auxList)
{
	int orden;
	int estado = -1;

	if(utn_getNumEntero(&orden, "\nIngresa [1] para ordenar de forma ascendente\nIngresa [0] para ordenar de forma descendente\n\nIngrese acá: ", "\n\t= | ¡Opción inválida! | =\n", 0, 1, 5) == 0)
	{
		if(orden == 1)
		{
			ll_sort(auxList, employee_CompararPorID, orden);
			estado = 0;
			printf("\nLista ordenada de forma ascendente por ID:");
		}
		else
		{
			ll_sort(auxList, employee_CompararPorID, orden);
			estado = 0;
			printf("\nLista ordenada de forma descendente por ID:");
		}
	}
	else
	{
		printf("\n\t¡No acertaste una! Te devolvemos al menú principal \n");
	}

	return estado;
}

int OrdenamientoPorSueldo(LinkedList* auxList)
{
	int orden;
	int estado = -1;

	if(utn_getNumEntero(&orden, "\nIngresa [1] para ordenar de forma ascendente\nIngresa [0] para ordenar de forma descendente\n\nIngrese acá: ", "\n\t= | ¡Opción inválida! | =\n", 0, 1, 5) == 0)
	{
		if(orden == 1)
		{
			ll_sort(auxList, employee_CompararPorSueldo, orden);
			estado = 0;
			printf("\nLista ordenada de forma ascendente por sueldo:");
		}
		else
		{
			ll_sort(auxList, employee_CompararPorSueldo, orden);
			estado = 0;
			printf("\nLista ordenada de forma descendente por sueldo:");
		}
	}
	else
	{
		printf("\n\t¡No acertaste una! Te devolvemos al menú principal \n");
	}

	return estado;
}

int OrdenamientoPorHorasTrabajadas(LinkedList* auxList)
{
	int orden;
	int estado = -1;

	if(utn_getNumEntero(&orden, "\nIngresa [1] para ordenar de forma ascendente\nIngresa [0] para ordenar de forma descendente\n\nIngrese acá: ", "\n\t= | ¡Opción inválida! | =\n", 0, 1, 5) == 0)
	{
		if(orden == 1)
		{
			ll_sort(auxList, employee_CompararPorHoras, orden);
			estado = 0;
			printf("\nLista ordenada de forma ascendente por horas trabajadas:");
		}
		else
		{
			ll_sort(auxList, employee_CompararPorHoras, orden);
			estado = 0;
			printf("\nLista ordenada de forma descendente por horas trabajadas:");
		}
	}
	else
	{
		printf("\n\t¡No acertaste una! Te devolvemos al menú principal \n");
	}

	return estado;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	Employee* pEmpleado;
	int estado;
	int len;
	int id;
	int horasTrabajadas;
	int sueldo;
	char nombre[128];
	estado = -1;

	pArchivo = fopen(path, "w");

	if(pArchivo != NULL && pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		fprintf(pArchivo, "id,nombre,horasTrabajadas,sueldo\n");
		for(int i = 0; i < len; i++)
		{
			pEmpleado = (Employee*)ll_get(pArrayListEmployee, i);

			if(employee_getId(pEmpleado, &id) == 0 &&
			   employee_getNombre(pEmpleado, nombre) == 0 &&
			   employee_getHorasTrabajadas(pEmpleado, &horasTrabajadas) == 0 &&
			   employee_getSueldo(pEmpleado, &sueldo) == 0)
			{
				fprintf(pArchivo, "%d, %s, %d, %d\n", id, nombre, horasTrabajadas, sueldo);
			}

			if(controller_IdIncremental > 0)
			{
				EscribirArchivoID();
			}

			estado = 0;
		}

		fclose(pArchivo);
	}

	if(estado == 0)
	{
		printf("\n\t¡Datos guardados exitosamente!\n");
	}
	else
	{
		printf("\n\t¡No hay nada que guardar!\n");
	}

    return estado;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	Employee* pEmpleado;
	int estado;
	int len;
	estado = -1;

	pArchivo = fopen(path, "wb");

	if(pArchivo != NULL && pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);

		for(int i = 0; i < len; i++)
		{
			pEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
			if(pEmpleado != NULL)
			{
				fwrite(pEmpleado, sizeof(Employee), 1, pArchivo);
				estado = 0;
			}
		}

		if(controller_IdIncremental > 0)
		{
			EscribirArchivoID();
		}

		fclose(pArchivo);
	}

	if(estado == 0)
	{
		printf("\n\t¡Datos guardados exitosamente!\n");
	}
	else
	{
		printf("\n\t¡No hay nada que guardar!\n");
	}


    return estado;
}

int controller_MostrarEmpleado(LinkedList* pArrayListEmployee, int indice)
{
	int estado = -1;
	Employee* pEmpleado;
	int auxid;
	int auxHoras;
	int auxSueldo;
	char auxNombre[128];

	if(pArrayListEmployee != NULL && indice >= 0)
	{
		pEmpleado = (Employee*)ll_get(pArrayListEmployee, indice);

		if(employee_getId(pEmpleado, &auxid) == 0 &&
		   employee_getNombre(pEmpleado, auxNombre) == 0 &&
		   employee_getHorasTrabajadas(pEmpleado, &auxHoras) == 0 &&
		   employee_getSueldo(pEmpleado, &auxSueldo) == 0)
		{
			printf("\n-----------------------------------------------------------------------------------");
			printf("\n| ID: %5d | NOMBRE: %12s | HORAS TRABAJADAS: %5d | SUELDO: %10d |", auxid, auxNombre, auxHoras, auxSueldo);
			printf("\n-----------------------------------------------------------------------------------");
			estado = 0;
		}
		else
		{
			printf("\n\tError al mostrar el empleado\n");
			estado = -1;
		}

	}

	return estado;
}

void MenuPrincipal(int* opcion)
{
	printf("\n\n=============================| MENU PRINCIPAL |==============================\n");
	printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
	printf("2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n");
	printf("3. Alta de empleado\n");
	printf("4. Modificar datos de empleado\n");
	printf("5. Baja de empleado\n");
	printf("6. Listar empleados\n");
	printf("7. Ordenar empleados\n");
	printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
	printf("9. Guardar los datos de los empleados en el archivo data.bin (modo binario).\n");
	printf("10. Salir\n");

	utn_getNumInt(opcion, "\nIngrese una opcion: ", "\n¡Error! Ingresa una opción del menú.\n", 1, 10);
}

void MenuEditarEmpleado(int* opcion)
{
	printf("\n ----------------------------------");
	printf("\n |    OPCIONES DE MODIFICACION    |\n");
	printf(" ----------------------------------\n");
	printf(" | 1. Modificar nombre            |\n");
	printf(" | 2. Modificar horas trabajadas  |\n");
	printf(" | 3. Modificar sueldo            |\n");
	printf(" | 4. Volver al menú principal    |\n");
	printf(" ----------------------------------\n");

	utn_getNumInt(opcion, "Ingrese una opción: ", "\n\t = | ¡Error! Ingresa una opción del menú | = \n\n", 1, 4);
}

void MenuOrdenamiento(int* opcion)
{
	printf("\n -----------------------------------");
	printf("\n |          ORDENAMIENTOS          |\n");
	printf(" -----------------------------------\n");
	printf(" | 1. Ordenar por nombre           |\n");
	printf(" | 2. Ordenar por ID               |\n");
	printf(" | 3. Ordenar por sueldo           |\n");
	printf(" | 4. Ordenar por horas trabajadas |\n");
	printf(" | 5. Volver al menú principal     |\n");
	printf(" -----------------------------------\n");

	utn_getNumInt(opcion, "Ingrese una opcion: ", "\n\t = | ¡Error! Ingresa una opción del menú | = \n\n", 1, 5);
}

