#include "core/audio/AudioProcessingUnit.h"

AudioProcessingUnit::AudioProcessingUnit(std::string_view name, size_t memory_size)
    : Peripheral(name, memory_size)
{
}

bool AudioProcessingUnit::address_in_range(uint16_t addr) const
{
    (void)addr;
    return true; // with the assumption that Bus will route the correct address; Audio unit has only
                 // 18 registers
}