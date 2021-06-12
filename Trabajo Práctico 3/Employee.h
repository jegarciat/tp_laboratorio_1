#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete(Employee*);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_CargarDatos(Employee* pEmpleado);
Employee* employee_BuscarPorID(LinkedList* pArrayListEmployee, int idBuscar);

int employee_CompararPorNombre(void* empleado1, void* empleado2);
int employee_CompararPorID(void* empleado1, void* empleado2);
int employee_CompararPorSueldo(void* empleado1, void* empleado2);
int employee_CompararPorHoras(void* empleado1, void* empleado2);



#endif // employee_H_INCLUDED
