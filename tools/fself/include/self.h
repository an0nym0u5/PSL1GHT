#ifndef __SELF_H__
#define __SELF_H__

#include "common.h"
#include "tools.h"

#define SCE_MAGIC 0x53434500

typedef struct {
	uint32_t magic;
	uint32_t version;
	uint16_t flags;
	uint16_t type;
	uint32_t metadata_offset;
	uint64_t header_len;
	uint64_t elf_filesize;
	uint64_t unknown;
	uint64_t appinfo_offset;
	uint64_t elf_offset;
	uint64_t phdr_offset;
	uint64_t shdr_offset;
	uint64_t section_info_offset;
	uint64_t sceversion_offset;
	uint64_t controlinfo_offset;
	uint64_t controlinfo_size;
	uint64_t padding;
} __attribute__((packed)) SELF;

typedef struct {
	uint64_t authid;
	uint32_t vendor_id;
	uint32_t self_type;
	uint32_t version;
	uint8_t padding[12];
} __attribute__((packed)) APP_INFO;

typedef struct {
  uint64_t offset;
  uint64_t size;
  uint32_t compressed; // 2=compressed
  uint32_t unknown1;
  uint32_t unknown2;
  uint32_t encrypted; // 1=encrypted
} __attribute__((packed)) SECTION_INFO;

typedef struct {
  uint32_t unknown1;
  uint32_t unknown2;
  uint32_t size;
  uint32_t unknown3;
  uint16_t section_idx;
  uint16_t unknown4;
  uint32_t unknown5;
  uint32_t unknown6;
  uint32_t unknown7;
  uint64_t offset;
  uint64_t str_size;
} __attribute__((packed)) SCEVERSION_INFO;

typedef struct {
	uint32_t type; // 1==control flags; 2==file digest; 3==npdrm header
	uint32_t size;
	uint64_t cont_flag; // 1==next block; 0==end block
	union {
		// type 1
		struct {
			uint32_t control_flags[8];
		} control_flags;

		// type 2
		struct {
			uint8_t digest1[20];
			uint8_t digest2[20];
			uint8_t padding[8];
		} file_digest;

		struct {
			uint32_t data[32];
		} npdrm;
	};
} __attribute__((packed)) CONTROL_INFO;

typedef struct {
  //uint8_t ignore[32];
  uint8_t key[16];
  uint8_t key_pad[16];
  uint8_t iv[16];
  uint8_t iv_pad[16];
} __attribute__((packed)) METADATA_INFO;

typedef struct {
  uint64_t signature_input_length;
  uint32_t unknown1;
  uint32_t section_count;
  uint32_t key_count;
  uint32_t signature_info_size;
  uint64_t unknown2;
} __attribute__((packed)) METADATA_HEADER;

typedef struct {
  uint64_t data_offset;
  uint64_t data_size;
  uint32_t type; // 1 = shdr, 2 == phdr
  uint32_t program_idx;
  uint32_t unknown;
  uint32_t sha1_idx;
  uint32_t encrypted; // 3=yes; 1=no
  uint32_t key_idx;
  uint32_t iv_idx;
  uint32_t compressed; // 2=yes; 1=no
} __attribute__((packed)) METADATA_SECTION_HEADER;

typedef struct {
  uint8_t sha1[20];
  uint8_t padding[12];
  uint8_t hmac_key[64];
} __attribute__((packed)) SECTION_HASH;

typedef struct {
  uint32_t unknown1;
  uint32_t signature_size;
  uint64_t unknown2;
  uint64_t unknown3;
  uint64_t unknown4;
  uint64_t unknown5;
  uint32_t unknown6;
  uint32_t unknown7;
} __attribute__((packed)) SIGNATURE_INFO;

typedef struct {
  uint8_t r[21];
  uint8_t s[21];
  uint8_t padding[6];
} __attribute__((packed)) SIGNATURE;


typedef struct {
  uint8_t *data;
  uint64_t size;
  uint64_t offset;
} SELF_SECTION;

void self_read_headers(FILE *in,SELF *self,APP_INFO *app_info,ELF *elf,ELF_PHDR **phdr, ELF_SHDR **shdr, SECTION_INFO **section_info,SCEVERSION_INFO *sceversion_info,CONTROL_INFO **control_info);

void self_write_self_header(char *self_data,uint64_t offset,SELF *in);
void self_write_appinfo_header(char *self_data,uint64_t offset,APP_INFO *in);
void self_write_elf_header(char *self_data,uint64_t offset,ELF *in);
void self_write_phdr_header(char *self_data,uint64_t offset,ELF *elf_hdr,ELF_PHDR *in);
void self_write_sectioninfo_header(char *self_data,uint64_t offset,ELF *elf_hdr,SECTION_INFO *in);
void self_write_sceversion_header(char *self_data,uint64_t offset,SCEVERSION_INFO *in);
void self_write_control_info_header(char *self_data,uint64_t offset,CONTROL_INFO *in,int npdrm);

void self_build_app_info_header(APP_INFO *app_info,int npdrm);
void self_build_sceversion_header(SCEVERSION_INFO *info,const void *elf_data,uint64_t elfOffset);
void self_build_controlinfo_header(CONTROL_INFO **control_info,int *info_len,const void *elf_data,int elf_len,int npdrm);
void self_build_self_header(SELF *self,ELF *elf_hdr,uint64_t *headerEnd,uint64_t *elfOffset,int elf_filesize,int ctrl_info_size,int npdrm);
void self_build_elf_section_info_headers(ELF *elf_hdr,ELF_PHDR **phdrs,ELF_SHDR **shdrs,SECTION_INFO **sec_info,const void *elf_data,uint64_t elfOffset);

#endif
