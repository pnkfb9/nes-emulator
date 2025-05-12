#include "core/mem/Bus.h"

#include "core/log/Logger.h"

Bus::Bus(std::string_view name)
{
    LOG(DEBUG, "[{}] Init");
}
uint8_t Bus::read(uint16_t addr)
{
    return 0;
}
void Bus::write(uint16_t addr, uint8_t data)
{
}
void Bus::registerDevice(Memory& device, uint16_t start_addr)
{
}
bool Bus::check_address(uint16_t address)
{
    return true;
}