int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);

int controller_MostrarEmpleado(LinkedList* pArrayListEmployee, int index);
int controller_Reubicar(LinkedList* pArrayListEmployee);
void MenuPrincipal(int* opcion);
void MenuEditarEmpleado(int* opcion);
int Edit_Nombre(LinkedList* pArrayListEmployee, int idEdit);
int Edit_Horas(LinkedList* pArrayListEmployee, int idEdit);
int Edit_Sueldo(LinkedList* pArrayListEmployee, int idEdit);
void MenuOrdenamiento(int* opcion);
int OrdenamientoPorNombre(LinkedList* auxList);
int OrdenamientoPorHorasTrabajadas(LinkedList* auxList);
int OrdenamientoPorSueldo(LinkedList* auxList);
int OrdenamientoPorID(LinkedList* auxList);
int EscribirArchivoID();
int LeerArchivoID();


