cmake_minimum_required(VERSION 3.6)
project(pathFinding)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Parser.cpp Parser.h SearchTemplates/Node.h SearchTemplates/Problem.cpp SearchTemplates/Problem.h DFS.cpp DFS.h SearchTemplates/Action.cpp SearchTemplates/Action.h SearchTemplates/SearchType.cpp SearchTemplates/SearchType.h SearchTemplates/SolutionResponse.cpp SearchTemplates/SolutionResponse.h SearchTemplates/Path.cpp SearchTemplates/Path.h SearchTemplates/BFS.cpp SearchTemplates/BFS.h SearchTemplates/Astar.cpp SearchTemplates/Astar.h sfmlGUI.cpp sfmlGUI.h main2.cpp SearchTemplates/Greedy.h SearchTemplates/Greedy.cpp)

add_executable(pathFinding ${SOURCE_FILES})

# Define sources and executable
set(EXECUTABLE_NAME "MySFML")
add_executable(${EXECUTABLE_NAME} main2.cpp ${SOURCE_FILES} SimpleTimer.cpp SimpleTimer.h RandomPaths.cpp RandomPaths.h SearchTemplates/Bidirectional.cpp SearchTemplates/Bidirectional.h SearchTemplates/MBAstar.cpp SearchTemplates/MBAstar.h)


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()