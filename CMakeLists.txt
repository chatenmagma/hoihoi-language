cmake_minimum_required(VERSION 3.25)

project(hoihoi
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS off)

# ANLR
set(ANTLR_JAR "/opt/antlr/antlr.jar")
set(GRAMMAR_LEXER "${CMAKE_CURRENT_SOURCE_DIR}/grammar/HoihoiLexer.g4")
set(GRAMMAR_PARSER "${CMAKE_CURRENT_SOURCE_DIR}/grammar/HoihoiParser.g4")
set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")

if(NOT EXISTS "${ANTLR_JAR}")
    message(FATAL_ERROR "ANTLR jar not found at ${ANTLR_JAR}")
endif()

find_package(Java REQUIRED COMPONENTS Runtime)

# Generated files by ANTLR
set(ANTLR_GENERATED_SOURCES
    "${GENERATED_DIR}/HoihoiLexer.cpp"
    "${GENERATED_DIR}/HoihoiParser.cpp"
    "${GENERATED_DIR}/HoihoiParserBaseVisitor.cpp"
    "${GENERATED_DIR}/HoihoiParserVisitor.cpp"
    "${GENERATED_DIR}/HoihoiLexer.h"
    "${GENERATED_DIR}/HoihoiParser.h"
    "${GENERATED_DIR}/HoihoiParserBaseVisitor.h"
    "${GENERATED_DIR}/HoihoiParserVisitor.h"
)

add_custom_command(
    OUTPUT ${ANTLR_GENERATED_SOURCES}

    COMMAND
        ${CMAKE_COMMAND} -E make_directory
        "${GENERATED_DIR}"

    COMMAND
        ${Java_JAVA_EXECUTABLE}
        -jar "${ANTLR_JAR}"
        -Dlanguage=Cpp
        -visitor
        -o "${GENERATED_DIR}"
        "${GRAMMAR_LEXER}"
        "${GRAMMAR_PARSER}"

    DEPENDS
        "${GRAMMAR_LEXER}"
        "${GRAMMAR_PARSER}"
        "${ANTLR_JAR}"

    COMMENT "Generating C++ par
#include ser from ANTLR grammar"
    VERBATIM
)

add_custom_target(antlr_generate
    DEPENDS ${ANTLR_GENERATED_SOURCES}
)

# Sources

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(hoihoi
    ${SOURCES}
    ${ANTLR_GENERATED_SOURCES}
)

add_dependencies(hoihoi antlr_generate)

# Includes directories

target_include_directories(hoihoi
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${GENERATED_DIR}"
        "/usr/local/include/antlr4-runtime"
)

# Antlr runtime

target_link_libraries(hoihoi
    PRIVATE
        antlr4-runtime
)

set_target_properties(hoihoi PROPERTIES
    BUILD_RPATH "/usr/local/lib"
)

# Compile warning

target_compile_options(hoihoi PRIVATE 
    -Wall 
    -Wextra 
    -Wno-overloaded-virtual
)

# Debug configuration

target_compile_options(hoihoi PRIVATE
    $<$<CONFIG:Debug>: -g>
    $<$<CONFIG:Debug>: -O0>
    $<$<CONFIG:Release>: -O2>
    $<$<CONFIG:Release>: -DNDEBUG>
)

target_compile_options(hoihoi PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

target_link_options(hoihoi PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

# Link-Time Optimization (LTO)
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_ERROR)

if(IPO_SUPPORTED)
    set_property(TARGET hoihoi PROPERTY
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    )
    message(STATUS "Release LTO enabled")
else()
    message(STATUS "Release LTO unavailable: ${IPO_ERROR}")
endif()
