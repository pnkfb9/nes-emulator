#include "Emulator.h"

#include "core/audio/AudioProcessingUnit.h"
#include "core/cpu/CPU6502.h"
#include "core/graphics/PictureProcessingUnit.h"
#include "core/log/Logger.h"
#include "core/mem/Bus.h"
#include "core/mem/RAM.h"
#include "core/mem/ROM.h"

Emulator::Emulator()
    : m_cpu(std::make_unique<CPU6502>("2A03"))
    , m_ppu(std::make_unique<PictureProcessingUnit>("2C02"))
    , m_apu(std::make_unique<AudioProcessingUnit>("APU"))
    , m_ram(std::make_unique<RAM>("RAM", 2048))
    , m_rom(std::make_unique<ROM>("ROM", 32768))
    , m_main_bus(std::make_shared<Bus>("Main Bus"))
{
    LOG(INFO, "NES EMULATOR \"Aurora\" - copyright 2025");
    LOG(INFO, "Initializing system...");
}