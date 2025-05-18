#include "core/common/Peripheral.h"

#include "core/log/Logger.h"
Peripheral::Peripheral(std::string_view name, size_t mem_size) : BaseMemory(mem_size)
{
    LOG(DEBUG, "{} Init", name);
}
/*
uint8_t Peripheral::read(uint16_t addr)
{
    return read(addr);
}
void Peripheral::write(uint16_t addr, uint8_t data)
{
    write(addr, data);
}

void Peripheral::reset()
{
    clear();
}

size_t Peripheral::memory_size()
{
    return m_base_memory.size();
}*/