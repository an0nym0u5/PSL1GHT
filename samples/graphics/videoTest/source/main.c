/* Now double buffered with animation.
 */ 

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <rsx/rsx.h>
#include <sysutil/video.h>

#include <sysutil/sysutil.h>

#include <io/pad.h>

#include "rsxutil.h"

static int exitapp, xmbopen;

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

s32 main(s32 argc, const char* argv[])
{
  gcmContextData *context;
  void *host_addr = NULL;
  rsxBuffer buffers[MAX_BUFFERS];
  int currentBuffer = 0;
  padInfo padinfo;
  padData paddata;
  u16 width;
  u16 height;
  int i;

  long frame = 0; // To keep track of how many frames we have rendered.

  /* Allocate a 1Mb buffer, alligned to a 1Mb boundary                          
   * to be our shared IO memory with the RSX. */
  host_addr = memalign (1024*1024, HOST_SIZE);
  context = initScreen (host_addr, HOST_SIZE);
  getResolution(&width, &height);
  for (i = 0; i < MAX_BUFFERS; i++)
    makeBuffer( &buffers[i], width, height, i);
  flip(context, MAX_BUFFERS - 1);
  setRenderTarget(context, &buffers[currentBuffer]);

  sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, eventHandler, NULL);

  ioPadInit(7);

  /* Ok, everything is setup. Now for the main loop. */
  exitapp = 1;
  while(exitapp){
    // Check the pads.
    ioPadGetInfo(&padinfo);
    for(i=0; i<MAX_PADS; i++){
      if(padinfo.status[i]){
        ioPadGetData(i, &paddata);

        if(paddata.BTN_START){
          goto end;
        }
      }

    }

    waitFlip(); /* Wait for the last flip to finish, so we can draw to the old buffer */
    drawFrame(&buffers[currentBuffer], frame++); /* Draw into the unused buffer */
    flip(context, buffers[currentBuffer].id); /* Flip buffer onto screen */

    currentBuffer = !currentBuffer;
    setRenderTarget(context, &buffers[currentBuffer]); /* change buffer */

    sysUtilCheckCallback(); /* check user attention span */
  }
  
 end:

  gcmSetWaitFlip(context);
  for (i = 0; i < MAX_BUFFERS; i++)
    rsxFree(buffers[i].ptr);
  rsxFinish(context, 1);
  free(host_addr);
  ioPadEnd();

  return 0;
}

