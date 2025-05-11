#include "core/mem/Memory.h"

#include "core/log/Logger.h"

template <size_t N>
Memory<N>::Memory(std::string_view name)
{
    LOG(DEBUG, "[{}] Memory Init", name);
    this->name = name;
    this->clear();
}

template <size_t N>
Memory<N>::~Memory()
{
}

template <size_t N>
uint8_t Memory<N>::read(uint16_t addr)
{
    uint8_t data = this->m_memory[addr];
    LOG(DEBUG, "[{}] Read 0x{:x} at address 0x{:x}", name, data, addr);
    return data;
}

template <size_t N>
void Memory<N>::write(uint16_t addr, uint8_t data)
{
    LOG(DEBUG, "[{}] Write 0x{:x} at address 0x{:x}", name, data, addr);
    this->m_memory[addr] = data;
}