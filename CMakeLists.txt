cmake_minimum_required(VERSION 3.21)

project(cpp_questions
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# Discover example directories (leaf folders under examples/)
# ------------------------------------------------------------------------------

file(GLOB_RECURSE EXAMPLE_MAIN_FILES
     CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/examples/**/main.cpp
)

foreach(main_src ${EXAMPLE_MAIN_FILES})
    # Example directory
    get_filename_component(example_dir ${main_src} DIRECTORY)

    # Collect all sources and headers in that directory
    file(GLOB example_sources
         CONFIGURE_DEPENDS
         ${example_dir}/*.cpp
         ${example_dir}/*.h
         ${example_dir}/*.hpp
    )

    # Create a stable target name from the path
    file(RELATIVE_PATH rel_dir ${CMAKE_SOURCE_DIR}/examples ${example_dir})
    string(REPLACE "/" "_" target_name ${rel_dir})
    string(REPLACE "\\" "_" target_name ${target_name})

    add_executable(${target_name} ${example_sources})

    # Headers are local to the example
    target_include_directories(${target_name} PRIVATE ${example_dir})

    # Warnings
    if (MSVC)
        target_compile_options(${target_name} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    # IDE grouping
    set_target_properties(${target_name} PROPERTIES
        FOLDER "examples/${rel_dir}"
    )
endforeach()
