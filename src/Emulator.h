#ifndef EMULATOR_H
#define EMULATOR_H

class CPU6502;
class PictureProcessingUnit;
class AudioProcessingUnit;
class Memory;
class Bus;
class Emulator
{
public:
    Emulator();

private:
    CPU6502*               m_cpu;
    PictureProcessingUnit* m_ppu;
    AudioProcessingUnit*   m_apu;
    Memory*                m_ram;
    Memory*                m_rom;
    Bus*                   m_main_bus;
};

#endif