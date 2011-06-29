/* Now double buffered with animation with one JPG dancing.
 */ 

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <rsx/rsx.h>
#include <sysutil/video.h>

#include <sysutil/sysutil.h>
#include <sysmodule/sysmodule.h>

#include <io/pad.h>

#include <jpgdec/jpgdec.h>

#include "rsxutil.h"
#include "psl1ght_jpg.h" // jpg in memory

#define USE_JPG_FROM_FILE false
#define JPG_FILE "/dev_usb/psl1ght_jpg.bin"

static int exitapp, xmbopen;
u32 module_flag;

static inline void
eventHandler(u64 status, u64 param, void * userdata)
{
  switch(status)
  {
    case SYSUTIL_EXIT_GAME:
      exitapp = 0;
      break;
    case SYSUTIL_MENU_OPEN:
      xmbopen = 1;
      break;
    case SYSUTIL_MENU_CLOSE:
      xmbopen = 0;
      break;
  }
}

void drawFrame(rsxBuffer *buffer, long frame) {
  s32 i, j;
  for(i = 0; i < buffer->height; i++) {
    s32 color = (i / (buffer->height * 1.0) * 256);
    /* This should make a nice black to green graident */
    color = (color << 8) | ((frame % 255) << 16);
    for(j = 0; j < buffer->width; j++)
      buffer->ptr[i* buffer->width + j] = color;
  }
}

static inline void
unload_modules()
{
  if(module_flag & 2)
    sysModuleUnload(SYSMODULE_JPGDEC);
  if(module_flag & 1)
    sysModuleUnload(SYSMODULE_FS);
}

s32 main(s32 argc, const char* argv[])
{
  gcmContextData *context;
  void *host_addr = NULL;
  rsxBuffer buffers[MAX_BUFFERS];
  int currentBuffer = 0;
  padInfo padinfo ;
  padData paddata ;
  u16 width;
  u16 height;
  int i;
  long frame = 0; /* to keep track of how many frames we have rendered */

  atexit(unload_modules);
  if(sysModuleLoad(SYSMODULE_FS) != 0)
    return 0;
  else
    module_flag |= 1;

  if(sysModuleLoad(SYSMODULE_JPGDEC) != 0)
    return 0;
  else
    module_flag |= 2;

  /* Allocate a 1Mb buffer, alligned to a 1Mb boundary
   * to be our shared IO memory with the RSX. */
  host_addr = memalign ( 1024*1024, HOST_SIZE ) ;
  context = screenInit ( host_addr, HOST_SIZE ) ;
  getResolution( &width, &height ) ;
  for (i = 0; i < MAX_BUFFERS; i++)
    makeBuffer( &buffers[i], width, height, i ) ;
  flip( context, MAX_BUFFERS - 1 ) ;
  setRenderTarget(context, &buffers[currentBuffer]) ;

  sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, eventHandler, NULL);

  ioPadInit(7) ;

  /* jpg bitmap buffer */
  jpgData jpg1;

#if USE_JPG_FROM_FILE == true
  const char *filename = JPG_FILE;
  /* load jpg from file */
  jpgLoadFromFile(filename, &jpg1);
#endif
#if USE_JPG_FROM_FILE == false
  /* load jpg from memory */
  jpgLoadFromBuffer((void *)psl1ght_jpg, psl1ght_jpg_size, &jpg1);
#endif

  /* Ok, everything is setup. Now for the main loop. */
  exitapp = 1;
  while(exitapp)
  {
    /* Check the pads. */
    ioPadGetInfo(&padinfo);
    for(i=0; i<MAX_PADS; i++){
      if(padinfo.status[i]){
        ioPadGetData(i, &paddata);

        if(paddata.BTN_CROSS){
          exitapp = 0;
          goto end;
        }
      }
    }

    waitFlip(); // Wait for the last flip to finish, so we can draw to the old buffer
    drawFrame(&buffers[currentBuffer], frame++); // Draw into the unused buffer

    if(jpg1.bmp_out)
    {
      static int x=0, y=0, dx=2, dy=2;
  
      u32 *scr = (u32 *)buffers[currentBuffer].ptr;
      u32 *jpg= (void *)jpg1.bmp_out;
      int n, m;
  
      /* update x, y coordinates */
      x+=dx;
      y+=dy;
  
      /* */
      if(x < 0)
      {
        x=0;
        dx=1;
      }

      /* screen width to jpg width */
      if(x > (buffers[currentBuffer].width - jpg1.width))
      {
        x=(buffers[currentBuffer].width - jpg1.width);
        dx=-2;
      }
  
      /* */
      if(y < 0)
      {
        y=0;
        dy=1;
      }

      /* screen height to jpg height */
      if(y > (buffers[currentBuffer].height - jpg1.height))
      {
        y = (buffers[currentBuffer].height - jpg1.height);
        dy=-2;
      }

      /* update screen buffer from coordinates */
      scr += y * buffers[currentBuffer].width + x;                     
  
      // draw JPG
      for(n=0;n<jpg1.height;n++)
      {
        if((y+n)>=buffers[currentBuffer].height) break;
        for(m=0;m<jpg1.width;m++)
        {
          if((x+m)>=buffers[currentBuffer].width) break;
          scr[m]=jpg[m];
        }
        jpg+=jpg1.pitch>>2;
        scr+=buffers[currentBuffer].width;
      }
    }

    waitFlip(); /* Wait for the last flip to finish, so we can draw to the old buffer */
    drawFrame(&buffers[currentBuffer], frame++); /* Draw into the unused buffer */
    flip(context, buffers[currentBuffer].id); /* Flip buffer onto screen */

    currentBuffer = !currentBuffer;
    setRenderTarget(context, &buffers[currentBuffer]) ; /* change buffer */

    sysUtilCheckCallback(); /* check user attention span */
  }

 end:

  gcmSetWaitFlip(context);
  for (i=0; i < MAX_BUFFERS; i++)
    rsxFree (buffers[i].ptr);
  rsxFinish (context, 1);
  free (host_addr);
  ioPadEnd();

  return 0;
}

