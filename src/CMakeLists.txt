project(Viewer LANGUAGES CXX)
find_package(nlohmann_json REQUIRED)

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
			   
			   

target_link_libraries (Viewer nlohmann_json::nlohmann_json)
 include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
  target_link_libraries(Viewer ${OPENSCENEGRAPH_LIBRARIES})




set_target_properties(Viewer PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(Viewer PROPERTIES RELWITHDEBINFO_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})

install(TARGETS Viewer
        CONFIGURATIONS Debug Release RelWithDebInfo 
        RUNTIME DESTINATION bin)
