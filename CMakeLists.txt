cmake_minimum_required(VERSION 3.5)

project(main)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES 
	src/main.cpp

	src/Logic/Event.hpp

	src/Objects/Texture.hpp
	src/Objects/Texture.cpp

	src/Controllers/Engine.cpp
	src/Controllers/Engine.hpp

	src/Controllers/InputHandler.cpp
	src/Controllers/InputHandler.hpp

	src/Controllers/Scene.hpp
	src/Controllers/Scene.cpp

	src/Objects/Object.hpp
	src/Objects/Object.cpp

	src/Logic/Hitbox.hpp
	src/Logic/Hitbox.cpp

	src/Logic/Position.hpp
	src/Logic/Position.cpp
)

include_directories(src)

IF(WIN32)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include/SDL2)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2_image/include/SDL2)
	
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/lib)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2_image/lib)
endif()

add_executable(main ${SOURCES})

IF(WIN32)
	target_link_libraries(main SDL2)
	target_link_libraries(main SDL2_image)
endif()

if(LINUX)
	target_link_libraries(main SDL2)
	target_link_libraries(main SDL2_image)
endif()