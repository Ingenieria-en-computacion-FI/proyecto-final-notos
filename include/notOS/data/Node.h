

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


	#define __notData_nodes_H__

	#include <stdbool.h>
	#include <stdint.h>


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


#endif


