cmake_minimum_required(VERSION 3.2)

project(graphics-frameworks-cpp)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(tinygl)
include_directories(src tinygl/include tinygl/imgui)
link_libraries(fmt::fmt spdlog::spdlog tinygl)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_compile_options(-Wno-gnu-anonymous-struct -Wno-nested-anon-types)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W3 /WX)
endif()

set(CHAPTERS
    02
    03
)

function(create_project_from_sources chapter demo)
    get_filename_component(NAME "${demo}" NAME_WE)
    add_executable(${NAME} ${demo})
    target_compile_definitions(${NAME} PRIVATE NAME="${NAME}")
    # copy shader files to build directory
    file(GLOB SHADERS
        "src/${chapter}/*.vert"
        "src/${chapter}/*.frag"
        "src/${chapter}/*.geom"
    )
    foreach(SHADER ${SHADERS})
        add_custom_command(TARGET ${NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:${NAME}>)
    endforeach(SHADER)
endfunction()

foreach(CHAPTER ${CHAPTERS})
    message(STATUS "Configuring examples for chapter ${CHAPTER}")
    file(GLOB EXAMPLES ${CMAKE_SOURCE_DIR}/src/${CHAPTER}/*.cpp)
    foreach(EXAMPLE ${EXAMPLES})
        message(STATUS "Configuring example ${EXAMPLE}")
        create_project_from_sources(${CHAPTER} ${EXAMPLE})
    endforeach(EXAMPLE)
endforeach(CHAPTER)
