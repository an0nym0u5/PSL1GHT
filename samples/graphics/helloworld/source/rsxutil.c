#line 1 "source/rsxutil.c"
/*
 * rsxutil.c
 *
 * This software is distributed under the terms of the GNU General Public
 * License ( "GPL" )  version 3, as published by the Free Software Foundation.
 */

#include <stdio.h>
#include <malloc.h> // free () 
#include <string.h> // memset () 
#include <unistd.h> // usleep () 

#include "common.h"
#include "debug.h"
#include "video.h"
#include "rsxutil.h"
#include "buffers.h"


/* initialize RSX */
inline void
rsxInitialization ( videoData *vdata ) 
{
  dbgprintf ( "initializing" ) ;

  static s32 i, ret ;

  vdata->currentBuffer = 0 ;
  vdata->chromakey = CHROMAKEY ;
  vdata->host_addr = memalign ( 1024*1024, HOST_SIZE ) ;

  vdata->context = rsxScreenInitialize ( vdata, HOST_SIZE ) ;
  if ( vdata->context == NULL ) 
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }

  for ( i = 0 ; i < MAX_BUFFERS ; i++ ) 
  {
    vdata->rsx_buffers[i].width = vdata->width ;
    vdata->rsx_buffers[i].height = vdata->height ;
    rsxMakeBuffer ( &vdata->rsx_buffers[i], i ) ;
    argprintf ( "buffer %d %p", i, vdata->rsx_buffers[i].ptr ) ;
  }

  /* not needed when using libresc */
  //rsxFlip ( vdata ) ;

  rsxSetRenderTarget ( vdata ) ;

  dbgprintf ( "initialized" ) ;

  return ;

  error:
  {
    if ( vdata->context ) 
    {
      rsxFinish ( vdata->context, 0 ) ;
    }

    if ( vdata->host_addr ) 
    {
      free ( vdata->host_addr ) ;
    }

    errprintf ( "FATAL ERROR EXITING: %x", ret ) ;
    exit ( EXIT_FAILURE ) ;
  }
}

gcmContextData *
rsxScreenInitialize ( videoData *vdata, u32 size ) 
{
  static s32 ret ;
  static s32 mode_size, last_size ;
  static u16 i ;
  gcmContextData *context = NULL ; /* Context to keep track of the RSX buffer. */
  videoResolution res ; /* Screen Resolutions */

  /* Initialize RSX context
   * which sets up the command buffer and shared IO memory
   */
  context = rsxInit ( CB_SIZE, size, vdata->host_addr ) ;
  if ( context == NULL ) 
  {
    errprintf ( "ERROR %x", ret ) ;
    goto error ;
  }

  /* Get the state of the display */
  ret = videoGetState ( VIDEO_PRIMARY, 0, &vdata->state ) ;
  if ( ret != 0 ) 
  {
    errprintf ( "ERROR %x", ret ) ;
    goto error ;
  }

  /* verify display state */
  if ( vdata->state.state != 0 ) 
  {
    errprintf ( "ERROR %x", ret ) ;
    goto error ;
  }

  /* clear video device info */
  memset ( &vdata->vinfo, 0, ( size_t ) sizeof ( videoDeviceInfo ) ) ;

  /* clear video configuration */
  memset ( &vdata->vconfig, 0, ( size_t ) sizeof ( videoConfiguration ) ) ;

  /* get available device information */
  ret = videoGetDeviceInfo ( 0, 0, &vdata->vinfo ) ;
  if ( ret != 0 )
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }

  /* Configure the buffer format to xRGB */
  vdata->vconfig.format = VIDEO_BUFFER_FORMAT_XRGB ;

  /* choose resolution / aspect / pitch to use */
  for ( i = 0 ; i < vdata->vinfo.availableModeCount ; i++ )
  {
    if ( vdata->vinfo.availableModes[i].resolution < VIDEO_RESOLUTION_1600x1080 )
    {
      ret = videoGetResolution ( vdata->vinfo.availableModes[i].resolution, &res ) ;
      if ( ret != 0 )
      {
        errprintf ( "ERROR %d", ret ) ;
        goto error ;
      }
    }
    else
    {
      continue ;
    }

    /* calculate display mode number of pixels */
    mode_size = res.width * res.height * vdata->vinfo.availableModes[i].aspect ;

    /* compare current display mode to last display mode, redefine values if higher resolution */
    if ( mode_size > last_size )
    {
      vdata->vconfig.resolution = vdata->vinfo.availableModes[i].resolution ;
      vdata->vconfig.aspect = vdata->vinfo.availableModes[i].aspect ;
      vdata->vconfig.pitch = res.width * sizeof ( u32 ) ;
    }

    last_size = mode_size ;
  }

  argprintf ( "resolution: %d :: format: %d :: aspect: %d :: pitch: %d", vdata->vconfig.resolution, vdata->vconfig.format, vdata->vconfig.aspect, vdata->vconfig.pitch ) ;

  /* wait for RSX command buffer to be idle to continue */
  rsxWaitIdle ( context ) ;

  /* configure video */
  ret = videoConfigure ( VIDEO_PRIMARY, &vdata->vconfig, NULL, 0 ) ;
  if ( ret != 0 ) 
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }

  /* verify video state */
  ret = videoGetState ( VIDEO_PRIMARY, 0, &vdata->state ) ;
  if ( ret != 0 ) 
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }

  /* Wait for VSYNC to flip */
  gcmSetFlipMode ( GCM_FLIP_VSYNC ) ;

  /* set width / height */
  vdata->width = BUFFER_WIDTH ;
  vdata->height = BUFFER_HEIGHT ;

  vdata->color_pitch = vdata->width * sizeof ( u32 ) ;
  vdata->depth_pitch = vdata->width * sizeof ( u32 ) ;

  vdata->depth_buffer = ( u32 * )  rsxMemalign ( 64, ( vdata->height * vdata->depth_pitch )  * 2 ) ;
  if ( vdata->depth_buffer == NULL ) 
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }
  else
  {
    argprintf ( "[depth_buffer] rsxMemalign ( 64, 0x%x ) = 0x%llx", ( vdata->height * vdata->depth_pitch )  * 2, ( long long unsigned int ) vdata->depth_buffer ) ;
  }

  ret = rsxAddressToOffset ( vdata->depth_buffer, &vdata->depth_offset ) ;
  if ( ret != 0 ) 
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }
  else
  {
    argprintf ( "[depth_offset] rsxAddressToOffset ( 0x%llx, 0x%x ) ", ( long long unsigned int ) vdata->depth_buffer, ( unsigned int ) vdata->depth_offset ) ;
  }

  gcmResetFlipStatus () ;

  return context ;

  error:
  {
    if ( context ) 
    {
      rsxFinish ( context, 0 ) ;
    }
  
    if ( vdata->host_addr ) 
    {
      free ( vdata->host_addr ) ;
    }

    return NULL ;
  }
}

/* create an RSX buffer */
int
rsxMakeBuffer ( rsxBuffer *buf, s32 id ) 
{
  static s32 ret ;

  /* populate buffer variables */
  buf->id = id ;
  buf->color_depth = sizeof ( u32 ) ;
  buf->color_pitch = buf->width * buf->color_depth ;
  buf->size = buf->width * buf->height * buf->color_depth ;
  buf->chromakey = CHROMAKEY ;

  buf->ptr = ( u32* )  rsxMemalign ( 64, buf->size ) ;
  if ( buf->ptr == NULL ) 
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }
  else
  {
    argprintf ( "buffer[%d] rsxMemalign ( 64, 0x%x ) = 0x%llx", id, buf->size, ( long long unsigned int ) buf->ptr ) ;
  }

  ret = rsxAddressToOffset ( buf->ptr, &buf->color_offset ) ;
  if ( ret != 0 ) 
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }
  else
  {
    argprintf ( "buffer[%d] rsxAddressToOffset ( 0x%llx, 0x%x ) ", id, ( long long unsigned int ) buf->ptr, ( unsigned int ) buf->color_offset ) ;
  }

  /* Register the display buffer with the RSX */
  ret = gcmSetDisplayBuffer ( id, buf->color_offset, buf->color_pitch, buf->width, buf->height ) ;
  if ( ret != 0 ) 
  {
    errprintf ( "ERROR %d", ret ) ;
    goto error ;
  }

  return TRUE ;

  error:
  {
    if ( buf->ptr != NULL ) 
    {
      rsxFree ( buf->ptr ) ;
    }

    return FALSE ;
  }
}

/* get current screen resolution */
int
rsxGetResolution ( u16 *width, u16 *height ) 
{
  videoState state ;
  videoResolution res ;

  /* Get the state of the display and resolution */
  if ( videoGetState ( 0, 0, &state ) == 0 &&
       videoGetResolution ( state.displayMode.resolution, &res ) == 0 ) 
  {
    if ( width ) 
    {
      *width = res.width ;
    }
    if ( height ) 
    {
      *height = res.height ;
    }
    return 0 ;
  }
  return -1 ;
}

/* wait for last flip to complete */
inline void 
rsxWaitFlip () 
{ 
  while ( gcmGetFlipStatus () != 0 ) 
    usleep ( 100 ) ;  /* Sleep, to not stress the cpu. */
  gcmResetFlipStatus () ;
}     
      
/* flip a buffer to screen */
inline int
rsxFlip ( videoData *vdata ) 
{
  if ( gcmSetFlip ( vdata->context, vdata->rsx_buffers[vdata->currentBuffer].id ) == 0 ) 
  {
    rsxFlushBuffer ( vdata->context ) ;
    /* Prevent the RSX from continuing until the flip has finished. */
    gcmSetWaitFlip ( vdata->context ) ;

    /* switch buffers */
    vdata->currentBuffer = !vdata->currentBuffer ;

    /* set new buffer as target */
    rsxSetRenderTarget ( vdata ) ;

    return TRUE ;
  }
  return FALSE ;
}
  
/* wait for the RSX command buffer to be idle */
inline void
rsxWaitIdle ( gcmContextData *context ) 
{       
  static u32 sLabelVal = 1 ;

  rsxSetWriteBackendLabel ( context, GCM_LABEL_INDEX, sLabelVal ) ;
  rsxSetWaitLabel ( context, GCM_LABEL_INDEX, sLabelVal ) ;

  sLabelVal++ ;

  rsxSetWriteBackendLabel ( context, GCM_LABEL_INDEX, sLabelVal ) ;

  rsxFlushBuffer ( context ) ;

  while ( * ( vu32 * )  gcmGetLabelAddress ( GCM_LABEL_INDEX )  != sLabelVal ) 
  {
    usleep ( 30 ) ;
  }
}

/* clear an RSX buffer */
inline void
rsxClearBuffer ( gcmContextData *context ) 
{
  rsxSetClearColor ( context, 0x00000000 ) ;
  rsxSetClearDepthValue ( context, 0x00000000 ) ;
  rsxClearSurface ( context, GCM_CLEAR_Z|GCM_CLEAR_R|GCM_CLEAR_G|GCM_CLEAR_B|GCM_CLEAR_A ) ;
}

/* rsx blending */
inline void
rsxBlend ( gcmContextData *context ) 
{
  rsxSetBlendFunc ( context, GCM_SRC_ALPHA, GCM_ONE_MINUS_SRC_ALPHA, GCM_SRC_ALPHA, GCM_ONE_MINUS_SRC_ALPHA ) ;
  rsxSetBlendEquation ( context, GCM_FUNC_ADD, GCM_FUNC_ADD ) ;
  rsxSetBlendEnable ( context, GCM_TRUE ) ;
}

/* set the current render target */
inline void
rsxSetRenderTarget ( videoData *vdata ) 
{
  gcmSurface sf ;

  /* clear surface struct */
  memset ( &sf, 0, sizeof ( gcmSurface ) ) ;

  sf.colorFormat      = GCM_TF_COLOR_A8R8G8B8 ;
  sf.colorTarget      = GCM_TF_TARGET_0 ;
  sf.colorLocation[0] = GCM_LOCATION_RSX ;
  sf.colorOffset[0]   = vdata->rsx_buffers[vdata->currentBuffer].color_offset ;
  sf.colorPitch[0]    = vdata->color_pitch ;

  sf.colorLocation[1] = GCM_LOCATION_RSX ;
  sf.colorOffset[1]   = 0 ;
  sf.colorPitch[1]    = 64 ;

  sf.colorLocation[2] = GCM_LOCATION_RSX ;
  sf.colorOffset[2]   = 0 ;
  sf.colorPitch[2]    = 64 ;

  sf.colorLocation[3] = GCM_LOCATION_RSX ;
  sf.colorOffset[3]   = 0 ;
  sf.colorPitch[3]    = 64 ;

  sf.depthFormat      = GCM_TF_ZETA_Z16 ;
  sf.depthLocation    = GCM_LOCATION_RSX ;
  sf.depthOffset      = vdata->depth_offset ;
  sf.depthPitch       = vdata->depth_pitch ;

  sf.type             = GCM_TF_TYPE_LINEAR ;
  sf.antiAlias 	      = GCM_TF_CENTER_1 ;

  sf.width            = vdata->rsx_buffers[vdata->currentBuffer].width ;
  sf.height           = vdata->rsx_buffers[vdata->currentBuffer].height ;
  sf.x                = 0 ;
  sf.y                = 0 ;

  /* set buffer surface */
  rsxSetSurface ( vdata->context, &sf ) ;

  /* clear new buffer */
  rsxClearBuffer ( vdata->context ) ;

  /* set pixel blending */
  rsxBlend ( vdata->context ) ;

  /* wait for command buffer to be idle */
  rsxWaitIdle ( vdata->context ) ;
}
