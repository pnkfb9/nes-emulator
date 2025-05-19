#include "core/common/Peripheral.h"

#include "core/log/Logger.h"
Peripheral::Peripheral(std::string_view name, size_t mem_size) : BaseMemory(mem_size)
{
    LOG(DEBUG, "{} Init", name);
}