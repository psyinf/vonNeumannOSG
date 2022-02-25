cmake_minimum_required(VERSION 3.15)
project(testProj VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_RELWITHDEBINFO_POSTFIX _rd)

set(PROJECT_NAMESPACE "vonNeumann")			# namespace for target aliases in this project
set(PROJECT_EXPORT_NAME "vonNeumann")			# export name to be used by install() and downstream find_package()
set(PROJECT_INSTALL_PREFIX "vonNeumann")		# folder 'prefix' for installed includes and libs

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)


install(EXPORT ${PROJECT_EXPORT_NAME} 
	FILE
		${PROJECT_EXPORT_NAME}Targets.cmake
	NAMESPACE
		${PROJECT_NAMESPACE}::
	DESTINATION
		${CMAKE_INSTALL_ARCHIVEDIR}/cmake/${PROJECT_EXPORT_NAME}
	COMPONENT
		${DEVELOP_COMPONENT}
)


list(APPEND CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/cmake/"
)

add_definitions(-Dcppkafka_EXPORTS)
# Run conan install automatically, or display warning if conan is not installed
include(cmake/conan_config.cmake)

if(WIN32)
    add_compile_definitions(WINDOWS=1)
endif ()

add_subdirectory(src/common)
add_subdirectory(src/SimpleViewer)
add_subdirectory(src/kafkaTest)
add_subdirectory(src/injectionTest)
add_subdirectory(src/ChartViewer)
add_subdirectory(src/plugins)
add_subdirectory(src/interfaces)

add_custom_target( conan-install ALL COMMAND conan install ${CMAKE_SOURCE_DIR}/conanfile.txt -if ${CMAKE_INSTALL_PREFIX} DEPENDS install)       
