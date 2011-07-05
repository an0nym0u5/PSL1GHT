/*! \file resc.h
 * \brief libresc
 * */

#ifndef __RESC_H__
#define __RESC_H__

#include <ppu-types.h>

#include <rsx/gcm_sys.h>
#include <sysutil/sysutil.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Error macros */
/* #define RESC_ERROR_BASE                          (0x80210300) */

#define RESC_ERROR_NOT_INITIALIZED               (0x80210301) /* (RESC_ERROR_BASE | 0x1) */
#define RESC_ERROR_REINITIALIZED                 (0x80210302) /* (RESC_ERROR_BASE | 0x2) */
#define RESC_ERROR_BAD_ALIGNMENT                 (0x80210303) /* (RESC_ERROR_BASE | 0x3) */
#define RESC_ERROR_BAD_ARGUMENT                  (0x80210304) /* (RESC_ERROR_BASE | 0x4) */
#define RESC_ERROR_LESS_MEMORY                   (0x80210305) /* (RESC_ERROR_BASE | 0x5) */
#define RESC_ERROR_GCM_FLIP_QUE_FULL             (0x80210306) /* (RESC_ERROR_BASE | 0x6) */
#define RESC_ERROR_BAD_COMBINATION               (0x80210307) /* (RESC_ERROR_BASE | 0x7) */

/* resource policies */
#define RESC_CONSTANT_VRAM                       0 /* (0 << 0) */
#define RESC_MINIMUM_VRAM                        1 /* (1 << 0) */
#define RESC_CONSTANT_GPU_LOAD                   0 /* (0 << 1) */  /* do not use */
#define RESC_MINIMUM_GPU_LOAD                    2 /* (1 << 1) */

/* dst formats */
#define RESC_SURFACE_A8R8G8B8                    GCM_TF_COLOR_A8R8G8B8       /* 8 */
#define RESC_SURFACE_F_W16Z16Y16X16              GCM_TF_COLOR_F_W16Z16Y16X16 /* 11 */

/* buffer modes */
#define RESC_UNDEFINED                           0
#define RESC_720x480                             1 /* (1 << 0) */
#define RESC_720x576                             2 /* (1 << 1) */
#define RESC_1280x720                            4 /* (1 << 2) */
#define RESC_1920x1080                           8 /* (1 << 3) */

/* ratio convert modes */
#define RESC_FULLSCREEN                          0
#define RESC_LETTERBOX                           1
#define RESC_PANSCAN                             2

/* PAL temporal mode */
#define RESC_PAL_50                              0
#define RESC_PAL_60_DROP                         1
#define RESC_PAL_60_INTERPOLATE                  2
#define RESC_PAL_60_INTERPOLATE_30_DROP          3
#define RESC_PAL_60_INTERPOLATE_DROP_FLEXIBLE    4
#define RESC_PAL_60_FOR_HSYNC                    5

/* convolution filter mode */
#define RESC_NORMAL_BILINEAR                     0
#define RESC_INTERLACE_FILTER                    1
#define RESC_3X3_GAUSSIAN                        2
#define RESC_2X3_QUINCUNX                        3
#define RESC_2X3_QUINCUNX_ALT                    4

/* table element */
#define RESC_ELEMENT_HALF                        0
#define RESC_ELEMENT_FLOAT                       1

/* flip mode */
#define RESC_DISPLAY_VSYNC                       0
#define RESC_DISPLAY_HSYNC                       1

/* Structures */
typedef struct _rescInitConfig
{
    size_t size;
    u32 resourcePolicy;
    u32 supportModes;
    u32 ratioMode;
    u32 palTemporalMode;
    u32 interlaceMode;
    u32 flipMode;
}rescInitConfig;

typedef struct _rescSrc
{
    u32 format;
    u32 pitch;
    u16 width;
    u16 height;
    u32 offset;
} rescSrc;

typedef struct _rescDsts
{
    u32 format;
    u32 pitch;
    u32 heightAlign;
} rescDsts;

/* Equivalents
 *
 * rescSetSrc()               gcmSetDisplayBuffer()
 * rescSetConvertAndFlip()    gcmSetFlip()
 * rescSetWaitFlip()          gcmSetWaitFlip()
 * rescSetFlipHandler()       gcmSetFlipHandler()
 * rescSetVBlankHandler()     gcmSetVBlankHandler()
 * rescGetFlipStatus()        gcmGetFlipStatus()
 * rescGetLasFlipTime()       gcmGetLastFlipTime()
 * rescResetFlipStatus()      gcmResetFlipStatus()
 */

s32 rescInit(const rescInitConfig* const initConfig);
void rescExit();
s32 rescSetDsts(const u32 dstsMode, const rescDsts* const dsts);
s32 rescSetDisplayMode(const u32 bufferMode);
s32 rescGetNumColorBuffers(const u32 dstsMode, const u32 palTemporalMode, const u32 reserved);
s32 rescGetBufferSize(int *colorBuffers, int *vertexArray, int *fragmentShader);
s32 rescSetBufferAddress(const void* const colorBuffers, const void* const vertexArray, const void* const fragmentShader);
s32 rescSetSrc(const s32 idx, const rescSrc* const src);
s32 rescSetConvertAndFlip(gcmContextData* context, const s32 idx);
void rescSetWaitFlip(gcmContextData* context);
s64 rescGetLastFlipTime();
void rescResetFlipStatus();
u32 rescGetFlipStatus();
s32 rescGetRegisterCount();
void rescSetRegisterCount(const s32 count);
s32 rescSetPalInterpolateDropFlexRatio(const float ratio);
s32 rescCreateInterlaceTable(void* ea, const float srcH, const s32 depth, const int length);
s32 rescAdjustAspectRatio(const float horizontal, const float vertical);

/* Register event handler */
void rescSetVBlankHandler(void (*handler)(const u32 head));
void rescSetFlipHandler(void (*handler)(const u32 head));

/* Utility functions */
s32  rescGcmSurface2RescSrc(const gcmSurface* const surface, rescSrc* const src);
s32  rescVideoResolution2RescBufferMode(const u32 resolutionId, u32* const bufferMode);

#ifdef __cplusplus
    }
#endif

#endif

