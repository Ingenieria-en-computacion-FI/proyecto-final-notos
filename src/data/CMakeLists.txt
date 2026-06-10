#
#	   ________  ___      __           ______            _____           __       __      __           _ 
#	  / ____/  |/  /___ _/ /_____     / ____/___  ____  / __(_)___ _   _/_/  ____/ /___ _/ /_____ _   | |
#	 / /   / /|_/ / __ `/ //_/ _ \   / /   / __ \/ __ \/ /_/ / __ `/  / /   / __  / __ `/ __/ __ `/   / /
#	/ /___/ /  / / /_/ / ,< /  __/  / /___/ /_/ / / / / __/ / /_/ /  / /   / /_/ / /_/ / /_/ /_/ /   / / 
#	\____/_/  /_/\__,_/_/|_|\___/   \____/\____/_/ /_/_/ /_/\__, /  / /    \__,_/\__,_/\__/\__,_/  _/_/  
#	                                                       /____/   |_|                           /_/    
#
#	Configuración (CMake) para la compilación del código
#	relativo a las estructuras de datos:
#	* Pila (Circular y de enlace simple).
#	* Cola (Circular y de enlace simple).
#	* Lista ligada (de enlace simple).
#	* Lista ligada (de enlace doble).
#


message('\nGenerando: \"Estructuras de datos\":')


#	Nodos (Nodes)
add_library(node STATIC Node.c)
set_libConfig(node)


#	Pila (Stack).
add_library(stack STATIC Stack.c)
set_libConfig(stack node)


#	Cola (Queue)
add_library(queue STATIC Queue.c)
set_libConfig(queue node)


#	Lista (list)
add_library(list STATIC List.c)
set_libConfig(list node)


