/*
 * elf.h
 * Copyright (C) Feb 10, 2014 by lidq
 *
 * elf可重定位头文件
 */

#ifndef _ELF_H_
#define _ELF_H_

#include <kernel/typedef.h>

#define EI_NIDENT 16

typedef struct elf32_hdr
{
	u8 e_ident[EI_NIDENT];
	u16 e_type;
	u16 e_machine;
	u32 e_version;
	u32 e_entry; /* Entry point */
	u32 e_phoff;
	u32 e_shoff;
	u32 e_flags;
	u16 e_ehsize;
	u16 e_phentsize;
	u16 e_phnum;
	u16 e_shentsize;
	u16 e_shnum;
	u16 e_shstrndx;
} Elf32_Ehdr;

typedef struct elf32_phdr
{
	u32 p_type;
	u32 p_offset;
	u32 p_vaddr;
	u32 p_paddr;
	u32 p_filesz;
	u32 p_memsz;
	u32 p_flags;
	u32 p_align;
} Elf32_Phdr;

typedef struct elf32_shdr
{
	u32 sh_name;
	u32 sh_type;
	u32 sh_flags;
	u32 sh_addr;
	u32 sh_offset;
	u32 sh_size;
	u32 sh_link;
	u32 sh_info;
	u32 sh_addralign;
	u32 sh_entsize;
} Elf32_Shdr;

typedef struct elf32_rel
{
	u32 r_offset;
	u32 r_info;
} Elf32_Rel;

typedef struct elf32_sym
{
	u32 st_name;
	u32 st_value;
	u32 st_size;
	u8 st_info;
	u8 st_other;
	u16 st_shndx;
} Elf32_Sym;

#endif
