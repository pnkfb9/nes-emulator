#include <cstdint>

#include "catch2/catch_test_macros.hpp"
#include "core/cpu/CPU6502.h"
#include "core/mem/Bus.h"
#include "core/mem/Memory.h"

TEST_CASE("Bus basic read/write", "[sys]")
{
    Bus    main_bus("main-bus");
    Memory ram("RAM", 2048);
    Memory rom("ROM", 40960);
    main_bus.registerDevice(ram, 0x0);
    main_bus.registerDevice(rom, 0x4020);
    uint8_t  data = 0x0U;
    uint16_t address = 0x0U;
    data = main_bus.read(address);
    REQUIRE(data == 0x0U);
    main_bus.write(address, 0x12U);
    REQUIRE(main_bus.read(0x0U) == 0x12U);
}

TEST_CASE("CPU Reset", "[cpu]")
{
}

TEST_CASE("LDA Immediate", "[cpu][instructions]")
{
}

TEST_CASE("STA Zero Page", "[cpu][instructions]")
{
}