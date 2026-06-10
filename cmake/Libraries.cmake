#
#	Configuración mínima para las librerias generadas por CMake:
#		*	Generacion en el directorio <lib>.
#		*	Directorio <include> para los archivos [.h].
#
add_library(includeConfig INTERFACE)

target_include_directories(includeConfig INTERFACE
	${PROJECT_SOURCE_DIR}/include
)

function (set_libConfig lib)

	target_link_libraries(${lib} PUBLIC includeConfig ${ARGN})

	set_target_properties(${lib} PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY	${PROJECT_SOURCE_DIR}/lib
		ARCHIVE_OUTPUT_DIRECTORY	${PROJECT_SOURCE_DIR}/lib
	)

endfunction()

function (set_testConfig test)

	target_link_libraries(${test} PUBLIC includeConfig)

	set_target_properties(${test} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY	${PROJECT_SOURCE_DIR}/tests/${NOTY_TEST_SUBDIR}
	)

endfunction()


