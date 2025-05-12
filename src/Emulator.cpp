#include "Emulator.h"

#include "core/cpu/CPU6502.h"
#include "core/log/Logger.h"
#include "core/mem/Bus.h"
#include "core/mem/Memory.h"

Emulator::Emulator()
{
    LOG(INFO, "NES EMULATOR \"Aurora\" - copyright 2025");
    LOG(INFO, "Initializing system...");
    m_main_bus = new Bus("main-bus");
    m_ram = new Memory("RAM", 2048);
    m_rom = new Memory("ROM", 40960);
    m_cpu = new CPU6502("CPU_6502");
    m_main_bus->registerDevice(*m_ram, 0x0);
    m_main_bus->registerDevice(*m_rom, 0x4020);
    m_cpu->registerBus(*m_main_bus);
}