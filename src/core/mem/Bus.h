#ifndef BUS_H
#define BUS_H
#include <cstdint>
#include <map>

#include "core/mem/Memory.h"
class Bus
{
public:
    Bus() {};
    Bus(std::string_view name);
    uint8_t read(uint16_t addr);
    void    write(uint16_t addr, uint8_t data);
    void    registerDevice(Memory& device, uint16_t start_addr);

private:
    std::string_view           name;
    std::map<unsigned, Memory> devices;
};

#endif