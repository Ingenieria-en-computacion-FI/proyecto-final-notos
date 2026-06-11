#include <stdlib.h>
#include <notOS/core/Scheduler.h>

#define PROCESSES	scheduler->processes


void processCast(void* dest, void* src) {
	*(Process*) dest = *(Process*) src;
}


Scheduler* initScheduler(Process* (*schedulerSearch)(Scheduler*)) {
	Scheduler* new_sche = malloc(sizeof(Scheduler));

	*new_sche = (Scheduler) {
		newQueue(sizeof(Process), processCast),
		schedulerSearch
	};

	return  new_sche;
}


void denitScheduler(Scheduler* scheduler) {
	deleteQueue(PROCESSES);
	free(scheduler);
}


Process* schedulerFIFO(Scheduler* scheduler) {
	//	El scheduler FIFO elimina normal los procesos.
	Process* process = NULL;
	
	if(!queueIsEmpty(PROCESSES))	process = PROCESSES->front->next->data;

	return process;
}

Process* schedulerRoundRobin(Scheduler* scheduler) {
	Process* process = NULL;

	if(!queueIsEmpty(PROCESSES))	{
		Node* aux = PROCESSES->front->next;
		process = aux->data;

		//	Round Robin mueve todo (el circulo) una posición.
		PROCESSES->front->next = aux->next;
		PROCESSES->rear->next = aux;
	}

	return process;
}

Process* schedulerShortJobFirst(Scheduler* scheduler) {
	Process* shortest = NULL;

	Node* n = PROCESSES->front->next;
	for(uint16_t i = 0; i < queueSize(PROCESSES); i++) {
		Process* process = (Process*) n->data;

		if(!shortest || shortest->remaining_time > process->remaining_time)
			shortest = process;

		n = n->next;
	}

	return shortest;
}


