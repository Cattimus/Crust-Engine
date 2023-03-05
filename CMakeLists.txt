cmake_minimum_required(VERSION 2.15)

project(main)

set(SOURCES 
	src/main.cpp

	src/Event.hpp

	src/Texture.hpp
	src/Texture.cpp

	src/Engine.cpp
	src/Engine.hpp

	src/Scene.hpp
	src/Scene.cpp

	src/Object.hpp
	src/Object.cpp
)

set(SOURCES_PROTOTYPE
	proto/main.cpp
	proto/Event.hpp
	proto/Testclass.hpp
)

include_directories(/usr/include/SDL2)
add_compile_options(-g -Wall)
add_executable(main ${SOURCES})
add_executable(proto ${SOURCES_PROTOTYPE})
target_link_libraries(main SDL2)
target_link_libraries(main SDL2_image)