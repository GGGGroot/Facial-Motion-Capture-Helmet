cmake_minimum_required(VERSION 2.8.4)  

set(Test LightTest)

set(Sources test.cpp)

add_executable(${Test} ${Sources})

target_link_libraries( ${Test} PUBLIC
	gtest_main
	mycode
)

add_test(NAME ${Test}
	COMMAND ${Test}
)
