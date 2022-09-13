set(APP_NAME SimpleViewer)
project(${APP_NAME} LANGUAGES CXX)
find_package(nlohmann_json REQUIRED)
find_package(openscenegraph MODULE REQUIRED)

file(GLOB HEADER_FILES 	CONFIGURE_DEPENDS "*.h")
file(GLOB CPP_FILES 	CONFIGURE_DEPENDS "*.cpp")

add_executable(${APP_NAME} 
	${HEADER_FILES}
	${CPP_FILES}
)
			   
			   


target_link_libraries (${APP_NAME} 
					PRIVATE
						nlohmann_json::nlohmann_json 

						OPENSCENEGRAPH::osg OPENSCENEGRAPH::OpenThreads OPENSCENEGRAPH::osgDB OPENSCENEGRAPH::osgGA OPENSCENEGRAPH::osgViewer 
				
						${PROJECT_NAMESPACE}::common
						${PROJECT_NAMESPACE}::interfaces
						
)




target_include_directories(${APP_NAME}
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" 
	FILES ${HEADER_FILES} ${CPP_FILES}
)





set_target_properties(${APP_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(${APP_NAME} PROPERTIES RELWITHDEBINFO_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})

install(TARGETS ${APP_NAME}
        CONFIGURATIONS Debug Release RelWithDebInfo 
        RUNTIME DESTINATION bin)

function(copy_runtime_dlls TARGET)
  get_property(already_applied TARGET "${TARGET}" PROPERTY _copy_runtime_dlls_applied)

  if (CMAKE_IMPORT_LIBRARY_SUFFIX AND NOT already_applied)
    add_custom_command(
      TARGET "${TARGET}" POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_RUNTIME_DLLS:${TARGET}>" "$<TARGET_FILE_DIR:${TARGET}>"
      COMMAND_EXPAND_LISTS
    )
 
    set_property(TARGET "${TARGET}" PROPERTY _copy_runtime_dlls_applied 1)
  endif ()
endfunction()

#copy_runtime_dlls(SimpleViewer)

set_target_properties(
    ${APP_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")