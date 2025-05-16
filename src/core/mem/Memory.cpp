#include "core/mem/Memory.h"

#include "core/log/Logger.h"

Memory::Memory(std::string_view name, size_t size) : name(name), m_memory(size, 0x0U), m_size(size)
{
    LOG(DEBUG, "[{}] Init", name);
    m_memory.reserve(size);
}

Memory::~Memory()
{
}

uint8_t Memory::read(uint16_t addr)
{
    uint8_t data = m_memory[addr];
    LOG(DEBUG, "[{}] Read 0x{:x} at address 0x{:x}", name, data, addr);
    return data;
}

void Memory::write(uint16_t addr, uint8_t data)
{
    LOG(DEBUG, "[{}] Write 0x{:x} at address 0x{:x}", name, data, addr);
    m_memory[addr] = data;
}

void Memory::clear()
{
    m_memory.clear();
}

unsigned Memory::size()
{
    return m_size;
}