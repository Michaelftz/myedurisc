#include "edurisc.h"

/*** CPU OPERATIONS ***/

/* NOP */
void RISC_OP_NOP(RISC_Machine *machine)
{
    return;
}

/* HLT - halts the program, by setting flag bit 0 to true */
void RISC_OP_HLT(RISC_Machine *machine)
{
    machine->options |= 0x01;
    return;
}

/* AND - bitwise AND, does not touch unused bits */
void RISC_OP_AND_X8(RISC_Machine *machine)
{
    uint16_t tX = machine->regs.X | 0xFF00;
    machine->regs.A &= tX;
    return;
}
void RISC_OP_AND_Y8(RISC_Machine *machine)
{
    uint16_t tY = machine->regs.Y | 0xFF00;
    machine->regs.A &= tY;
    return;
}
void RISC_OP_AND_imm8(RISC_Machine *machine)
{
    uint16_t ti = machine->mem[++machine->regs.IP] | 0xFF00;
    machine->regs.A &= ti;
    return;
}
/*void RISC_OP_AND_X16(RISC_Machine *machine)
{
    machine->regs.A &= machine->regs.X;
    return;
}
void RISC_OP_AND_Y16(RISC_Machine *machine)
{
    machine->regs.A &= machine->regs.Y;
    return;
}
void RISC_OP_AND_imm16(RISC_Machine *machine)
{
    uint16_t high = machine->mem[++machine->regs.IP] << 8;
    uint16_t low = machine->mem[++machine->regs.IP];
    machine->regs.A &= (high | low);
    return;
}*/

/* OR - bitwise OR, does not touch unused bits */
void RISC_OP_OR_X8(RISC_Machine *machine)
{
    uint16_t tX = machine->regs.X & 0x00FF;
    machine->regs.A |= tX;
    return;
}
void RISC_OP_OR_Y8(RISC_Machine *machine)
{
    uint16_t tY = machine->regs.Y & 0x00FF;
    machine->regs.A |= tY;
    return;
}
void RISC_OP_OR_imm8(RISC_Machine *machine)
{
    uint16_t ti = machine->mem[++machine->regs.IP] & 0x00FF;
    machine->regs.A |= ti;
    return;
}
/*void RISC_OP_OR_X16(RISC_Machine *machine)
{
    machine->regs.A |= machine->regs.X;
    return;
}
void RISC_OP_OR_Y16(RISC_Machine *machine)
{
    machine->regs.A |= machine->regs.Y;
    return;
}
void RISC_OP_OR_imm16(RISC_Machine *machine)
{
    uint16_t high = machine->mem[++machine->regs.IP] << 8;
    uint16_t low = machine->mem[++machine->regs.IP];
    machine->regs.A |= (high | low);
    return;
}*/

/* ADD - arithmetic addition operation */
void RISC_OP_ADD_X8(RISC_Machine *machine)
{
    uint16_t tA = machine->regs.A & 0x00FF; // clear high bits
    uint16_t tX = machine->regs.X & 0x00FF;
    tA += tX;
    if(tA > 0xFF) // checks for overflow
    {
        machine->regs.CF |= 0x04;
    }
    machine->regs.A &= 0xFF00;
    machine->regs.A |= (tA & 0x00FF);
    return;
}
void RISC_OP_ADD_Y8(RISC_Machine *machine)
{
    uint16_t tY = machine->regs.Y & 0x00FF; // clear high bits
    uint16_t tA = machine->regs.A + tY; // adds the prepared values
    if( (machine->regs.A & 0xFF00) != (tA & 0xFF00) ) // checks for overflow
        machine->regs.CF |= 0x04;
    machine->regs.A = tA;
    return;
}
void RISC_OP_ADD_imm8(RISC_Machine *machine)
{
    uint16_t ti = machine->mem[++machine->regs.IP] & 0x00FF;
    uint16_t tA = machine->regs.A + ti;
    if( (machine->regs.A & 0xFF00) != (tA & 0xFF00) ) // checks for overflow
        machine->regs.CF |= 0x04;
    machine->regs.A = tA;
    return;
}
/*void RISC_OP_ADD_X16(RISC_Machine *machine)
{
    machine->regs.A += machine->regs.X;
    return;
}
void RISC_OP_ADD_Y16(RISC_Machine *machine)
{
    machine->regs.A += machine->regs.Y;
    return;
}
void RISC_OP_ADD_imm16(RISC_Machine *machine)
{
    uint16_t high = machine->mem[++machine->regs.IP] << 8;
    uint16_t low = machine->mem[++machine->regs.IP];
    machine->regs.A += (high | low);
    return;
}*/

/* SUB - arithmetic subtraction operation */
void RISC_OP_SUB_X8(RISC_Machine *machine)
{
    uint16_t tX = machine->regs.X & 0x00FF; // clear high bits
    uint16_t tA = machine->regs.A - tX; // adds the prepared values
    if( (machine->regs.A & 0xFF00) != (tA & 0xFF00) ) // checks for overflow
        machine->regs.CF |= 0x04;
    machine->regs.A = tA;
    return;
}
void RISC_OP_SUB_Y8(RISC_Machine *machine)
{
    uint16_t tY = machine->regs.Y & 0x00FF; // clear high bits
    uint16_t tA = machine->regs.A - tY; // adds the prepared values
    if( (machine->regs.A & 0xFF00) != (tA & 0xFF00) ) // checks for overflow
        machine->regs.CF |= 0x04;
    machine->regs.A = tA;
    return;
}
void RISC_OP_SUB_imm8(RISC_Machine *machine)
{
    uint16_t ti = machine->mem[++machine->regs.IP] & 0x00FF;
    uint16_t tA = machine->regs.A - ti;
    if( (machine->regs.A & 0xFF00) != (tA & 0xFF00) ) // checks for overflow
        machine->regs.CF |= 0x04;
    machine->regs.A = tA;
    return;
}
/*void RISC_OP_SUB_X16(RISC_Machine *machine)
{
    machine->regs.A -= machine->regs.X;
    return;
}
void RISC_OP_SUB_Y16(RISC_Machine *machine)
{
    machine->regs.A -= machine->regs.Y;
    return;
}
void RISC_OP_SUB_imm16(RISC_Machine *machine)
{
    uint16_t high = machine->mem[++machine->regs.IP] << 8;
    uint16_t low = machine->mem[++machine->regs.IP];
    machine->regs.A -= (high | low);
    return;
}*/


/* RISC: RESET OPS */
void RISC_ResetOps(RISC_Machine *machine)
{
    if(machine->ops != NULL)
    {
        free(machine->ops);
    }

    machine->ops = calloc(256, sizeof(void *));
    //printf("0x%p\n", &machine->ops);

    machine->ops[0x00] = &RISC_OP_NOP;
    machine->ops[0x01] = &RISC_OP_NOP;
	machine->ops[0x02] = &RISC_OP_NOP;
	machine->ops[0x03] = &RISC_OP_NOP;
	machine->ops[0x04] = &RISC_OP_NOP;
	machine->ops[0x05] = &RISC_OP_NOP;
	machine->ops[0x06] = &RISC_OP_NOP;
	machine->ops[0x07] = &RISC_OP_NOP;
	machine->ops[0x08] = &RISC_OP_NOP;
	machine->ops[0x09] = &RISC_OP_NOP;
	machine->ops[0x0A] = &RISC_OP_NOP;
	machine->ops[0x0B] = &RISC_OP_NOP;
	machine->ops[0x0C] = &RISC_OP_NOP;
	machine->ops[0x0D] = &RISC_OP_NOP;
	machine->ops[0x0E] = &RISC_OP_NOP;
	machine->ops[0x0F] = &RISC_OP_NOP;
	machine->ops[0x10] = &RISC_OP_AND_X8;
	machine->ops[0x11] = &RISC_OP_AND_Y8;
	machine->ops[0x12] = &RISC_OP_AND_imm8;
	machine->ops[0x13] = &RISC_OP_NOP;
	machine->ops[0x14] = &RISC_OP_NOP;
	machine->ops[0x15] = &RISC_OP_NOP;
	machine->ops[0x16] = &RISC_OP_NOP;
	machine->ops[0x17] = &RISC_OP_NOP;
	machine->ops[0x18] = &RISC_OP_OR_X8;
	machine->ops[0x19] = &RISC_OP_OR_Y8;
	machine->ops[0x1A] = &RISC_OP_OR_imm8;
	machine->ops[0x1B] = &RISC_OP_NOP;
	machine->ops[0x1C] = &RISC_OP_NOP;
	machine->ops[0x1D] = &RISC_OP_NOP;
	machine->ops[0x1E] = &RISC_OP_NOP;
	machine->ops[0x1F] = &RISC_OP_NOP;
	machine->ops[0x20] = &RISC_OP_NOP;
	machine->ops[0x21] = &RISC_OP_NOP;
	machine->ops[0x22] = &RISC_OP_NOP;
	machine->ops[0x23] = &RISC_OP_NOP;
	machine->ops[0x24] = &RISC_OP_NOP;
	machine->ops[0x25] = &RISC_OP_NOP;
	machine->ops[0x26] = &RISC_OP_NOP;
	machine->ops[0x27] = &RISC_OP_NOP;
	machine->ops[0x28] = &RISC_OP_NOP;
	machine->ops[0x29] = &RISC_OP_NOP;
	machine->ops[0x2A] = &RISC_OP_NOP;
	machine->ops[0x2B] = &RISC_OP_NOP;
	machine->ops[0x2C] = &RISC_OP_NOP;
	machine->ops[0x2D] = &RISC_OP_NOP;
	machine->ops[0x2E] = &RISC_OP_NOP;
	machine->ops[0x2F] = &RISC_OP_NOP;
	machine->ops[0x30] = &RISC_OP_NOP;
	machine->ops[0x31] = &RISC_OP_NOP;
	machine->ops[0x32] = &RISC_OP_NOP;
	machine->ops[0x33] = &RISC_OP_NOP;
	machine->ops[0x34] = &RISC_OP_NOP;
	machine->ops[0x35] = &RISC_OP_NOP;
	machine->ops[0x36] = &RISC_OP_NOP;
	machine->ops[0x37] = &RISC_OP_NOP;
	machine->ops[0x38] = &RISC_OP_NOP;
	machine->ops[0x39] = &RISC_OP_NOP;
	machine->ops[0x3A] = &RISC_OP_NOP;
	machine->ops[0x3B] = &RISC_OP_NOP;
	machine->ops[0x3C] = &RISC_OP_NOP;
	machine->ops[0x3D] = &RISC_OP_NOP;
	machine->ops[0x3E] = &RISC_OP_NOP;
	machine->ops[0x3F] = &RISC_OP_NOP;
	machine->ops[0x40] = &RISC_OP_ADD_X8;
	machine->ops[0x41] = &RISC_OP_ADD_Y8;
	machine->ops[0x42] = &RISC_OP_ADD_imm8;
	machine->ops[0x43] = &RISC_OP_NOP;
	machine->ops[0x44] = &RISC_OP_NOP;
	machine->ops[0x45] = &RISC_OP_NOP;
	machine->ops[0x46] = &RISC_OP_NOP;
	machine->ops[0x47] = &RISC_OP_NOP;
	machine->ops[0x48] = &RISC_OP_SUB_X8;
	machine->ops[0x49] = &RISC_OP_SUB_Y8;
	machine->ops[0x4A] = &RISC_OP_SUB_imm8;
	machine->ops[0x4B] = &RISC_OP_NOP;
	machine->ops[0x4C] = &RISC_OP_NOP;
	machine->ops[0x4D] = &RISC_OP_NOP;
	machine->ops[0x4E] = &RISC_OP_NOP;
	machine->ops[0x4F] = &RISC_OP_NOP;
	machine->ops[0x50] = &RISC_OP_NOP;
	machine->ops[0x51] = &RISC_OP_NOP;
	machine->ops[0x52] = &RISC_OP_NOP;
	machine->ops[0x53] = &RISC_OP_NOP;
	machine->ops[0x54] = &RISC_OP_NOP;
	machine->ops[0x55] = &RISC_OP_NOP;
	machine->ops[0x56] = &RISC_OP_NOP;
	machine->ops[0x57] = &RISC_OP_NOP;
	machine->ops[0x58] = &RISC_OP_NOP;
	machine->ops[0x59] = &RISC_OP_NOP;
	machine->ops[0x5A] = &RISC_OP_NOP;
	machine->ops[0x5B] = &RISC_OP_NOP;
	machine->ops[0x5C] = &RISC_OP_NOP;
	machine->ops[0x5D] = &RISC_OP_NOP;
	machine->ops[0x5E] = &RISC_OP_NOP;
	machine->ops[0x5F] = &RISC_OP_NOP;
	machine->ops[0x60] = &RISC_OP_NOP;
	machine->ops[0x61] = &RISC_OP_NOP;
	machine->ops[0x62] = &RISC_OP_NOP;
	machine->ops[0x63] = &RISC_OP_NOP;
	machine->ops[0x64] = &RISC_OP_NOP;
	machine->ops[0x65] = &RISC_OP_NOP;
	machine->ops[0x66] = &RISC_OP_NOP;
	machine->ops[0x67] = &RISC_OP_NOP;
	machine->ops[0x68] = &RISC_OP_NOP;
	machine->ops[0x69] = &RISC_OP_NOP;
	machine->ops[0x6A] = &RISC_OP_NOP;
	machine->ops[0x6B] = &RISC_OP_NOP;
	machine->ops[0x6C] = &RISC_OP_NOP;
	machine->ops[0x6D] = &RISC_OP_NOP;
	machine->ops[0x6E] = &RISC_OP_NOP;
	machine->ops[0x6F] = &RISC_OP_NOP;
	machine->ops[0x70] = &RISC_OP_NOP;
	machine->ops[0x71] = &RISC_OP_NOP;
	machine->ops[0x72] = &RISC_OP_NOP;
	machine->ops[0x73] = &RISC_OP_NOP;
	machine->ops[0x74] = &RISC_OP_NOP;
	machine->ops[0x75] = &RISC_OP_NOP;
	machine->ops[0x76] = &RISC_OP_NOP;
	machine->ops[0x77] = &RISC_OP_NOP;
	machine->ops[0x78] = &RISC_OP_NOP;
	machine->ops[0x79] = &RISC_OP_NOP;
	machine->ops[0x7A] = &RISC_OP_NOP;
	machine->ops[0x7B] = &RISC_OP_NOP;
	machine->ops[0x7C] = &RISC_OP_NOP;
	machine->ops[0x7D] = &RISC_OP_NOP;
	machine->ops[0x7E] = &RISC_OP_NOP;
	machine->ops[0x7F] = &RISC_OP_NOP;
	machine->ops[0x80] = &RISC_OP_NOP;
	machine->ops[0x81] = &RISC_OP_NOP;
	machine->ops[0x82] = &RISC_OP_NOP;
	machine->ops[0x83] = &RISC_OP_NOP;
	machine->ops[0x84] = &RISC_OP_NOP;
	machine->ops[0x85] = &RISC_OP_NOP;
	machine->ops[0x86] = &RISC_OP_NOP;
	machine->ops[0x87] = &RISC_OP_NOP;
	machine->ops[0x88] = &RISC_OP_NOP;
	machine->ops[0x89] = &RISC_OP_NOP;
	machine->ops[0x8A] = &RISC_OP_NOP;
	machine->ops[0x8B] = &RISC_OP_NOP;
	machine->ops[0x8C] = &RISC_OP_NOP;
	machine->ops[0x8D] = &RISC_OP_NOP;
	machine->ops[0x8E] = &RISC_OP_NOP;
	machine->ops[0x8F] = &RISC_OP_NOP;
	machine->ops[0x90] = &RISC_OP_NOP;
	machine->ops[0x91] = &RISC_OP_NOP;
	machine->ops[0x92] = &RISC_OP_NOP;
	machine->ops[0x93] = &RISC_OP_NOP;
	machine->ops[0x94] = &RISC_OP_NOP;
	machine->ops[0x95] = &RISC_OP_NOP;
	machine->ops[0x96] = &RISC_OP_NOP;
	machine->ops[0x97] = &RISC_OP_NOP;
	machine->ops[0x98] = &RISC_OP_NOP;
	machine->ops[0x99] = &RISC_OP_NOP;
	machine->ops[0x9A] = &RISC_OP_NOP;
	machine->ops[0x9B] = &RISC_OP_NOP;
	machine->ops[0x9C] = &RISC_OP_NOP;
	machine->ops[0x9D] = &RISC_OP_NOP;
	machine->ops[0x9E] = &RISC_OP_NOP;
	machine->ops[0x9F] = &RISC_OP_NOP;
	machine->ops[0xA0] = &RISC_OP_NOP;
	machine->ops[0xA1] = &RISC_OP_NOP;
	machine->ops[0xA2] = &RISC_OP_NOP;
	machine->ops[0xA3] = &RISC_OP_NOP;
	machine->ops[0xA4] = &RISC_OP_NOP;
	machine->ops[0xA5] = &RISC_OP_NOP;
	machine->ops[0xA6] = &RISC_OP_NOP;
	machine->ops[0xA7] = &RISC_OP_NOP;
	machine->ops[0xA8] = &RISC_OP_NOP;
	machine->ops[0xA9] = &RISC_OP_NOP;
	machine->ops[0xAA] = &RISC_OP_NOP;
	machine->ops[0xAB] = &RISC_OP_NOP;
	machine->ops[0xAC] = &RISC_OP_NOP;
	machine->ops[0xAD] = &RISC_OP_NOP;
	machine->ops[0xAE] = &RISC_OP_NOP;
	machine->ops[0xAF] = &RISC_OP_NOP;
	machine->ops[0xB0] = &RISC_OP_NOP;
	machine->ops[0xB1] = &RISC_OP_NOP;
	machine->ops[0xB2] = &RISC_OP_NOP;
	machine->ops[0xB3] = &RISC_OP_NOP;
	machine->ops[0xB4] = &RISC_OP_NOP;
	machine->ops[0xB5] = &RISC_OP_NOP;
	machine->ops[0xB6] = &RISC_OP_NOP;
	machine->ops[0xB7] = &RISC_OP_NOP;
	machine->ops[0xB8] = &RISC_OP_NOP;
	machine->ops[0xB9] = &RISC_OP_NOP;
	machine->ops[0xBA] = &RISC_OP_NOP;
	machine->ops[0xBB] = &RISC_OP_NOP;
	machine->ops[0xBC] = &RISC_OP_NOP;
	machine->ops[0xBD] = &RISC_OP_NOP;
	machine->ops[0xBE] = &RISC_OP_NOP;
	machine->ops[0xBF] = &RISC_OP_NOP;
	machine->ops[0xC0] = &RISC_OP_NOP;
	machine->ops[0xC1] = &RISC_OP_NOP;
	machine->ops[0xC2] = &RISC_OP_NOP;
	machine->ops[0xC3] = &RISC_OP_NOP;
	machine->ops[0xC4] = &RISC_OP_NOP;
	machine->ops[0xC5] = &RISC_OP_NOP;
	machine->ops[0xC6] = &RISC_OP_NOP;
	machine->ops[0xC7] = &RISC_OP_NOP;
	machine->ops[0xC8] = &RISC_OP_NOP;
	machine->ops[0xC9] = &RISC_OP_NOP;
	machine->ops[0xCA] = &RISC_OP_NOP;
	machine->ops[0xCB] = &RISC_OP_NOP;
	machine->ops[0xCC] = &RISC_OP_NOP;
	machine->ops[0xCD] = &RISC_OP_NOP;
	machine->ops[0xCE] = &RISC_OP_NOP;
	machine->ops[0xCF] = &RISC_OP_NOP;
	machine->ops[0xD0] = &RISC_OP_NOP;
	machine->ops[0xD1] = &RISC_OP_NOP;
	machine->ops[0xD2] = &RISC_OP_NOP;
	machine->ops[0xD3] = &RISC_OP_NOP;
	machine->ops[0xD4] = &RISC_OP_NOP;
	machine->ops[0xD5] = &RISC_OP_NOP;
	machine->ops[0xD6] = &RISC_OP_NOP;
	machine->ops[0xD7] = &RISC_OP_NOP;
	machine->ops[0xD8] = &RISC_OP_NOP;
	machine->ops[0xD9] = &RISC_OP_NOP;
	machine->ops[0xDA] = &RISC_OP_NOP;
	machine->ops[0xDB] = &RISC_OP_NOP;
	machine->ops[0xDC] = &RISC_OP_NOP;
	machine->ops[0xDD] = &RISC_OP_NOP;
	machine->ops[0xDE] = &RISC_OP_NOP;
	machine->ops[0xDF] = &RISC_OP_NOP;
	machine->ops[0xE0] = &RISC_OP_NOP;
	machine->ops[0xE1] = &RISC_OP_NOP;
	machine->ops[0xE2] = &RISC_OP_NOP;
	machine->ops[0xE3] = &RISC_OP_NOP;
	machine->ops[0xE4] = &RISC_OP_NOP;
	machine->ops[0xE5] = &RISC_OP_NOP;
	machine->ops[0xE6] = &RISC_OP_NOP;
	machine->ops[0xE7] = &RISC_OP_NOP;
	machine->ops[0xE8] = &RISC_OP_NOP;
	machine->ops[0xE9] = &RISC_OP_NOP;
	machine->ops[0xEA] = &RISC_OP_NOP;
	machine->ops[0xEB] = &RISC_OP_NOP;
	machine->ops[0xEC] = &RISC_OP_NOP;
	machine->ops[0xED] = &RISC_OP_NOP;
	machine->ops[0xEE] = &RISC_OP_NOP;
	machine->ops[0xEF] = &RISC_OP_NOP;
	machine->ops[0xF0] = &RISC_OP_NOP;
	machine->ops[0xF1] = &RISC_OP_NOP;
	machine->ops[0xF2] = &RISC_OP_NOP;
	machine->ops[0xF3] = &RISC_OP_NOP;
	machine->ops[0xF4] = &RISC_OP_NOP;
	machine->ops[0xF5] = &RISC_OP_NOP;
	machine->ops[0xF6] = &RISC_OP_NOP;
	machine->ops[0xF7] = &RISC_OP_NOP;
	machine->ops[0xF8] = &RISC_OP_NOP;
	machine->ops[0xF9] = &RISC_OP_NOP;
	machine->ops[0xFA] = &RISC_OP_NOP;
	machine->ops[0xFB] = &RISC_OP_NOP;
	machine->ops[0xFC] = &RISC_OP_NOP;
	machine->ops[0xFD] = &RISC_OP_NOP;
	machine->ops[0xFE] = &RISC_OP_NOP;
	machine->ops[0xFF] = &RISC_OP_HLT;

    return;
}
