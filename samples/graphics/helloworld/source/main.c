#line 1 "source/main.c"
/*
 * main.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h> // memalign

#include <ppu-types.h>

#include <sys/thread.h>
#include <sys/process.h>
#include <sysutil/sysutil.h> // sysUtilRegisterCallback, sysUtilCheckCallback
#include <sysmodule/sysmodule.h>

#include <io/pad.h> // ioPadInit, ioPadCheck, ioPadEnd

#include "common.h"
#include "debug.h"
#include "pad.h"
#include "video.h"
#include "buffers.h"
#include "font.h"
#include "event.h"
#include "shader.h"


/* global for loaded sysmodules */
u32 module_flag ;

/* set initial stack size */
SYS_PROCESS_PARAM( 1001, 0x100000 ) ;


/* load sysmodule if not loaded */
void
sysmoduleLoad ( s32 flag, sysModuleId id )
{
  static s32 ret ;

  if ( ( ret = sysModuleIsLoaded ( id ) ) != SYSMODULE_LOADED )
  {
    if ( ( ret = sysModuleLoad ( id ) ) != SYSMODULE_OK )
    {
      errprintf ( "ERROR: cannot load flag: %d, id:%x, ret:%x", flag, id, ret ) ;
      exit ( EXIT_FAILURE ) ;
    }
    module_flag |= flag ;
  }
  else
  {
    argprintf ( "sysmodule already loaded: flag: %d, id:%x, (%x)", flag, id, ret ) ;
  }
}

/* unload sysmodule if loaded */
void
sysmoduleUnload ( s32 flag, sysModuleId id )
{
  s32 ret ;

  if ( module_flag & flag )
  {
    if ( ( ret = sysModuleIsLoaded ( id ) ) == SYSMODULE_LOADED )
    {
      if ( ( ret = sysModuleUnload ( id ) ) != SYSMODULE_OK )
      {
        errprintf ( "ERROR: cannot unload flag: %d, id:%x, ret:%x", flag, id, ret ) ;
      }
    }
    else
    {
      errprintf ( "ERROR: sysmodule flag: %d, id:%x, (%x)", flag, id, ret ) ;
    }
  }
}

/* load sysmodules */
void
modulesLoad ()
{
  /* load sysmodule */
  sysmoduleLoad ( 1, SYSMODULE_FS ) ;
  /* load sysmodule */
  sysmoduleLoad ( 2, SYSMODULE_SYSUTIL ) ;
  /* load sysmodule */
  sysmoduleLoad ( 3, SYSMODULE_GCM_SYS ) ;
  /* load sysmodule */
  sysmoduleLoad ( 4, SYSMODULE_RESC ) ;
  /* load sysmodule */
  sysmoduleLoad ( 5, SYSMODULE_IO ) ;
}

/* unload sysmodules at exit */
void
modulesUnload ()
{
  /* unload io sysmodule */
  sysmoduleUnload ( 5, SYSMODULE_IO ) ;
  /* unload resc sysmodule */
  sysmoduleUnload ( 4, SYSMODULE_RESC ) ;
  /* unload gcm_sys sysmodule */
  sysmoduleUnload ( 3, SYSMODULE_GCM_SYS ) ;
  /* unload sysutil sysmodule */
  sysmoduleUnload ( 2, SYSMODULE_SYSUTIL ) ;
  /* unload fs sysmodule */
  sysmoduleUnload ( 1, SYSMODULE_FS ) ;
}

/*
 *
 * main
 *
 */
s32 main(s32 argc, const char *argv[])
{
  char line = LINE_SIZE + LINE_SIZE ;

  /* thread variables */
  u64 priority = 1500 ;
  size_t stacksize = 0x100000 ;
  sys_ppu_thread_t vid_thread_id ;
  sys_ppu_thread_t pad_thread_id ;

  /* data structures */
  eventData evt_data ;
  padBtnData pad_data ;
  videoData vid_data ;
  shaderData shd_data ;
  fontBuffer fon_buffer ;
  fontData fon_data ;

  dbgprintf ( "main initializing" ) ;

  /* register modulesUnload for execution at type exit */
  if ( atexit ( modulesUnload ) != 0 )
  {
    dbgprintf ( "cannot set exit function" ) ;
    exit ( EXIT_FAILURE ) ;
  }

  /* load sysmodule sprx' */
  modulesLoad () ;

  /* register eventHandler */
  eventInitialization ( &evt_data ) ;

  /* initialize controller io */
  padInitialization ( &pad_data ) ;

  /* pointer to exitapp */
  pad_data.exitapp = &evt_data.exitapp ;

  /* lock pad mutex */
  sysMutexLock ( pad_data.mutex, NO_TIMEOUT ) ;

  /* create pad thread */
  sysThreadCreate ( &pad_thread_id, padWorker, (void *)&pad_data,
                    priority + 10, stacksize, THREAD_JOINABLE, "padWorker" ) ;

  /* wait for pad thread to be ready */
  sysCondWait ( pad_data.cond, NO_TIMEOUT ) ;

  /* release lock */
  sysMutexUnlock ( pad_data.mutex ) ;

  /* initialize video */
  videoInitialization ( &vid_data ) ;

  /* lock video mutex */
  sysMutexLock ( vid_data.mutex, NO_TIMEOUT ) ;

  /* create video thread */
  sysThreadCreate ( &vid_thread_id, videoWorker, (void *)&vid_data,
                    priority + 20, stacksize, THREAD_JOINABLE, "videoWorker" ) ;

  /* wait for video thread to be ready */
  sysCondWait ( vid_data.cond, NO_TIMEOUT ) ;

  /* release lock */
  sysMutexUnlock ( vid_data.mutex ) ;

  /* initialize font settings */
  sysSemWait ( vid_data.sem, TIMEOUT ) ;
  fontInitialization ( &fon_data, FONT_SIZE, vid_data.width, vid_data.height ) ;
  sysSemPost ( vid_data.sem, 1 ) ;

  /* pointer to fon_buffer for video thread */
  sysSemWait ( fon_buffer.sem, TIMEOUT ) ;
  sysSemWait ( vid_data.sem, TIMEOUT ) ;
  vid_data.fon_buffer = &fon_buffer ;
  sysSemPost ( vid_data.sem, 1 ) ;
  sysSemPost ( fon_buffer.sem, 1 ) ;

  /* width / height for fon_buffer */
  sysSemWait ( fon_buffer.sem, TIMEOUT ) ;
  sysSemWait ( vid_data.sem, TIMEOUT ) ;
  fon_buffer.width = vid_data.width ;
  fon_buffer.height = vid_data.height ;
  sysSemPost ( vid_data.sem, 1 ) ;
  sysSemPost ( fon_buffer.sem, 1 ) ;

  /* initialize fon_buffer */
  fontBufferInitialization ( &vid_data, &fon_data ) ;

  /* initialize shader */
  shaderInitialization ( &shd_data ) ;

  /* initialize resc */
  rescInitialization ( &vid_data ) ;

  /* pointer to exitapp */
  sysSemWait ( vid_data.sem, TIMEOUT ) ;
  vid_data.exitapp = &evt_data.exitapp ;
  sysSemPost ( vid_data.sem, 1 ) ;

  /*
   *  initialization complete
   */

  /* signal pad thread to start */
  sysMutexLock ( pad_data.mutex, NO_TIMEOUT ) ;
  dbgprintf ( "signalling padWorker...") ;
  sysCondSignal ( pad_data.cond ) ;
  sysMutexUnlock ( pad_data.mutex ) ;

  /* signal video thread to start */
  sysMutexLock ( vid_data.mutex, NO_TIMEOUT ) ;
  dbgprintf ( "signalling videoWorker...") ;
  sysCondSignal ( vid_data.cond ) ;
  sysMutexUnlock ( vid_data.mutex ) ;

  /*
   *  start rendering to screen
   */

  sprintf ( fon_data.string, "PSL1GHT HelloWorld" ) ;
  sysSemWait ( fon_buffer.sem, TIMEOUT ) ;
  fontPrint ( &fon_data, LINE_INDENT, line, fon_data.string, &fon_buffer ) ;
  sysSemPost ( fon_buffer.sem, 1 ) ;

  /* Let's do some printing */
  sysSemWait ( fon_buffer.sem, TIMEOUT ) ;
  fontPrint ( &fon_data, LINE_INDENT, line += LINE_SIZE, "Hello World!", &fon_buffer ) ;
  sysSemWait ( fon_buffer.sem, TIMEOUT ) ;

  sprintf ( fon_data.string, "Hello World." ) ;
  sysSemWait ( fon_buffer.sem, TIMEOUT ) ;
  fontPrint ( &fon_data, LINE_INDENT, line += LINE_SIZE, fon_data.string, &fon_buffer ) ;
  sysSemPost ( fon_buffer.sem, 1 ) ;

  /* exit message */
  sysSemWait ( fon_buffer.sem, TIMEOUT ) ;
  fontPrint ( &fon_data, fon_buffer.width / 3, fon_buffer.height / 2, "Press X to quit", &fon_buffer )  ;
  sysSemPost ( fon_buffer.sem, 1 ) ;

  /* loop until exit */
  while ( evt_data.exitapp )
  {
    /* check for controller input */
    padCheckState ( &pad_data ) ;

    /* check if XMB */
    sysUtilCheckCallback () ;

    /* exit if user quit via xmb */
    if ( evt_data.exitapp == 0 )
    {
      goto end ;
    }
  }

  end:
  {
    dbgprintf ( "main stopping" ) ;

    /* toggle exitapp so threads quit */
    evt_data.exitapp = 0 ;

    /* lock mutex */
    sysMutexLock ( vid_data.mutex, NO_TIMEOUT ) ;

    /* wait for video to exit */
    sysCondWait ( vid_data.cond, NO_TIMEOUT ) ;

    /* release lock */
    sysMutexUnlock ( vid_data.mutex ) ;

    /* free fon_buffer resources */
    fontBufferFinish ( &fon_buffer ) ;

    /* close pads */
    padFinish ( &pad_data ) ;

    /* free video resources */
    videoFinish ( &vid_data ) ;

    /* finish remaining */
    eventFinish () ;

    /* free font resources */
    fontFinish( &fon_data ) ;

    dbgprintf ( "main exiting" ) ;

    exit ( EXIT_SUCCESS ) ;
  }
}

