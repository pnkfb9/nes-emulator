#include "core/graphics/PictureProcessingUnit.h"

PictureProcessingUnit::PictureProcessingUnit(std::string_view name, size_t size)
    : Peripheral(name, size)
{
}
bool PictureProcessingUnit::address_in_range(uint16_t addr) const
{
    (void)addr;
    return true;
}