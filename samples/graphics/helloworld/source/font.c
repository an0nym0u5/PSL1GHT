#line 1 "source/font.c"
/*
 * font.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#include "common.h"
#include "debug.h"
#include "font.h"
#include "buffers.h"
#include "video.h"

#include "AndaleMono_ttf.h"


/* initialize freetype */
void
fontInitialization ( fontData *fdata, s32 fontSize, s32 width, s32 height )
{
  dbgprintf ( "initializing" ) ;

  static s32 ret ;

  fdata->bgColor = FONT_COLOR_BLACK ;
  fdata->fgColor = FONT_COLOR_WHITE ;
  fdata->fontSize = FONT_SIZE ;
  fdata->fontPath = "none" ;
  fdata->fontName = "AndaleMono.ttf" ;
  fdata->fontPtr = (FT_Byte*)AndaleMono_ttf ;
  fdata->fontLen = AndaleMono_ttf_size ;
  fdata->x = 0 ;
  fdata->y = 0 ;
  fdata->width = width ;
  fdata->height = height ;
  fdata->chromakey = FONT_CHROMAKEY ;

  ret = FT_Init_FreeType ( &fdata->library ) ;
  if ( ret )
  {
    dbgprintf ( "freetype init error" ) ;
    goto error ;
  }

  /* load ttf */
  fontLoadTTF ( fdata ) ;

  dbgprintf ( "initialized" ) ;

  return ;

error:
  FT_Done_FreeType ( fdata->library ) ;
}

/* free resources */
void
fontFinish ( fontData *fdata )
{
  dbgprintf ( "finishing" ) ;
  FT_Stroker_Done ( fdata->stroker ) ;
  FT_Done_Glyph ( fdata->glyph ) ;
  FT_Done_FreeType ( fdata->library ) ;
}

/* load freetype font */
void
fontLoadTTF ( fontData *fdata )
{
  argprintf ( "loading font: %s", fdata->fontName ) ;

  static s32 ret ;

  /* load font from memory */
  ret = FT_New_Memory_Face( fdata->library, fdata->fontPtr, fdata->fontLen, 0, &fdata->face ) ;
  if ( ret )
  {
    argprintf ( "unable to load font %s [%d]", fdata->fontName, ret ) ;
    goto error ;
  }

  /* stroker */
  ret = FT_Stroker_New ( fdata->library, &fdata->stroker ) ;
  if ( ret )
  {
    argprintf ( "unable to create stroker %d", ret ) ;
    goto error ;
  }
  FT_Stroker_Set ( fdata->stroker, 40, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0 ) ;

  /* enable kerning */
  fdata->fontKerning = FT_HAS_KERNING(fdata->face) ;

  /* font size in pixels */
  ret = FT_Set_Pixel_Sizes ( fdata->face, 0, fdata->fontSize ) ;
  if( ret ) {
    argprintf ( "SetPixelSize error %d", ret ) ;
    goto error ;
  }
  return ;

error:
  FT_Done_Face ( fdata->face ) ;
  FT_Done_FreeType ( fdata->library ) ;
}

/* clear text buffer */
inline void
fontBufferClear ( fontBuffer *fbuf )
{
  memset ( fbuf->ptr, 0x00, ( size_t )( fbuf->width * fbuf->height * sizeof ( u32 ) ) ) ;
}

/* initialize buffer */
void
fontBufferInitialization (videoData *vdata, fontData *fdata )
{
  dbgprintf ( "initializing" ) ;

  fontBuffer *fbuf = vdata->fon_buffer ;

  fbuf->chromakey = fdata->chromakey ;
  fbuf->width = fdata->width ;
  fbuf->height = fdata->height ;
  fbuf->color_depth = sizeof(u32) ;
  fbuf->color_pitch = fbuf->width * fbuf->color_depth ;
  fbuf->size = fbuf->width * fbuf->height * fbuf->color_depth ;

  fbuf->ptr = (u32*) rsxMemalign (64, fbuf->size) ;
  argprintf ( "rsxMemalign( 64, 0x%x ) = 0x%llx", fbuf->size, (long long unsigned int)fbuf->ptr ) ;
  rsxAddressToOffset ( fbuf->ptr, &fbuf->color_offset ) ;
  argprintf ( "rsxAddressToOffset ( 0x%llx, 0x%x )", (long long unsigned int)fbuf->ptr, (unsigned int)fbuf->color_offset ) ;
  fontBufferClear( fbuf ) ;

  /* initialize semaphore attributes */
  fbuf->sem_attr.key            = 0x02 ;
  fbuf->sem_attr.attr_protocol  = SYS_SEM_ATTR_PROTOCOL ;
  fbuf->sem_attr.attr_pshared   = SYS_SEM_ATTR_PSHARED ;

  /* create semaphore */
  sysSemCreate ( &fbuf->sem, &fbuf->sem_attr, 1, SEM_CONSUMERS ) ;

  dbgprintf ( "initialized" ) ;
}

void
fontBufferFinish( fontBuffer *fbuf )
{
  dbgprintf ( "finishing" ) ;

  sysSemDestroy ( fbuf->sem ) ;

  /* free buffer */
  rsxFree ( fbuf->ptr ) ;
}

/* print text to buffer */
void
fontPrint( fontData *fdata, s32 x, s32 y, char* text, fontBuffer *buf )
{
  s32 i = 0 ;
  s32 error = 0 ;
  size_t textlen = strlen ( text ) ;

  if ( textlen > 0 )
  {
    fdata->pen.x = 0 ;
    fdata->pen.y = fdata->fontSize ;

    FT_GlyphSlot slot = fdata->face->glyph ;
    FT_UInt glyph_index = 0 ;
    FT_UInt previous_glyph = 0 ;

    /* enable kerning */
    fdata->fontKerning = FT_HAS_KERNING(fdata->face) ;

    for(i = 0 ; i < textlen ; i++)
    {
      /* retrieve glyph index from character code */
      glyph_index = FT_Get_Char_Index(fdata->face, text[i]) ;

      /* grab kerning info */
      if ( fdata->fontKerning && previous_glyph && glyph_index )
      {
        FT_Vector delta ;
        FT_Get_Kerning ( fdata->face, previous_glyph, glyph_index, FT_KERNING_DEFAULT, &delta ) ;
        fdata->pen.x += delta.x >> 6 ;
      }

      /* load glyph image into the slot (erase previous one) */
      error = FT_Load_Glyph ( fdata->face, glyph_index, FT_LOAD_RENDER ) ;
      if ( error ) continue ;

      FT_Get_Glyph ( fdata->face->glyph, &fdata->glyph ) ;

      FT_Glyph_StrokeBorder ( &fdata->glyph, fdata->stroker, 0, 0 ) ;

      /* draw glyph to fontBuffer */
      fontDrawBitmap ( &slot->bitmap,
                       fdata->pen.x + slot->bitmap_left + x,
                       (fdata->pen.y - slot->bitmap_top + y - fdata->fontSize),
                       buf,
                       fdata ) ;

      /* store current glyph index in previous */
      previous_glyph = glyph_index ;

      /* increment pen position */
      fdata->pen.x += slot->advance.x >> 6 ;
      fdata->pen.y += slot->advance.y >> 6 ;
    }
  }
}

/* draw font glyph into buffer */
void
fontDrawBitmap ( FT_Bitmap *bitmap, s32 offset, s32 top, fontBuffer *fbuf, fontData *fdata )
{
  static s32 color, a, r, g, b ;
  FT_Int x, y, i, j ;
  FT_Int x_max = offset + bitmap->width ;
  FT_Int y_max = top + bitmap->rows ;

  s32 fgA = A(fdata->fgColor) ;
  s32 fgR = R(fdata->fgColor) ;
  s32 fgG = G(fdata->fgColor) ;
  s32 fgB = B(fdata->fgColor) ;

  u32 width = fbuf->width ;
  u32 height = fbuf->height ;

  for ( x = offset, i = 0 ; x < x_max ; x++, i++ )
  {
    if ( x >= width ) break ;
    for ( y = top, j = 0 ; y < y_max ; y++, j++ )
    {
      if ( y >= height ) break ;

      /* grab the current glyph pixel value */
      color = bitmap->buffer[bitmap->width * j + i] ;

      /* calculate ARGB values for pixel color */
      a = ( ( fgA * color + 255 ) >> 8 ) ;
      r = ( ( fgR * color + 255 ) >> 8 ) ;
      g = ( ( fgG * color + 255 ) >> 8 ) ;
      b = ( ( fgB * color + 255 ) >> 8 ) ;

      /* fill buffer with pixel values */
      *( fbuf->ptr + fbuf->width * y + x ) = COLOR_TO_ARGB(a, r, g, b) ;
    }
  }
}

/* draw buffer to rsx */
void
fontBufferDraw( gcmContextData *context, fontBuffer *fbuf, rsxBuffer *rbuf )
{
  gcmTransferScale xferscale ;
  memset ( &xferscale, 0, sizeof ( xferscale ) ) ;

  gcmTransferSurface xfersurface ;
  memset ( &xfersurface, 0, sizeof ( xfersurface ) ) ;

  /* configure transfer scale */
  xferscale.conversion = GCM_TRANSFER_CONVERSION_TRUNCATE ;
  xferscale.format = GCM_TRANSFER_SCALE_FORMAT_A8R8G8B8 ;
  xferscale.operation = GCM_TRANSFER_OPERATION_SRCCOPY_AND ;
  xferscale.clipX = 0 ;
  xferscale.clipY = 0 ;
  xferscale.clipW = rbuf->width ;
  xferscale.clipH = rbuf->height ;
  xferscale.outX = 0 ;
  xferscale.outY = 0 ;
  xferscale.outW = rbuf->width ;
  xferscale.outH = rbuf->height ;
  xferscale.inW = fbuf->width ;
  xferscale.inH = fbuf->height ;

  xferscale.ratioX = rsxGetFixedSint32 ( (float)xferscale.inW / (float)xferscale.outW ) ;
  xferscale.ratioY = rsxGetFixedSint32 ( (float)xferscale.inH / (float)xferscale.outH ) ;

  xferscale.pitch = fbuf->color_pitch ;
  xferscale.origin = GCM_TRANSFER_ORIGIN_CORNER ;
  xferscale.interp = GCM_TRANSFER_INTERPOLATOR_NEAREST ;
  xferscale.offset = fbuf->color_offset ;

  xferscale.inX = rsxGetFixedUint16 ( 1.0f ) ;
  xferscale.inY = rsxGetFixedUint16 ( 1.0f ) ;

  /* configure destination surface for transfer */
  xfersurface.format = GCM_TRANSFER_SURFACE_FORMAT_A8R8G8B8 ;
  xfersurface.pitch = rbuf->color_pitch ;
  xfersurface.offset = rbuf->color_offset ;

  /* blit font buffer */
  rsxSetTransferScaleMode ( context, GCM_TRANSFER_LOCAL_TO_LOCAL, GCM_TRANSFER_SURFACE ) ;
  rsxSetTransferScaleSurface ( context, &xferscale, &xfersurface ) ;
}

