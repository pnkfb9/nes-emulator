cmake_minimum_required(VERSION 3.15)
project(nes-emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Policy settings
cmake_policy(SET CMP0077 NEW)

# SDL2 find package
find_package(SDL2 REQUIRED)

include(FetchContent)

# fmt library
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmt)

# Catch2 for testing
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# Core library components as OBJECT library for reuse
add_library(core_objects OBJECT
    src/core/cpu/CPU6502.cpp
    src/core/cpu/CPU6502.h
    src/core/cpu/RegisterSet.h
    src/core/cpu/InstructionSet.h
    src/core/log/Logger.cpp
    src/core/log/Logger.h
    src/core/mem/RAM.cpp
    src/core/mem/RAM.h
    src/core/mem/ROM.cpp
    src/core/mem/ROM.h
    src/core/mem/BaseMemory.cpp
    src/core/mem/BaseMemory.h
    src/core/mem/Bus.cpp
    src/core/mem/Bus.h
    src/core/common/Peripheral.cpp
    src/core/common/Peripheral.h 
    src/core/graphics/PictureProcessingUnit.cpp
    src/core/graphics/PictureProcessingUnit.h
    src/core/audio/AudioProcessingUnit.cpp
    src/core/audio/AudioProcessingUnit.h
    src/core/utils/RomLoader.cpp
    src/core/utils/RomLoader.h
    src/Emulator.cpp
    src/Emulator.h

)

# Main include directory for all components
target_include_directories(core_objects
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${fmt_SOURCE_DIR}/include>
)

# Main executable
add_executable(nes-emulator main.cpp)
target_link_libraries(nes-emulator
    PRIVATE
        core_objects
        fmt::fmt
        SDL2::SDL2
)

# Test executable
add_executable(tests tests/cpu_tests.cpp)
target_link_libraries(tests
    PRIVATE
        core_objects
        fmt::fmt
        Catch2::Catch2WithMain
)

# Enable testing
enable_testing()
add_test(NAME cpu-tests COMMAND tests)

# Common debug flags
set(COMMON_DEBUG_FLAGS -Wall -Wextra -g -O0)

# Sanitizer configuration function
function(add_sanitizer_flags target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        # Check if sanitizers are supported
        include(CheckCXXCompilerFlag)
        set(SANITIZER_FLAGS "-fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls")
        check_cxx_compiler_flag("${SANITIZER_FLAGS}" HAVE_SANITIZERS)
        
        if(HAVE_SANITIZERS)
            if(APPLE AND CMAKE_GENERATOR STREQUAL "Xcode")
                # Xcode-specific settings
                set_property(TARGET ${target} PROPERTY XCODE_ATTRIBUTE_ENABLE_ADDRESS_SANITIZER "YES")
                set_property(TARGET ${target} PROPERTY XCODE_ATTRIBUTE_ENABLE_UNDEFINED_BEHAVIOR_SANITIZER "YES")
            else()
                # Makefile/Ninja generators
                target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS})
                target_link_options(${target} PRIVATE ${SANITIZER_FLAGS})
            endif()
        else()
            message(WARNING "Sanitizers not supported for target ${target}")
        endif()
    endif()
endfunction()

# Apply debug options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Apply common debug flags
    target_compile_options(core_objects PRIVATE ${COMMON_DEBUG_FLAGS})
    target_compile_options(nes-emulator PRIVATE ${COMMON_DEBUG_FLAGS})
    target_compile_options(tests PRIVATE ${COMMON_DEBUG_FLAGS})

    # Apply sanitizers to all targets
    add_sanitizer_flags(core_objects)
    add_sanitizer_flags(nes-emulator)
    add_sanitizer_flags(tests)
endif()

# Installation (optional)
install(TARGETS nes-emulator
    RUNTIME DESTINATION bin
)