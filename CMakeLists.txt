cmake_minimum_required(VERSION 2.6)
project(AONX)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${AONX_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${AONX_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# Look up SDL2 and add the include directory to our include path
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories(${SDL_MIXER_INCLUDE_DIR})

include_directories("${PROJECT_BINARY_DIR}/../include")

file(GLOB_RECURSE AONX_SOURCES "src/*.cpp")
file(GLOB_RECURSE AONX_HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${AONX_SOURCES})

target_link_libraries(${PROJECT_NAME}  ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDL_MIXER_LIBRARY} ${OPENGL_LIBRARIES} )

