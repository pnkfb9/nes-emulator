#ifndef REGISTER_SET_H
#define REGISTER_SET_H

#include <cstdint>

enum StatusFlags
{
    C = (1 << 0), // Carry
    Z = (1 << 1), // Zero
    I = (1 << 2), // Interrupt Disable
    D = (1 << 3), // Decimal Mode
    B = (1 << 4), // Break
    U = (1 << 5), // Unused (always 1)
    V = (1 << 6), // Overflow
    N = (1 << 7)  // Negative
};
struct RegisterSet
{
public:
    uint8_t  A;  // Accumulator
    uint8_t  X;  // X Register
    uint8_t  Y;  // Y Register
    uint8_t  SP; // Stack Pointer
    uint16_t PC; // Program Counter
    uint8_t  P;  // Status Register

    void reset()
    {
        A = 0;
        X = 0;
        Y = 0;
        SP = 0;
        PC = 0xFF;
        P = 0;
    }
};

#endif