cmake_minimum_required(VERSION 3.1)

project(graphics-frameworks-cpp)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(tinygl)
include_directories(src tinygl/include)
link_libraries(fmt::fmt spdlog::spdlog tinygl)
if (TARGET glm::glm)
    link_libraries(glm::glm)
else()
    link_libraries(glm)
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
