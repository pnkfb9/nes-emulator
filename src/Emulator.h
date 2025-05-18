#ifndef EMULATOR_H
#define EMULATOR_H

#include <memory>
class CPU6502;
class PictureProcessingUnit;
class AudioProcessingUnit;
class RAM;
class ROM;
class Bus;
class Emulator
{
public:
    Emulator();

private:
    std::unique_ptr<CPU6502>               m_cpu;
    std::unique_ptr<PictureProcessingUnit> m_ppu;
    std::unique_ptr<AudioProcessingUnit>   m_apu;
    std::unique_ptr<RAM>                   m_ram;
    std::unique_ptr<ROM>                   m_rom;
    std::shared_ptr<Bus>                   m_main_bus;
};

#endif