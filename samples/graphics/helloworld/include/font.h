/*
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef __FONT_H__
#define __FONT_H__


#include <stdbool.h>
#include <ppu-types.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_SYNTHESIS_H
#include FT_STROKER_H

#include "buffers.h"
#include "video.h"


#define MAX_STRING           256
#define LINE_INDENT          40
#define LINE_SIZE            40

#define FONT_SIZE            40
#define FONT_CHROMAKEY       CHROMAKEY

#define FONT_COLOR_NONE      -1
#define FONT_COLOR_BLACK     0xff000000
#define FONT_COLOR_GREY      0xff444444
#define FONT_COLOR_WHITE     0xffffffff

#define FONT_COLOR_RED       0xfffa001c
#define FONT_COLOR_ORANGE    0xfffa8500
#define FONT_COLOR_YELLOW    0xfffae900
#define FONT_COLOR_GREEN     0xff3fd711
#define FONT_COLOR_BLUE      0xff1775ca

#define FONT_COLOR_FG        FONT_COLOR_BLUE
#define FONT_COLOR_BG        FONT_COLOR_BLACK

#define COLOR_TO_ARGB(alpha, red, green, blue) (((alpha) << 24) | ((red) << 16) | ((green) << 8) | (blue))
#define COLOR_TO_RGB(red, green, blue) (((red) << 16) | ((green) << 8) | (blue))

#define VALUE_TO_ARGB(value) (((value) << 24) | ((value) << 16) | ((value) << 8) | (value))
#define VALUE_TO_RGB(value) (((value) << 16) | ((value) << 8) | (value))

#define A(argb)  (((argb) >> 24) & 0xFF)
#define R(argb)  (((argb) >> 16) & 0xFF)
#define G(argb)  (((argb) >>  8) & 0xFF)
#define B(argb)  ( (argb)        & 0xFF)


typedef struct _font_data
{
  s32 x ;
  s32 y ;
  s32 fgColor ;
  s32 bgColor ;
  s32 fontSize ;
  s32 width ;
  s32 height ;
  u32 chromakey ;
  char string[1024] ;
  /* freetype */
  char *fontPath ;
  char *fontName ;
  char *fontFile ;
  bool fontKerning ;
  FT_Byte *fontPtr ;
  s32 fontLen ;
  FT_Library library ;
  FT_Glyph glyph ;
  FT_Stroker stroker ;
  FT_Face face ;
  FT_Bitmap *bitmap ;
  FT_Vector pen ;
} fontData ;


void fontInitialization(fontData *fdata, s32 fontSize, s32 width, s32 height);
void fontFinish (fontData *fdata);
void fontLoadTTF (fontData *fdata);
void fontDrawBitmap (FT_Bitmap *bitmap, int offset, int top, fontBuffer *fbuf, fontData *fdata);
void fontPrint (fontData *fdata, s32 x, s32 y, char* text, fontBuffer *fbuf);

void fontBufferInitialization(videoData *vdata, fontData *fdata);
void fontBufferDraw(gcmContextData *context, fontBuffer *fbuf, rsxBuffer *rbuf);
void fontBufferFinish(fontBuffer *fbuf);



#endif /* __FONT_H__ */

