project(KafkaTest LANGUAGES CXX)


add_executable(KafkaTest
               main.cpp
               )
			   
			   

find_package(cppkafka MODULE REQUIRED)

target_link_libraries(KafkaTest cppkafka::cppkafka)





set_target_properties(KafkaTest PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(KafkaTest PROPERTIES RELWITHDEBINFO_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})

install(TARGETS KafkaTest
        CONFIGURATIONS Debug Release RelWithDebInfo 
        RUNTIME DESTINATION bin)
