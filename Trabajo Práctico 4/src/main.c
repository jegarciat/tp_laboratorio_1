/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/main_test.h"
#include "../inc/LinkedList.h"
#include "../inc/Controller.h"
#include "../inc/Employee.h"

//Jorge García 1C - Trabajo Práctico 4: Laboratorio I - Legajo: 111263

int main(void)
{
	setbuf(stdout, NULL);

	//startTesting(1);  // ll_newLinkedList
	//startTesting(2);  // ll_len
	//startTesting(3);  // getNode - test_getNode
	//startTesting(4);  // addNode - test_addNode
	//startTesting(5);  // ll_add
	//startTesting(6);  // ll_get
	//startTesting(7);  // ll_set
	//startTesting(8);  // ll_remove
	//startTesting(9);  // ll_clear
	//startTesting(10); // ll_deleteLinkedList
	//startTesting(11); // ll_indexOf
	//startTesting(12); // ll_isEmpty
	//startTesting(13); // ll_push
	//startTesting(14); // ll_pop
	//startTesting(15); // ll_contains
	//startTesting(16); // ll_containsAll
	//startTesting(17); // ll_subList
	//startTesting(18); // ll_clone
	//startTesting(19); // ll_sort

    int opcion = 0;
    int datosCargadosText = 0;
    int datosCargadosBin = 0;

    LinkedList* listaEmpleados = ll_newLinkedList();

    do
    {
    	MenuPrincipal(&opcion);

        switch(opcion)
        {
            case 1:
            	if(datosCargadosText == 0 && datosCargadosBin == 0)
            	{
					if(controller_loadFromText("data.csv", listaEmpleados) == 0)
					{
						datosCargadosText = 1;
					}
            	}
            	else
            	{
            		printf("\n\t¡Ya se cargo archivo!\n");
            	}
                break;

            case 2:
            	if(datosCargadosBin == 0 && datosCargadosText == 0)
            	{
            		if(controller_loadFromBinary("data.bin", listaEmpleados) == 0)
            		{
						datosCargadosBin = 1;
            		}
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
            	if(controller_Reubicar(listaEmpleados) == 0)
            	{
            		controller_ListEmployee(listaEmpleados);
            		printf("\n\t\t\t¡Reubicacion exitosa!\n");
            	}
            	break;
            	break;
            case 9:
            	if(datosCargadosBin == 1 || datosCargadosText == 1)
            	{
					controller_saveAsText("data.csv", listaEmpleados);
            	}
            	else
            	{
            		printf("\n\t¡Tienes que cargar primero el archivo para agregarle los cambios realizados!\n");
            	}
            	break;
            case 10:
            	if(datosCargadosBin == 1 || datosCargadosText == 1)
            	{
            		controller_saveAsBinary("data.bin", listaEmpleados);
            	}
            	else
            	{
               		printf("\n\t¡Tienes que cargar primero el archivo para agregarle los cambios realizados!\n");
            	}
            	break;
            case 11:
            	printf("\n\t¡Saliste del programa!\n");
            	break;
        }

    }while(opcion != 12);

    return 0;
}

































