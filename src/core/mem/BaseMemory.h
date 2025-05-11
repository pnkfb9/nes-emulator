#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include <array>
#include <cstdint>
template <size_t N>
class BaseMemory
{
public:
    BaseMemory();
    virtual ~BaseMemory() = 0;
    virtual void    write(uint16_t addr, uint8_t data) = 0;
    virtual uint8_t read(uint16_t addr) = 0;
    void            clear() { m_memory.fill(0x0U); }
    size_t          size() const { return N; }

protected:
    std::array<uint8_t, N> m_memory;
};
#endif