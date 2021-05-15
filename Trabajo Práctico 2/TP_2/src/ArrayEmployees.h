/*
 * ArrayEmployees.h
 *
 *  Programa: Trabajo práctico 2
 *      Author: Jorge García 1°C
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Input.h"

#define EMPTY 1
#define OCCUPIED 0

#define QTY_EMPLOYEES 1000

typedef struct
{
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int isEmpty;

}sEmployee;

/**
 * \brief Increases the base employee ID by 1 and returns it.
 * \return Incremental integer by 1 unrepeatable.
 */
int Employee_GetID();

/** \brief To indicate that all position in the array are empty,
    	   this function put the flag (isEmpty) in TRUE in all
		   position of the array
* \param list sEmployee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initEmployees(sEmployee* list, int len);

/** \brief find an Employee by Id en returns the index position in array.
*
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
* \param id int ID to be searched
* \return Return employee index position or (-1) if [Invalid length or NULL
		  pointer received or employee not found]
*
*/
int FindEmployeeByID(sEmployee* list, int len, int id);

/** \brief Find first empty position in the array
 *
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
 * \return Returns the index of the position empty or -1 in case of error [Invalid length or NULL
	pointer received or if there is no free space]
 *
 */
int Employees_SearchFree(sEmployee* list, int len);

/** \brief add in an existing list of employees the data of an employee
 * 		   in the first empty position
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
* \param auxIndex int Free position where data is loaded
* \return int Return (-1) if error [Invalid length or NULL pointer or without
		  free space] - (0) if Ok
*
*/
int addEmployee(sEmployee* list, int len, int auxIndex);

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
*
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
* \param id int ID to be removed
* \return int Return (-1) if the entered id does not exist
* 		  (-2) if the remove was canceled or if error [Invalid length or NULL pointer]
*  		  (0) if Ok
*
*/
int removeEmployee(sEmployee* list, int len, int id);

/**
 * \brief Function that provides the options to modify an employee, asks the user for an option and validates it.
 * \return The chosen option (1 to 5).
 */
int ModificationMenu();

/**
 * \brief Modify an employee using an ID entered by the user.
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
 * \return (-2) If the modification was canceled or if Error [Invalid length or NULL pointer]
 *         (-1) If the entered ID does not exist.
 *          (0) if Ok.
 */
int ModifyEmployee(sEmployee* list, int len);

/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
*
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
* \param order int [0] indicate UP - [1] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int sortEmployees(sEmployee* list, int len, int order);

/** \brief print the content of employees array
*
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
* \return int retorno (-1) If there are no loaded employees or if Error [Invalid length or NULL pointer]
* 		  (0) if Ok
*
*/
int printEmployees(sEmployee* list, int len);

/** \brief Print a single employee.
*
 * \param sEmployee auxEmployee A single employee to be displayed
* \return void
*
*/
void printEmployee(sEmployee auxEmployee);

/** \brief Print the sectors.
* \return void
*/
void printSectors();

/** \brief Function that loads 8 employees to test.
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
 */
void TestEmployees(sEmployee* list, int len);

#endif /* ARRAYEMPLOYEES_H_ */
