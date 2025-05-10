#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H
#include <array>
#include <cstdint>
#include <string_view>

enum class Opcode : uint8_t
{
    BRK = 0x00,
    ORA_INDX = 0x01,
    KIL = 0x02,      // Undocumented (halts CPU)
    SLO_INDX = 0x03, // Undocumented (ASL + ORA)
    NOP_ZP = 0x04,   // Undocumented
    ORA_ZP = 0x05,
    ASL_ZP = 0x06,
    SLO_ZP = 0x07, // Undocumented
    PHP = 0x08,
    ORA_IMM = 0x09,
    ASL_ACC = 0x0A,
    ANC_IMM = 0x0B, // Undocumented (AND + C flag)
    NOP_ABS = 0x0C, // Undocumented
    ORA_ABS = 0x0D,
    ASL_ABS = 0x0E,
    SLO_ABS = 0x0F, // Undocumented

    BPL = 0x10,
    ORA_INDY = 0x11,
    KIL_2 = 0x12,    // Undocumented (halts CPU)
    SLO_INDY = 0x13, // Undocumented
    NOP_ZPX = 0x14,  // Undocumented
    ORA_ZPX = 0x15,
    ASL_ZPX = 0x16,
    SLO_ZPX = 0x17, // Undocumented
    CLC = 0x18,
    ORA_ABSY = 0x19,
    NOP_IMPL = 0x1A, // Undocumented
    SLO_ABSY = 0x1B, // Undocumented
    NOP_ABSX = 0x1C, // Undocumented
    ORA_ABSX = 0x1D,
    ASL_ABSX = 0x1E,
    SLO_ABSX = 0x1F, // Undocumented

    JSR = 0x20,
    AND_INDX = 0x21,
    KIL_3 = 0x22,    // Undocumented (halts CPU)
    RLA_INDX = 0x23, // Undocumented (ROL + AND)
    BIT_ZP = 0x24,
    AND_ZP = 0x25,
    ROL_ZP = 0x26,
    RLA_ZP = 0x27, // Undocumented
    PLP = 0x28,
    AND_IMM = 0x29,
    ROL_ACC = 0x2A,
    ANC_IMM_2 = 0x2B, // Undocumented (AND + C flag)
    BIT_ABS = 0x2C,
    AND_ABS = 0x2D,
    ROL_ABS = 0x2E,
    RLA_ABS = 0x2F, // Undocumented

    BMI = 0x30,
    AND_INDY = 0x31,
    KIL_4 = 0x32,     // Undocumented (halts CPU)
    RLA_INDY = 0x33,  // Undocumented
    NOP_ZPX_2 = 0x34, // Undocumented
    AND_ZPX = 0x35,
    ROL_ZPX = 0x36,
    RLA_ZPX = 0x37, // Undocumented
    SEC = 0x38,
    AND_ABSY = 0x39,
    NOP_IMPL_2 = 0x3A, // Undocumented
    RLA_ABSY = 0x3B,   // Undocumented
    NOP_ABSX_2 = 0x3C, // Undocumented
    AND_ABSX = 0x3D,
    ROL_ABSX = 0x3E,
    RLA_ABSX = 0x3F, // Undocumented

    RTI = 0x40,
    EOR_INDX = 0x41,
    KIL_5 = 0x42,    // Undocumented (halts CPU)
    SRE_INDX = 0x43, // Undocumented (LSR + EOR)
    NOP_ZP_2 = 0x44, // Undocumented
    EOR_ZP = 0x45,
    LSR_ZP = 0x46,
    SRE_ZP = 0x47, // Undocumented
    PHA = 0x48,
    EOR_IMM = 0x49,
    LSR_ACC = 0x4A,
    ALR_IMM = 0x4B, // Undocumented (AND + LSR)
    JMP_ABS = 0x4C,
    EOR_ABS = 0x4D,
    LSR_ABS = 0x4E,
    SRE_ABS = 0x4F, // Undocumented

    BVC = 0x50,
    EOR_INDY = 0x51,
    KIL_6 = 0x52,     // Undocumented (halts CPU)
    SRE_INDY = 0x53,  // Undocumented
    NOP_ZPX_3 = 0x54, // Undocumented
    EOR_ZPX = 0x55,
    LSR_ZPX = 0x56,
    SRE_ZPX = 0x57, // Undocumented
    CLI = 0x58,
    EOR_ABSY = 0x59,
    NOP_IMPL_3 = 0x5A, // Undocumented
    SRE_ABSY = 0x5B,   // Undocumented
    NOP_ABSX_3 = 0x5C, // Undocumented
    EOR_ABSX = 0x5D,
    LSR_ABSX = 0x5E,
    SRE_ABSX = 0x5F, // Undocumented

    RTS = 0x60,
    ADC_INDX = 0x61,
    KIL_7 = 0x62,    // Undocumented (halts CPU)
    RRA_INDX = 0x63, // Undocumented (ROR + ADC)
    NOP_ZP_3 = 0x64, // Undocumented
    ADC_ZP = 0x65,
    ROR_ZP = 0x66,
    RRA_ZP = 0x67, // Undocumented
    PLA = 0x68,
    ADC_IMM = 0x69,
    ROR_ACC = 0x6A,
    ARR_IMM = 0x6B, // Undocumented (AND + ROR)
    JMP_IND = 0x6C,
    ADC_ABS = 0x6D,
    ROR_ABS = 0x6E,
    RRA_ABS = 0x6F, // Undocumented

    BVS = 0x70,
    ADC_INDY = 0x71,
    KIL_8 = 0x72,     // Undocumented (halts CPU)
    RRA_INDY = 0x73,  // Undocumented
    NOP_ZPX_4 = 0x74, // Undocumented
    ADC_ZPX = 0x75,
    ROR_ZPX = 0x76,
    RRA_ZPX = 0x77, // Undocumented
    SEI = 0x78,
    ADC_ABSY = 0x79,
    NOP_IMPL_4 = 0x7A, // Undocumented
    RRA_ABSY = 0x7B,   // Undocumented
    NOP_ABSX_4 = 0x7C, // Undocumented
    ADC_ABSX = 0x7D,
    ROR_ABSX = 0x7E,
    RRA_ABSX = 0x7F, // Undocumented

    NOP_IMM = 0x80, // Undocumented
    STA_INDX = 0x81,
    NOP_IMM_2 = 0x82, // Undocumented
    SAX_INDX = 0x83,  // Undocumented (STA + STX)
    STY_ZP = 0x84,
    STA_ZP = 0x85,
    STX_ZP = 0x86,
    SAX_ZP = 0x87, // Undocumented
    DEY = 0x88,
    NOP_IMM_3 = 0x89, // Undocumented
    TXA = 0x8A,
    XAA_IMM = 0x8B, // Undocumented (TXA + AND)
    STY_ABS = 0x8C,
    STA_ABS = 0x8D,
    STX_ABS = 0x8E,
    SAX_ABS = 0x8F, // Undocumented

    BCC = 0x90,
    STA_INDY = 0x91,
    KIL_9 = 0x92,    // Undocumented (halts CPU)
    AHX_INDY = 0x93, // Undocumented (STA + STX)
    STY_ZPX = 0x94,
    STA_ZPX = 0x95,
    STX_ZPY = 0x96,
    SAX_ZPY = 0x97, // Undocumented
    TYA = 0x98,
    STA_ABSY = 0x99,
    TXS = 0x9A,
    TAS_ABSY = 0x9B, // Undocumented (STA + STX + SP)
    SHY_ABSX = 0x9C, // Undocumented (STA + STY)
    STA_ABSX = 0x9D,
    SHX_ABSY = 0x9E, // Undocumented (STA + STX)
    AHX_ABSY = 0x9F, // Undocumented (STA + STX + STY)

    LDY_IMM = 0xA0,
    LDA_INDX = 0xA1,
    LDX_IMM = 0xA2,
    LAX_INDX = 0xA3, // Undocumented (LDA + LDX)
    LDY_ZP = 0xA4,
    LDA_ZP = 0xA5,
    LDX_ZP = 0xA6,
    LAX_ZP = 0xA7, // Undocumented
    TAY = 0xA8,
    LDA_IMM = 0xA9,
    TAX = 0xAA,
    LAX_IMM = 0xAB, // Undocumented (LDA + LDX)
    LDY_ABS = 0xAC,
    LDA_ABS = 0xAD,
    LDX_ABS = 0xAE,
    LAX_ABS = 0xAF, // Undocumented

    BCS = 0xB0,
    LDA_INDY = 0xB1,
    KIL_10 = 0xB2,   // Undocumented (halts CPU)
    LAX_INDY = 0xB3, // Undocumented
    LDY_ZPX = 0xB4,
    LDA_ZPX = 0xB5,
    LDX_ZPY = 0xB6,
    LAX_ZPY = 0xB7, // Undocumented
    CLV = 0xB8,
    LDA_ABSY = 0xB9,
    TSX = 0xBA,
    LAS_ABSY = 0xBB, // Undocumented (LDA + TSX)
    LDY_ABSX = 0xBC,
    LDA_ABSX = 0xBD,
    LDX_ABSY = 0xBE,
    LAX_ABSY = 0xBF, // Undocumented

    CPY_IMM = 0xC0,
    CMP_INDX = 0xC1,
    NOP_IMM_4 = 0xC2, // Undocumented
    DCP_INDX = 0xC3,  // Undocumented (DEC + CMP)
    CPY_ZP = 0xC4,
    CMP_ZP = 0xC5,
    DEC_ZP = 0xC6,
    DCP_ZP = 0xC7, // Undocumented
    INY = 0xC8,
    CMP_IMM = 0xC9,
    DEX = 0xCA,
    SBX_IMM = 0xCB, // Undocumented (CMP + DEX)
    CPY_ABS = 0xCC,
    CMP_ABS = 0xCD,
    DEC_ABS = 0xCE,
    DCP_ABS = 0xCF, // Undocumented

    BNE = 0xD0,
    CMP_INDY = 0xD1,
    KIL_11 = 0xD2,    // Undocumented (halts CPU)
    DCP_INDY = 0xD3,  // Undocumented
    NOP_ZPX_5 = 0xD4, // Undocumented
    CMP_ZPX = 0xD5,
    DEC_ZPX = 0xD6,
    DCP_ZPX = 0xD7, // Undocumented
    CLD = 0xD8,
    CMP_ABSY = 0xD9,
    NOP_IMPL_5 = 0xDA, // Undocumented
    DCP_ABSY = 0xDB,   // Undocumented
    NOP_ABSX_5 = 0xDC, // Undocumented
    CMP_ABSX = 0xDD,
    DEC_ABSX = 0xDE,
    DCP_ABSX = 0xDF, // Undocumented

    CPX_IMM = 0xE0,
    SBC_INDX = 0xE1,
    NOP_IMM_5 = 0xE2, // Undocumented
    ISC_INDX = 0xE3,  // Undocumented (INC + SBC)
    CPX_ZP = 0xE4,
    SBC_ZP = 0xE5,
    INC_ZP = 0xE6,
    ISC_ZP = 0xE7, // Undocumented
    INX = 0xE8,
    SBC_IMM = 0xE9,
    NOP = 0xEA,
    SBC_IMM_2 = 0xEB, // Undocumented (alternate SBC)
    CPX_ABS = 0xEC,
    SBC_ABS = 0xED,
    INC_ABS = 0xEE,
    ISC_ABS = 0xEF, // Undocumented

    BEQ = 0xF0,
    SBC_INDY = 0xF1,
    KIL_12 = 0xF2,    // Undocumented (halts CPU)
    ISC_INDY = 0xF3,  // Undocumented
    NOP_ZPX_6 = 0xF4, // Undocumented
    SBC_ZPX = 0xF5,
    INC_ZPX = 0xF6,
    ISC_ZPX = 0xF7, // Undocumented
    SED = 0xF8,
    SBC_ABSY = 0xF9,
    NOP_IMPL_6 = 0xFA, // Undocumented
    ISC_ABSY = 0xFB,   // Undocumented
    NOP_ABSX_6 = 0xFC, // Undocumented
    SBC_ABSX = 0xFD,
    INC_ABSX = 0xFE,
    ISC_ABSX = 0xFF // Undocumented
};

enum class AddrMode : uint8_t
{
    IMPL,
    ACC,
    IMM,
    ZP,
    ZPX,
    ZPY,
    ABS,
    ABSX,
    ABSY,
    IND,
    INDX,
    INDY,
    REL
};

struct Instruction
{
    std::string_view mnemonic;
    bool             undocumented;
    uint8_t          size;
    uint8_t          base_cycles;
    uint8_t          page_cross_penalty;
    AddrMode         mode;
};

constexpr auto INSTRUCTIONS =
    std::array<Instruction, 256>{{/* 0x00 */ {"BRK", false, 1, 7, 0, AddrMode::IMPL},
                                  /* 0x01 */ {"ORA", false, 2, 6, 0, AddrMode::INDX},
                                  /* 0x02 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x03 */ {"SLO", true, 2, 8, 0, AddrMode::INDX},
                                  /* 0x04 */ {"NOP", true, 2, 3, 0, AddrMode::ZP},
                                  /* 0x05 */ {"ORA", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0x06 */ {"ASL", false, 2, 5, 0, AddrMode::ZP},
                                  /* 0x07 */ {"SLO", true, 2, 5, 0, AddrMode::ZP},
                                  /* 0x08 */ {"PHP", false, 1, 3, 0, AddrMode::IMPL},
                                  /* 0x09 */ {"ORA", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0x0A */ {"ASL", false, 1, 2, 0, AddrMode::ACC},
                                  /* 0x0B */ {"ANC", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0x0C */ {"NOP", true, 3, 4, 0, AddrMode::ABS},
                                  /* 0x0D */ {"ORA", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0x0E */ {"ASL", false, 3, 6, 0, AddrMode::ABS},
                                  /* 0x0F */ {"SLO", true, 3, 6, 0, AddrMode::ABS},

                                  /* 0x10 */ {"BPL", false, 2, 2, 1, AddrMode::REL},
                                  /* 0x11 */ {"ORA", false, 2, 5, 1, AddrMode::INDY},
                                  /* 0x12 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x13 */ {"SLO", true, 2, 8, 1, AddrMode::INDY},
                                  /* 0x14 */ {"NOP", true, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x15 */ {"ORA", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x16 */ {"ASL", false, 2, 6, 0, AddrMode::ZPX},
                                  /* 0x17 */ {"SLO", true, 2, 6, 0, AddrMode::ZPX},
                                  /* 0x18 */ {"CLC", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x19 */ {"ORA", false, 3, 4, 1, AddrMode::ABSY},
                                  /* 0x1A */ {"NOP", true, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x1B */ {"SLO", true, 3, 7, 1, AddrMode::ABSY},
                                  /* 0x1C */ {"NOP", true, 3, 4, 1, AddrMode::ABSX},
                                  /* 0x1D */ {"ORA", false, 3, 4, 1, AddrMode::ABSX},
                                  /* 0x1E */ {"ASL", false, 3, 7, 0, AddrMode::ABSX},
                                  /* 0x1F */ {"SLO", true, 3, 7, 1, AddrMode::ABSX},

                                  /* 0x20 */ {"JSR", false, 3, 6, 0, AddrMode::ABS},
                                  /* 0x21 */ {"AND", false, 2, 6, 0, AddrMode::INDX},
                                  /* 0x22 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x23 */ {"RLA", true, 2, 8, 0, AddrMode::INDX},
                                  /* 0x24 */ {"BIT", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0x25 */ {"AND", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0x26 */ {"ROL", false, 2, 5, 0, AddrMode::ZP},
                                  /* 0x27 */ {"RLA", true, 2, 5, 0, AddrMode::ZP},
                                  /* 0x28 */ {"PLP", false, 1, 4, 0, AddrMode::IMPL},
                                  /* 0x29 */ {"AND", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0x2A */ {"ROL", false, 1, 2, 0, AddrMode::ACC},
                                  /* 0x2B */ {"ANC", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0x2C */ {"BIT", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0x2D */ {"AND", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0x2E */ {"ROL", false, 3, 6, 0, AddrMode::ABS},
                                  /* 0x2F */ {"RLA", true, 3, 6, 0, AddrMode::ABS},

                                  /* 0x30 */ {"BMI", false, 2, 2, 1, AddrMode::REL},
                                  /* 0x31 */ {"AND", false, 2, 5, 1, AddrMode::INDY},
                                  /* 0x32 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x33 */ {"RLA", true, 2, 8, 1, AddrMode::INDY},
                                  /* 0x34 */ {"NOP", true, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x35 */ {"AND", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x36 */ {"ROL", false, 2, 6, 0, AddrMode::ZPX},
                                  /* 0x37 */ {"RLA", true, 2, 6, 0, AddrMode::ZPX},
                                  /* 0x38 */ {"SEC", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x39 */ {"AND", false, 3, 4, 1, AddrMode::ABSY},
                                  /* 0x3A */ {"NOP", true, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x3B */ {"RLA", true, 3, 7, 1, AddrMode::ABSY},
                                  /* 0x3C */ {"NOP", true, 3, 4, 1, AddrMode::ABSX},
                                  /* 0x3D */ {"AND", false, 3, 4, 1, AddrMode::ABSX},
                                  /* 0x3E */ {"ROL", false, 3, 7, 0, AddrMode::ABSX},
                                  /* 0x3F */ {"RLA", true, 3, 7, 1, AddrMode::ABSX},

                                  /* 0x40 */ {"RTI", false, 1, 6, 0, AddrMode::IMPL},
                                  /* 0x41 */ {"EOR", false, 2, 6, 0, AddrMode::INDX},
                                  /* 0x42 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x43 */ {"SRE", true, 2, 8, 0, AddrMode::INDX},
                                  /* 0x44 */ {"NOP", true, 2, 3, 0, AddrMode::ZP},
                                  /* 0x45 */ {"EOR", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0x46 */ {"LSR", false, 2, 5, 0, AddrMode::ZP},
                                  /* 0x47 */ {"SRE", true, 2, 5, 0, AddrMode::ZP},
                                  /* 0x48 */ {"PHA", false, 1, 3, 0, AddrMode::IMPL},
                                  /* 0x49 */ {"EOR", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0x4A */ {"LSR", false, 1, 2, 0, AddrMode::ACC},
                                  /* 0x4B */ {"ALR", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0x4C */ {"JMP", false, 3, 3, 0, AddrMode::ABS},
                                  /* 0x4D */ {"EOR", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0x4E */ {"LSR", false, 3, 6, 0, AddrMode::ABS},
                                  /* 0x4F */ {"SRE", true, 3, 6, 0, AddrMode::ABS},

                                  /* 0x50 */ {"BVC", false, 2, 2, 1, AddrMode::REL},
                                  /* 0x51 */ {"EOR", false, 2, 5, 1, AddrMode::INDY},
                                  /* 0x52 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x53 */ {"SRE", true, 2, 8, 1, AddrMode::INDY},
                                  /* 0x54 */ {"NOP", true, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x55 */ {"EOR", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x56 */ {"LSR", false, 2, 6, 0, AddrMode::ZPX},
                                  /* 0x57 */ {"SRE", true, 2, 6, 0, AddrMode::ZPX},
                                  /* 0x58 */ {"CLI", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x59 */ {"EOR", false, 3, 4, 1, AddrMode::ABSY},
                                  /* 0x5A */ {"NOP", true, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x5B */ {"SRE", true, 3, 7, 1, AddrMode::ABSY},
                                  /* 0x5C */ {"NOP", true, 3, 4, 1, AddrMode::ABSX},
                                  /* 0x5D */ {"EOR", false, 3, 4, 1, AddrMode::ABSX},
                                  /* 0x5E */ {"LSR", false, 3, 7, 0, AddrMode::ABSX},
                                  /* 0x5F */ {"SRE", true, 3, 7, 1, AddrMode::ABSX},

                                  /* 0x60 */ {"RTS", false, 1, 6, 0, AddrMode::IMPL},
                                  /* 0x61 */ {"ADC", false, 2, 6, 0, AddrMode::INDX},
                                  /* 0x62 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x63 */ {"RRA", true, 2, 8, 0, AddrMode::INDX},
                                  /* 0x64 */ {"NOP", true, 2, 3, 0, AddrMode::ZP},
                                  /* 0x65 */ {"ADC", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0x66 */ {"ROR", false, 2, 5, 0, AddrMode::ZP},
                                  /* 0x67 */ {"RRA", true, 2, 5, 0, AddrMode::ZP},
                                  /* 0x68 */ {"PLA", false, 1, 4, 0, AddrMode::IMPL},
                                  /* 0x69 */ {"ADC", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0x6A */ {"ROR", false, 1, 2, 0, AddrMode::ACC},
                                  /* 0x6B */ {"ARR", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0x6C */ {"JMP", false, 3, 5, 0, AddrMode::IND},
                                  /* 0x6D */ {"ADC", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0x6E */ {"ROR", false, 3, 6, 0, AddrMode::ABS},
                                  /* 0x6F */ {"RRA", true, 3, 6, 0, AddrMode::ABS},

                                  /* 0x70 */ {"BVS", false, 2, 2, 1, AddrMode::REL},
                                  /* 0x71 */ {"ADC", false, 2, 5, 1, AddrMode::INDY},
                                  /* 0x72 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x73 */ {"RRA", true, 2, 8, 1, AddrMode::INDY},
                                  /* 0x74 */ {"NOP", true, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x75 */ {"ADC", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x76 */ {"ROR", false, 2, 6, 0, AddrMode::ZPX},
                                  /* 0x77 */ {"RRA", true, 2, 6, 0, AddrMode::ZPX},
                                  /* 0x78 */ {"SEI", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x79 */ {"ADC", false, 3, 4, 1, AddrMode::ABSY},
                                  /* 0x7A */ {"NOP", true, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x7B */ {"RRA", true, 3, 7, 1, AddrMode::ABSY},
                                  /* 0x7C */ {"NOP", true, 3, 4, 1, AddrMode::ABSX},
                                  /* 0x7D */ {"ADC", false, 3, 4, 1, AddrMode::ABSX},
                                  /* 0x7E */ {"ROR", false, 3, 7, 0, AddrMode::ABSX},
                                  /* 0x7F */ {"RRA", true, 3, 7, 1, AddrMode::ABSX},

                                  /* 0x80 */ {"NOP", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0x81 */ {"STA", false, 2, 6, 0, AddrMode::INDX},
                                  /* 0x82 */ {"NOP", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0x83 */ {"SAX", true, 2, 6, 0, AddrMode::INDX},
                                  /* 0x84 */ {"STY", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0x85 */ {"STA", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0x86 */ {"STX", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0x87 */ {"SAX", true, 2, 3, 0, AddrMode::ZP},
                                  /* 0x88 */ {"DEY", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x89 */ {"NOP", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0x8A */ {"TXA", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x8B */ {"XAA", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0x8C */ {"STY", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0x8D */ {"STA", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0x8E */ {"STX", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0x8F */ {"SAX", true, 3, 4, 0, AddrMode::ABS},

                                  /* 0x90 */ {"BCC", false, 2, 2, 1, AddrMode::REL},
                                  /* 0x91 */ {"STA", false, 2, 6, 0, AddrMode::INDY},
                                  /* 0x92 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0x93 */ {"AHX", true, 2, 6, 0, AddrMode::INDY},
                                  /* 0x94 */ {"STY", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x95 */ {"STA", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0x96 */ {"STX", false, 2, 4, 0, AddrMode::ZPY},
                                  /* 0x97 */ {"SAX", true, 2, 4, 0, AddrMode::ZPY},
                                  /* 0x98 */ {"TYA", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x99 */ {"STA", false, 3, 5, 0, AddrMode::ABSY},
                                  /* 0x9A */ {"TXS", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0x9B */ {"TAS", true, 3, 5, 0, AddrMode::ABSY},
                                  /* 0x9C */ {"SHY", true, 3, 5, 0, AddrMode::ABSX},
                                  /* 0x9D */ {"STA", false, 3, 5, 0, AddrMode::ABSX},
                                  /* 0x9E */ {"SHX", true, 3, 5, 0, AddrMode::ABSY},
                                  /* 0x9F */ {"AHX", true, 3, 5, 0, AddrMode::ABSY},

                                  /* 0xA0 */ {"LDY", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0xA1 */ {"LDA", false, 2, 6, 0, AddrMode::INDX},
                                  /* 0xA2 */ {"LDX", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0xA3 */ {"LAX", true, 2, 6, 0, AddrMode::INDX},
                                  /* 0xA4 */ {"LDY", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0xA5 */ {"LDA", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0xA6 */ {"LDX", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0xA7 */ {"LAX", true, 2, 3, 0, AddrMode::ZP},
                                  /* 0xA8 */ {"TAY", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xA9 */ {"LDA", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0xAA */ {"TAX", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xAB */ {"LAX", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0xAC */ {"LDY", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0xAD */ {"LDA", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0xAE */ {"LDX", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0xAF */ {"LAX", true, 3, 4, 0, AddrMode::ABS},

                                  /* 0xB0 */ {"BCS", false, 2, 2, 1, AddrMode::REL},
                                  /* 0xB1 */ {"LDA", false, 2, 5, 1, AddrMode::INDY},
                                  /* 0xB2 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0xB3 */ {"LAX", true, 2, 5, 1, AddrMode::INDY},
                                  /* 0xB4 */ {"LDY", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0xB5 */ {"LDA", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0xB6 */ {"LDX", false, 2, 4, 0, AddrMode::ZPY},
                                  /* 0xB7 */ {"LAX", true, 2, 4, 0, AddrMode::ZPY},
                                  /* 0xB8 */ {"CLV", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xB9 */ {"LDA", false, 3, 4, 1, AddrMode::ABSY},
                                  /* 0xBA */ {"TSX", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xBB */ {"LAS", true, 3, 4, 1, AddrMode::ABSY},
                                  /* 0xBC */ {"LDY", false, 3, 4, 1, AddrMode::ABSX},
                                  /* 0xBD */ {"LDA", false, 3, 4, 1, AddrMode::ABSX},
                                  /* 0xBE */ {"LDX", false, 3, 4, 1, AddrMode::ABSY},
                                  /* 0xBF */ {"LAX", true, 3, 4, 1, AddrMode::ABSY},

                                  /* 0xC0 */ {"CPY", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0xC1 */ {"CMP", false, 2, 6, 0, AddrMode::INDX},
                                  /* 0xC2 */ {"NOP", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0xC3 */ {"DCP", true, 2, 8, 0, AddrMode::INDX},
                                  /* 0xC4 */ {"CPY", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0xC5 */ {"CMP", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0xC6 */ {"DEC", false, 2, 5, 0, AddrMode::ZP},
                                  /* 0xC7 */ {"DCP", true, 2, 5, 0, AddrMode::ZP},
                                  /* 0xC8 */ {"INY", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xC9 */ {"CMP", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0xCA */ {"DEX", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xCB */ {"SBX", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0xCC */ {"CPY", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0xCD */ {"CMP", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0xCE */ {"DEC", false, 3, 6, 0, AddrMode::ABS},
                                  /* 0xCF */ {"DCP", true, 3, 6, 0, AddrMode::ABS},

                                  /* 0xD0 */ {"BNE", false, 2, 2, 1, AddrMode::REL},
                                  /* 0xD1 */ {"CMP", false, 2, 5, 1, AddrMode::INDY},
                                  /* 0xD2 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0xD3 */ {"DCP", true, 2, 8, 1, AddrMode::INDY},
                                  /* 0xD4 */ {"NOP", true, 2, 4, 0, AddrMode::ZPX},
                                  /* 0xD5 */ {"CMP", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0xD6 */ {"DEC", false, 2, 6, 0, AddrMode::ZPX},
                                  /* 0xD7 */ {"DCP", true, 2, 6, 0, AddrMode::ZPX},
                                  /* 0xD8 */ {"CLD", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xD9 */ {"CMP", false, 3, 4, 1, AddrMode::ABSY},
                                  /* 0xDA */ {"NOP", true, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xDB */ {"DCP", true, 3, 7, 1, AddrMode::ABSY},
                                  /* 0xDC */ {"NOP", true, 3, 4, 1, AddrMode::ABSX},
                                  /* 0xDD */ {"CMP", false, 3, 4, 1, AddrMode::ABSX},
                                  /* 0xDE */ {"DEC", false, 3, 7, 0, AddrMode::ABSX},
                                  /* 0xDF */ {"DCP", true, 3, 7, 1, AddrMode::ABSX},

                                  /* 0xE0 */ {"CPX", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0xE1 */ {"SBC", false, 2, 6, 0, AddrMode::INDX},
                                  /* 0xE2 */ {"NOP", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0xE3 */ {"ISC", true, 2, 8, 0, AddrMode::INDX},
                                  /* 0xE4 */ {"CPX", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0xE5 */ {"SBC", false, 2, 3, 0, AddrMode::ZP},
                                  /* 0xE6 */ {"INC", false, 2, 5, 0, AddrMode::ZP},
                                  /* 0xE7 */ {"ISC", true, 2, 5, 0, AddrMode::ZP},
                                  /* 0xE8 */ {"INX", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xE9 */ {"SBC", false, 2, 2, 0, AddrMode::IMM},
                                  /* 0xEA */ {"NOP", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xEB */ {"SBC", true, 2, 2, 0, AddrMode::IMM},
                                  /* 0xEC */ {"CPX", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0xED */ {"SBC", false, 3, 4, 0, AddrMode::ABS},
                                  /* 0xEE */ {"INC", false, 3, 6, 0, AddrMode::ABS},
                                  /* 0xEF */ {"ISC", true, 3, 6, 0, AddrMode::ABS},

                                  /* 0xF0 */ {"BEQ", false, 2, 2, 1, AddrMode::REL},
                                  /* 0xF1 */ {"SBC", false, 2, 5, 1, AddrMode::INDY},
                                  /* 0xF2 */ {"KIL", true, 1, 0, 0, AddrMode::IMPL},
                                  /* 0xF3 */ {"ISC", true, 2, 8, 1, AddrMode::INDY},
                                  /* 0xF4 */ {"NOP", true, 2, 4, 0, AddrMode::ZPX},
                                  /* 0xF5 */ {"SBC", false, 2, 4, 0, AddrMode::ZPX},
                                  /* 0xF6 */ {"INC", false, 2, 6, 0, AddrMode::ZPX},
                                  /* 0xF7 */ {"ISC", true, 2, 6, 0, AddrMode::ZPX},
                                  /* 0xF8 */ {"SED", false, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xF9 */ {"SBC", false, 3, 4, 1, AddrMode::ABSY},
                                  /* 0xFA */ {"NOP", true, 1, 2, 0, AddrMode::IMPL},
                                  /* 0xFB */ {"ISC", true, 3, 7, 1, AddrMode::ABSY},
                                  /* 0xFC */ {"NOP", true, 3, 4, 1, AddrMode::ABSX},
                                  /* 0xFD */ {"SBC", false, 3, 4, 1, AddrMode::ABSX},
                                  /* 0xFE */ {"INC", false, 3, 7, 0, AddrMode::ABSX},
                                  /* 0xFF */ {"ISC", true, 3, 7, 1, AddrMode::ABSX}}};

#endif