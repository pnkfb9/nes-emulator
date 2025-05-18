#ifndef PERIPHERAL_H
#define PERIPHERAL_H
#include <string_view>

#include "core/mem/BaseMemory.h"

class Peripheral : public BaseMemory
{
public:
    Peripheral(std::string_view name, size_t mem_size);
    virtual ~Peripheral() = default;
    // virtual uint8_t read(uint16_t addr);
    // virtual void    write(uint16_t addr, uint8_t data);
    // virtual void    reset();
    // size_t          memory_size();
    virtual bool address_in_range(uint16_t addr) const = 0;

protected:
    std::string_view m_name;
};

#endif