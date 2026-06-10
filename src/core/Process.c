#include <stdlib.h>

#include <notyOS/core/Process.h>


Process* newProcess(uint16_t pid, uint16_t cpu_time, uint16_t mem_req, ProcessPriority priority) {
	Process* new_process = malloc(sizeof(Process));

	*new_process = (Process) {
		pid,
		cpu_time, cpu_time,	//	En un inicio, el tiempo restante es el tiempo total.
		mem_req,
		priority,
		READY
	};

	return new_process;
}

void deleteProcess(Process* process) {
	free(process);
}
	
	
