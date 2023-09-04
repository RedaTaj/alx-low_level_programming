#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

/* Macro to handle errors and exit with status code 98 */
#define die(message) do { perror(message); exit(98); } while (0)

/* Function to print the ELF header information */
void print_elf_header(char *filename);

/* Entry point of the program */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		return (98);
	}

	/* Call the function to print ELF header information */
	print_elf_header(argv[1]);

	return (0);
}

/* Function to print the ELF header information */
void print_elf_header(char *filename)
{
	int fd;
	Elf64_Ehdr header;
	int i;

	/* Open the ELF file */
	if ((fd = open(filename, O_RDONLY)) == -1)
		die("Error: Can't read file");

	/* Read the ELF header */
	if (read(fd, &header, sizeof(header)) == -1)
		die("Error: Can't read ELF header");

	/* Check if it's a valid ELF file */
	if (header.e_ident[EI_MAG0] != ELFMAG0 || header.e_ident[EI_MAG1] != ELFMAG1 ||
		header.e_ident[EI_MAG2] != ELFMAG2 || header.e_ident[EI_MAG3] != ELFMAG3)
		die("Error: Not an ELF file");

	/* Print ELF header information */
	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x%c", header.e_ident[i], i == EI_NIDENT - 1 ? '\n' : ' ');
	}

	printf("  Class:                             ELF%d\n", header.e_ident[EI_CLASS] == ELFCLASS32 ? 32 : 64);
	printf("  Data:                              %s\n", header.e_ident[EI_DATA] == ELFDATA2LSB
													  ? "2's complement, little endian"
													  : "2's complement, big endian");
	printf("  Version:                           %d (current)\n", header.e_ident[EI_VERSION]);
	printf("  OS/ABI:                            UNIX - ");
	switch (header.e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE: printf("System V\n"); break;
		case ELFOSABI_HPUX: printf("HP-UX\n"); break;
		case ELFOSABI_NETBSD: printf("NetBSD\n"); break;
		case ELFOSABI_LINUX: printf("Linux\n"); break;
		case ELFOSABI_SOLARIS: printf("Solaris\n"); break;
		case ELFOSABI_IRIX: printf("IRIX\n"); break;
		case ELFOSABI_FREEBSD: printf("FreeBSD\n"); break;
		case ELFOSABI_TRU64: printf("TRU64\n"); break;
		case ELFOSABI_ARM: printf("ARM\n"); break;
		case ELFOSABI_STANDALONE: printf("Standalone App\n"); break;
		default: printf("<unknown: %x>\n", header.e_ident[EI_OSABI]); break;
	}

	printf("  ABI Version:                       %d\n", header.e_ident[EI_ABIVERSION]);
	printf("  Type:                              ");
	switch (header.e_type)
	{
		case ET_NONE: printf("NONE (None)\n"); break;
		case ET_REL: printf("REL (Relocatable file)\n"); break;
		case ET_EXEC: printf("EXEC (Executable file)\n"); break;
		case ET_DYN: printf("DYN (Shared object file)\n"); break;
		case ET_CORE: printf("CORE (Core file)\n"); break;
		default: printf("<unknown: %x>\n", header.e_type); break;
	}

	printf("  Entry point address:               ");
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		header.e_entry = ((header.e_entry << 8) & 0xFF00FF00) |
						 ((header.e_entry >> 8) & 0xFF00FF),
		header.e_entry = (header.e_entry << 16) | (header.e_entry >> 16);
	printf("0x%lx\n", header.e_ident[EI_CLASS] == ELFCLASS32 ? (unsigned long int)header.e_entry : header.e_entry);

	/* Close the file */
	close(fd);
}

