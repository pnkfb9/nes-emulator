#ifndef BUS_H
#define BUS_H
#include <cstdint>
#include <unordered_map>

#include "core/common/Peripheral.h"
class Bus
{
public:
    Bus() {};
    Bus(std::string_view name);
    // Delete copy operations
    Bus(const Bus&) = delete;
    Bus& operator=(const Bus&) = delete;

    // Allow move operations
    Bus(Bus&&) = default;
    Bus&     operator=(Bus&&) = default;
    uint8_t  read(uint16_t addr);
    void     write(uint16_t addr, uint8_t data);
    void     registerDevice(std::unique_ptr<Peripheral> device, uint16_t start_addr);
    uint16_t translate_address(uint16_t address);

private:
    std::string_view                                          name;
    std::unordered_map<uint16_t, std::unique_ptr<Peripheral>> devices;
};

#endif