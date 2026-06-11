#
#	Configuración mínima del compilador de C.
#	Preferentamete GCC, pero bueno.
#
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_compile_options(
	-g
	-O0
	-Wall
	-Wextra
	-Wpedantic
)


