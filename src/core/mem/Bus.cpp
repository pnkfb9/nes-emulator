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
    uint16_t real_addr = translate_address(addr);
    LOG(DEBUG, "read address: {}, translated address: {}", addr, real_addr);
    for (auto& device : devices)
    {
        if (in_range(real_addr, device.first, device.second->size()))
        {
            return device.second->read(real_addr - device.first);
        }
    }
    throw std::out_of_range("Failed to read at address " + std::to_string(addr));
}
void Bus::write(uint16_t addr, uint8_t data)
{
    uint16_t real_addr = translate_address(addr);
    LOG(DEBUG, "write address: {}, translated address: {}", addr, real_addr);
    for (auto& device : devices)
    {
        if (in_range(real_addr, device.first, device.second->size()))
        {
            uint16_t base_addr = real_addr - device.first;
            device.second->write(base_addr, data);
            return;
        }
    }
    throw std::out_of_range("Write failed at address " + std::to_string(addr));
}
void Bus::registerDevice(std::unique_ptr<Peripheral> device, uint16_t start_addr)
{
    assert(!devices.count(start_addr));
    devices[start_addr] = std::move(device);
}

uint16_t Bus::translate_address(uint16_t address)
{
    if (address <= 0x1FFFU) // RAM or mirrors of RAM
    {
        return address & 0x07FFU;
    }
    else if (address <= 0x3FFFU) // PPU registers or mirrors
    {
        return address & 0x2007U;
    }
    return address;
}
