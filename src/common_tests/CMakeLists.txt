project(commonTest LANGUAGES CXX)
find_package(GTest CONFIG REQUIRED)

enable_testing()

include(GoogleTest)

add_executable(commonTest StringToolsTest.cpp)

target_link_libraries(commonTest 

		
	PRIVATE
		GTest::GTest 
		${PROJECT_NAMESPACE}::common
)


gtest_discover_tests(commonTest)