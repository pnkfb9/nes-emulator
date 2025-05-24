#include <cstdint>
#include <random>

#include "catch2/catch_test_macros.hpp"
#include "core/log/Logger.h"
#include "core/mem/Bus.h"
#include "core/mem/RAM.h"
#include "core/utils/RomLoader.h"

TEST_CASE("Bus basic read/write to RAM", "[sys]")
{
    Logger::setLogLevel(Logger::Level::DEBUG);
    std::random_device rd;
    unsigned int       seed = rd();
    LOG(INFO, "Bus basic test on read/write. only RAM, no PPU or APU.");
    LOG(INFO, "Using seed: {}", seed); // Catch2 will show this if test fails
    std::mt19937                           gen(seed);
    std::uniform_int_distribution<uint8_t> dist(0, 255);
    Bus                                    main_bus("main-bus");
    RAM                                    ram("RAM", 0x800U);
    main_bus.registerDevice(std::make_unique<RAM>(ram), 0x0U);
    uint8_t data = 0x0U;

    for (uint16_t addr = 0x0U; addr < 0x3FFFU; addr++)
    {
        data = main_bus.read(addr);
        uint8_t wr = dist(gen);
        main_bus.write(addr, wr);
        data = main_bus.read(addr);
        REQUIRE(data == wr);
    }
}

TEST_CASE("Basic ROM load", "[rom]")
{
    LOG(INFO, "Basic ROM load.");
    RomLoader             rl;
    ROM                   rom("ROM", 0x1000U);
    PictureProcessingUnit ppu;
    rl.load_from_file(
        "/Users/panc/development/nes-emulator/roms/nes-test-roms/other/apocalypse.nes",
        rom,
        ppu);
    INesHeader header = rl.getINesHeader();
}

TEST_CASE("LDA Immediate", "[cpu][instructions]")
{
}

TEST_CASE("STA Zero Page", "[cpu][instructions]")
{
}