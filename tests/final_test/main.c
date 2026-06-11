#include <notOS/notOS.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print(const char* s) {
	printf("%s", s); 
	fflush(stdout);
}


//	Algoritmos de manejo de memoria.
MemoryBlock* (*fit_algorithms[])(Memory*, uint16_t) = {
	memoryFirstFit,
	memoryBestFit,
	memoryWorstFit
};

//	Tipo de scheduler.
Process* (*scheduler_type[])(Scheduler*) = {
	schedulerFIFO,
	schedulerRoundRobin,
	schedulerShortJobFirst
};

//	Definida en Scheduler.c
void processCast(void* dest, void* src);

const char* delim = ",";


int main(int argc, char **argv) {
	int n_args = argc - 1;

	//	Obtener el tipo de scheduler y fit.
	int sche_t = (int) strtol(*(argv + 1), NULL, 10);
	int fit_t = (int) strtol(*(argv + 2), NULL, 10);

	//	Iniciar OS
	Scheduler* scheduler = initScheduler(scheduler_type[sche_t]);
	Memory* ram = initRAM(3000, fit_algorithms[fit_t]);
	
	puts("Iniciando <notOS>... Hola...");

	List* processes = newList(sizeof(Process), processCast);

	puts("\nLista de procesos a ejecutar:");
	for(int i = 0; i < n_args - 2; i++) {
		uint16_t pid = (uint16_t) strtol(strtok(*(argv + 3 + i), delim), NULL, 10);

		uint16_t cpu_t = (uint16_t) strtol(strtok(NULL, delim), NULL, 10);	
		uint16_t mem_r = (uint16_t) strtol(strtok(NULL, delim), NULL, 10);

		uint8_t prior = (uint8_t) strtol(strtok(NULL, delim), NULL, 10);	
	
		Process* p = newProcess(pid, cpu_t, mem_r, (ProcessPriority) prior);

		printf("\tP{%u}: %u[t_u], %u[mb]\n", p->pid, p->burst_time, p->memory_required);

		listAddLast(processes, p);
		deleteProcess(p);
	}

	puts("\nIniciando bucle...\n");
	//	Bucle del OS.
	while(!listIsEmpty(processes) || !queueIsEmpty(scheduler->processes)) {
		//	Intentar cargar los procesos en memoria.
		while(!listIsEmpty(processes)) {
			Process p;
			listFirst(processes, &p);

			//	Si falla alocar en memoria.
			if(!allocateMemory(ram, p.pid, p.memory_required)) {
				//if(memoryIsFragmented(ram))	memoryCoalesce(ram);
				//else
				memoryAddBlock(ram, p.memory_required);

				//	Si vuelve a fallar, la memoria total no es suficiente
				if(!allocateMemory(ram, p.pid, p.memory_required))	break;
			}
			listRemoveFirst(processes, &p);
			schedulerAddProcess(scheduler, &p);
			
			printf("Se agrego P{%u} al scheduler.\n", p.pid);
		}
	
		//	No hay ningun proceso
		if(queueIsEmpty(scheduler->processes))	break;

		//	Ejecutar proceso
		Process* exe = scheduler->schedulerSearch(scheduler);

		processExecute(exe);

		printf("Ejecutando P{%u}, tiempo restante: %u\n", exe->pid, exe->remaining_time);

		processUpdate(exe);

		if(processGetState(exe) == FINISHED) {
			printf("P{%u} terminado, borrando...\n", exe->pid);

			freeMemory(ram, exe->pid);
			schedulerRemoveProcess(scheduler, exe);
		}
	}
	puts("\nApagando <notOS>... Adios...");

	//	Apagar OS
	denitRAM(ram);
	denitScheduler(scheduler);

	deleteList(processes);

	return 0;
}
