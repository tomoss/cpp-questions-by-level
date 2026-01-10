cmake_minimum_required(VERSION 3.21)

project(cpp_questions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# Discover example main files: examples/*/*/src/main.cpp
# ------------------------------------------------------------------------------

file(GLOB_RECURSE EXAMPLE_MAIN_FILES
     CONFIGURE_DEPENDS
     ${CMAKE_SOURCE_DIR}/examples/*/*/src/main.cpp
)

message(STATUS "Searching examples in: ${CMAKE_SOURCE_DIR}/examples")
message(STATUS "Found main files: ${EXAMPLE_MAIN_FILES}")

if (EXAMPLE_MAIN_FILES STREQUAL "")
    message(FATAL_ERROR "No examples found. Expected examples/*/*/src/main.cpp")
endif()

foreach(main_src ${EXAMPLE_MAIN_FILES})

    # src directory
    get_filename_component(src_dir ${main_src} DIRECTORY)
    # example root directory
    get_filename_component(example_dir ${src_dir} DIRECTORY)

    # collect all cpp in src/
    file(GLOB example_sources
         CONFIGURE_DEPENDS
         ${src_dir}/*.cpp
    )

    # collect headers (optional)
    file(GLOB example_headers
         CONFIGURE_DEPENDS
         ${example_dir}/include/*.h
         ${example_dir}/include/*.hpp
    )

    # target name from relative path
    file(RELATIVE_PATH rel_dir ${CMAKE_SOURCE_DIR}/examples ${example_dir})
    string(REPLACE "/" "_" target_name ${rel_dir})
    string(REPLACE "\\" "_" target_name ${target_name})

    add_executable(${target_name}
        ${example_sources}
        ${example_headers}
    )

    # local include paths
    target_include_directories(${target_name} PRIVATE
        ${example_dir}/include
        ${src_dir}
    )

    # warnings
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
