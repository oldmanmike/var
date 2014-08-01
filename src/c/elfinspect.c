/********************************
 * File:    elfinspect.c        *
 * Author:  Michael Carpenter   *
 * Class:   Operating Systems   *
 * Date:    22/2/14             *
 *******************************/
#include <err.h>
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[ ]) {
    FILE* fpHandle = NULL;
    char* SectNames = NULL;
    Elf64_Ehdr elfHdr;
    Elf64_Phdr elfPhdr;
    Elf64_Shdr elfShdr;
    int stripped = 0;
    int i = 0;

    printf("File is: %s\n", argv[1]);
    
    if (argc != 2)
        errx(EXIT_FAILURE, "usage: %s file-name", argv[0]);

    if ((fpHandle = fopen(argv[1],"r")) == NULL) {
        fprintf(stderr, "elfinspect: cannot open '%s' (No such file or directory)\n", argv[1]);
        exit(1);
    }

    fread(&elfHdr, 1, sizeof elfHdr, fpHandle);
    if (elfHdr.e_ident[EI_MAG0] != 127) {
        fprintf(stderr, "elfinspect: %s is not an ELF file\n", argv[1]);
        exit(1);
    }
    fseek(fpHandle, elfHdr.e_phoff, SEEK_SET);
    fread(&elfPhdr, 1, sizeof elfPhdr, fpHandle);

    fseek(fpHandle, elfHdr.e_shoff + elfHdr.e_shstrndx * sizeof elfShdr, SEEK_SET);
    fread(&elfShdr, 1, sizeof elfShdr, fpHandle);

    SectNames = malloc(elfShdr.sh_size);
    fseek(fpHandle, elfShdr.sh_offset, SEEK_SET);
    fread(SectNames, 1, elfShdr.sh_size, fpHandle);

    for (i = 0; i < elfHdr.e_shnum; i++) {
        fseek(fpHandle, elfHdr.e_shoff + i * sizeof elfShdr, SEEK_SET);
        fread(&elfShdr, 1, sizeof elfShdr, fpHandle);

        if (elfShdr.sh_type == SHT_STRTAB)
            stripped = 1;
    }


    printf("Magic:                              %x %x %x %x %x %x %x %x %x %x\n", elfHdr.e_ident[EI_MAG0], elfHdr.e_ident[EI_MAG1], elfHdr.e_ident[EI_MAG2], elfHdr.e_ident[EI_MAG3], elfHdr.e_ident[EI_CLASS], elfHdr.e_ident[EI_DATA], elfHdr.e_ident[EI_VERSION], elfHdr.e_ident[EI_OSABI], elfHdr.e_ident[EI_ABIVERSION], elfHdr.e_ident[EI_PAD]); 
    printf("Class:                              %#x\n", elfHdr.e_ident[EI_CLASS]);
    printf("Data:                               %#x\n", elfHdr.e_ident[EI_DATA]);
    printf("Version:                            %#x\n", elfHdr.e_ident[EI_VERSION]);
    printf("OS/ABI:                             %#x\n", elfHdr.e_ident[EI_OSABI]);
    printf("ABI Version:                        %#x\n", elfHdr.e_ident[EI_ABIVERSION]);
    printf("Type:                               %#x\n", elfHdr.e_type);
    printf("Machine:                            %#x\n", elfHdr.e_machine);
    printf("Version:                            %#x\n", elfHdr.e_version);
    printf("Entry Point:                        %#x\n", elfHdr.e_entry);
    printf("Start of program headers:           %d (bytes into file)\n", elfHdr.e_phoff);
    printf("Start of section headers:           %d (bytes into file)\n", elfHdr.e_shoff);
    printf("Flags:                              %#x\n", elfHdr.e_flags);
    printf("Size of this header:                %d (bytes)\n", elfHdr.e_ehsize);
    printf("Size of program headers:            %d (bytes)\n", elfHdr.e_phentsize);
    printf("Number of program headers:          %d\n", elfHdr.e_phnum);
    printf("Size of section headers:            %d (bytes)\n", elfHdr.e_shentsize);
    printf("Number of section headers:          %d\n", elfHdr.e_shnum);
    printf("Section header string table index:  %d\n", elfHdr.e_shstrndx);
    //printf("==Program Header Table==\n");
    //printf("Test:                               %x\n", 127);
    //printf("Another Test:                       %#x\n", SHT_SYMTAB);
    if (stripped) {
        printf("Stripped:                           True\n");
    } else {
        printf("Stripped:                           False\n");
    }

    fclose(fpHandle);
    
    return(0);
}
/*********************************************************************
=================== ls ==================  

File is: ls
Magic:                              7f 45 4c 46 2 1 1 0 0 0
Class:                              0x2
Data:                               0x1
Version:                            0x1
OS/ABI:                             0
ABI Version:                        0
Type:                               0x2
Machine:                            0x3e
Version:                            0x1
Entry Point:                        0x40488f
Start of program headers:           64 (bytes into file)
Start of section headers:           108288 (bytes into file)
Flags:                              0
Size of this header:                64 (bytes)
Size of program headers:            56 (bytes)
Number of program headers:          9
Size of section headers:            64 (bytes)
Number of section headers:          28
Section header string table index:  27
Stripped:                           True

=================== t =================== 

File is: t
Magic:                              7f 45 4c 46 1 1 1 0 0 0
Class:                              0x1
Data:                               0x1
Version:                            0x1
OS/ABI:                             0
ABI Version:                        0
Type:                               0x2
Machine:                            0x3
Version:                            0x1
Entry Point:                        0x8048310
Start of program headers:           5996 (bytes into file)
Start of section headers:           2097204 (bytes into file)
Flags:                              0x210024
Size of this header:                6 (bytes)
Size of program headers:            0 (bytes)
Number of program headers:          52
Size of section headers:            0 (bytes)
Number of section headers:          32820
Section header string table index:  2052
Stripped:                           False

================== add ================== 

File is: add
Magic:                              7f 45 4c 46 2 1 1 0 0 0
Class:                              0x2
Data:                               0x1
Version:                            0x1
OS/ABI:                             0
ABI Version:                        0
Type:                               0x2
Machine:                            0x3e
Version:                            0x1
Entry Point:                        0x4003d0
Start of program headers:           64 (bytes into file)
Start of section headers:           4416 (bytes into file)
Flags:                              0
Size of this header:                64 (bytes)
Size of program headers:            56 (bytes)
Number of program headers:          9
Size of section headers:            64 (bytes)
Number of section headers:          30
Section header string table index:  27
Stripped:                           True

=================== s ===================  

File is: s
elfinspect: s is not an ELF file
******************************************************************/

