/*
 * libfont.h
 */

#ifndef __LIBFONT_H__
#define __LIBFONT_H__

#include <ppu-types.h>

#ifdef __cplusplus
extern "C" {
#endif


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
 * font structs
 */
typedef struct _font_entry
{
    u32 lock;
    u32 uniqueId;
    const void* fontLib ATTRIBUTE_PRXPTR;
    void* fontH ATTRIBUTE_PRXPTR;
} fontEntry;

typedef struct _font_config
{
    struct
    {
        u32* buffer ATTRIBUTE_PRXPTR;
        u32 size;
    } FileCache;
    u32 fontEntriesMax;
    fontEntry* fontEntries ATTRIBUTE_PRXPTR;
    u32 flags;
} fontConfig;

typedef struct _font_library
{
    u32 libraryType;
    u32 libraryVersion;
    u32 SystemClosed[];
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
    u16* contourIndexs ATTRIBUTE_PRXPTR;
    u32 flags;
    void* generateEnv ATTRIBUTE_PRXPTR;
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
    float SystemClosed[];
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
    void* buffer ATTRIBUTE_PRXPTR;
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
    void* SystemReserved[64] ATTRIBUTE_PRXPTR;
} font;

typedef struct _font_renderer_config
{
    struct
    {
        void* buffer ATTRIBUTE_PRXPTR;
        u32 initSize;
        u32 maxSize;
        u32 expandSize;
        u32 resetSize;
    } BufferingPolicy;
} fontRendererConfig;

typedef struct _font_renderer
{
    void *systemReserved[64] ATTRIBUTE_PRXPTR;
} fontRenderer;

typedef struct _font_graphics
{
    u32 graphicsType;
    u32 SystemClosed[];
} fontGraphics;

typedef struct _font_graphics_draw_context
{
    void* SystemReserved[64] ATTRIBUTE_PRXPTR;
} fontGraphicsDrawContext;


/*
 * font functions
 */
//s32 fontInitLibrary(fontLibraryConfig*,const fontLibrary**lib);
void fontGetRevisionFlags(u64*revisionFlags);
void fontGetInitializedRevisionFlags(u64*revisionFlags);
s32 fontInitializeWithRevision(u64 revisionFlags,fontConfig* config);


s32 fontGetLibrary(font*,const fontLibrary**lib,u32* type);
s32 fontGlyphGetScalePixel(fontGlyph*,float *w,float *h);
s32 fontSetScalePixel(font*,float w,float h);
s32 fontGetScalePixel(font*,float *w,float *h);
s32 fontGetKerning(font*,u32 preCode,u32 code,fontKerning* kerning);

s32 fontSetFontsetOpenMode(const fontLibrary*,u32 openMode);
s32 fontSetFontOpenMode(const fontLibrary*,u32 openMode);

s32 fontOpenFontset(const fontLibrary*,fontType*,font*);
s32 fontOpenFontsetOnMemory(const fontLibrary*,fontType*,font*);

s32 fontOpenFontFile(const fontLibrary*,u8* fontPath,u32 subNum,s32 uniqueID,font*);
s32 fontOpenFontMemory(const fontLibrary*,void* fontAddr,u32 fontSize,u32 subNum,s32 uniqueID,font*);
s32 fontOpenFontInstance(font*org,font*ins);

s32 fontAdjustGlyphExpandBuffer(font*,s32 pointN,s32 contourN);
s32 fontGetGlyphExpandBufferInfo(font*,s32* pointN,s32* contourN);

s32 fontSetResolutionDpi(font*,u32 hDpi,u32 vDpi);
s32 fontGetResolutionDpi(font*,u32 *hDpi,u32 *vDpi);

s32 fontAdjustFontScaling(font*,float fontScale);
s32 fontSetScalePoint(font*,float w,float h);
s32 fontSetEffectSlant(font*,float effectSlant);
s32 fontGetScalePoint(font*,float *w,float *h);

s32 fontSetEffectWeight(font*,float effectWeight);
s32 fontGetEffectWeight(font*,float *effectWeight);

s32 fontGetEffectSlant(font*,float *effectSlant);

s32 fontGetHorizontalLayout(font*,fontHorizontalLayout* layout);
s32 fontGetVerticalLayout(font*,fontVerticalLayout* layout);

s32 fontGetFontIdCode(font*,u32 code,u32*fontId,u32*fontcode);

s32 fontGetCharGlyphMetrics(font*,u32 code,fontGlyphMetrics*);
s32 fontGetCharGlyphMetricsVertical(font*,u32 code,fontGlyphMetrics*);

s32 fontSetupRenderScalePoint(font*,float w,float h);
s32 fontSetupRenderScalePixel(font*,float w,float h);

s32 fontSetupRenderEffectWeight(font*,float additionalWeight);
s32 fontSetupRenderEffectSlant(font*,float effectSlant);

s32 fontGetRenderScalePoint(font*,float *w,float *h);
s32 fontGetRenderScalePixel(font*,float *w,float *h);

s32 fontGetRenderEffectWeight(font*,float *effectWeight);
s32 fontGetRenderEffectSlant(font*,float *effectSlant);

s32 fontGetRenderCharGlyphMetrics(font*,u32 code,fontGlyphMetrics*);
s32 fontGetRenderCharGlyphMetricsVertical(font*cfEx,u32 code,fontGlyphMetrics*metrics);
s32 fontGetRenderScaledKerning(font*,u32 preCode,u32 code,fontKerning* kerning);

s32 fontGenerateCharGlyph(font*,u32 code,fontGlyph**);
s32 fontGenerateCharGlyphVertical(font*,u32 code,fontGlyph**);

s32 fontDeleteGlyph(font*,fontGlyph*);

s32 fontDelete(const fontLibrary*,void*);

void fontRenderSurfaceInit(fontRenderSurface*,void* buffer,s32 bufWidthByte,s32 pixelSizeByte,s32 w,s32 h);
void fontRenderSurfaceSetScissor(fontRenderSurface*,s32 x0,s32 y0,u32 w,u32 h);

s32 fontRenderCharGlyphImage(font*,u32 code,fontRenderSurface*,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);
s32 fontRenderCharGlyphImageHorizontal(font*,u32 code,fontRenderSurface*,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);
s32 fontRenderCharGlyphImageVertical(font*,u32 code,fontRenderSurface*,float x,float y,fontGlyphMetrics*,fontImageTransInfo*);

s32 fontCreateRenderer(const fontLibrary* lib,fontRendererConfig* confing,fontRenderer* renderer);
s32 fontBindRenderer(font*,fontRenderer*);
s32 fontUnbindRenderer(font*);
s32 fontGetBindingRenderer(font*,fontRenderer**);
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
s32 fontCloseFont(font*cf);
s32 fontEndGraphics(const fontGraphics*);
s32 fontEndLibrary(const fontLibrary*lib);
s32 fontEnd(void);

/*
 * font helpers
 */

static inline void fontConfig_initialize(fontConfig* config)
{
    config->FileCache.buffer = (u32*)0;
    config->FileCache.size = 0;
    config->fontEntriesMax = 0;
    config->fontEntries = (fontEntry*)0;
    config->flags = 0x00000000;
}

static inline void fontRendererConfig_initialize(fontRendererConfig* config)
{
    config->BufferingPolicy.buffer = (void*)0;
    config->BufferingPolicy.initSize = 0;
    config->BufferingPolicy.maxSize  = 0;
    config->BufferingPolicy.expandSize = 1;
    config->BufferingPolicy.resetSize  = 0;
}

static inline void fontRendererConfig_setAllocateBuffer(fontRendererConfig* config,u32 initSize,u32 maxSize)
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

typedef void* (*fontMallocCallback)(void*Object,u32 size);
typedef void  (*fontFreeCallback)(void*Object,void*free_address);
typedef void* (*fontReallocCallback)(void*Object,void*p,u32 reallocSize);
typedef void* (*fontCallocCallback)(void*Object,u32 num,u32 size);
typedef void  (*fontGetOutlineVertexCallback)(void*arg,s32 contourN,s32 vertexNumber,s32 vertexAttr,float x,float y);

typedef struct fontMemoryInterface
{
    void* Object ATTRIBUTE_PRXPTR;
    fontMallocCallback Malloc;
    fontFreeCallback Free;
    fontReallocCallback Realloc;
    fontCallocCallback Calloc;
} fontMemoryInterface;

static inline void fontMemoryInterface_initialize(fontMemoryInterface*mIF)
{
    mIF->Object = (void*)0;
    mIF->Malloc = (fontMallocCallback)0;
    mIF->Free = (fontFreeCallback  )0;
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
    void* library ATTRIBUTE_PRXPTR;
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
s32 fontFTInitLibraryFreeTypeWithRevision(u64 revisionFlags,fontLibraryConfigFT*config,fontLibrary **lib);
void fontFTGetInitializedRevisionFlags(u64*revisionFlags);


/*
 * fontFT helpers
 */
static inline void fontFTLibraryConfig_initialize(fontLibraryConfigFT* config)
{
    config->library = (void*)0;
    fontMemoryInterface_initialize(&config->MemoryIF);
    return;
}

static inline s32 fontFTInitLibraryFreeType(fontLibraryConfigFT* config,fontLibrary **lib)
{
    u64 revisionFlags = 0LL;

    fontFTGetRevisionFlags(&revisionFlags);
    return fontFTInitLibraryFreeTypeWithRevision(revisionFlags,config,lib);
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LIBFONT_H__ */

