

/*
 *	"data/Node.h"	---->	Encabezado que define:
 *
 *				* Node:
 *					data	(información).
 *
 *					*last	(enlace a un nodo anterior).
 *					*next	(enlace a un nodo siguiente).
 *
 *				* Funciones para trabajar con nodos.
*/


#ifndef __notData_nodes_H__


	#include <stdint.h>

	#define __notData_nodes_H__


	/**
	 *	@brief	Estructura de datos "Nodo".
	 *	
	 *		Contenedor con información de un tipo específico
	 *		(de un tamaño específico) con enlaces (punteros) a otros
	 *		nodos conocidos. En nuestro caso, nodos de doble enlace.
	*
	 *	@note	Dentro de las distintas implementaciones se tratará a los nodos
	 *		como simples o dobles según le convenga al código.
	*/
	typedef struct Node {
		void* data;		///<	Información almacenada.
		
		struct Node* prev;	///<	Enlace a un nodo anterior.
		struct Node* next;	///<	Enlace a un nodo siguiente.
	} Node;
	

	/*	Funciones para (almacenar / liberar) nodos.	*/

		/**
		 *	@brief	Almacena en memoria un nodo de doble enlace.
		 *
		 *	@param	src	Puntero a la información a encapsular.
		 *	@param	size	Tamaño del bloque de memoria a almacenar.
		 *
		 *	@return	Puntero al nodo creado.
		*/
		Node* newNode(void* src, uint16_t size);

		/**
		 *	@brief	Almacena en memoria un nodo auxiliar.
		 *
		 *	@note	Con "nodo auxiliar" me refiero a un nodo que no reserva memoria
		 *		para el bloque ${data}. Esto es util para mi implementación de los
		 *		nodos ${head} y ${tail}.
		 *
		 *	@return	Puntero al nodo (auxiliar) creado.
		*/
		Node* auxNode();
	
		/**
		 *	@brief	Libera el bloque de memoria reservado por un nodo.
		 *
		 *	@param	node	Puntero al nodo a eliminar.
		*/
		void deleteNode(Node* node);


	/*	Funciones auxiliares para (generar / liberar) los bloques de memoria.	*/

		/**
		 *	@brief	Almacena en memoria un bloque de tamaño definido.
		 *
		 *	@param	memblock_size	Tamaño del bloque de memoria a almacenar.
		 *
		 *	@return	Puntero al bloque de memoria creado.
		*/
		void* memblockCreate(uint16_t memblock_size);

		/**
		 *	@brief	Libera el bloque de memoria reservado.
		 *
		 *	@param	memblock_addr	Puntero al bloque de memoria a liberar.
		*/
		void memblockDelete(void* memblock_addr);


#endif


