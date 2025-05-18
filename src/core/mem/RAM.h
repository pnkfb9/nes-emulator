#ifndef RAM_H
#define RAM_H

#include "core/common/Peripheral.h"
class RAM : public Peripheral
{
public:
    RAM(std::string_view name, size_t memory_size);
    ~RAM() override = default;
    bool address_in_range(uint16_t addr) const override;
};
#endif