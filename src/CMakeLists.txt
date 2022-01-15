project(Viewer LANGUAGES CXX)

add_executable(Viewer
               Viewer.cpp
               ConfigCache.h
			   Entity.h
               EntityBehavior.h
               EntityBehavior.cpp
               EntityConf.h
               EntityConf.cpp
			   EntityTypes.h
			   SimpleScene.h
			   SimpleScene.cpp
               EntityUpdateCallback.h
               EntityUpdateCallback.cpp
               SceneConfig.h

			Vec3dPid.h
               )
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

#target_link_libraries(Viewer PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(Viewer PRIVATE ${OPENSCENEGRAPH_LIBRARIES})
target_include_directories(Viewer PRIVATE ${PLOG_INCLUDE_DIRS})




set_target_properties(Viewer PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(Viewer PROPERTIES RELWITHDEBINFO_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})

install(TARGETS Viewer
        CONFIGURATIONS Debug Release RelWithDebInfo 
        RUNTIME DESTINATION bin)
