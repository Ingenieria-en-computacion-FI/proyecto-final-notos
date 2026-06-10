#
#	 _____ ___  ___      _          _____              __ _          __  _                     __  
#	/  __ \|  \/  |     | |        /  __ \            / _(_)        / / | |                    \ \ 
#	| /  \/| .  . | __ _| | _____  | /  \/ ___  _ __ | |_ _  __ _  | |  | |__   __ _ ___  ___   | |
#	| |    | |\/| |/ _` | |/ / _ \ | |    / _ \| '_ \|  _| |/ _` | | |  | '_ \ / _` / __|/ _ \  | |
#	| \__/\| |  | | (_| |   <  __/ | \__/\ (_) | | | | | | | (_| | | |  | |_) | (_| \__ \  __/  | |
#	 \____/\_|  |_/\__,_|_|\_\___|  \____/\___/|_| |_|_| |_|\__, | | |  |_.__/ \__,_|___/\___|  | |
#	                                                         __/ |  \_\                        /_/ 
#	                                                        |___/                                  
#
#	Configuración (base) para la compilación de los archivos del proyecto.
#	Porque ni loco uso Makefiles manuales, más chamba :p.
#
cmake_minimum_required(VERSION 3.20)

project(
	notyOS
	VERSION	1.0.0
	LANGUAGES C
)


#	Configuración extra, modulada
include(cmake/Compiler.cmake)
include(cmake/Libraries.cmake)


#	Sources
add_subdirectory(src/data)
add_subdirectory(src/core)

#	Tests
add_subdirectory(tests/data)


