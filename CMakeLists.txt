cmake_minimum_required(VERSION 3.16)

# Project name and version
project(Cryptor VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Define source and include directories
set(SRC_DIR "src")
set(INCLUDE_DIR "include")
set(BIN_DIR "build")

file(GLOB SOURCES ${SRC_DIR}/*.cpp)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${BIN_DIR})

# Include directories
include_directories(${INCLUDE_DIR})

# Find dependencies
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

# Brotli (assumes it is installed using Homebrew or similar package manager)
find_path(BROTLI_INCLUDE_DIR brotli)
find_library(BROTLI_COMMON_LIBRARY NAMES brotlicommon)
find_library(BROTLI_ENC_LIBRARY NAMES brotlienc)
find_library(BROTLI_DEC_LIBRARY NAMES brotlidec)

if(NOT BROTLI_INCLUDE_DIR OR NOT BROTLI_COMMON_LIBRARY OR NOT BROTLI_ENC_LIBRARY OR NOT BROTLI_DEC_LIBRARY)
    message(FATAL_ERROR "Brotli libraries not found. Make sure they are installed.")
endif()

# Libraries for dependencies
set(DEPENDENT_LIBRARIES
    OpenSSL::SSL
    OpenSSL::Crypto
    ZLIB::ZLIB
    ${BROTLI_COMMON_LIBRARY}
    ${BROTLI_ENC_LIBRARY}
    ${BROTLI_DEC_LIBRARY}
    pthread
)

# Frameworks for macOS
if(APPLE)
    list(APPEND DEPENDENT_LIBRARIES
        "-framework CoreFoundation"
        "-framework Security"
    )
endif()

# Compiler definitions
add_definitions(
    -DCPPHTTPLIB_OPENSSL_SUPPORT
    -DCPPHTTPLIB_ZLIB_SUPPORT
    -DCPPHTTPLIB_BROTLI_SUPPORT
)

# Add executable targets
add_executable(cryptor ${SRC_DIR}/cryptor.cpp)
add_executable(unit ${SRC_DIR}/unit.cpp)

# Link libraries to executables
target_link_libraries(cryptor PRIVATE ${DEPENDENT_LIBRARIES})
target_link_libraries(unit PRIVATE ${DEPENDENT_LIBRARIES})

# Installation rules
install(TARGETS cryptor unit DESTINATION ${BIN_DIR})
