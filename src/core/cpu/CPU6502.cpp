#include "CPU6502.h"

#include "core/cpu/InstructionSet.h"
#include "core/log/Logger.h"

CPU6502::CPU6502()
{
    LOG(DEBUG, "CPU init");
    this->reset();
}

void CPU6502::reset()
{
    LOG(DEBUG, "CPU reset");
    m_registers.reset();
}

void CPU6502::step()
{
    // fetch, decode and execute goes in here
    uint8_t           opcode = fetch();
    const Instruction inst = decode(opcode);
    execute(inst); // PC increment will go here
}
void CPU6502::interrupt(uint16_t vector)
{
}

uint8_t CPU6502::fetch()
{
    return m_memory.read(m_registers.PC);
}

const Instruction CPU6502::decode(uint8_t opcode)
{
    return INSTRUCTIONS[opcode];
}

void CPU6502::execute(const Instruction& instruction)
{
}