project(ChartViewer LANGUAGES CXX)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(ChartViewer
               main.cpp
               )
			   
			   
find_package(Qt6 COMPONENTS Widgets Core QWindowsIntegrationPlugin REQUIRED)
qt_import_plugins(ChartViewer
    INCLUDE Qt::QWindowsIntegrationPlugin
)

target_link_libraries(ChartViewer Qt6::Widgets Qt6::Core Qt6::QWindowsIntegrationPlugin)





set_target_properties(ChartViewer PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(ChartViewer PROPERTIES RELWITHDEBINFO_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})

install(TARGETS ChartViewer
        CONFIGURATIONS Debug Release RelWithDebInfo 
        RUNTIME DESTINATION bin)
		
