#include <stdint.h>

typedef struct
{
    // 8-bit ALU (arithmetic and logic)
    uint8_t A; // accumulator
    uint8_t X; // general-purpose
    uint8_t Y; // general-purpose

    // 8-bit control (pointers and flags)
    uint8_t DI; // destination index (general-purpose pointer)
    uint8_t SI; // source index (general-purpose pointer)
    uint8_t IP; // instruction pointer
    uint8_t BP; // base pointer (stack base)
    uint8_t SP; // stack pointer (current stack position)
    uint8_t CF; // CPU flags

    // 8-bit (memory segmentation) (***only in future versions***)
    //uint8_t CSEG; // code segment
    //uint8_t DSEG; // data segment
    //uint8_t SSEG; // stack segment
} RISC_er8_Regs;
