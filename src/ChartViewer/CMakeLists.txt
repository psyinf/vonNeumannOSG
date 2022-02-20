project(ChartViewer LANGUAGES CXX)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(ChartViewer
               main.cpp
               )
			   
find_package(cppkafka MODULE REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets Core QWindowsIntegrationPlugin Charts)



target_link_libraries(ChartViewer  
    Qt6::Widgets 
    Qt6::Core 
    Qt6::QWindowsIntegrationPlugin 
    Qt6::Charts
    cppkafka::cppkafka)





set_target_properties(ChartViewer PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(ChartViewer PROPERTIES RELWITHDEBINFO_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})

install(TARGETS ChartViewer
        CONFIGURATIONS Debug Release RelWithDebInfo 
        RUNTIME DESTINATION bin)
		
set_target_properties(
    ChartViewer PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")