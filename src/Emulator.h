#ifndef EMULATOR_H
#define EMULATOR_H
#include "core/audio/AudioProcessingUnit.h"
#include "core/cpu/CPU6502.h"
#include "core/graphics/PictureProcessingUnit.h"
#include "core/mem/Bus.h"
#include "core/mem/Memory.h"
class Emulator
{
public:
    Emulator();

private:
    CPU6502               cpu;
    PictureProcessingUnit ppu;
    AudioProcessingUnit   apu;
    Memory<2048>          ram;
    Memory<524288>        rom;
    Bus                   main_bus;
};

#endif