#include "Memory.h"

#include "core/log/Logger.h"

Memory::Memory()
{
    LOG(DEBUG, "Memory Init");
}

void Memory::write(uint16_t addr, uint8_t data)
{
    m_memory[addr] = data;
}

uint8_t Memory::read(uint16_t addr)
{
    return m_memory[addr];
}