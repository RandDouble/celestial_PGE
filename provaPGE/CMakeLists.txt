cmake_minimum_required(VERSION 3.8)

project (celestial LANGUAGES CXX)
# setting cpp standard and enforcing its use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




set(SOURCE src/main.cpp) 
add_executable(celestial.exe ${SOURCE})

# Defines targets and sources 
add_subdirectory(src)
# add_subdirectory(incs)

target_include_directories(celestial.exe
	PUBLIC
		incs
		${PROJECT_BINARY_DIR}
		${PROJECT_SOURCE_DIR}/Intrfc
		${PROJECT_SOURCE_DIR}/Balls
		${PROJECT_SOURCE_DIR}/MovementEngine
		${PROJECT_SOURCE_DIR}/Celestial
		${PROJECT_SOURCE_DIR}/olcPixelGameEngine
)

target_link_libraries(celestial.exe
	PUBLIC
		Intrfc
		Balls
		MovementEngine
		Celestial
		olcPixelGameEngine
)


# Adding Interface

#add_library(intrfc "")

#target_sources(intrfc
#	PRIVATE
#		${CMAKE_CURRENT_LIST_DIR}/interface.cpp
#	PUBLIC
#		${CMAKE_CURRENT_LIST_DIR}/interface.h
#)

#target_include_directories(intrfc
#	PUBLIC
#		${CMAKE_CURRENT_LIST_DIR}
#)

# Adding Balls

#add_library(Balls "")

#target_sources(Balls
#	PRIVATE
#		${CMAKE_CURRENT_LIST_DIR}/Balls.cpp
#	PUBLIC
#		${CMAKE_CURRENT_LIST_DIR}/Balls.h
#)

#target_include_directories(Balls
#	PUBLIC
#		${CMAKE_CURRENT_LIST_DIR}
#)
#
## Adding MovementEngine
#
#add_library(MovementEngine "")
#
#target_sources(MovementEngine
#	PRIVATE
#		${CMAKE_CURRENT_LIST_DIR}/MovementEngine.cpp
#	PUBLIC
#		${CMAKE_CURRENT_LIST_DIR}/MovementEngine.h
#)
#
#target_include_directories(MovementEngine
#	PUBLIC
#		${CMAKE_CURRENT_LIST_DIR}
#)
#
## Adding 
#
## target_link_libraries(celestial.exe PUBLIC obj)
#target_include_directories(celestial.exe PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/incs")

# Some settings for Unix systems
if(UNIX)
	set(CMAKE_CXX_FLAGS "-lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17")
	target_link_libraries(celestial.exe PRIVATE -lX11 -lGL -lpthread -lpng -lstdc++fs)
endif(UNIX)
