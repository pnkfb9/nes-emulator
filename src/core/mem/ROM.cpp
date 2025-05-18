#include "core/mem/ROM.h"

ROM::ROM(std::string_view name, size_t memory_size) : Peripheral(name, memory_size)
{
}

bool ROM::address_in_range(uint16_t addr) const
{
    (void)addr;
    return true;
}
void ROM::write(uint16_t addr, uint8_t data)
{
    (void)addr;
    (void)data;
    throw std::runtime_error("Attempt to write to ROM!");
}

bool ROM::load_from_file(const std::string& path)
{
    return true;
}