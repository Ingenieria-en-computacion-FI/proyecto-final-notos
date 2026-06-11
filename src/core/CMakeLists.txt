#
#	   ________  ___      __           ______            _____           __                           _ 
#	  / ____/  |/  /___ _/ /_____     / ____/___  ____  / __(_)___ _   _/_/  _________  ________     | |
#	 / /   / /|_/ / __ `/ /assign/_/ _ \   / /   / __ \/ __ \/ /_/ / __ `/  / /   / ___/ __ \/ ___/ _ \    / /
#	/ /___/ /  / / /_/ / ,< /  __/  / /___/ /_/ / / / / __/ / /_/ /  / /   / /__/ /_/ / /  /  __/   / / 
#	\____/_/  /_/\__,_/_/|_|\___/   \____/\____/_/ /_/_/ /_/\__, /  / /    \___/\____/_/   \___/  _/_/  
#	                                                       /____/   |_|                          /_/    
#
#	Configuración (CMake) para la compilación del código
#	relativo a las estructuras del sistema operativo:
#	* Procesos.
#	* Manejo de memoria.
#	* Scheduler.
#


message('\nGenerando: \"Estructuras del OS\":')


#	Procesos (process)
add_library(process STATIC Process.c)
set_libConfig(process)

#	Memoria (memory)
add_library(memory STATIC Memory.c)
set_libConfig(memory list)

#	Scheduler (scheduler)
add_library(scheduler STATIC Scheduler.c)
set_libConfig(scheduler process queue stack)


