#include <stdarg.h>
#include "tools.h"
#include "sha1.h"

static void sha1finalize(struct SHA1Context *ctx,uint8_t *digest)
{
	uint32_t i;

	for(i = 0; i < 5; i++) {
		*digest++ = ctx->Message_Digest[i] >> 24 & 0xff;
		*digest++ = ctx->Message_Digest[i] >> 16 & 0xff;
		*digest++ = ctx->Message_Digest[i] >> 8 & 0xff;
		*digest++ = ctx->Message_Digest[i] & 0xff;
	}
}

void fail(const char *a, ...)
{
	char msg[1024];
	va_list va;

	va_start(va, a);
	vsnprintf(msg, sizeof msg, a, va);
	fprintf(stderr, "%s\n", msg);
	perror("perror");

	exit(1);
}

void elf_read_elf_header(const void *elf_data,ELF *elf_hdr)
{
	memcpy(elf_hdr,elf_data,sizeof(ELF));

	elf_hdr->type = swap16 (elf_hdr->type);
	elf_hdr->machine = swap16 (elf_hdr->machine);
	elf_hdr->version = swap32 (elf_hdr->version);
	elf_hdr->entry_point = swap64 (elf_hdr->entry_point);
	elf_hdr->phdr_offset = swap64 (elf_hdr->phdr_offset);
	elf_hdr->shdr_offset = swap64 (elf_hdr->shdr_offset);
	elf_hdr->flags = swap16 (elf_hdr->flags);
	elf_hdr->header_size = swap32 (elf_hdr->header_size);
	elf_hdr->phent_size = swap16 (elf_hdr->phent_size);
	elf_hdr->phnum = swap16 (elf_hdr->phnum);
	elf_hdr->shent_size = swap16 (elf_hdr->shent_size);
	elf_hdr->shnum = swap16 (elf_hdr->shnum);
	elf_hdr->shstrndx = swap16 (elf_hdr->shstrndx);
}

void elf_read_phdr_header(const void *elf_data,ELF *elf_hdr,ELF_PHDR **elf_phdr)
{
	uint16_t i;
	ELF_PHDR *phdr = NULL;

	phdr = malloc (sizeof(ELF_PHDR) * elf_hdr->phnum);

	memcpy(phdr,(char*)elf_data + elf_hdr->phdr_offset,sizeof(ELF_PHDR)*elf_hdr->phnum);

	for (i = 0; i < elf_hdr->phnum; i++) {
		phdr[i].type = swap32 (phdr[i].type);
		phdr[i].flags = swap32 (phdr[i].flags);
		phdr[i].offset_in_file = swap64 (phdr[i].offset_in_file);
		phdr[i].vitual_addr = swap64 (phdr[i].vitual_addr);
		phdr[i].phys_addr = swap64 (phdr[i].phys_addr);
		phdr[i].segment_size = swap64 (phdr[i].segment_size);
		phdr[i].segment_mem_size = swap64 (phdr[i].segment_mem_size);
		phdr[i].alignment = swap64 (phdr[i].alignment);
	}

	*elf_phdr = phdr;
}

void elf_read_shdr_header(const void *elf_data,ELF *elf_hdr,ELF_SHDR **elf_shdr)
{
	uint16_t i;
	ELF_SHDR *shdr = NULL;

	shdr = malloc(sizeof(ELF_SHDR) * elf_hdr->shnum);

	memcpy(shdr,(char*)elf_data + elf_hdr->shdr_offset,sizeof(ELF_SHDR)*elf_hdr->shnum);

	for(i=0;i<elf_hdr->shnum;i++) {
		shdr[i].name_idx = swap32(shdr[i].name_idx);
		shdr[i].type = swap32(shdr[i].type);
		shdr[i].flags = swap64(shdr[i].flags);
		shdr[i].virtual_addr = swap64(shdr[i].virtual_addr);
		shdr[i].offset_in_file = swap64(shdr[i].offset_in_file);
		shdr[i].segment_size = swap64(shdr[i].segment_size);
		shdr[i].link = swap32(shdr[i].link);
		shdr[i].info = swap32(shdr[i].info);
		shdr[i].addr_align = swap64(shdr[i].addr_align);
		shdr[i].entry_size = swap64(shdr[i].entry_size);
	}

	*elf_shdr = shdr;
}

int elf_get_shstr_idx(const void *elf_data,const char *section_name)
{
	uint16_t i;
	ELF elf_hdr;
	const char *name = NULL;
	ELF_SHDR *elf_shdr = NULL;
	ELF_SHDR *shstr_sec = NULL;

	elf_read_elf_header(elf_data,&elf_hdr);
	elf_read_shdr_header(elf_data,&elf_hdr,&elf_shdr);
	
	shstr_sec = &elf_shdr[elf_hdr.shstrndx];
	for(i=0;i<elf_hdr.shnum;i++) {
		name = (char*)elf_data + shstr_sec->offset_in_file + elf_shdr[i].name_idx;
		if(strncmp(name,section_name,strlen(section_name))==0) break;
	}
	free(elf_shdr);
	
	if(i>=elf_hdr.shnum) return -1;

	return i;
}

uint64_t elf_get_shstr_off(const void *elf_data,const char *section_name)
{
	uint16_t i;
	ELF elf_hdr;
	uint64_t off = -1;
	const char *name = NULL;
	ELF_SHDR *elf_shdr = NULL;
	ELF_SHDR *shstr_sec = NULL;

	elf_read_elf_header(elf_data,&elf_hdr);
	elf_read_shdr_header(elf_data,&elf_hdr,&elf_shdr);
	
	shstr_sec = &elf_shdr[elf_hdr.shstrndx];
	for(i=0;i<elf_hdr.shnum;i++) {
		name = (char*)elf_data + shstr_sec->offset_in_file + elf_shdr[i].name_idx;
		if(strncmp(name,section_name,strlen(section_name))==0) break;
	}
	if(i<elf_hdr.shnum) off = elf_shdr[i].offset_in_file;

	free(elf_shdr);
	return  off;
}

void elf_write_elf_header(void *elf_data,ELF *elf_hdr)
{
	ELF *out = (ELF*)elf_data;

	memcpy(out->ident,elf_hdr->ident,sizeof(elf_hdr->ident));
	out->type = swap16(elf_hdr->type);
	out->machine = swap16(elf_hdr->machine);
	out->version = swap32(elf_hdr->version);
	out->entry_point = swap64(elf_hdr->entry_point);
	out->phdr_offset = swap64(elf_hdr->phdr_offset);
	out->shdr_offset = swap64(elf_hdr->shdr_offset);
	out->flags = swap16(elf_hdr->flags);
	out->header_size = swap32(elf_hdr->header_size);
	out->phent_size = swap16(elf_hdr->phent_size);
	out->phnum = swap16(elf_hdr->phnum);
	out->shent_size = swap16(elf_hdr->shent_size);
	out->shnum = swap16(elf_hdr->shnum);
	out->shstrndx = swap16(elf_hdr->shstrndx);
}

void elf_write_phdr_header(void *elf_data,ELF *elf_hdr,ELF_PHDR *phdr)
{
	uint16_t i;
	ELF_PHDR *elf_phdr = (ELF_PHDR*)elf_data;

	for(i=0;i<elf_hdr->phnum;i++) {
		elf_phdr[i].type = swap32(phdr[i].type);
		elf_phdr[i].flags = swap32(phdr[i].flags);
		elf_phdr[i].offset_in_file = swap64(phdr[i].offset_in_file);
		elf_phdr[i].vitual_addr = swap64(phdr[i].vitual_addr);
		elf_phdr[i].phys_addr = swap64(phdr[i].phys_addr);
		elf_phdr[i].segment_size = swap64(phdr[i].segment_size);
		elf_phdr[i].segment_mem_size = swap64(phdr[i].segment_mem_size);
		elf_phdr[i].alignment = swap64(phdr[i].alignment);
	}
}

void sha1(const void *data,uint32_t len,uint8_t *digest)
{
	struct SHA1Context ctx;

	SHA1Reset(&ctx);
	SHA1Input(&ctx, data, len);
	SHA1Result(&ctx);

	sha1finalize(&ctx, digest);
}

void sha1_hmac(const void *data,uint32_t len,uint8_t *key,uint8_t *digest)
{
	uint32_t i;
	uint8_t tmp[84]; // opad + hash(ipad + message)
	uint8_t ipad[64];
	struct SHA1Context ctx;

	SHA1Reset(&ctx);

	for(i=0;i<64;i++) {
		tmp[i] = key[i] ^ 0x5c; // opad
		ipad[i] = key[i] ^ 0x36;
	}

	SHA1Input(&ctx, ipad, 64);
	SHA1Input(&ctx, data, len);
	SHA1Result(&ctx);

	sha1finalize(&ctx, tmp + 64);

	sha1(tmp, 84, digest);

}

#ifdef WIN32
void get_rand(uint8_t *bfr,uint32_t size)
{
	HCRYPTPROV hProv;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		fail("unable to open random");

	if (!CryptGenRandom(hProv, size, bfr))
		fail("unable to read random numbers");

	CryptReleaseContext(hProv, 0);
}
#else
void get_rand(uint8_t *bfr,uint32_t size)
{
	FILE *fp;

	fp = fopen("/dev/urandom", "r");
	if (fp == NULL)
		fail("unable to open random");

	if (fread(bfr, size, 1, fp) != 1)
		fail("unable to read random numbers");

	fclose(fp);
}
#endif
