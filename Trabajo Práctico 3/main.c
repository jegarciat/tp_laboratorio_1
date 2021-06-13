#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main()
{
    int opcion = 0;
    int datosCargadosText = 0;
    int datosCargadosBin = 0;

	setbuf(stdout, NULL);

    LinkedList* listaEmpleados = ll_newLinkedList();

    do
    {
    	MenuPrincipal(&opcion);

        switch(opcion)
        {
            case 1:
            	if(datosCargadosText == 0 && datosCargadosBin == 0)
            	{
					controller_loadFromText("test.csv", listaEmpleados);
					datosCargadosText = 1;
            	}
            	else
            	{
            		printf("\n\t¡Ya se cargo archivo!\n");
            	}
                break;

            case 2:
            	if(datosCargadosBin == 0 && datosCargadosText == 0)
            	{
            		controller_loadFromBinary("test.bin", listaEmpleados);
            		datosCargadosBin = 1;
            	}
            	else
            	{
            		printf("\n\t¡Ya se cargo archivo!\n");
            	}

            	break;
            case 3:
            	controller_addEmployee(listaEmpleados);
            	break;
            case 4:
            	controller_editEmployee(listaEmpleados);
            	break;
            case 5:
            	controller_removeEmployee(listaEmpleados);
            	break;
            case 6:
            	ll_sort(listaEmpleados, employee_CompararPorID, 1);
            	controller_ListEmployee(listaEmpleados);
            	break;
            case 7:
            	controller_sortEmployee(listaEmpleados);
            	break;
            case 8:
            	if(datosCargadosBin == 1 || datosCargadosText == 1)
            	{
					controller_saveAsText("test.csv", listaEmpleados);
            	}
            	else
            	{
            		printf("\n\t¡Tienes que cargar primero el archivo para agregarle los cambios realizados!\n");
            	}
            	break;
            case 9:
            	if(datosCargadosBin == 1 || datosCargadosText == 1)
            	{
            		controller_saveAsBinary("test.bin", listaEmpleados);
            	}
            	else
            	{
               		printf("\n\t¡Tienes que cargar primero el archivo para agregarle los cambios realizados!\n");
            	}
            	break;
            case 10:
            	printf("\n\t¡Saliste del programa!\n");
            	break;
        }

    }while(opcion != 10);

    return 0;
}

//Jorge García 1°C - Trabajo Práctico 3: Laboratorio I
