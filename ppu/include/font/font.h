/*
 * libfont.h
 */

#ifndef __LIBFONT_H__
#define __LIBFONT_H__

#include <ppu-types.h>

#ifdef __cplusplus
extern "C" {
#endif


#define FONT_SYSTEM_MAX                             (16)
#define FONT_FILE_CACHE_SIZE                        (1*1024*1024) //1MB

#define FONT_LIBRARY_TYPE_NONE                      (0)
#define FONT_LIBRARY_TYPE_FREETYPE                  (2)

#define FONT_OPEN_MODE_DEFAULT                      (0)
#define FONT_OPEN_MODE_IGNORE_VERTICAL_METRICS      (1<<0)

#define FONT_GRAPHICS_DRAW_TYPE_MONO                (0) 
#define FONT_GRAPHICS_DRAW_TYPE_COLOR               (1) 
#define FONT_GRAPHICS_DRAW_TYPE_COLOR_REVERSE       (2) 

#define FONT_GLYPH_OUTLINE_CONTROL_DISTANCE_DEFAULT (0.125f)

#define FONT_OK                                     CELL_OK
#define FONT_ERROR_FATAL                            (0x80540001)
#define FONT_ERROR_INVALID_PARAMETER                (0x80540002)
#define FONT_ERROR_UNINITIALIZED                    (0x80540003)
#define FONT_ERROR_INITIALIZE_FAILED                (0x80540004)
#define FONT_ERROR_INVALID_CACHE_BUFFER             (0x80540005)
#define FONT_ERROR_ALREADY_INITIALIZED              (0x80540006)
#define FONT_ERROR_ALLOCATION_FAILED                (0x80540007)
#define FONT_ERROR_NO_SUPPORT_FONTSET               (0x80540008)
#define FONT_ERROR_OPEN_FAILED                      (0x80540009)
#define FONT_ERROR_READ_FAILED                      (0x8054000a)
#define FONT_ERROR_FONT_OPEN_FAILED                 (0x8054000b)
#define FONT_ERROR_FONT_NOT_FOUND                   (0x8054000c)
#define FONT_ERROR_FONT_OPEN_MAX                    (0x8054000d)
#define FONT_ERROR_FONT_CLOSE_FAILED                (0x8054000e)
#define FONT_ERROR_ALREADY_OPENED                   (0x8054000f)

#define FONT_ERROR_NO_SUPPORT_FUNCTION              (0x80540010)
#define FONT_ERROR_NO_SUPPORT_CODE                  (0x80540011)
#define FONT_ERROR_NO_SUPPORT_GLYPH                 (0x80540012)

#define FONT_ERROR_BUFFER_SIZE_NOT_ENOUGH           (0x80540016)

#define FONT_ERROR_RENDERER_ALREADY_BIND            (0x80540020)
#define FONT_ERROR_RENDERER_UNBIND                  (0x80540021)
#define FONT_ERROR_RENDERER_INVALID                 (0x80540022)
#define FONT_ERROR_RENDERER_ALLOCATION_FAILED       (0x80540023)
#define FONT_ERROR_ENOUGH_RENDERING_BUFFER          (0x80540024)

#define FONT_ERROR_NO_SUPPORT_SURFACE               (0x80540040)

#define fontVertexesGlyph_getDataAddr(vGlyph)       ((vGlyph)?(vGlyph)->data:(fontVertexesGlyphData*)0)
#define fontVertexesGlyph_getDataSize(vGlyph)       (((vGlyph)&&(vGlyph)->data)?(vGlyph)->data->size:0)
#define fontVertexesGlyph_getSubHeader(vGlyph)      ((vGlyph)?(vGlyph)->subHeader:(fontVertexesGlyphSubHeader*)0)

/*
 * font enums
 */
/*
enum {
   FONT_SYSTEM_FONT0 = 0,
   FONT_SYSTEM_GOTHIC_LATIN = FONT_SYSTEM_FONT0,
   FONT_SYSTEM_GOTHIC_JP,
   FONT_SYSTEM_SANS_SERIF,
   FONT_SYSTEM_SERIF,
   FONT_USER_FONT0 = SYSTEM_FONT_MAX
}FontEnum;
*/

/*
 * font structs
 */
typedef struct _font_entry
{
    u32 lock;
    u32 uniqueId;
    const void *fontLib ATTRIBUTE_PRXPTR;
    void *fontH ATTRIBUTE_PRXPTR;
} fontEntry;

typedef struct _file_cache
{
    u32 *buffer ATTRIBUTE_PRXPTR;
    u32 size;
} fileCache;

typedef struct _font_config
{
    fileCache FileCache;
    u32 fontEntriesMax;
    fontEntry *fontEntries ATTRIBUTE_PRXPTR;
    u32 flags;
} fontConfig;

typedef struct _font_library
{
    u32 libraryType;
    u32 libraryVersion;
    u32 **SystemClosed ATTRIBUTE_PRXPTR;
} fontLibrary;

typedef struct _font_type
{
    u32 type;
    u32 map;
} fontType;

typedef struct _font_horizontal_layout
{
    float baseLineY;
    float lineHeight;
    float effectHeight;
} fontHorizontalLayout;

typedef struct _font_vertical_layout
{
    float baseLineX;
    float lineWidth;
    float effectWidth;
} fontVerticalLayout;

typedef struct _font_glyph_metrics
{
    float width;
    float height;
    struct
    {
        float bearingX;
        float bearingY;
        float advance;
    } Horizontal;
    struct
    {
        float bearingX;
        float bearingY;
        float advance;
    } Vertical;
} fontGlyphMetrics;

typedef struct _font_glyph_outline
{
    s16 contoursCount;
    s16 pointsCount;
    struct
    {
        float x;
        float y;
    } *Points ATTRIBUTE_PRXPTR;
    u8 *pointTags ATTRIBUTE_PRXPTR;
    u16 *contourIndexs ATTRIBUTE_PRXPTR;
    u32 flags;
    void *generateEnv ATTRIBUTE_PRXPTR;
} fontGlyphOutline;

typedef struct _font_glyph
{
    u16 CF_type;
    u16 type;
    u32 size;
    fontGlyphMetrics Metrics;
    fontGlyphOutline Outline;
} fontGlyph;

typedef struct _font_vertexes_glyph_sub_header
{
    u32 size;
    float SystemReserved[11];
} fontVertexesGlyphSubHeader;

typedef struct _font_vertexes_glyph_data
{
    const u32 size;
    float *SystemClosed ATTRIBUTE_PRXPTR;
} fontVertexesGlyphData;

typedef struct _font_vertexes_glyph
{
    fontVertexesGlyphData *data ATTRIBUTE_PRXPTR;
    fontVertexesGlyphSubHeader *subHeader ATTRIBUTE_PRXPTR;
} fontVertexesGlyph;

typedef struct _font_glyph_bounding_box
{
    struct
    {
        float x;
        float y;
    } Min;
    struct
    {
        float x;
        float y;
    } Max;
} fontGlyphBoundingBox;


typedef struct _fontKerning
{
    float offsetX;
    float offsetY;
} fontKerning;

typedef struct _font_glyph_style
{
    struct
    {
        float widthPixel;
        float heightPixel;
    } Scale;
    struct
    {
        float weight;
        float slant;
    } Effect;

} fontGlyphStyle;

typedef struct _font_render_surface
{
    void *buffer ATTRIBUTE_PRXPTR;
    s32 widthByte;
    s32 pixelSizeByte;
    s32 width,height;
    struct
    {
        u32 x0;
        u32 y0;
        u32 x1;
        u32 y1;
    } Scissor;
} fontRenderSurface;

typedef struct _font_image_trans_info
{
    u8 *Image ATTRIBUTE_PRXPTR;
    u32 imageWidthByte;
    u32 imageWidth;
    u32 imageHeight;
    void *Surface ATTRIBUTE_PRXPTR;
    u32 surfWidthByte;
} fontImageTransInfo;

typedef struct _font
{
    u32 *SystemReserved[64] ;
} fontContainer;

typedef struct _font_renderer_config
{
    struct
    {
        void *buffer ATTRIBUTE_PRXPTR;
        u32 initSize;
        u32 maxSize;
        u32 expandSize;
        u32 resetSize;
    } BufferingPolicy;
} fontRendererConfig;

typedef struct _font_renderer
{
    void *systemReserved[64];
} fontRenderer;

typedef struct _font_graphics
{
    u32 graphicsType;
    u32 *SystemClosed ATTRIBUTE_PRXPTR;
} fontGraphics;

typedef struct _font_graphics_draw_context
{
    void *SystemReserved[64];
} fontGraphicsDrawContext;


/*
 * font functions
 */
//s32 fontInitLibrary(fontLibraryConfig*,const fontLibrary**lib);
void fontGetRevisionFlags(u64*revisionFlags);
void fontGetInitializedRevisionFlags(u64*revisionFlags);
s32 fontInitializeWithRevision(u64 revisionFlags,fontConfig *config);


s32 fontGetLibrary(fontContainer *fc,const fontLibrary**lib,u32 *type);
s32 fontGlyphGetScalePixel(fontGlyph*,float *w,float *h);
s32 fontSetScalePixel(fontContainer *fc,float w,float h);
s32 fontGetScalePixel(fontContainer *fc,float *w,float *h);
s32 fontGetKerning(fontContainer *fc,u32 preCode,u32 code,fontKerning *kerning);

s32 fontSetFontsetOpenMode(const fontLibrary*,u32 openMode);
s32 fontSetFontOpenMode(const fontLibrary*,u32 openMode);

s32 fontOpenFontset(const fontLibrary*,fontType*,fontContainer *fc);
s32 fontOpenFontsetOnMemory(const fontLibrary*,fontType*,fontContainer *fc);

s32 fontOpenFontFile(const fontLibrary*,u8* fontPath,u32 subNum,s32 uniqueID,fontContainer *fc);
s32 fontOpenFontMemory(const fontLibrary*,void* fontAddr,u32 fontSize,u32 subNum,s32 uniqueID,fontContainer *fc);
s32 fontOpenFontInstance(fontContainer *org,fontContainer *ins);

s32 fontAdjustGlyphExpandBuffer(fontContainer *fc,s32 pointN,s32 contourN);
s32 fontGetGlyphExpandBufferInfo(fontContainer *fc,s32* pointN,s32* contourN);

s32 fontSetResolutionDpi(fontContainer *fc,u32 hDpi,u32 vDpi);
s32 fontGetResolutionDpi(fontContainer *fc,u32 *hDpi,u32 *vDpi);

s32 fontAdjustFontScaling(fontContainer *fc,float fontScale);
s32 fontSetScalePoint(fontContainer *fc,float w,float h);
s32 fontSetEffectSlant(fontContainer *fc,float effectSlant);
s32 fontGetScalePoint(fontContainer *fc,float *w,float *h);

s32 fontSetEffectWeight(fontContainer *fc,float effectWeight);
s32 fontGetEffectWeight(fontContainer *fc,float *effectWeight);

s32 fontGetEffectSlant(fontContainer *fc,float *effectSlant);

s32 fontGetHorizontalLayout(fontContainer *fc,fontHorizontalLayout* layout);
s32 fontGetVerticalLayout(fontContainer *fc,fontVerticalLayout* layout);

s32 fontGetFontIdCode(fontContainer *fc,u32 code,u32*fontId,u32*fontcode);

s32 fontGetCharGlyphMetrics(fontContainer *fc,u32 code,fontGlyphMetrics*);
s32 fontGetCharGlyphMetricsVertical(fontContainer *fc,u32 code,fontGlyphMetrics*);

s32 fontSetupRenderScalePoint(fontContainer *fc,float w,float h);
s32 fontSetupRenderScalePixel(fontContainer *fc,float w,float h);

s32 fontSetupRenderEffectWeight(fontContainer *fc,float additionalWeight);
s32 fontSetupRenderEffectSlant(fontContainer *fc,float effectSlant);

s32 fontGetRenderScalePoint(fontContainer *fc,float *w,float *h);
s32 fontGetRenderScalePixel(fontContainer *fc,float *w,float *h);

s32 fontGetRenderEffectWeight(fontContainer *fc,float *effectWeight);
s32 fontGetRenderEffectSlant(fontContainer *fc,float *effectSlant);

s32 fontGetRenderCharGlyphMetrics(fontContainer *fc,u32 code,fontGlyphMetrics*);
s32 fontGetRenderCharGlyphMetricsVertical(fontContainer *cf,u32 code,fontGlyphMetrics*metrics);
s32 fontGetRenderScaledKerning(fontContainer *fc,u32 preCode,u32 code,fontKerning* kerning);

s32 fontGenerateCharGlyph(fontContainer *fc,u32 code,fontGlyph**);
s32 fontGenerateCharGlyphVertical(fontContainer *fc,u32 code,fontGlyph**);

s32 fontDeleteGlyph(fontContainer *fc,fontGlyph*);

s32 fontDelete(const fontLibrary*,void*);

void fontRenderSurfaceInit(fontRenderSurface*,void* buffer,s32 bufWidthByte,s32 pixelSizeByte,s32 w,s32 h);
void fontRenderSurfaceSetScissor(fontRenderSurface*,s32 x0,s32 y0,u32 w,u32 h);

s32 fontRenderCharGlyphImage(fontContainer *fc,u32 code,fontRenderSurface*,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);
s32 fontRenderCharGlyphImageHorizontal(fontContainer *fc,u32 code,fontRenderSurface*,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);
s32 fontRenderCharGlyphImageVertical(fontContainer *fc,u32 code,fontRenderSurface*,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);

s32 fontCreateRenderer(const fontLibrary* lib,fontRendererConfig* confing,fontRenderer* renderer);
s32 fontBindRenderer(fontContainer *fc,fontRenderer*);
s32 fontUnbindRenderer(fontContainer *fc);
s32 fontGetBindingRenderer(fontContainer *fc,fontRenderer**);
s32 fontDestroyRenderer(fontRenderer* renderer);

s32 fontGlyphRenderImage(fontGlyph*,fontGlyphStyle*,fontRenderer*,fontRenderSurface*surf,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);
s32 fontGlyphRenderImageHorizontal(fontGlyph*,fontGlyphStyle*,fontRenderer*,fontRenderSurface*surf,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);
s32 fontGlyphRenderImageVertical(fontGlyph*,fontGlyphStyle*,fontRenderer*,fontRenderSurface*surf,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);

s32 fontGlyphGetHorizontalShift(fontGlyph*,float*shiftX,float*shiftY);
s32 fontGlyphGetVerticalShift(fontGlyph*,float*shiftX,float*shiftY);
s32 fontGlyphGetOutlineControlDistance(fontGlyph*,float maxScale,float baseControlDistance,float*controlDistance);

//s32 fontGlyphGetOutlineVertexes(fontGlyph* glyph,float controlDistance,fontGetOutlineVertexesIF* getIF,fontGlyphBoundingBox* bbox,u32* vcount);
s32 fontGlyphGetVertexesGlyphSize(fontGlyph* glyph,float controlDistance,u32* useSize);
s32 fontGlyphSetupVertexesGlyph(fontGlyph* glyph,float controlDistance,u32* mappedBuf,u32 mappedBufSize,fontVertexesGlyph* vGlyph,u32* dataSize);
s32 fontVertexesGlyphRelocate(fontVertexesGlyph* vGlyph,fontVertexesGlyph* vGlyph2,fontVertexesGlyphSubHeader*,u32* localBuf,u32 copySize);

s32 fontGraphicsSetupDrawContext(const fontGraphics*,fontGraphicsDrawContext*);

s32 fontGraphicsSetDrawType(fontGraphicsDrawContext*,u32 type);
s32 fontGraphicsGetDrawType(fontGraphicsDrawContext*,u32*type);

s32 fontGraphicsSetFontRGBA(fontGraphicsDrawContext*,float fontRGBA[4]);
s32 fontGraphicsGetFontRGBA(fontGraphicsDrawContext*,float fontRGBA[4]);
s32 fontGraphicsSetLineRGBA(fontGraphicsDrawContext*,float lineRGBA[4]);
s32 fontGraphicsGetLineRGBA(fontGraphicsDrawContext*,float lineRGBA[4]);

s32 fontGraphicsSetScalePixel(fontGraphicsDrawContext*,float w,float h);
s32 fontGraphicsGetScalePixel(fontGraphicsDrawContext*,float *w,float *h);

s32 fontClearFileCache(void);
s32 fontCloseFont(fontContainer *fc);
s32 fontEndGraphics(const fontGraphics*);
s32 fontEndLibrary(const fontLibrary*lib);
s32 fontEnd(void);

/*
 * font helpers
 */

static inline void fontConfigInitialize(fontConfig* config)
{
    config->FileCache.buffer = (u32*)0;
    config->FileCache.size = 0;
    config->fontEntriesMax = 0;
    config->fontEntries = (fontEntry*)0;
    config->flags = 0x00000000;
}

static inline void fontRendererConfigInitialize(fontRendererConfig* config)
{
    config->BufferingPolicy.buffer = (void*)0;
    config->BufferingPolicy.initSize = 0;
    config->BufferingPolicy.maxSize  = 0;
    config->BufferingPolicy.expandSize = 1;
    config->BufferingPolicy.resetSize  = 0;
}

static inline void fontRendererConfigSetAllocateBuffer(fontRendererConfig* config,u32 initSize,u32 maxSize)
{
    config->BufferingPolicy.buffer = (void*)0;
    config->BufferingPolicy.initSize = initSize;
    config->BufferingPolicy.maxSize  = maxSize;
    config->BufferingPolicy.expandSize = 1;
    config->BufferingPolicy.resetSize  = 0;
}

static inline s32 fontInit(fontConfig *config)
{
    u64 revisionFlags = 0LL;

    fontGetRevisionFlags(&revisionFlags);
    return fontInitializeWithRevision(revisionFlags,config);
}

/*
 * font callbacks
 */
void *fontMalloc(void *obj, u32 size);
void fontFree(void *obj, void *ptr);
void *fontRealloc(void *obj, void *ptr, u32 size);
void *fontCalloc(void *obj, u32 num, u32 size);

typedef void* (*fontMallocCallback)(void*obj,u32 size);
typedef void  (*fontFreeCallback)(void*obj,void*ptr);
typedef void* (*fontReallocCallback)(void*obj,void*ptr,u32 size);
typedef void* (*fontCallocCallback)(void*obj,u32 num,u32 size);
typedef void  (*fontGetOutlineVertexCallback)(void*arg,s32 contourN,s32 vertexNumber,s32 vertexAttr,float x,float y);

typedef struct fontMemoryInterface
{
    void *Object ATTRIBUTE_PRXPTR;
    fontMallocCallback Malloc ATTRIBUTE_PRXPTR;
    fontFreeCallback Free ATTRIBUTE_PRXPTR;
    fontReallocCallback Realloc ATTRIBUTE_PRXPTR;
    fontCallocCallback Calloc ATTRIBUTE_PRXPTR;
} fontMemoryInterface;

static inline void fontMemoryInterfaceInitialize(fontMemoryInterface*mIF)
{
    mIF->Object = (void*)0;
    mIF->Malloc = (fontMallocCallback)0;
    mIF->Free = (fontFreeCallback)0;
    mIF->Realloc = (fontReallocCallback)0;
    mIF->Calloc = (fontCallocCallback)0;
}

/*
typedef struct fontGetOutlineVertexesIF
{
    fontGetOutlineVertexCallback callback;
    void* arg;
} fontGetOutlineVertexesIF;
*/

/*
 * fontFT structs
 */

typedef struct _font_library_config_FT
{
    void *library ATTRIBUTE_PRXPTR;
    fontMemoryInterface MemoryIF;
} fontLibraryConfigFT;

typedef struct _font_renderer_config_FT
{
    struct
    {
        void* buffer ATTRIBUTE_PRXPTR;
        u32 initSize;
        u32 maxSize;
        u32 expandSize;
        u32 resetSize;
    } BufferingPolicy;
} fontRendererConfigFT;


/*
 * fontFT functions
 */
void fontFTGetRevisionFlags(u64*revisionFlags);
s32 fontFTInitLibraryFreeTypeWithRevision(u64 revisionFlags,fontLibraryConfigFT *config,fontLibrary **lib);
void fontFTGetInitializedRevisionFlags(u64*revisionFlags);


/*
 * fontFT helpers
 */
static inline void fontFTLibraryConfigInitialize(fontLibraryConfigFT* config)
{
    config->library = (void*)0;
    fontMemoryInterfaceInitialize(&config->MemoryIF);
    return;
}

static inline s32 fontFTInitLibraryFreeType(fontLibraryConfigFT* config,fontLibrary **lib)
{
    u64 revisionFlags = 0LL;

    fontFTGetRevisionFlags(&revisionFlags);
    return fontFTInitLibraryFreeTypeWithRevision(revisionFlags,config,lib);
}

static inline void fontFTRendererConfigInitialize(fontRendererConfigFT* config)
{
    config->BufferingPolicy.buffer = (void*)0;
    config->BufferingPolicy.initSize = 0;
    config->BufferingPolicy.maxSize  = 0;
    config->BufferingPolicy.expandSize = 1;
    config->BufferingPolicy.resetSize  = 0;
}

static inline void fontFTRendererConfigSetAllocateBuffer(fontRendererConfigFT* config,u32 initSize,u32 maxSize)
{
    config->BufferingPolicy.buffer = (void*)0;
    config->BufferingPolicy.initSize = initSize;
    config->BufferingPolicy.maxSize  = maxSize;
    config->BufferingPolicy.expandSize = 1;
    config->BufferingPolicy.resetSize  = 0;
}



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LIBFONT_H__ */

