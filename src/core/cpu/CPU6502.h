#ifndef CPU_6502_H
#define CPU_6502_H

#include <cstdint>

#include "RegisterSet.h"
// #include "core/mem/Memory.h"

struct Instruction;
class CPU6502
{
public:
    CPU6502();
    ~CPU6502() = default;

    void reset();                    // Resets the CPU to its initial state
    void step();                     // Executes a single clock cycle
    void interrupt(uint16_t vector); // interrupt handling

private:
    // Registers
    RegisterSet m_registers;
    // Memory
    // Memory m_memory;

    // Helper functions
    uint8_t           fetch();
    const Instruction decode(uint8_t opcode);
    void              execute(const Instruction& instruction);
};

#endif // CPU_6502_H