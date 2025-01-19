cmake_minimum_required(VERSION 3.16)
project(tmlc VERSION 1.0)

message("-- System is: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE RelWifDebInfo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(WIN32)
  set(CMAKE_REQUIRED_FLAGS "-lSDL2main -lSDL2 -lSDL2_image -lm")
else()
  set(CMAKE_REQUIRED_FLAGS "-lSDL2 -lSDL2_image -lm")
endif()

file(GLOB SOURCES "src/*.c")

find_library(SDL2_LIBRARY_MAIN NAMES SDL2main)
find_library(SDL2_LIBRARY NAMES SDL2)
find_library(SDL2_IMG_LIBRARY NAMES SDL2_image)

find_path(SDL2_INC NAMES SDL2/SDL.h PATHS SDL2/include/)
find_path(SDL2_IMG_INC NAMES SDL2/SDL_image.h PATHS SDL2/include/)

message("")
if(NOT SDL2_INC)
  message(FATAL_ERROR "SDL2 includes not found!")
else()
  message(STATUS "SDL2 includes found at ${SDL2_INC}")
endif()

if(NOT SDL2_IMG_INC)
  message(FATAL_ERROR "SDL2_image includes not found!")
else()
  message(STATUS "SDL2_image includes found at ${SDL2_IMG_INC}")
endif()

if(NOT SDL2_LIBRARY_MAIN)
  message(WARNING "SDL2main not found!")
else()
  message(STATUS "SDL2main found at ${SDL2_LIBRARY_MAIN}")
endif()

if(NOT SDL2_LIBRARY)
  message(FATAL_ERROR "SDL2 not found, please install it via your package manager!")
else()
  message(STATUS "SDL2 found at ${SDL2_LIBRARY}")
endif()

if(NOT SDL2_IMG_LIBRARY)
  message(FATAL_ERROR "SDL2_image not found, please install it via your package manager!")
else()
  message(STATUS "SDL2_image found at ${SDL2_IMG_LIBRARY}")
endif()
message("")


if(WIN32 OR MSYS)
  message("-- BUILDING FOR WINDOWS!")

  add_executable(tmlc  ${SOURCES})
  target_compile_definitions(tmlc PRIVATE SDL_MAIN_HANDLED)
  target_compile_options(tmlc PRIVATE -Wall -Wextra -pedantic)

  include_directories(${SDL2_IMG_INC} ${SDL2_INC})

  target_link_libraries(tmlc ${SDL2_LIBRARY_MAIN} ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY} m)
else()
  message("-- BUILDING FOR LINUX!")

  add_executable(tmlc ${SOURCES})
  target_compile_options(tmlc PRIVATE -Wall -Wextra -pedantic)
  include_directories(${SDL2_IMG_INC} ${SDL2_INC})

  target_link_libraries(tmlc ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY} m)
endif()




