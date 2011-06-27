#include "self.h"

void usage()
{
	printf("fself [options] input.elf output.self\n");
	printf("If output is not specified, fself will default to EBOOT.BIN\n");
	printf("Options:\n");
	printf("\t-n create npdrm self, to be used with pkg.py\n");
}

int main(int argc,char *argv[])
{
	int j,i,npdrm;
	FILE *f = NULL;
	ELF elf_header;
	SELF self_header;
	APP_INFO app_info;
	ELF_PHDR *elf_phdr;
	ELF_SHDR *elf_shdr;
	SECTION_INFO *sec_info;
	SCEVERSION_INFO sceversion_info;
	CONTROL_INFO *control_info = NULL;
	char *iofile[] = { NULL, "EBOOT.BIN" };

	if(argc<2) usage();
	
	npdrm = 0;
	for(i=1;i<argc;i++) {
		if(argv[i][0]=='-') {
			switch(argv[i][1]) {
				case 'n':
					npdrm = 1;
					break;
			}
		} else
			break;
	}
	for(j=0;i<argc;i++,j++) iofile[j] = argv[i];

	if(iofile[0] && iofile[1]) {
		char *elf_data = NULL;
		char *self_data = NULL;
		size_t selfDataSize,ret;
		int info_len,elf_len = 0;
		uint64_t headerEnd,elfOffset;

		f = fopen(iofile[0],"rb");
		if(f) {
			fseek(f,0,SEEK_END);
			elf_len = ftell(f);
			fseek(f,0,SEEK_SET);

			elf_data = malloc(elf_len);
			ret = fread(elf_data,1,elf_len,f);

			fclose(f);

			if(ret!=elf_len) fail("Failed reading ELF");
		}

		elf_read_elf_header(elf_data,&elf_header);

		self_build_app_info_header(&app_info,npdrm);
		self_build_controlinfo_header(&control_info,&info_len,elf_data,elf_len,npdrm);
		self_build_self_header(&self_header,&elf_header,&headerEnd,&elfOffset,elf_len,info_len,npdrm);
		self_build_elf_section_info_headers(&elf_header,&elf_phdr,&elf_shdr,&sec_info,elf_data,elfOffset);
		self_build_sceversion_header(&sceversion_info,elf_data,elfOffset);

		selfDataSize = (size_t)(elfOffset + elf_len);

		self_data = calloc((size_t)(elfOffset + elf_len),1);
		self_write_self_header(self_data,0,&self_header);
		self_write_appinfo_header(self_data,self_header.appinfo_offset,&app_info);
		self_write_elf_header(self_data,self_header.elf_offset,&elf_header);
		self_write_phdr_header(self_data,self_header.phdr_offset,&elf_header,elf_phdr);
		self_write_sectioninfo_header(self_data,self_header.section_info_offset,&elf_header,sec_info);
		self_write_sceversion_header(self_data,self_header.sceversion_offset,&sceversion_info);
		self_write_control_info_header(self_data,self_header.controlinfo_offset,control_info,npdrm);

		memcpy(self_data + elfOffset,elf_data,elf_len);

		ret = 0;
		f = fopen(iofile[1],"wb");
		if(f) {
			ret = fwrite(self_data,1,selfDataSize,f);
			fclose(f);
		} else
			fail("Could not open SELF for writing");

		if(ret!=selfDataSize) fail("Failed writing SELF");
	}

	return 0;
}
