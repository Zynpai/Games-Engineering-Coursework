cmake_minimum_required(VERSION 3.11)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(Games_Engineering)


SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})


add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")




file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader sfml-graphics)

add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

file(GLOB_RECURSE SOURCES Dungeon_Defence/*.cpp Dungeon_Defence/*.h)
add_executable(DUNGEON_DEFENCE ${SOURCES} )
target_include_directories(DUNGEON_DEFENCE SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(DUNGEON_DEFENCE sfml-graphics lib_tile_level_loader lib_maths lib_ecm)

set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY 
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)