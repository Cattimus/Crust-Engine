cmake_minimum_required(VERSION 2.15)

project(main)

set(SOURCES 
	src/main.cpp

	src/Engine.cpp
	src/Engine.hpp

	src/Scene.hpp
	src/Scene.cpp
)

include_directories(/usr/include/SDL2)
add_executable(main ${SOURCES})
target_link_libraries(main SDL2)