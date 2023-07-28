cmake_minimum_required(VERSION 2.15)

project(main)

set(SOURCES 
	src/main.cpp

	src/Logic/Event.hpp

	src/Objects/Texture.hpp
	src/Objects/Texture.cpp

	src/Controllers/Engine.cpp
	src/Controllers/Engine.hpp

	src/Controllers/Scene.hpp
	src/Controllers/Scene.cpp

	src/Objects/Object.hpp
	src/Objects/Object.cpp

	src/Logic/Hitbox.hpp
	src/Logic/Hitbox.cpp

	src/Logic/Position.hpp
	src/Logic/Position.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)
add_compile_options(-g -Wall)
add_executable(main ${SOURCES})
target_link_libraries(main SDL2)
target_link_libraries(main SDL2_image)
