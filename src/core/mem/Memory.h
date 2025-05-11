#ifndef MEMORY_H
#define MEMORY_H
#include <cstddef>
#include <string_view>

#include "core/mem/BaseMemory.h"

template <size_t N>
class Memory : public BaseMemory<N>
{
public:
    Memory(std::string_view name);
    ~Memory();
    uint8_t read(uint16_t addr);
    void    write(uint16_t addr, uint8_t data);

private:
    std::string_view name;
};

#endif