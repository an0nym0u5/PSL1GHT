#ifndef __LIBFONT_FT_H__
#define __LIBFONT_FT_H__


#include <ppu-types.h>
#include <font/libfont.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FONT_LIBRARY_TYPE_FREETYPE  (2)

typedef struct _font_library_config_FT
{
    void* library;
    fontMemoryInterface MemoryIF;
} fontLibraryConfigFT;

typedef struct _font_renderer_config_FT
{
    struct
    {
        void* buffer;
        uint32_t initSize;
        uint32_t maxSize;
        uint32_t expandSize;
        uint32_t resetSize;
    } BufferingPolicy;
} fontRendererConfigFT;

static inline void fontLibraryConfigFT_initialize(fontLibraryConfigFT* config)
{
    config->library = (void*)0;
    fontMemoryInterface_initialize(&config->MemoryIF);
    return;
}

static inline int fontInitLibraryFreeType(fontLibraryConfigFT* config,const fontLibrary**lib)
{
    extern void fontFTGetStubRevisionFlags(uint64_t*revisionFlags);
    extern int fontInitLibraryFreeTypeWithRevision(uint64_t,fontLibraryConfigFT*,const fontLibrary**lib);
    uint64_t revisionFlags = 0LL;
    
    fontFTGetStubRevisionFlags(&revisionFlags);
    return fontInitLibraryFreeTypeWithRevision(revisionFlags,config,lib);
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LIBFONT_FT_H__ */

