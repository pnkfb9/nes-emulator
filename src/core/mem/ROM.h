#ifndef ROM_H
#define ROM_H

#include "core/common/Peripheral.h"
class ROM : public Peripheral
{
public:
    ROM(std::string_view name, size_t memory_size);
    ~ROM() override = default;
    bool address_in_range(uint16_t addr) const override;
    void write(uint16_t addr, uint8_t data);
    void load(std::vector<uint8_t> data);
};
#endif