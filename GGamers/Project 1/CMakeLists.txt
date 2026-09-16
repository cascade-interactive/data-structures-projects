cmake_minimum_required(VERSION 3.14)
project(data_structures_projects)

set(CMAKE_CXX_STANDARD 14)

file(GLOB PROJECT_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(data_structures_projects
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
)

target_include_directories(data_structures_projects PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
