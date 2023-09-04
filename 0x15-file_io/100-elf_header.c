#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void validate_elf(unsigned char *magic_numbers);
void display_magic_numbers(unsigned char *magic_numbers);
void display_class(unsigned char *magic_numbers);
void display_data_encoding(unsigned char *magic_numbers);
void display_elf_version(unsigned char *magic_numbers);
void display_os_abi(unsigned char *magic_numbers);
void display_abi_version(unsigned char *magic_numbers);
void display_elf_type(unsigned int elf_type, unsigned char *magic_numbers);
void display_entry_point(unsigned long int entry_point, unsigned char *magic_numbers);
void close_elf_file(int file_descriptor);

/**
 * validate_elf - Verifies if a file is an ELF (Executable and Linkable Format).
 * @magic_numbers: Pointer to an array containing the ELF magic numbers.
 *
 * Description: Exits with code 98 if the file is not an ELF.
 */
void validate_elf(unsigned char *magic_numbers)
{
	int index;

	for (index = 0; index < 4; index++)
	{
		if (magic_numbers[index] != 127 &&
		    magic_numbers[index] != 'E' &&
		    magic_numbers[index] != 'L' &&
		    magic_numbers[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * display_magic_numbers - Displays the magic numbers of an ELF header.
 * @magic_numbers: Pointer to an array containing the ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void display_magic_numbers(unsigned char *magic_numbers)
{
	int index;

	printf(" Magic Numbers: ");

	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", magic_numbers[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
 * display_class - Displays the ELF class (32-bit or 64-bit) of an ELF header.
 * @magic_numbers: Pointer to an array containing the ELF class.
 */
void display_class(unsigned char *magic_numbers)
{
	printf(" ELF Class: ");

	switch (magic_numbers[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("Invalid\n");
		break;
	case ELFCLASS32:
		printf("32-bit ELF\n");
		break;
	case ELFCLASS64:
		printf("64-bit ELF\n");
		break;
	default:
		printf("<unknown: %x>\n", magic_numbers[EI_CLASS]);
	}
}

/**
 * display_data_encoding - Displays the data encoding of an ELF header.
 * @magic_numbers: Pointer to an array containing the ELF data encoding.
 */
void display_data_encoding(unsigned char *magic_numbers)
{
	printf(" Data Encoding: ");

	switch (magic_numbers[EI_DATA])
	{
	case ELFDATANONE:
		printf("Invalid\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little-endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big-endian\n");
		break;
	default:
		printf("<unknown: %x>\n", magic_numbers[EI_DATA]);
	}
}

/**
 * display_elf_version - Displays the ELF version.
 * @magic_numbers: Pointer to an array containing the ELF version.
 */
void display_elf_version(unsigned char *magic_numbers)
{
	printf(" ELF Version: %d", magic_numbers[EI_VERSION]);

	switch (magic_numbers[EI_VERSION])
	{
	case EV_CURRENT:
		printf(" (Current)\n");
		break;
	default:
		printf("\n");
		break;
	}
}

/**
 * display_os_abi - Displays the operating system and ABI of an ELF header.
 * @magic_numbers: Pointer to an array containing the ELF OS/ABI.
 */
void display_os_abi(unsigned char *magic_numbers)
{
	printf(" OS/ABI: ");

	switch (magic_numbers[EI_OSABI])
	{
	case ELFOSABI_NONE:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone Application\n");
		break;
	default:
		printf("<unknown: %x>\n", magic_numbers[EI_OSABI]);
	}
}

/**
 * display_abi_version - Displays the ABI version of an ELF header.
 * @magic_numbers: Pointer to an array containing the ELF ABI version.
 */
void display_abi_version(unsigned char *magic_numbers)
{
	printf(" ABI Version: %d\n", magic_numbers[EI_ABIVERSION]);
}

/**
 * display_elf_type - Displays the type of an ELF header.
 * @elf_type: The ELF type.
 * @magic_numbers: Pointer to an array containing the ELF class.
 */
void display_elf_type(unsigned int elf_type, unsigned char *magic_numbers)
{
	if (magic_numbers[EI_DATA] == ELFDATA2MSB)
		elf_type >>= 8;

	printf(" ELF Type: ");

	switch (elf_type)
	{
	case ET_NONE:
		printf("No Type (None)\n");
		break;
	case ET_REL:
		printf("Relocatable File (REL)\n");
		break;
	case ET_EXEC:
		printf("Executable File (EXEC)\n");
		break;
	case ET_DYN:
		printf("Shared Object File (DYN)\n");
		break;
	case ET_CORE:
		printf("Core File (CORE)\n");
		break;
	default:
		printf("<unknown: %x>\n", elf_type);
	}
}
/**
 * display_entry_point - Displays the entry point of an ELF header.
 * @entry_point: The address of the ELF entry point.
 * @magic_numbers: Pointer to an array containing the ELF class.
 */
void display_entry_point(unsigned long int entry_point, unsigned char *magic_numbers)
{
	printf(" Entry Point Address: ");

	if (magic_numbers[EI_DATA] == ELFDATA2MSB)
	{
		entry_point = ((entry_point << 8) & 0xFF00FF00) |
					  ((entry_point >> 8) & 0xFF00FF);
		entry_point = (entry_point << 16) | (entry_point >> 16);
	}

	if (magic_numbers[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)entry_point);
	else
		printf("%#lx\n", entry_point);
}

/**
 * close_elf_file - Closes an ELF file.
 * @file_descriptor: The file descriptor of the ELF file.
 *
 * Description: Exits with code 98 if the file cannot be closed.
 */
void close_elf_file(int file_descriptor)
{
	if (close(file_descriptor) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close file descriptor %d\n", file_descriptor);
		exit(98);
	}
}

/**
 * main - Displays information from the ELF header of an ELF file.
 * @argc: Number of arguments provided to the program.
 * @argv: Array of argument pointers.
 *
 * Return: 0 on success.
 *
 * Description: Exits with code 98 if the file is not an ELF or if any error occurs.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int file_descriptor, read_result;

	file_descriptor = open(argv[1], O_RDONLY);
	if (file_descriptor == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		close_elf_file(file_descriptor);
		dprintf(STDERR_FILENO, "Error: Unable to allocate memory for ELF header\n");
		exit(98);
	}

	read_result = read(file_descriptor, header, sizeof(Elf64_Ehdr));
	if (read_result == -1)
	{
		free(header);
		close_elf_file(file_descriptor);
		dprintf(STDERR_FILENO, "Error: Unable to read file %s\n", argv[1]);
		exit(98);
	}

	validate_elf(header->e_ident);
	printf("ELF Header Information:\n");
	display_magic_numbers(header->e_ident);
	display_class(header->e_ident);
	display_data_encoding(header->e_ident);
	display_elf_version(header->e_ident);
	display_os_abi(header->e_ident);
	display_abi_version(header->e_ident);
	display_elf_type(header->e_type, header->e_ident);
	display_entry_point(header->e_entry, header->e_ident);

	free(header);
	close_elf_file(file_descriptor);
	return (0);
}

