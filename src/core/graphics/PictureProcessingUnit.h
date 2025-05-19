#ifndef PICTURE_PROCESSING_UNIT_H
#define PICTURE_PROCESSING_UNIT_H
#include "core/common/Peripheral.h"
// addresses for the PPU registers
enum PPURegisterMap
{
    PPUCTRL = 0x2000U,
    PPUMASK,
    PPUSTATUS,
    OAMADDR,
    OAMDATA,
    PPUSCROLL,
    PPUADDR,
    PPUDATA
};
class PictureProcessingUnit : public Peripheral
{
public:
    PictureProcessingUnit(std::string_view name = "PPU", size_t size = 0x3FFFU);
    ~PictureProcessingUnit() override = default;
    bool address_in_range(uint16_t addr) const override;
    void load(std::vector<uint8_t> data);

private:
};
#endif