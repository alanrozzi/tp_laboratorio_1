#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

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
	/* Creo una lista dinamica y la retorna */
	LinkedList* this = (LinkedList*)malloc(sizeof(LinkedList));
	/*Inicializo para no tener basura*/
	if(this!=NULL)
	{
		this->pFirstNode=NULL;
		this->size=0;
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
	int retorno=-1;
	if(this!=NULL)
	{
		//retorna el campo de la lista.
		retorno = this->size;
	}
	return retorno;
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
	/*Genero un nodo auxiliar*/
	Node* pNode=NULL;
	if(this!=NULL && nodeIndex>=0 && nodeIndex<(ll_len(this)))
	{
		//Como busco los indices sin referencia de alguno?
		//Seteo como default el primero de la lista, asi la recorro pasando uno por uno hasta llegar al que necesito.
		pNode=this->pFirstNode;
		for(int i=0;i<nodeIndex;i++)
		{
			//Una vez que saltee toda la lista hasta parar antes del que necesito, obtengo el nodo que busco.
			pNode=pNode->pNextNode;
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
    int retorno = -1;
    Node* newNode;
    Node* prevNode;
    if(this!= NULL && nodeIndex>=0 && nodeIndex<=ll_len(this)) //pElement can be NULL
    {
    	//creo el nodo
    	newNode=(Node*)malloc(sizeof(Node));
    	if(newNode!=NULL)
    	{
    		//INICIO
    		if(nodeIndex==0)
    		{
    			newNode->pNextNode=this->pFirstNode;
    			this->pFirstNode=newNode;
    		}
    		else
    		{
    			//MEDIO y FINAL usan la misma logica
    			//obtengo el previo
    			prevNode=getNode(this, nodeIndex-1);
    			if(prevNode!=NULL)
    			{
    				newNode->pNextNode=prevNode->pNextNode;
    				prevNode->pNextNode=newNode;
    			}
    			else
    			{
    				free(prevNode);
    			}
    		}
    		//agrego los datos restantes
    		newNode->pElement=pElement;
    		this->size++;
    		retorno=0;
    	}
    }
    return retorno;
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
	int retorno = -1;
	if(this!=NULL)
	{
		//aniado al final de la lista con len
		if(addNode(this, ll_len(this), pElement)==0)
		{
			retorno=0;
		}
	}
	return retorno;
}

/** \brief Retorna un puntero al elemento que se encuentra en el índice especificado.
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
	void* pElement=NULL;
	Node* auxNode;
	if(this!=NULL && index>=0 && index<ll_len(this) && ll_len(this)>0)
	{
		//Obtengo el Nodo
		auxNode = getNode(this, index);
		if(auxNode!=NULL)
		{
			//Retorno el elemento del nodo que necesito
			pElement=auxNode->pElement;
		}
	}
	return pElement;
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
    int retorno = -1;
    Node* auxNode;
    if(this!=NULL && index>=0 && index<ll_len(this) && ll_len(this)>0)
	{
		//Obtengo el Nodo que quiero modificar el elemento
		auxNode = getNode(this, index);
		if(auxNode!=NULL)
		{
			//Seteo el elemento del nodo que necesito
			auxNode->pElement=pElement;
			retorno=0;
		}
	}
    return retorno;
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
    int retorno = -1;
    Node* auxNode;
    Node* prevNode;
    if(this!=NULL && index>=0 && index<ll_len(this) && ll_len(this)>0)
	{
    	auxNode = getNode(this, index);
    	if(auxNode!=NULL)
    	{
    		if(index==0) //primero
			{
				this->pFirstNode=auxNode->pNextNode;
				free(auxNode);
				retorno=0;
			}
			else //otro
			{
				prevNode=getNode(this, index-1);
				if(prevNode!=NULL)
				{
					prevNode->pNextNode=auxNode->pNextNode;
					free(auxNode);
					retorno=0;
				}
			}
    		this->size--;
    	}
	}
    return retorno;
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
    int retorno = -1;
    if(this!=NULL)
	{
    	while(ll_len(this)!=0)
    	{
    		//al remover el primero, el segundo para al lugar del primero sucesivamente
    		ll_remove(this, 0);
    	}
    	retorno=0;
	}
    return retorno;
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
    int retorno = -1;
    if(this!=NULL) //se puede no validar, esta en ll_clear
	{
    	//Si pudo limpiar la lista, procede a eliminarla
    	if(ll_clear(this)==0)
    	{
    		free(this);
    		retorno=0;
    	}
	}
    return retorno;
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
    int retorno = -1;
    if(this!=NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			if(ll_get(this, i)==pElement)//paso al siguiente si no encuentra
			{
				retorno = i;
				//encuentro, rompo, devuelvo indice
				break;
			}
		}
	}
    return retorno;
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
    int retorno = -1;
    if(this!=NULL)
	{
    	retorno=0;
		if(ll_len(this)==0)
		{
			retorno=1;
		}
	}
    return retorno;
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
    int retorno = -1;
    if(this!=NULL && index>=0 && index<=ll_len(this))
    {
    	if(addNode(this, index, pElement)==0)
		{
			retorno=0;
		}
    }
    return retorno;
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
    void* pElement = NULL;
    if(this!=NULL && index>=0 && index<ll_len(this))
	{
    	//Retorno el elemento del nodo que elimine
    	pElement=ll_get(this, index);
		if(ll_remove(this, index)!=0)
		{
			pElement=NULL;// si no puede eliminar, retorna NULL
		}
	}
	return pElement;
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
    int retorno = -1;
    if(this!=NULL)
    {
    	retorno=0;
    	if(ll_indexOf(this, pElement)>=0)//si existe devuelve su indice, entonces existe en la lista
		{
			retorno=1;
		}
    }
    return retorno;
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
    int retorno = -1;
    void* pElement;
    if(this!=NULL && this2!=NULL)
    {
    	retorno=1; //empezamos con que los contiene
    	for(int i=0; i<ll_len(this2); i++) //recorro solo la segunda lista
		{
    		pElement=ll_get(this2, i);//agarro elemento de la segunda
    		if(ll_contains(this, pElement)==0)//verifico si dicho elemento NO esta en la primera
    		{
    			retorno=0; //da error y termina de iterar
    			break;
    		}
		}
    }
    return retorno;
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
    LinkedList* cloneArray = NULL;
    if(this!=NULL && from>=0 && from<to && to<=ll_len(this)) 	//verifico, from<ll_len(this)
    {
    	cloneArray=ll_newLinkedList(); //inicializo sublista
    	if(cloneArray!=NULL)
    	{
    		for(int i=from; i<to; i++) //recorro los elementos a copiar
			{
				if(ll_add(cloneArray, ll_get(this, i))!=0) //si da error al aniadir
				{
					ll_deleteLinkedList(cloneArray); //elimino la lista
					//cloneArray=NULL;
					break;
				}
			}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this!=NULL)
    {
    	cloneArray=ll_subList(this, 0, ll_len(this)); //desde 0 hasta el final de la lista original, copia TOD0
    }
    return cloneArray;
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
	int retorno = -1;
	int i, j;
	void* pElementPrev;
	void* pElementNext;
	if(this!=NULL && pFunc!=NULL && (order==0 || order==1))
	{
		for(i=0; i<ll_len(this)-1; i++)
		{
			for (j=i+1; j<ll_len(this); j++)
			{
				pElementPrev=ll_get(this, i);
				pElementNext=ll_get(this, j);
				if(pFunc(pElementPrev,pElementNext)>0 && order==1)
				{
					ll_set(this, i, pElementNext);
					ll_set(this, j, pElementPrev);
				}
				else
				{
					if(pFunc(pElementPrev,pElementNext)<0 && order==0)
					{
						ll_set(this, i, pElementNext);
						ll_set(this, j, pElementPrev);
					}
				}
			}
		}
		retorno=0;
	}
	return retorno;
}

