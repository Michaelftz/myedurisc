#include "edurisc.h"

RISC_Machine *RISC_Init(unsigned int memory_size)
{
    RISC_Machine *this_machine = malloc(sizeof(RISC_Machine)); // See docs on info for RISC_Machine

    /* MAIN MEMORY */
    uint8_t *memory = calloc(memory_size, 1); // Virtual RAM in memory: static, include pointer (just name, as pointer assumed with arrays) in RISC_Machine instance under .mem member

    this_machine->mem = memory;
    this_machine->mem_size = memory_size;

    return this_machine;
}

void RISC_Quit(RISC_Machine *machine) //CHANGE TO INT! - error options
{
    free(machine->mem);
    free(machine);
    return;
}

int RISC_LoadBinMem(FILE *fp, RISC_Machine *machine, uint16_t memory_addr, uint16_t count) //pointer to input file, pointer to machine, start memory address, number of bytes
{
    if((memory_addr + count) >= machine->mem_size)
        return 0; // ERROR: May not exceed total RAM area. (early return)

    if( (machine->mem[510] == 0x4D && machine->mem[511] == 46) )
        return 0; // ERROR: May not intrude secure boot area. (early return)

    fread(machine->mem, 1, count, fp);

    return 1;
}
