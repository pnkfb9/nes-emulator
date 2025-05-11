#ifndef BUS_H
#define BUS_H
#include <cstdint>
class Bus
{
public:
    Bus();
    uint8_t read(uint16_t addr);
    void    write(uint16_t addr, uint8_t data);
};

#endif