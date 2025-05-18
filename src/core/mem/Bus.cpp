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
    for (auto& device : devices)
    {
        if (in_range(addr, device.first, device.second->size()))
        {
            uint16_t base_addr = addr - device.first;
            if (device.second->address_in_range(base_addr))
            {
                return device.second->read(base_addr);
            }
        }
    }
    throw std::out_of_range("Failed to read at address " + std::to_string(addr));
}
void Bus::write(uint16_t addr, uint8_t data)
{
    for (auto& device : devices)
    {
        if (in_range(addr, device.first, device.second->size()))
        {
            uint16_t base_addr = addr - device.first;
            if (device.second->address_in_range(base_addr))
            {
                device.second->write(base_addr, data);
                return;
            }
        }
    }
    throw std::out_of_range("Write failed at address " + std::to_string(addr));
}
void Bus::registerDevice(std::unique_ptr<Peripheral> device, uint16_t start_addr)
{
    assert(!devices.count(start_addr));
    devices[start_addr] = std::move(device);
}
