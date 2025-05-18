#ifndef AUDIO_PROCESSING_UNIT_H
#define AUDIO_PROCESSING_UNIT_H

#include "core/common/Peripheral.h"
class AudioProcessingUnit : public Peripheral
{
public:
    AudioProcessingUnit(std::string_view name, size_t memory_size = 0x17U);
    ~AudioProcessingUnit() override = default;
    bool address_in_range(uint16_t addr) const override;
};
#endif