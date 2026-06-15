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
	src/core/main.cpp
	src/core/Application.cpp
	
	src/models/ApplicationSettings.cpp
	
	src/components/musicplayer/MusicPlayerConnector.cpp
	src/components/musicplayer/MusicPlayerUI.cpp
	src/components/musicplayer/MusicPlayerLogic.cpp
	
	src/components/playlist/PlaylistConnector.cpp
	src/components/playlist/PlaylistUI.cpp
	src/components/playlist/PlaylistLogic.cpp
)

set(HEADERS
	src/core/Application.h
	
	src/models/ApplicationSettings.h
	
	src/components/musicplayer/MusicPlayerConnector.h
	src/components/musicplayer/MusicPlayerUI.h
	src/components/musicplayer/MusicPlayerLogic.h
	
	src/components/playlist/PlaylistConnector.h
	src/components/playlist/PlaylistUI.h
	src/components/playlist/PlaylistLogic.h

	src/components/IConnector.h
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