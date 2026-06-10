cmake_minimum_required(VERSION 3.16)

project(TinyMint_Player VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS 
	Core 
	Widgets 
	Multimedia
)

qt_standard_project_setup()

set(SOURCES
	main.cpp
	Application.cpp
	MusicPlayer.cpp
	ApplicationSettings.cpp
)

set(HEADERS
	Application.h
	MusicPlayer.h
	ApplicationSettings.h
)

qt_add_executable(TinyMint_Player ${SOURCES} ${HEADERS})

target_link_libraries(TinyMint_Player PRIVATE
	Qt6::Core
	Qt6::Widgets
	Qt6::Multimedia
)

set_target_properties(TinyMint_Player PROPERTIES
    WIN32_EXECUTABLE TRUE
)