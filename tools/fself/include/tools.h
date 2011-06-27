#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "common.h"

typedef struct {
	uint8_t ident[16];
	uint16_t type;
	uint16_t machine;
	uint32_t version;
	uint64_t entry_point;
	uint64_t phdr_offset;
	uint64_t shdr_offset;
	uint16_t flags;
	uint32_t header_size;
	uint16_t phent_size;
	uint16_t phnum;
	uint16_t shent_size;
	uint16_t shnum;
	uint16_t shstrndx;
} __attribute__((packed)) ELF;

typedef struct {
  uint32_t type;
  uint32_t flags;
  uint64_t offset_in_file;
  uint64_t vitual_addr;
  uint64_t phys_addr;
  uint64_t segment_size;
  uint64_t segment_mem_size;
  uint64_t alignment;
} __attribute__((packed)) ELF_PHDR;

typedef struct {
  uint32_t name_idx;
  uint32_t type;
  uint64_t flags;
  uint64_t virtual_addr;
  uint64_t offset_in_file;
  uint64_t segment_size;
  uint32_t link;
  uint32_t info;
  uint64_t addr_align;
  uint64_t entry_size;
} __attribute__((packed)) ELF_SHDR;

void elf_read_elf_header(const void *elf_data,ELF *elf_hdr);
void elf_read_phdr_header(const void *elf_data,ELF *elf_hdr,ELF_PHDR **elf_phdr);
void elf_read_shdr_header(const void *elf_data,ELF *elf_hdr,ELF_SHDR **elf_shdr);
int elf_get_shstr_idx(const void *elf_data,const char *section_name);
uint64_t elf_get_shstr_off(const void *elf_data,const char *section_name);

void elf_write_elf_header(void *elf_data,ELF *elf_hdr);
void elf_write_phdr_header(void *elf_data,ELF *elf_hdr,ELF_PHDR *phdr);

void sha1(const void *data,uint32_t len,uint8_t *digest);
void sha1_hmac(const void *data,uint32_t len,uint8_t *key,uint8_t *digest);

void get_rand(uint8_t *bfr,uint32_t size);

void fail(const char *a, ...);

#endif
