#include <stdio.h>
#include <stdlib.h>
#include "../inc/LinkedList.h"
#include "../inc/Controller.h"
#include "../inc/Employee.h"
#include "../inc/parser.h"
#include "../inc/utn.h"

/** \brief Genera un ID único incremental en 1.
 *
 * \return int controller_IdIncremental+1
 *
 */
static int controller_IdIncremental = 0;
static int controller_ObtenerID()
{
	return controller_IdIncremental += 1;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Dirección del archivo de donde se cargaran los datos
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] En caso de exito
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	int estado;
	int parser;
	estado = -1;

	pArchivo = fopen(path, "r");

	if(pArchivo == NULL)
	{
		printf("\n\n[PRINT DE CONTROL]: ¡pArchivo es igual a NULL!\n");
	}

	if(pArrayListEmployee == NULL)
	{
		printf("\n\n¡[PRINT DE CONTROL]: pArrayListEmployee es igual a NULL!\n");
	}

	if(pArchivo != NULL && pArrayListEmployee != NULL)
	{
		parser = parser_EmployeeFromText(pArchivo, pArrayListEmployee);

		if(parser != -1)
		{
			printf("\n\t¡Datos cargados correctamente!\n");
			if(controller_IdIncremental == 0)
			{
				controller_IdIncremental += parser;
				EscribirArchivoID();
			}

			estado = 0;
		}
		else
		{
			printf("\n\n¡Error en parser_EmployeeFromText!\n");
		}
	}
	else
	{
		printf("\n\n¡El archivo no se pudo abrir o no existe!\n");
	}

	fclose(pArchivo);

    return estado;
}

/** \brief Carga los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param path char* Dirección del archivo de donde se cargaran los datos
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] En caso de exito
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	int estado;
	int parser;
	estado = -1;

	pArchivo = fopen(path, "rb");

	if(pArchivo == NULL)
	{
		printf("\n\n[PRINT DE CONTROL]: ¡pArchivo es igual a NULL!\n");
	}

	if(pArrayListEmployee == NULL)
	{
		printf("\n\n[PRINT DE CONTROL]: ¡pArrayListEmployee es igual a NULL!\n");
	}

	if(pArchivo != NULL && pArrayListEmployee != NULL)
	{
		parser = parser_EmployeeFromBinary(pArchivo, pArrayListEmployee);

		if(parser != -1)
		{
			printf("\n\t¡Datos cargados correctamente!\n");
			if(controller_IdIncremental == 0)
			{
				controller_IdIncremental += parser;
				EscribirArchivoID();
			}

			estado = 0;
		}
		else
		{
			printf("\n\n¡Error en parser_EmployeeFromBinary!\n");
		}
	}
	else
	{
		printf("\n\n¡El archivo no se pudo abrir o no existe!\n");
	}

	fclose(pArchivo);

    return estado;
}

/** \brief Guarda el controller_IdIncremental en el archivo ID_Maximo.csv
 *
 * \return int [-1] Si hay un error al abrir el archivo - [0] Si se logro guardar
 *
 */
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

/** \brief Carga el ID máximo de el archivo ID_Maximo.csv
 *
 * \return int [-1] Si hay un error al abrir el archivo - [0] Si se logro cargar
 *
 */
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
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores o si se cancelo el alta - [0] Si se agrego el empleado
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

/** \brief Modificar datos de un empleado
 *
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] En caso de exito
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
					if(Edit_Nombre(pArrayListEmployee, auxID) == 0)
					{
						printf("\n\t¡MODIFICACIÓN EXITOSA!\n");
						controller_MostrarEmpleado(pArrayListEmployee, indexEdit);
					}
					break;

				case 2:
					printf("\n[MODIFICACION DE HORAS TRABAJADAS]\n");
					if(Edit_Horas(pArrayListEmployee, auxID) == 0)
					{
						printf("\n\t¡MODIFICACIÓN EXITOSA!\n");
						controller_MostrarEmpleado(pArrayListEmployee, indexEdit);
					}
					break;

				case 3:
					printf("\n[MODIFICACIÓN DEL SUELDO]\n");
					if(Edit_Sueldo(pArrayListEmployee, auxID) == 0)
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

/** \brief Modifica el nombre de un empleado
 *
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \param idEdit int ID del empleado a modificar
 * \return int [-1] Si hay errores o se cancelo la modificación - [0] Si se modificó el nombre
 *
 */
int Edit_Nombre(LinkedList* pArrayListEmployee, int idEdit)
{
	Employee* pEmpleado;
	char auxNombre[128];
	char respuesta;
	int estado = -1;

	pEmpleado = employee_BuscarPorID(pArrayListEmployee, idEdit);
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

/** \brief Modifica las horas trabajadas de un empleado
 *
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \param idEdit int ID del empleado a modificar
 * \return int [-1] Si hay errores o se cancelo la modificación - [0] Si se modificaron las horas trabajadas
 *
 */
int Edit_Horas(LinkedList* pArrayListEmployee, int idEdit)
{
	Employee* pEmpleado;
	int auxHoras;
	char respuesta;
	int estado = -1;

	pEmpleado = employee_BuscarPorID(pArrayListEmployee, idEdit);
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

/** \brief Modifica el sueldo de un empleado
 *
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \param idEdit int ID del empleado a modificar
 * \return int [-1] Si hay errores o se cancelo la modificación - [0] Si se modificó el sueldo
 *
 */
int Edit_Sueldo(LinkedList* pArrayListEmployee, int idEdit)
{
	Employee* pEmpleado;
	int auxSueldo;
	char respuesta;
	int estado = -1;

	pEmpleado = employee_BuscarPorID(pArrayListEmployee, idEdit);
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

/** \brief Baja de un empleado
 *
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] En caso de exito
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
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] En caso de exito
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int estado = -1;
	int len;

	if(pArrayListEmployee != NULL && !ll_isEmpty(pArrayListEmployee))
	{
		len = ll_len(pArrayListEmployee);

		for(int i = 0; i < len; i++)
		{
			controller_MostrarEmpleado(pArrayListEmployee, i);
		}

		estado = 0;
	}
	else
	{
		printf("\n\t¡No hay empleados cargados en la lista!\n");
	}

    return estado;
}

/** \brief Ordenar empleados
 *
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] En caso de exito
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

/** \brief Ordena la lista de empleados por nombre
 *
 * \param auxList LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] Si se ordeno la lista
 *
 */
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

/** \brief Ordena la lista de empleados por ID
 *
 * \param auxList LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] Si se ordeno la lista
 *
 */
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

/** \brief Ordena la lista de empleados por sueldo
 *
 * \param auxList LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] Si se ordeno la lista
 *
 */
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

/** \brief Ordena la lista de empleados por horas trabajadas
 *
 * \param auxList LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] Si se ordeno la lista
 *
 */
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
 * \param path char* Dirección del archivo donde se guardaran los datos
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] En caso de exito
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

/** \brief Guarda los datos de los empleados en el archivo data.bin (modo binario).
 *
 * \param path char* Dirección del archivo donde se guardaran los datos
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \return int [-1] Si hay errores - [0] En caso de exito
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

/** \brief Muestra un empleado
 *
 * \param pArrayListEmployee LinkedList* Array del LinkedList
 * \param indice int Posición del empleado a listar
 * \return int [-1] Si hay errores - [0] En caso de exito
 *
 */
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
			printf("\n--------------------------------------------------------------------------------------");
			printf("\n| ID: %5d | NOMBRE: %15s | HORAS TRABAJADAS: %5d | SUELDO: %10d |", auxid, auxNombre, auxHoras, auxSueldo);
			printf("\n--------------------------------------------------------------------------------------");
			estado = 0;
		}
		else
		{
			printf("\n\tError al mostrar el empleado\n");
		}
	}

	return estado;
}

/** \brief Menu con las opciones principales para interactuar con el usuario.
 *
 * \param opcion int* Opcion elegida
 */
void MenuPrincipal(int* opcion)
{
	printf("\n\n =============================|      TP4       |==============================");
	printf("\n =============================| MENU PRINCIPAL |==============================\n");
	printf(" 1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
	printf(" 2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n");
	printf(" 3. Alta de empleado\n");
	printf(" 4. Modificar datos de empleado\n");
	printf(" 5. Baja de empleado\n");
	printf(" 6. Listar empleados\n");
	printf(" 7. Ordenar empleados\n");
	printf(" 8. Reubicar empleado\n");
	printf(" 9. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
	printf(" 10. Guardar los datos de los empleados en el archivo data.bin (modo binario).\n");
	printf(" 11. Salir\n");

	utn_getNumInt(opcion, "\nIngrese una opcion: ", "\n¡Error! Ingresa una opción del menú.\n", 1, 13);
}

/** \brief Menu con las opciones de modificación.
 *
 * \param opcion int* Opcion elegida
 */
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

/** \brief Menu con las opciones de ordenamiento.
 *
 * \param opcion int* Opcion elegida
 */
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

int controller_Reubicar(LinkedList* pArrayListEmployee)
{
	Employee* pEmpleadoReubicar;
	Employee* pAuxiliar;
	Employee* pEmpleado;
	int auxID_1;
	int auxID_2;
	int estado;
	int auxIndex_1;
	int auxIndex_2;
	estado = -1;

	if(pArrayListEmployee != NULL && !ll_isEmpty(pArrayListEmployee))
	{
		controller_ListEmployee(pArrayListEmployee);

		utn_getNumIntSM(&auxID_1, "\nIngrese el ID del empleado a reubicar: ", "\n\t = | ¡Error! Ingrese un ID válido | =\n", 1);

		pEmpleadoReubicar = employee_BuscarPorID(pArrayListEmployee, auxID_1);
		auxIndex_1 = ll_indexOf(pArrayListEmployee, pEmpleadoReubicar);

		if(auxIndex_1 == -1)
		{
			printf("\n\t¡El ID ingresado no existe!\n");
		}
		else
		{
			controller_ListEmployee(pArrayListEmployee);
			printf("\n\t EMPLEADO A REUBICAR ");
			controller_MostrarEmpleado(pArrayListEmployee, auxIndex_1);
			utn_getNumIntSM(&auxID_2, "\nIngrese el ID donde lo quiere reubicar: ", "\n\t = | ¡Error! Ingrese un ID válido | =\n", 1);

			pEmpleado = employee_BuscarPorID(pArrayListEmployee, auxID_2);
			auxIndex_2 = ll_indexOf(pArrayListEmployee, pEmpleado);

			if(auxIndex_2 != -1)
			{
				pAuxiliar = (Employee*)ll_pop(pArrayListEmployee, auxIndex_1);
				ll_push(pArrayListEmployee, auxIndex_2, pAuxiliar);
				estado = 0;
			}
			else
			{
				printf("\n\t¡El ID ingresado no existe!\n");
			}
		}
	}
	else
	{
		printf("\n\t¡No hay empleados cargados en la lista!\n");
	}

	return estado;
}

