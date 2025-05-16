#include "core/mem/Bus.h"

#include <cassert>

#include "core/log/Logger.h"

static bool in_range(uint16_t address, uint16_t start_address, unsigned size)
{
    return (address >= start_address && address <= start_address + size);
}

Bus::Bus(std::string_view name) : name(name)
{
    LOG(DEBUG, "Init");
}

uint8_t Bus::read(uint16_t addr)
{
    bool    done = false;
    uint8_t res = 0x0U;
    for (auto& device : devices)
    {
        if (in_range(addr, device.first, device.second.size()))
        {
            res = device.second.read(addr - device.first);
            done = true;
        }
    }
    assert(done);
    return res;
}
void Bus::write(uint16_t addr, uint8_t data)
{
    bool done = false;
    for (auto& device : devices)
    {
        if (in_range(addr, device.first, device.second.size()))
        {
            device.second.write(addr - device.first, data);
            done = true;
        }
    }
    assert(done);
}
void Bus::registerDevice(Memory& device, uint16_t start_addr)
{
    assert(!devices.count(start_addr));
    auto element = std::make_pair(start_addr, device);
    devices.insert(element);
}
