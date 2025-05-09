#ifndef CPU_6502_H
#define CPU_6502_H

#include <cstdint>
#include "RegisterSet.h"
#include "core/mem/Memory.h"


class CPU6502 {
public:
    CPU6502();
    ~CPU6502() = default;

    void reset(); // Resets the CPU to its initial state
    void step(); // Executes a single clock cycle
    void interrupt(uint16_t vector); //interrupt handling     

private:
    // Registers
    RegisterSet registers;
    //Memory
    Memory memory;
    // Helper functions
    uint8_t fetch();
    void execute(uint8_t opcode);

    // Memory interface
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
};

#endif // CPU_6502_H