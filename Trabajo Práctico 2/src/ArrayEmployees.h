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
* \param id int ID to register
* \param name[] char name to register
* \param lastName[] char lastName to register
* \param salary float salary to register
* \param sector int sector to register
* \return int Return (-1) if error [Invalid length or NULL pointer or without free space] -
* 					  (0) if Ok
*
*/
int addEmployee(sEmployee* list, int len, int id, char name[], char lastName[], float salary, int sector);

/** \brief Request an employee's data
 *
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (Employee) if Ok
 *
*/
sEmployee Employee_RequestData(sEmployee* list, int len);

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
*
* \param list sEmployee* Pointer to array of employees
* \param len int Array length
* \param id int ID to be removed
* \return int Return (-1) if the remove was canceled or if error [Invalid length or NULL pointer]
*  		 			  (0) if Ok
*
*/
int removeEmployee(sEmployee* list, int len, int id);

/**
 * \brief Function that provides the options to modify an employee, asks the user for an option and validates it.
 * \return void.
 */
void ModificationMenu(int* option);

/**
 * \brief Modify an employee using an ID entered by the user.
 * \param list sEmployee* Pointer to array of employees
 * \param len int Array length
 */
void ModifyEmployee(sEmployee* list, int len);

/** \brief Modify an employee's name
*
* \param list sEmployee* Pointer to array of employees
* \param indexEdit int the position of the employee to modify
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int Edit_Name(sEmployee* list, int indexEdit);

/** \brief Modify an employee's last name
*
* \param list sEmployee* Pointer to array of employees
* \param indexEdit int the position of the employee to modify
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int Edit_LastName(sEmployee* list, int indexEdit);

/** \brief Modify an employee's salary
*
* \param list sEmployee* Pointer to array of employees
* \param indexEdit int the position of the employee to modify
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int Edit_Salary(sEmployee* list, int indexEdit);

/** \brief Modify an employee's sector
*
* \param list sEmployee* Pointer to array of employees
* \param indexEdit int the position of the employee to modify
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int Edit_Sector(sEmployee* list, int indexEdit);

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

/** \brief Sort employees by ID from highest to lowest
*
* \param list sEmployee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int sortEmployeesByID(sEmployee* list, int len);

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
