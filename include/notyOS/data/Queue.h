

/*
 *	"data/Queue.h"	---->	Encabezado que define:
 *
 *				* Queue:
 *					length		(número de elementos).
 *					type_size	(tamaño de los datos).
 *
 *					*cast(*v,*v)	(callback cast).
 *
 *					*front		(enlace al frente de la cola).
 *					*rear		(enlace al final de la cola).
 *
 *				* Funciones para trabajar con Colas.
*/


#ifndef __notData_queue_H__


	#include <stdbool.h>

	#include "Node.h"
	
	#define __notData_queue_H__


	/**
	 *	@brief	Estructura de datos "Cola".
	 *	
	 *		Estructura con dos nodos auxiliares (frente y final) que sigue el principio FIFO.
	 *		Se aprovecha de los nodos para generar una estructura dinámina donde
	 *		los elementos en ella se "forman", como en una fila. El primero en formarse
	 *		es el primero en salir de la cola.
	*/
	typedef struct {
		int16_t length;			///<	Cantidad de datos almacenados en la pila.
		uint16_t type_size;		///<	Tamaño (en bytes) del tipo de dato almacenado.
		
		void (*cast)(void*, void*);	///<	Callback a la función cast.	
		
		struct Node* front;		///<	Nodo auxiliar que apunta al frente de la cola.
		struct Node* rear;		///<	Nodo auxiliar que apunta al final de la cola.
	} Queue;
	

	/*	Funciones para (almacenar / liberar) colas.	*/

		/**
		 *	@brief	Almacena en memoria una cola de elementos de tamaño fijo.
		 *
		 *	@param	size	Tamaño del tipo de dato (fijo) a almacenar.
		 *	@param	cast	Puntero al callback para hacer casting de tipos.
		 *
		 *	@return	Puntero a la cola creada.
		*/
		Queue* newQueue(uint16_t size, void (*cast)(void*, void*));

		/**
		 *	@brief	Libera el bloque de memoria reservado por una cola.
		 *
		 *	@param	queue	Puntero a la cola a eliminar.
		*/
		void  deleteQueue(Queue* queue);


	/*	Funciones para (insertar / extraer) elementos de una cola.	*/

		/**
		 *	@brief	Inserta un elemento al final de la cola.
		 *
		 *	@param	queue	Puntero a la cola donde se insertará un elemento.
		 *	@param	data	Información que se almacenar en la cola.
		*/
		void queueEnqueue(Queue* queue, void* data);

		/**
		 *	@brief	Elimina y devuelve el elemento al frente de la cola.
		 *
		 *	@param	queue	Puntero a la cola donde se eliminará un elemento.
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		 *
		 *	@return	Puntero a la información almacenada.
		*/
		void queueDequeue(Queue* queue, void* dest);

		/**
		 *	@brief	Devuelve el valor al frente de la cola.
		 *
		 *	@param	queue	Puntero a la cola a obtener su elemento al frente (front).
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		 *
		 *	@return	Puntero a la información almacenada.
		*/
		void queueFront(Queue* queue, void* dest);
		
		/**
		 *	@brief	Devuelve el valor al final de la cola.
		 *
		 *	@param	queue	Puntero a la cola a obtener su elemento al final (rear).
		 *	@param	dest	Puntero a la variable destino (donde almacenar la información extraída).
		 *
		 *	@return	Puntero a la información almacenada.
		*/
		void queueRear(Queue* queue, void* dest);


	/*	Funciones "Auxiliares"	*/

		/**
		 *	@brief	Devuelve el tamaño de la cola (número de elementos).
		 *
		 *	@param	queue	Puntero a la cola a analizar.
		 *
		 *	@return	Entero de 8 bytes con su valor siendo el número de elementos
		 *		dentro de la cola.
		*/
		inline static int16_t queueSize(Queue* queue) {
			return queue->length;
		}

		/**
		 *	@brief	Determina si una cola está vacía (que no tiene elementos).
		 *
		 *	@param	queue	Puntero a la cola a analizar.
		 *
		 *	@return	"Verdadero" (true) si la cola está vacía (size() == 0).
		*/
		inline static bool queueIsEmpty(Queue* queue) {
			return queueSize(queue) == 0;
		}

		/**
		 *	@brief	Toma una cola cualquiera y elimina todos sus elementos.
		 *
		 *	@param	queue	Puntero a la cola a vaciar.
		*/
		void queueClear(Queue *queue);


#endif


