#include "edurisc.h"

/* NOP */
void RISC_OP_NOP(RISC_Machine *machine)
{
    return;
}

/* HLT - halts the program, by setting options flag bit 1 to true */
void RISC_OP_HLT(RISC_Machine *machine)
{
    machine->options |= 0x0002;
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

void RISC_OP_AND_X16(RISC_Machine *machine)
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
}


/* ADD - arithmetic add operation */
void RISC_OP_ADD_X8(RISC_Machine *machine)
{
    uint16_t tX = machine->regs.X & 0x00FF; // clear high bits
    uint16_t tA = machine->regs.A + tX; // adds the prepared values
    if( (machine->regs.A & 0xFF00) != (tA & 0xFF00) ) // checks for overflow
        machine->regs.CF |= 0x0003;
    machine->regs.A = tA;
    return;
}
void RISC_OP_ADD_Y8(RISC_Machine *machine)
{
    uint16_t tY = machine->regs.Y & 0x00FF; // clear high bits
    uint16_t tA = machine->regs.A + tY; // adds the prepared values
    if( (machine->regs.A & 0xFF00) != (tA & 0xFF00) ) // checks for overflow
        machine->regs.CF |= 0x03;
    machine->regs.A = tA;
    return;
}
void RISC_OP_ADD_imm8(RISC_Machine *machine)
{
    uint16_t ti = machine->mem[++machine->regs.IP] & 0x00FF;
    uint16_t tA = machine->regs.A + ti;
    if( (machine->regs.A & 0xFF00) != (tA & 0xFF00) ) // checks for overflow
        machine->regs.CF |= 0x03;
    machine->regs.A = tA;
    return;
}
void RISC_OP_ADD_X16(RISC_Machine *machine)
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
}
