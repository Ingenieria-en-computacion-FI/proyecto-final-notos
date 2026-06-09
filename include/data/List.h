

/**
 *	"data/List.h"	---->	Encabezado que define:
 *
 *				* List:
 *					length		(número de elementos).
 *					type_size	(tamaño de los datos).
 *					
 *					*cast(*v,*v)	(callback cast).
 *
 *					*start		(enlace al inicio de la lista).
 *					*end		(enlace al final de la lista).
 *
 *				* Funciones para trabajar con listas.
*/


#ifndef __notData_list_H__


	#include <stdbool.h>

	#include "Node.h"
	
	#define __notData_list_H__


	/**
	 *	@brief	Estructura de datos "Lista".
	 *	
	 *		Estructura con un solo nodo auxiliar que sigue el principio LIFO.
	 *		Se aprovecha de los nodos para generar una estructura dinámina donde
	 *		los elementos en ella se "apilan".
	*/
	typedef struct {
		int16_t length;			///<	Cantidad de datos almacenados en la pila.
		uint16_t type_size;		///<	Tamaño (en bytes) del tipo de dato almacenado.
		
		void (*cast)(void*, void*);	///<	Callback a la función cast.	
		
		struct Node* start;		///<	Nodo auxiliar que apunta al inicio de la lista.
		struct Node* end;		///<	Nodo auxiliar que apunta al final de la lista.
	} List;
	

	/*	Funciones para (almacenar / liberar) listas.	*/

		/**
		 *	@brief	Almacena en memoria una lista de elementos de tamaño fijo.
		 *
		 *	@param	size	Tamaño del tipo de dato (fijo) a almacenar.
		 *	@param	cast	Puntero al callback para hacer casting de tipos.
		 *
		 *	@return	Puntero a la lista creada.
		*/
		List* newList(uint16_t size, void (*cast)(void*, void*));

		/**
		 *	@brief	Libera el bloque de memoria reservado por una lista.
		 *
		 *	@param	list	Puntero a la lista a eliminar.
		*/
		void  deleteList(List* list);


	/*	Funciones para (insertar / extraer) elementos de una lista.	*/

		/**
		 *	@brief	Inserta un elemento a la lista en la posición ${index}.
		 *
		 *	@param	list	Puntero a la lista donde se insertará un elemento.
		 *	@param	index	Índice donde insertar el elemento.
		 *	@param	data	Información que se almacenar en la lista.
		*/
		void listAdd(List* list, int16_t index, void* data);
		
		/**
		 *	@brief	Inserta un elemento al inicio de la lista.
		 *
		 *	@param	list	Puntero a la lista donde se insertará un elemento (al inicio).
		 *	@param	data	Información que se almacenar en la lista.
		*/
		inline static void listAddFirst(List* list, void* data) {
			listAdd(list, 0, data);
		}
		
		/**
		 *	@brief	Inserta un elemento al final de la lista.
		 *
		 *	@param	list	Puntero a la lista donde se insertará un elemento (al final).
		 *	@param	data	Información que se almacenar en la lista.
		*/
		inline static void listAddLast(List* list, void* data) {
			listAdd(list, list->length, data);
		}

		/**
		 *	@brief	Elimina y almacena el elemento en la posición ${index} de la lista.
		 *
		 *	@param	lista	Puntero a la lista donde se eliminará un elemento.
		 *	@param	index	Índice donde eliminar el elemento.
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		*/
		void listRemove(List* list, int16_t index, void* dest);
		
		/**
		 *	@brief	Elimina y almacena el elemento al inicio de la lista.
		 *
		 *	@param	list	Puntero a la lista donde se eliminará un elemento (al inicio).
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		*/
		inline static void listRemoveFirst(List* list, void* dest) {
			listRemove(list, 0, dest);
		}
		
		/**
		 *	@brief	Elimina y almacena el elemento al final de la lista.
		 *
		 *	@param	list	Puntero a la lista donde se eliminará un elemento (al final).
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		*/
		inline static void listRemoveLast(List* list, void* dest) {
			listRemove(list, list->length - 1, dest);
		}

		/**
		 *	@brief	Devuelve el valor al inicio de la lista.
		 *
		 *	@param	list	Puntero a la lista a obtener su valor al inicio (start).
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		*/
		void listFirst(List* list, void* dest);
		
		/**
		 *	@brief	Devuelve el valor en la cima de la pila.
		 *
		 *	@param	list	Puntero a la lista a obtener su valor al final (end).
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		*/
		void listLast(List* list, void* dest);


	/*	Funciones "Auxiliares"	*/

		/**
		 *	@brief	Devuelve el tamaño de la lista (número de elementos).
		 *
		 *	@param	list	Puntero a la lista a analizar.
		 *
		 *	@return	Entero de 8 bytes con su valor siendo el número de elementos
		 *		dentro de la lista.
		*/
		inline static int16_t listSize(List* list) {
			return list->length;
		}

		/**
		 *	@brief	Determina si una lista está vacía (que no tiene elementos).
		 *
		 *	@param	list	Puntero a la lista a analizar.
		 *
		 *	@return	"Verdadero" (true) si la lista está vacía (size() == 0).
		*/
		inline static bool listIsEmpty(List* list) {
			return listSize(list) == 0;
		}

		/**
		 *	@brief	Toma una lista cualquiera y elimina todos sus elementos.
		 *
		 *	@param	list	Puntero a la lista a vaciar.
		*/
		inline static void listClear(List *list) {
			void* auxBlock = memblockCreate(list->type_size);

			while(!listIsEmpty(list))
				listRemoveFirst(list, auxBlock);

			memblockDelete(auxBlock);
		}


#endif


