#include "core/mem/BaseMemory.h"

#include "core/log/Logger.h"

BaseMemory::BaseMemory(size_t size) : m_memory(size, 0x0U), m_size(size)
{
    LOG(DEBUG, "Init");
    m_memory.reserve(size);
}

BaseMemory::~BaseMemory()
{
}

uint8_t BaseMemory::read(uint16_t addr)
{
    uint8_t data = m_memory[addr];
    LOG(DEBUG, "Read 0x{:x} at address 0x{:x}", data, addr);
    return data;
}

void BaseMemory::write(uint16_t addr, uint8_t data)
{
    LOG(DEBUG, "Write 0x{:x} at address 0x{:x}", data, addr);
    m_memory[addr] = data;
}

void BaseMemory::clear()
{
    m_memory.clear();
}

unsigned BaseMemory::size()
{
    return m_size;
}