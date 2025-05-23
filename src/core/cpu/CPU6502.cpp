#include "CPU6502.h"

#include "core/cpu/InstructionSet.h"
#include "core/log/Logger.h"
#include "core/mem/Bus.h"

CPU6502::CPU6502(std::string_view name) : name(name)
{
    LOG(DEBUG, "Init");
    reset();
}

void CPU6502::reset()
{
    LOG(DEBUG, "Reset");
    m_registers.reset();
}

void CPU6502::step()
{
    LOG(DEBUG, "Step()");
    // fetch, decode and execute goes in here
    uint8_t           opcode = fetch();
    const Instruction inst = decode(opcode);
    execute(inst); // PC increment will go here
}
void CPU6502::interrupt(uint16_t vector)
{
    (void)vector;
}

uint8_t CPU6502::fetch()
{
    return main_bus->read(m_registers.PC);
}

const Instruction CPU6502::decode(uint8_t opcode)
{
    return INSTRUCTIONS[opcode];
}

void CPU6502::execute(const Instruction& instruction)
{
    (void)instruction;
}

void CPU6502::registerBus(std::shared_ptr<Bus> bus)
{
    main_bus = std::move(bus);
}