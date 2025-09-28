set(QT_CREATOR_SKIP_CONAN_SETUP ON)

cmake_minimum_required(VERSION 3.8)
project(battery_reader LANGUAGES CXX)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(DEBUG "ccache found")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
endif()

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(spdlog REQUIRED)

file(GLOB SOURCES "sources/*.cpp")
file(GLOB HEADERS "headers/*.hpp")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON)

add_compile_definitions(SPDLOG_COMPILED_LIB)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)
target_include_directories(${PROJECT_NAME} PUBLIC "headers")
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog Boost::program_options i2c)
