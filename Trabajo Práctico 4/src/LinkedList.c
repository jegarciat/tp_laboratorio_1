#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = NULL;
    this = (LinkedList*)malloc(sizeof(LinkedList));

    if(this != NULL)
    {
    	this->size = 0;
    	this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	returnAux = this->size;
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int len = ll_len(this);
	Node* pNode = NULL;

	if(this != NULL && nodeIndex >= 0 && nodeIndex < len)
	{
		pNode = this->pFirstNode;

        for(int i = 0; i < nodeIndex; i++) //Recorro hasta el nodo deseado.
        {
            pNode = pNode->pNextNode;
        }
	}

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	int len = ll_len(this);
	Node* anteriorNode;
	Node* nuevoNode = NULL;
    int returnAux = -1;

	if(this != NULL && nodeIndex >= 0 && nodeIndex <= len)
	{
		nuevoNode = (Node*)malloc(sizeof(Node));

		if(nuevoNode != NULL)
		{
			nuevoNode->pElement = pElement;

			if(nodeIndex == 0)
			{
				nuevoNode->pNextNode = this->pFirstNode; //Apunto el nuevoNode a lo que apuntaba el pFirstNode (NULL u otro nodo)
				this->pFirstNode = nuevoNode; //El nuevo first node sera el que cree
			}
			else
			{
				anteriorNode = getNode(this, nodeIndex-1);
				nuevoNode->pNextNode = anteriorNode->pNextNode; //Apunto el nuevoNode a lo que apuntaba anteriorNode
				anteriorNode->pNextNode = nuevoNode; //El anteriorNode lo apunto al que cree
			}

			this->size++;
			returnAux = 0;
		}
	}

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this != NULL)
    {
    	addNode(this, len, pElement);
    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNodeAux = NULL;
    int len = ll_len(this);

    if(this != NULL && index >= 0 && index <= len)
    {
    	pNodeAux = getNode(this, index); //Obtengo el nodo en el index especificado

    	if(pNodeAux != NULL)
    	{
			returnAux = pNodeAux->pElement; //Retorno el elemento apuntado por el nodo
    	}
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
	int returnAux = -1;
	Node* pNodeAux = NULL;
	int len = ll_len(this);

	if(this != NULL && index >= 0 && index <= len)
	{
		pNodeAux = getNode(this, index);
		if(pNodeAux != NULL)
		{
			pNodeAux->pElement = pElement;
			returnAux = 0;
		}
	}

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	int returnAux = -1;
	int len = ll_len(this);
	Node* anteriorNode;
	Node* pNodeAux;

	if(this != NULL && index >= 0 && index <= len)
	{
		pNodeAux = getNode(this, index);
		if(pNodeAux != NULL)
		{
			if(index == 0) //Si es el primer nodo
			{
				this->pFirstNode = pNodeAux->pNextNode; //El primer nodo de lista pasa a ser el siguiente al que se va a remover
				free(pNodeAux);
			}
			else
			{
				anteriorNode = getNode(this, index-1);
				if(anteriorNode != NULL)
				{
					anteriorNode->pNextNode = pNodeAux->pNextNode; //Apunto el anteriorNode a lo que apuntaba el nodo a remover (NULL u otro nodo)
					free(pNodeAux);
				}
			}

			this->size--;
			returnAux = 0;
		}
	}

    return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
	int returnAux = -1;
	int len = ll_len(this);

	if(this != NULL)
	{
		for(int i = 0; i < len; i++)
		{
			ll_remove(this, 0);
		}

		returnAux = 0;

		/*if(ll_len(this) == 0) //Comprueba si se limpio toda la lista
		{
			returnAux = 0;
		}*/
	}

    return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
	int returnAux = -1;

	if(this != NULL && ll_clear(this) == 0)
	{
		free(this);
		returnAux = 0;
	}

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
	int len = ll_len(this);
	Node* pNode = NULL;

	if(this != NULL)
	{
		for(int i = 0; i < len; i++)
		{
			pNode = getNode(this, i); //Obtengo nodo por nodo hasta que encuentre un nodo que apunte a pElement

			if(pNode != NULL && pNode->pElement == pElement)
			{
				returnAux = i;
				break;
			}
		}
	}

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
	int len = ll_len(this);

	if(this != NULL)
	{
		returnAux = 1; //Si esta vacia

		if(len > 0)
		{
			returnAux = 0; //Si no esta vacia
		}
	}
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
	int returnAux = -1;
	int len = ll_len(this);

	if(this != NULL && index >= 0 && index <= len)
	{
		addNode(this, index, pElement);
		returnAux = 0;
	}

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* pElement;
	int len = ll_len(this);

	if(this != NULL && index >= 0 && index <= len)
	{
		pElement = ll_get(this, index); //Obtengo el elemento apuntado por index
		if(pElement != NULL && ll_remove(this, index) == 0) //Libero el nodo y retorno el elemento que apunta
		{
			returnAux = pElement;
		}
	}

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
	int returnAux = -1;

	if(this != NULL)
	{
		returnAux = 0; //Si no esta en la lista

		if(ll_indexOf(this, pElement) != -1) //Si indexOf me devolvio un indice
		{
			returnAux = 1; //Si esta en lista
		}
	}

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int len2 = ll_len(this2);
    void* auxElement;

	if(this != NULL && this2 != NULL)
	{
		returnAux = 1; //Arranco suponiendo que this2 está contenida en this

		for(int i = 0; i < len2; i++)
		{
			auxElement = ll_get(this2, i);

			if(auxElement != NULL && ll_contains(this, auxElement) == 0) //Busco si hay un elemento que NO este en this con ll_contains (devuelve 0 si no está)
			{
				returnAux = 0;
				break;
			}
		}
	}

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneList = NULL;
    int len = ll_len(this);
    void* auxElement;

    if(this != NULL && from >= 0 && from < to && to > from && to <= len)
    {
    	cloneList = ll_newLinkedList();

    	if(cloneList != NULL)
    	{
    		for(int i = from; i < to; i++)
    		{
    			auxElement = ll_get(this, i);
    			ll_add(cloneList, auxElement); //Agrego los elementos que entran en el rango pasado como parámetro
    		}
    	}
    }

    return cloneList;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneList;
    int len = ll_len(this);

    if(this != NULL)
    {
		cloneList = ll_subList(this, 0, len);
    }

    return cloneList;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int len = ll_len(this);
    void* buffer;
    void* pElement1;
    void* pElement2;

    if(this != NULL && pFunc != NULL && (order == 1 || order == 0))
    {
    	for(int i = 0; i < len-1; i++)
    	{
    		for(int j = i+1; j < len; j++)
    		{
    			pElement1 = ll_get(this, i);
    			pElement2 = ll_get(this, j);

    			if((pFunc(pElement1, pElement2) == 1 && order == 1) || (pFunc(pElement1, pElement2) == -1 && order == 0))
    			{
    				buffer = pElement1;
    				ll_set(this, i, pElement2);
    				ll_set(this, j, buffer);
    			}
    		}
    	}

    	returnAux = 0;
    }

    return returnAux;
}

