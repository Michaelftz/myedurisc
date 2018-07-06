#include "edurisc.h"

RISC_Machine *RISC_Init(size_t memory_size)
{
    RISC_Machine *this_machine = malloc(sizeof(RISC_Machine)); // See docs on info for RISC_Machine

    /* MAIN MEMORY */
    uint8_t *memory = calloc(memory_size, 1); // Virtual RAM in memory: static, include pointer (just name, as pointer assumed with arrays) in RISC_Machine instance under .mem member

    this_machine->mem = memory;
    this_machine->mem_size = memory_size;
    this_machine->regs = (RISC_er8_Regs){0}; // Initialize registers to 0
    this_machine->ops = NULL;
    this_machine->options = 0;

    RISC_ResetOps(this_machine);

    return this_machine;
}

void RISC_Quit(RISC_Machine *machine) //CHANGE TO INT! - error options
{
    free(machine->mem);
    free(machine);
    return;
}

inline void RISC_MachineIter(RISC_Machine *machine)
{
    uint8_t this_inst = machine->mem[machine->regs.IP];
    //printf("0x%p\n", machine->ops[this_inst]);
    (machine->ops[this_inst])(machine);
    machine->regs.IP++;
    return;
}

void RISC_MachineStart(RISC_Machine *machine)
{
    while(!(machine->options & 0x01))
    {
        RISC_MachineIter(machine);
    }

    return;
}

void RISC_MachineStop(RISC_Machine *machine)
{
    free(machine->ops);

    return;
}

int RISC_LoadBinMem(FILE *fp, RISC_Machine *machine, uint16_t memory_addr, uint16_t count) //pointer to input file, pointer to machine, start memory address, number of bytes
{
    if((memory_addr + count) >= machine->mem_size)
        return 0; // ERROR: May not exceed total RAM area. (early return)

    if( (machine->mem[510] == 0x4D && machine->mem[511] == 0x46) )
        return 0; // ERROR: May not intrude secure boot area. (early return)

    fread(machine->mem, 1, count, fp);

    return 1;
}
