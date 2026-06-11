

/*
 *	"process/Process.h"
 *
 *	Encabezado que define:
 *
 *	* ProcessState.
 *	* ProcessPriority.
 *	* Process.
*/


#ifndef __notCore_process_H__


	#include <stdint.h>

	#define __notCore_process_H__

	#define __notQuantum__	2

	
	///	Enum con los posibles estados de un proceso.
	typedef enum : uint8_t {
		READY,		///<	El proceso está listo para entrar en ejecución.
		RUNNING,	///<	El proceso se está ejecutando.
		BLOCKED,	///<	El proceso se bloqueo.
		FINISHED	///<	El proceso fue ejecutado correctamente.
	} ProcessState;


	///	Enum con las posibles prioridades de un proceso.
	typedef enum : uint8_t {
		EXECUTE_WHEN_POSIBLE,	///<	Prioridad 0:	Ejecutar con prioridad baja.
		NORMAL_PRIORITY,	///<	Prioridad 1:	Ejecutar con prioridad normal.
		HIGH_PRIORITY,		///<	Prioridad 2:	Ejecutar con prioridad alta.
		BEFORE_THE_REST		///<	Prioridad 3:	Ejecutar antes que todo lo demás.
	} ProcessPriority;


	/**
	 *	@brief	Proceso (simulado) del sistema operativo.
	 *	
	 *		Contenedor con los datos necesarios para simular
	 *		los procesos del sistema operativo.
	*/
	typedef struct {
		uint16_t pid;			///<	Identificador del proceso (Process ID).

		uint16_t burst_time;		///<	Tiempo (total) requerido de CPU.
		uint16_t remaining_time;	///<	Tiempo restante para terminar su ejecución.

		uint16_t memory_required;	///<	Memoria necesaria para almacenar el proceso en memoria. 
		
		ProcessPriority priority;	///<	Prioridad del proceso.
		ProcessState state;		///<	Estado actual del proceso.
	} Process;


	/**
	 *	@brief	Almacena en memoria un proceso del simulador.
	 *
	 *	@param	pid		PID del nuevo proceso.
	 *	@param	cpu_time	Tiempo requerido para la ejecución completa del proceso.
	 *	@param	mem_req		Memoria requerida por el proceso.
	 *	@param	priority	Prioridad de ejecución del proceso.
	 *
	 *	@return	Puntero al nuevo proceso.
	*/
	Process* newProcess(uint16_t pid, uint16_t cpu_time, uint16_t mem_req, ProcessPriority priority);

	/**
	 *	@brief	Libera el bloque de memoria reservado por un proceso.
	 *
	 *	@param	process	Puntero al proceso a liberar.
	*/
	void deleteProcess(Process* process);
	
	
	/**
	 *	@brief.	Cambia el estado actual de un proceso.
	 *
	 *	@param	process	Puntero al proceso a editar.
	 *	@param	state	Nuevo estado del proceso.
	*/
	inline static void processSetState(Process* process, ProcessState state) {
		process->state = state;
	}

	/**
	 *	@brief.	Devuelve el estado actual de un proceso.
	 *
	 *	@param	process	Puntero al proceso a revisar.
	 *
	 *	@return	El estado actual del proceso.
	*/
	inline static ProcessState processGetState(Process* process) {
		return process->state;
	}

	/**
	 *	@brief.	Ejecuta un proceso por un tiempo determinado (Quantum = 2).
	 *
	 *	@param	process	Puntero al proceso a ejecutar.
	*/
	inline static void processExecute(Process* process) {
		processSetState(process, RUNNING);
		process->remaining_time -= (process->remaining_time < __notQuantum__)
					? process->remaining_time : __notQuantum__;
	}

	/**
	 *	@brief.	Actualiza el estado de un proceso después de ser enviada a la CPU.
	 *
	 *		Determina si el proceso debe ser bloqueado, o bien,
	 *		ha terminado su ejecución completa ---cambia su estado a
	 *		${FINISHED} o ${BLOCKED}.
	 *
	 *	@param	process	Puntero al proceso a actualizar.
	*/
	inline static void processUpdate(Process* process) {
		processSetState(
			process,
			(process->remaining_time == 0) ? FINISHED : BLOCKED
		);
	}


#endif


