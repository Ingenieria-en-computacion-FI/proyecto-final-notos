#
#	   ________  ___      __           ______            _____           __                     _ 
#	  / ____/  |/  /___ _/ /_____     / ____/___  ____  / __(_)___ _   _/_/  _______________   | |
#	 / /   / /|_/ / __ `/ //_/ _ \   / /   / __ \/ __ \/ /_/ / __ `/  / /   / ___/ ___/ ___/   / /
#	/ /___/ /  / / /_/ / ,< /  __/  / /___/ /_/ / / / / __/ / /_/ /  / /   (__  ) /  / /__    / / 
#	\____/_/  /_/\__,_/_/|_|\___/   \____/\____/_/ /_/_/ /_/\__, /  / /   /____/_/   \___/  _/_/  
#	                                                       /____/   |_|                    /_/
#
#	Configuración (CMake) para la compilación de
#	los archivos fuente <.c>.
#


add_subdirectory(data)
add_subdirectory(core)


#	Libreria final
add_library(notOS SHARED notOS.c)
set_libConfig(notOS stack queue list memory scheduler)


