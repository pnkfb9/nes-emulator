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
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0  # Latest stable release
)
FetchContent_MakeAvailable(fmt)

# Catch2 installation
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
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
    src/core/mem/BaseMemory.h
    src/core/mem/Memory.cpp
    src/core/mem/Memory.h
    src/core/mem/Bus.cpp
    src/core/mem/Bus.h
    src/core/graphics/PictureProcessingUnit.cpp
    src/core/graphics/PictureProcessingUnit.h
    src/core/audio/AudioProcessingUnit.cpp
    src/core/audio/AudioProcessingUnit.h
    src/Emulator.cpp
    src/Emulator.h
    )

# Main include directory for all components
target_include_directories(core_objects
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${fmt_SOURCE_DIR}/include>  # Add fmt headers
)

# Main executable
add_executable(nes-emulator
    main.cpp
)

# Link core components and SDL2 to main executable
target_link_libraries(nes-emulator
    PRIVATE
        core_objects
        fmt::fmt
        SDL2::SDL2
)

# Test executable
add_executable(tests
    tests/cpu_tests.cpp
)

# Link core components and Catch2 to tests
target_link_libraries(tests
    PRIVATE
        core_objects
        fmt::fmt
        Catch2::Catch2WithMain
)

# Enable testing
enable_testing()
add_test(NAME cpu-tests COMMAND tests)

# Compiler options for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Common debug flags for all platforms
    target_compile_options(core_objects PRIVATE
        -Wall
        -Wextra
        -g
        -O0
    )
    
    target_compile_options(nes-emulator PRIVATE
        -Wall
        -Wextra
        -g
        -O0
    )
    
    target_compile_options(tests PRIVATE
        -Wall
        -Wextra
        -g
        -O0
    )

    # Sanitizer configuration
    if(APPLE)
        # Apple-specific sanitizer setup (works for both Intel and ARM)
        set(SANITIZER_FLAGS "-fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls")
        
        # For Xcode generator, use Xcode-specific settings
        if(CMAKE_GENERATOR STREQUAL "Xcode")
            set(CMAKE_XCODE_ATTRIBUTE_ENABLE_ADDRESS_SANITIZER "YES")
            set(CMAKE_XCODE_ATTRIBUTE_ENABLE_UNDEFINED_BEHAVIOR_SANITIZER "YES")
        else()
            # For Makefile/Ninja generators
            target_compile_options(core_objects PRIVATE ${SANITIZER_FLAGS})
            target_link_options(core_objects PRIVATE ${SANITIZER_FLAGS})
            
            target_compile_options(nes-emulator PRIVATE ${SANITIZER_FLAGS})
            target_link_options(nes-emulator PRIVATE ${SANITIZER_FLAGS})
            
            target_compile_options(tests PRIVATE ${SANITIZER_FLAGS})
            target_link_options(tests PRIVATE ${SANITIZER_FLAGS})
        endif()
    else()
        # Linux/other platforms
        target_compile_options(core_objects PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
            -fno-optimize-sibling-calls
        )
        target_link_options(core_objects PRIVATE -fsanitize=address,undefined)
        
        target_compile_options(nes-emulator PRIVATE
            -fsanitize=address,undefined
        )
        target_link_options(nes-emulator PRIVATE -fsanitize=address,undefined)
        
        target_compile_options(tests PRIVATE
            -fsanitize=address,undefined
        )
        target_link_options(tests PRIVATE -fsanitize=address,undefined)
    endif()
endif()

# Installation (optional)
install(TARGETS nes-emulator
    RUNTIME DESTINATION bin
)