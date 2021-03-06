#ifndef INFORMES_H_
#define INFORMES_H_

#include "ArrayEmployees.h"
#include "Input.h"

/**
 * \brief Function that shows the main menu, asks the user for an option and validate it.
 * \return void.
 */
void MainMenu(int* option);

/**
* \brief Function that displays the reports menu, prompts the user for an option and validate it.
* \return void.
 */
void Reports_Menu(int* option);

/** \brief Calculate the total amount of salary for all employees.
*
* \param list sEmployee* Pointer to array of employees
* \param len int Array length
* \return int totalSalary (0) If there are no loaded employees or if Error [Invalid length or NULL pointer]
* 		  or the total amount in salary
*
*/
float TotalSalary(sEmployee* list, int len);

/** \brief Calculate the average salary of all registered employees.
*
* \param list sEmployee* Pointer to array of employees
* \param len int Array length
* \return int average (0) If there are no loaded employees or if Error [Invalid length or NULL pointer]
* 		  or the average salary.
*/
float AverageSalary(sEmployee* list, int len);

/** \brief The function counts employees with a salary greater than the average salary.
*
* \param list sEmployee* Pointer to array of employees
* \param len int Array length
* \param averageSalary float the average salary
* \return int counter (0) If there are no loaded employees or if Error [Invalid length or NULL pointer]
* 		  or the number of employees with a salary above the average.
*/
int QuantityEmployeesWithHighSalary(sEmployee* list, int len, float averageSalary);

/** \brief The function displays all available reports in a menu with options.
*
* \param list sEmployee* Pointer to array of employees
* \param len int Array length
* \return void
*/
void Reports(sEmployee* list, int len);

#endif /* INFORMES_H_ */
