#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#define MEM_SIZE_6502 (1<<16)   //64K
class Memory{

    public:
        Memory();
        ~Memory() = default;
        void write(uint16_t addr,uint8_t data);
        uint8_t read(uint16_t addr);

    private:
        uint8_t m_memory[MEM_SIZE_6502];
};
#endif