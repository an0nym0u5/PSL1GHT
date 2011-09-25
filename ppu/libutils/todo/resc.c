#line 1 "source/rescutil.c"
/*
 * rescutil.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#include <stdio.h>
#include <malloc.h> // free()
#include <string.h> // memset()
#include <unistd.h> // usleep()

#include <rsx/resc.h>


#include "common.h"
#include "video.h"
#include "rescutil.h"
#include "buffers.h"


/* global for flip state */
static bool flipped = true ;


/* initialize resc */
void
rescInitialize ( videoData *vdata )
{
  dbgprintf ( "initializing" ) ;

  static s32 ret ;

  /* Get the state of the display */
  ret = videoGetState (VIDEO_PRIMARY, 0, &vdata->state) ;
  if (ret != 0)
  {
    errprintf ( "ERROR %x", ret ) ;
    goto error;
  }

  /* Make sure display is enabled */
  if (vdata->state.state != 0 )
  {
    errprintf ( "ERROR %x", vdata->state.state ) ;
    goto error;
  }

  /* initialize resc configuration */
  memset (&vdata->rconfig, 0, (size_t)sizeof( rescInitConfig ));

  vdata->rconfig.size = sizeof( rescInitConfig ) ;
  vdata->rconfig.resourcePolicy = RESC_MINIMUM_GPU_LOAD | RESC_CONSTANT_VRAM ;
  vdata->rconfig.supportModes = RESC_1920x1080 | RESC_1280x720 | RESC_720x576 | RESC_720x480 ;
  vdata->rconfig.ratioMode = (vdata->state.displayMode.aspect == ASPECT_4_3) ? RESC_LETTERBOX : RESC_FULLSCREEN ;
  vdata->rconfig.palTemporalMode = RESC_PAL_50 ;
  vdata->rconfig.interlaceMode = RESC_NORMAL_BILINEAR ;
  vdata->rconfig.flipMode = RESC_DISPLAY_VSYNC ;

  ret = rescInit ( &vdata->rconfig ) ;
  if ( ret != 0 )
  {
    errprintf ( "ERROR %x", ret ) ;
    goto error;
  }

  rescVideoResolution2RescBufferMode ( vdata->state.displayMode.resolution, &vdata->bufMode ) ;

  /* 0 */
  {
    vdata->dsts[0].format = RESC_SURFACE_A8R8G8B8 ;
    vdata->dsts[0].pitch = 0xc00 ;
    vdata->dsts[0].heightAlign = 64 ;

    ret = rescSetDsts ( RESC_720x480, &vdata->dsts[0] ) ;
    if ( ret != 0 )
    {
      errprintf ( "ERROR %x", ret ) ;
      goto error;
    }
  }

  /* 1 */
  {
    vdata->dsts[1].format = RESC_SURFACE_A8R8G8B8 ;
    vdata->dsts[1].pitch = 0xc00 ;
    vdata->dsts[1].heightAlign = 64 ;

    ret = rescSetDsts ( RESC_720x576, &vdata->dsts[1] ) ;
    if ( ret != 0 )
    {
      errprintf ( "ERROR %x", ret ) ;
      goto error;
    }
  }

  /* 2 */
  {
    vdata->dsts[2].format = RESC_SURFACE_A8R8G8B8 ;
    vdata->dsts[2].pitch = 0x1400 ;
    vdata->dsts[2].heightAlign = 64 ;

    ret = rescSetDsts ( RESC_1280x720, &vdata->dsts[2] ) ;
    if ( ret != 0 )
    {
      errprintf ( "ERROR %x", ret ) ;
      goto error;
    }
  }

  /* 3 */
  {
    vdata->dsts[3].format = RESC_SURFACE_A8R8G8B8 ;
    vdata->dsts[3].pitch = 0x2000 ;
    vdata->dsts[3].heightAlign = 32 ;

    ret = rescSetDsts ( RESC_1920x1080, &vdata->dsts[3] ) ;
    if ( ret != 0 )
    {
      errprintf ( "ERROR %x", ret ) ;
      goto error;
    }
  }

  ret = rescSetDisplayMode ( vdata->bufMode ) ;
  if ( ret != 0 )
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error;
  }

  ret = rescGetBufferSize ( &vdata->cbuf.size, &vdata->vertbuf.size, &vdata->fragbuf.size ) ;
  if ( ret != 0 )
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error;
  }

  vdata->cbuf.ptr = (void*) rsxMemalign ( 0x10000, vdata->cbuf.size ) ;
  vdata->vertbuf.ptr = (void*) rsxMemalign ( 0x80, vdata->vertbuf.size ) ;
  vdata->fragbuf.ptr = (void*) rsxMemalign ( 0x80, vdata->fragbuf.size ) ;

  ret = rescSetBufferAddress ( vdata->cbuf.ptr, vdata->vertbuf.ptr, vdata->fragbuf.ptr ) ;
  if ( ret != 0 )
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error;
  }

  argprintf("Required size,  color: 0x%x vertex: 0x%x fragment: 0x%x", vdata->cbuf.size, vdata->vertbuf.size, vdata->fragbuf.size);
  argprintf("Buf addr given, color: %p vertex: %p fragment: %p", vdata->cbuf.ptr, vdata->vertbuf.ptr, vdata->fragbuf.ptr);

  /* */
  /* TILING BULLSHIT GOES HERE */
  /* */

  rescSetFlipHandler ( rescFlipCallback ) ;

  rescSetRenderTarget ( vdata ) ;

  return ;
  
  error:
  {
    return ;
  }
}

/* rescFlip callback */
void
rescFlipCallback ( u32 head )
{
  (void)head ;
  flipped = true ;
}

/* wait until flip */
void
rescWaitFlip ( void )
{
  while (!flipped)
  {
    usleep ( 100 ) ;
  }
  flipped = false ;
}

/* flip a buffer to screen */
inline int
rescFlip ( videoData *vdata )
{
  if ( rescSetConvertAndFlip ( vdata->context, vdata->rsx_buffers[vdata->currentBuffer].id ) == 0 )
  {
    rsxFlushBuffer ( vdata->context ) ;

    /* Prevent the RSX from continuing until the flip has finished. */
    rescSetWaitFlip ( vdata->context ) ;

    /* set render target */
    rescSetRenderTarget ( vdata ) ;

    return TRUE;
  }
  return FALSE;
}
  
/* set the current render target */
inline void
rescSetRenderTarget(videoData *vdata )
{
  gcmSurface sf;
  rescSrc src;

  sf.colorFormat = GCM_TF_COLOR_A8R8G8B8;
  sf.colorTarget = GCM_TF_TARGET_0;
  sf.colorLocation[0] = GCM_LOCATION_RSX;
  sf.colorOffset[0] = vdata->rsx_buffers[vdata->currentBuffer].color_offset;
  sf.colorPitch[0] = vdata->color_pitch;

  sf.colorLocation[1] = GCM_LOCATION_RSX;
  sf.colorLocation[2] = GCM_LOCATION_RSX;
  sf.colorLocation[3] = GCM_LOCATION_RSX;
  sf.colorOffset[1] = 0;
  sf.colorOffset[2] = 0;
  sf.colorOffset[3] = 0;
  sf.colorPitch[1] = 64;
  sf.colorPitch[2] = 64;
  sf.colorPitch[3] = 64;

  sf.depthFormat = GCM_TF_ZETA_Z16;
  sf.depthLocation = GCM_LOCATION_RSX;
  sf.depthOffset = vdata->depth_offset;
  sf.depthPitch = vdata->depth_pitch;

  sf.type = GCM_TF_TYPE_LINEAR;
  sf.antiAlias 	= GCM_TF_CENTER_1;

  sf.width = vdata->rsx_buffers[vdata->currentBuffer].width;
  sf.height = vdata->rsx_buffers[vdata->currentBuffer].height;
  sf.x = 0;
  sf.y = 0;

  rsxSetSurface ( vdata->context, &sf ) ;

  /* new */
  rsxClearBuffer ( vdata->context ) ;

  /* new */
  rsxBlend ( vdata->context ) ;

  /* new */
  rsxWaitIdle ( vdata->context ) ;

  rescGcmSurface2RescSrc ( &sf, &src ) ;
  rescSetSrc ( vdata->currentBuffer, &src ) ;
}

