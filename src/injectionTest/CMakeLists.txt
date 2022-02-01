project(injectionTest LANGUAGES CXX)


add_executable(injectionTest
               main.cpp
               )
			   
			   

find_package(kangaru REQUIRED)
find_package(pslog REQUIRED)

target_link_libraries(injectionTest kangaru::kangaru pslog::pslog)





set_target_properties(injectionTest PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(injectionTest PROPERTIES RELWITHDEBINFO_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})

install(TARGETS injectionTest
        CONFIGURATIONS Debug Release RelWithDebInfo 
        RUNTIME DESTINATION bin)
