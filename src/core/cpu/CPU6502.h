#ifndef CPU_6502_H
#define CPU_6502_H

#include <cstdint>
#include <string_view>

#include "RegisterSet.h"
#include "core/mem/Bus.h"

struct Instruction;
class CPU6502
{
public:
    CPU6502(std::string_view name);
    ~CPU6502() = default;

    void reset();                    // Resets the CPU to its initial state
    void step();                     // Executes a single clock cycle
    void interrupt(uint16_t vector); // interrupt handling
    void registerBus(std::shared_ptr<Bus> bus);

private:
    std::string_view name;
    // Registers
    RegisterSet          m_registers;
    std::shared_ptr<Bus> main_bus;
    // Helper functions
    uint8_t           fetch();
    const Instruction decode(uint8_t opcode);
    void              execute(const Instruction& instruction);
};

#endif // CPU_6502_H