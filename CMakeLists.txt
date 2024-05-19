cmake_minimum_required(VERSION 3.0.0)
project(FIFA13_Randomizer VERSION 0.1.0)

include(CTest)
include_directories("./include/")
enable_testing()

add_library(player src/player.cpp)
add_library(playerlink src/playerlink.cpp)
add_library(team src/team.cpp)
add_library(league src/league.cpp)
add_library(stringtools src/StringTools.cpp)

add_executable(FIFA13_Randomizer main.cpp)
target_link_libraries(FIFA13_Randomizer player team playerlink league stringtools)

set_property(TARGET FIFA13_Randomizer PROPERTY CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(TARGET FIFA13_Randomizer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/leagues.txt ${CMAKE_SOURCE_DIR}/build)
add_custom_command(TARGET FIFA13_Randomizer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/players.txt ${CMAKE_SOURCE_DIR}/build)
add_custom_command(TARGET FIFA13_Randomizer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/leagueteamlinks.txt ${CMAKE_SOURCE_DIR}/build)
add_custom_command(TARGET FIFA13_Randomizer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/teamplayerlinks.txt ${CMAKE_SOURCE_DIR}/build)