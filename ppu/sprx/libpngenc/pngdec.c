/* libpng.c
*/

#include <malloc.h>
#include <string.h>
#include <ppu-asm.h>

#include <pngdec/pngdec.h>

static void* png_malloc(u32 size,void *usrdata)
{
	return malloc(size);
}

static void png_free(void *ptr,void *usrdata)
{
	return free(ptr);
}

static s32 decodePNG(pngDecSource *src,pngData *out)
{
	s32 mHandle,sHandle,ret;
	u32 space_allocated;
	u64 bytes_per_line;
	pngDecInfo DecInfo;
	pngDecInParam inParam;
	pngDecOutParam outParam;
	pngDecDataInfo DecDataInfo;
	pngDecThreadInParam InThdParam;
	pngDecThreadOutParam OutThdParam;

	InThdParam.enable = 0;
	InThdParam.ppu_prio = 512;
	InThdParam.spu_prio = 200;
	InThdParam.malloc_func = __get_addr32(__get_opd32(png_malloc));
	InThdParam.malloc_arg = 0; // no args
	InThdParam.free_func = __get_addr32(__get_opd32(png_free));
	InThdParam.free_arg = 0; // no args

	ret= pngDecCreate(&mHandle, &InThdParam, &OutThdParam);

	out->bmp_out = NULL;
	if(ret==0) {
		ret = pngDecOpen(mHandle,&sHandle,src,&space_allocated);
		if(ret==0) {
			ret = pngDecReadHeader(mHandle,sHandle,&DecInfo);
			if(ret==0) {
				inParam.cmd_ptr = 0;
				inParam.mode = PNGDEC_TOP_TO_BOTTOM;
				inParam.space = PNGDEC_ARGB;
				inParam.bit_depth = 8;
				inParam.pack_flag = 1;
				if(DecInfo.space==PNGDEC_GRAYSCALE_ALPHA || DecInfo.space==PNGDEC_RGBA || DecInfo.chunk_info&0x10)
					inParam.alpha_select = 0;
				else
					inParam.alpha_select = 1;

				inParam.alpha = 0xff;

				ret = pngDecSetParameter(mHandle,sHandle,&inParam,&outParam);
			}

			if(ret==0) {
				out->pitch = bytes_per_line = outParam.width*4;
				out->bmp_out = malloc(out->pitch*outParam.height);
				if(!out->bmp_out)
					ret = -1;
				else {
					memset(out->bmp_out,0,(bytes_per_line*outParam.height));
					
					ret = pngDecDecodeData(mHandle,sHandle,out->bmp_out,&bytes_per_line,&DecDataInfo);
					if(ret==0 && DecDataInfo.status==0) {
						out->width = outParam.width;
						out->height = outParam.height;

						ret = 0;
					}
				}
			}
			pngDecClose(mHandle,sHandle);
		}
		if(ret && out->bmp_out) {
			free(out->bmp_out);
			out->bmp_out = NULL;
		}

		pngDecDestroy(mHandle);
	}
	return ret;
}

s32 pngLoadFromFile(const char *filename,pngData *out)
{
	pngDecSource source;

	memset(&source,0,sizeof(pngDecSource));

	source.stream = PNGDEC_FILE;
	source.file_name = __get_addr32(filename);
	source.enable = PNGDEC_DISABLE;

	return decodePNG(&source,out);
}

s32 pngLoadFromBuffer(const void *buffer,u32 size,pngData *out)
{
	pngDecSource source;

	memset(&source,0,sizeof(pngDecSource));

	source.stream = PNGDEC_BUFFER;
	source.stream_ptr = __get_addr32(buffer);
	source.stream_size = size;
	source.enable = PNGDEC_DISABLE;

	return decodePNG(&source,out);
}
