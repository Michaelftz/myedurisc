// VERSION SYSTEM 1: Major.2DigitMinor VersionBlock YYYY.MM.DD.LETTER

/* INCLUDE HEADERS */
#include "edurisc.h"

int main(int argc, char **argv)
{
    /* DATA DECLARATIONS */
    FILE *RISC_ROM; // make global?

    /* COMMAND-LINE INTERFACE SETUP */
    if(argc == 1) // If no arguments, then print information, including usage format.
    {
        printf("%s \n\n", _RISC_MENU_WELCOME);
        printf("%s \n\n", _RISC_MENU_USAGE);
        return 0;
    }
    if(strncmp(argv[1], "--", 2) == 0) // If begins with '--', then go override
    {
        if(strncmp(argv[1], "--about", 7) == 0) // Display about info
            printf("hi \n\n"); // NEED TO FINISH!!!
        else if(strncmp(argv[1], "--license", 9) == 0) // Display license info
            printf("%s \n\n", _RISC_MENU_LICENSE);
        else if(strncmp(argv[1], "--version", 9) == 0) // Display version info
            printf("Current version: %s \nPlease check the official website or VCS for more updates. \n\n", _RISC_MENU_VERSION);
        else
            printf("%s \n\n%s \n\n", _RISC_MENU_WELCOME, _RISC_MENU_USAGE);
        return 0;
    }

    /* INITIALIZE VIRTUAL MACHINE */
    RISC_Machine *machine = RISC_Init(_RISC_RAM_SIZE);

    /* OPEN ROM FILE */
    if( !(RISC_ROM = fopen(argv[1], "rb")) )
    {
        printf("ERROR: Could not open file \"%s\".\nPlease verify the file and its permissions. \n\n", argv[1]);
        return 1;
    }

    /* BOOT PROCESS */
    if( !RISC_LoadBinMem(RISC_ROM, machine, 0, 512) )
    {
        printf("ERROR: Could not load file into memory. \nPlease verify requirements of hardware, software, and security. \n\n");
        return 1;
    }

    printf("MEMORY: %u bytes\nFIRST BYTE: 0x%X\n", machine->mem_size, machine->mem[0x00]);

    /* CLOSE FILE AND FREE MEMORY */
    RISC_Quit(machine);
    fclose(RISC_ROM);

    return 0;
}
