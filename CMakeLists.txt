cmake_minimum_required(VERSION 3.6)
project(pathFinding)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Parser.cpp Parser.h SearchTemplates/Node.h SearchTemplates/Problem.cpp SearchTemplates/Problem.h DFS.cpp DFS.h SearchTemplates/Action.cpp SearchTemplates/Action.h SearchTemplates/SearchType.cpp SearchTemplates/SearchType.h SearchTemplates/SolutionResponse.cpp SearchTemplates/SolutionResponse.h SearchTemplates/Path.cpp SearchTemplates/Path.h SearchTemplates/BFS.cpp SearchTemplates/BFS.h SearchTemplates/Astar.cpp SearchTemplates/Astar.h)
add_executable(pathFinding ${SOURCE_FILES})