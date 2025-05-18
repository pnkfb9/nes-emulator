#include "core/mem/RAM.h"

RAM::RAM(std::string_view name, size_t memory_size) : Peripheral(name, memory_size)
{
}

bool RAM::address_in_range(uint16_t addr) const
{
    (void)addr;
    return true;
}