cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# create project
project(firex)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# include(CheckIncludeFileCXX)
# check_include_file_cxx(any HAS_ANY)
# check_include_file_cxx(string_view HAS_STRING_VIEW)
# check_include_file_cxx(coroutine HAS_COROUTINE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -fcoroutines")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add executable
add_executable(firex main.cpp)

include(cmake/CPM.cmake)

SET(BUILD_YAML_CONFIG OFF)

CPMAddPackage(
  NAME yaml
  VERSION 0.9.0
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.9.0
)

CPMAddPackage(
    NAME drogon
    VERSION 1.9.12
    GITHUB_REPOSITORY drogonframework/drogon
    GIT_TAG v1.9.12
)

# drogon
target_include_directories(drogon PRIVATE ${yaml_SOURCE_DIR}/include)
target_compile_definitions(drogon PRIVATE HAS_YAML_CPP)

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE drogon yaml-cpp)
