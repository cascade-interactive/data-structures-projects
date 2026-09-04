cmake_minimum_required(VERSION 4.3)
project(data_structures_projects)

set(CMAKE_CXX_STANDARD 14)

include_directories("Project 1")

add_executable(data_structures_projects
        "Project 1/CircularLinkedList.hpp"
        "Project 1/main.cpp"
)
