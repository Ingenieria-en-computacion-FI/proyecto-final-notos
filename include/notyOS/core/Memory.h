

/*
 *	"core/Memory.h"	---->	Encabezado que define:
 *
 *				* Memoryblock:
 *					start	Inicio del bloque.
 *					size	Tamaño del bloque (end = start + size - 1).
 *
 *					free	Determina si el bloque está libre.
 *					pid	PID del proceso que ocupa dicho bloque.
 *
 *				* Memory:
 *					*blocks	Lista con los bloques de memoria en la ram.
 *					size	Tamaño de la RAM.
 *
 *				* Funciones para trabajar con la memoria simulada.
*/


#ifndef __notCore_memoryblock_H__


	#include <notyOS/data/List.h>

	#define __notCore_memoryblock_H__


	/**
	 *	@brief	Definición de un bloque de memoria (MemoryBlock).
	 *
	 *		Contiene todos los campos necesarios para
	 *		emular un bloque de memoria.
	*/
	typedef struct {
		uint16_t start;		///<	Índice, en memoria, donde inicia el bloque.

		uint16_t used_mem;	///<	Indica la cantidad de memoria del bloque que está utilizada.
		uint16_t size;		///<	Tamaño del bloque de memoria.		

		uint16_t pid;		///<	PID del proceso que lo ocupa.
	} MemoryBlock;

	
	/**
	 *	@brief	RAM simulada.
	 *
	 *		Simula la memoria RAM de un sistema operativo,
	 *		es limitada y está dividida en bloques.
	*/
	typedef struct Memory {
		List* blocks;		///<	Cola circular que representa los bloques en la RAM del OS.

		///	Algoritmo para encontrar bloques libres.
		MemoryBlock* (*fitAlgorithm)(struct Memory*, uint16_t);

		uint16_t free_memory;	///<	Memoria (aún) disponible en toda la unidad.
		uint16_t size;		///<	Tamaño total (en MB) de la RAM simulada.
	} Memory;


	/**
	 *	@brief	Inicializa la lista para los futuros bloques de memoria (RAM del OS).
	 *
	 *	@param	ram	Memoria simulada a inicializar.
	 *	@param	size	Tamaño maximo (en MB) de la unidad simulada.
	*/
	Memory* initRAM(uint16_t size, MemoryBlock* (*fitAlgorithm)(Memory*, uint16_t));

	/**
	 *	@brief	Desactiva una unidad de RAM simulada.
	 *
	 *	@param	ram	Memoria simulada a desactivar.
	*/
	void denitRAM(Memory* ram);
	

	/**
	 *	@brief	Almacena un bloque de memoria en la RAM simulada.
	 *
	 *	@param	ram	Unidad en donde se alojará el nuevo bloque.
	 *	@param	pid	PID del proceso aisgnado al bloque.
	 *	@param	size	Tamaño (en MB) del bloque a asignar.
	 *
	 *	@return	Verdadero (true) si se generó el bloque de memoria.
	*/
	bool allocateMemory(Memory* ram, uint16_t pid, uint16_t size);

	/**
	 *	@brief	Libera un bloque de memoria de la unidad simulada.
	 *
	 *	@param	ram	Puntero al bloque de memoria a liberar.
	 *	@param	pid	PID para identificar el bloque a eliminar.
	*/
	void freeMemory(Memory* ram, uint16_t pid);


	void memoryAddBlock(Memory* ram, uint16_t size);

	void memoryCoalesce(Memory* ram);


	MemoryBlock* memoryFirstFit(Memory* ram, uint16_t size);

	MemoryBlock* memoryBestFit(Memory* ram, uint16_t size);

	MemoryBlock* memoryWorstFit(Memory* ram, uint16_t size);


	inline static bool memoryBlockIsFree(MemoryBlock* block) {
		return block->used_mem == 0;
	}

	inline static uint16_t getBlocksUse(Memory* ram) {
		MemoryBlock block = (MemoryBlock) {0, 0, 0, 0};
		listLast(ram->blocks, &block);

		return (block.start + block.size);
	}

	inline static uint16_t getFreeMemory(Memory* ram) {
		return ram->free_memory;
	}

	inline static uint16_t getUsedMemory(Memory* ram) {
		return ram->size - getFreeMemory(ram);
	}


	inline static bool memoryIsFragmented(Memory* ram) {
		return getBlocksUse(ram) != getUsedMemory(ram);
	}


#endif


