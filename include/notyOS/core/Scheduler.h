

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


#ifndef __notCore_scheduler_H__


	#include <notyOS/core/Process.h>
	#include <notyOS/data/Queue.h>

	#define __notCore_scheduler_H__


	/**
	 *	@brief	Definición del Scheduler.
	 *
	 *		Es la estructura del OS que se encarga de manejar los procesos del mismo:
	 *		su ejecución, creación, liberación y manejo en general.
	*/
	typedef struct Scheduler {
		Queue* processes;				///<	Cola con los procesos que administar.

		Process* (*schedulerSearch)(struct Scheduler*);	///<	Función para administar el scheduler. 
	} Scheduler;

	
	/**
	 *	@brief	Inicializa un scheduler (simulado) para el OS.
	 *
	 *	@param	shcedulerUpdate	Puntero al schedulerUpdate.
	*/
	Scheduler* initScheduler(Process* (*schedulerSearch)(Scheduler*));

	/**
	 *	@brief	Desactiva el scheduler del OS simulado.
	 *
	 *	@param	shceduler	Puntero al scheduler a desactivar.
	*/
	void denitScheduler(Scheduler* scheduler);


	/**
	 *	@brief	Almacena un proceso en la cola de ejecución.
	 *
	 *	@param	scheduler	Scheduler del OS.
	 *	@param	process		Proceso a agregar a la cola de ejecucion.
	*/
	inline static void schedulerAddProcess(Scheduler* scheduler, Process* process) {
		queueEnqueue(scheduler->processes, process);
	}

	/**
	 *	@brief	Libera el proceso ya terminado de la cola de ejecución.
	 *
	 *	@param	scheduler	Scheduler del OS.
	 *	@param	process		Proceso a eliminar a la cola de ejecucion.
	*/
	inline static void schedulerRemoveProcess(Scheduler* scheduler, Process* process) {
		queueDequeue(scheduler->processes, process);
	}


	Process* schedulerFIFO(Scheduler* scheduler);

	Process* schedulerRoundRobin(Scheduler* scheduler);

	Process* schedulerShortJobFirst(Scheduler* scheduler);


#endif


