

/*
 *	"data/Stack.h"	---->	Encabezado que define:
 *
 *				* Stack:
 *					length		(número de elementos).
 *					type_size	(tamaño de los datos).
 *					
 *					*cast(*v,*v)	(callback cast).
 *
 *					*peak		(enlace a la cima de la pila).
 *
 *				* Funciones para trabajar con Pilas.
*/


#ifndef __notData_stack_H__


	#include <stdbool.h>

	#include "Node.h"
	
	#define __notData_stack_H__


	/**
	 *	@brief	Estructura de datos "Pila".
	 *	
	 *		Estructura con un solo nodo auxiliar que sigue el principio LIFO.
	 *		Se aprovecha de los nodos para generar una estructura dinámina donde
	 *		los elementos en ella se "apilan".
	*/
	typedef struct {
		int16_t length;			///<	Cantidad de datos almacenados en la pila.
		uint16_t type_size;		///<	Tamaño (en bytes) del tipo de dato almacenado.
		
		void (*cast)(void*, void*);	///<	Callback a la función cast.	
		
		struct Node* top;		///<	Nodo auxiliar que apunta a la cima de la pila.
	} Stack;
	

	/*	Funciones para (almacenar / liberar) pilas.	*/

		/**
		 *	@brief	Almacena en memoria una pila de elementos de tamaño fijo.
		 *
		 *	@param	size	Tamaño del tipo de dato (fijo) a almacenar.
		 *	@param	cast	Puntero al callback para hacer casting de tipos.
		 *
		 *	@return	Puntero a la pila creada.
		*/
		Stack* newStack(uint16_t size, void (*cast)(void*, void*));

		/**
		 *	@brief	Libera el bloque de memoria reservado por una pila.
		 *
		 *	@param	stack	Puntero a la pila a eliminar.
		*/
		void  deleteStack(Stack* stack);


	/*	Funciones para (insertar / extraer) elementos de una pila.	*/

		/**
		 *	@brief	Inserta un elemento en la cima de la pila.
		 *
		 *	@param	stack	Puntero a la pila donde se insertará un elemento.
		 *	@param	data	Información que se almacenar en la pila.
		*/
		void stackPush(Stack* stack, void* data);

		/**
		 *	@brief	Elimina y devuelve el elemento en la cima de la pila.
		 *
		 *	@param	stack	Puntero a la pila donde se eliminará un elemento.
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		*/
		void stackPop(Stack* stack, void* dest);

		/**
		 *	@brief	Devuelve el valor en la cima de la pila.
		 *
		 *	@param	stack	Puntero a la pila a obtener su elemento en la cima (top).
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		*/
		void stackTop(Stack* stack, void* dest);


	/*	Funciones "Auxiliares"	*/

		/**
		 *	@brief	Devuelve el tamaño de la pila (número de elementos).
		 *
		 *	@param	stack	Puntero a la pila a analizar.
		 *
		 *	@return	Entero de 8 bytes con su valor siendo el número de elementos
		 *		dentro de la pila.
		*/
		inline static int32_t stackSize(Stack* stack) {
			return stack->length;
		}

		/**
		 *	@brief	Determina si una pila está vacía (que no tiene elementos).
		 *
		 *	@param	stack	Puntero a la pila a analizar.
		 *
		 *	@return	"Verdadero" (true) si la pila está vacía (size() == 0).
		*/
		inline static bool stackIsEmpty(Stack* stack) {
			return stackSize(stack) == 0;
		}

		/**
		 *	@brief	Toma una pila cualquiera y elimina todos sus elementos.
		 *
		 *	@param	stack	Puntero a la pila a vaciar.
		*/
		void stackClear(Stack *stack);


#endif


