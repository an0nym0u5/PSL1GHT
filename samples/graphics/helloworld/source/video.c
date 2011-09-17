#line 1 "source/video.c"
/*
 * video.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#include <stdio.h>
#include <time.h>
#include <sys/sem.h>
#include <sys/mutex.h>
#include <sys/cond.h>
#include <sys/thread.h>           /* for threads */

#include "common.h"
#include "debug.h"
#include "video.h"
#include "rsxutil.h"
#include "buffers.h"
#include "font.h"


void
videoInitialization ( videoData *vdata )
{
  dbgprintf ( "initializing" ) ;

  /* initialize semaphore attributes */
  vdata->sem_attr.key            = 0x01 ;
  vdata->sem_attr.attr_protocol  = SYS_SEM_ATTR_PROTOCOL ;
  vdata->sem_attr.attr_pshared   = SYS_SEM_ATTR_PSHARED ;

  /* initialize mutex attributes */
  vdata->mutex_attr.key              = 0x01 ;
  vdata->mutex_attr.attr_protocol    = SYS_MUTEX_PROTOCOL_FIFO ;
  vdata->mutex_attr.attr_pshared     = SYS_MUTEX_ATTR_PSHARED ;
  vdata->mutex_attr.attr_recursive   = SYS_MUTEX_ATTR_RECURSIVE ;
  vdata->mutex_attr.attr_adaptive    = SYS_MUTEX_ATTR_ADAPTIVE ;

  /* initialize condition attributes */
  vdata->cond_attr.key               = 0x01 ;
  vdata->cond_attr.attr_pshared      = SYS_COND_ATTR_PSHARED ;

  /* create semaphore */
  sysSemCreate ( &vdata->sem, &vdata->sem_attr, 1, SEM_CONSUMERS ) ;

  /* create mutex */
  sysMutexCreate ( &vdata->mutex, &vdata->mutex_attr ) ;

  /* create cond */
  sysCondCreate ( &vdata->cond, vdata->mutex, &vdata->cond_attr ) ;

  /* initialize rsx context and buffers */
  rsxInitialization ( vdata ) ;

  dbgprintf ( "initialized" ) ;
}

void
videoFinish ( videoData *vdata )
{
  dbgprintf ( "video finishing" ) ;

  static s32 i ;
  /* make sure no flip is in progress */
  gcmSetWaitFlip ( vdata->context ) ;

  /* free rsx buffers */
  for ( i = 0 ; i < MAX_BUFFERS ; i++ )
  {
    rsxFree ( vdata->rsx_buffers[i].ptr ) ;
  }

  /* finish rsx context */
  rsxFinish ( vdata->context, 1 ) ;

  /* free host_addr memory */
  free ( vdata->host_addr ) ;

  /* destroy semaphore */
  sysSemDestroy ( vdata->sem ) ;

  /* destroy cond */
  sysCondDestroy ( vdata->cond ) ;

  /* destroy mutex */
  sysMutexDestroy ( vdata->mutex ) ;
}

inline void
videoDrawFrame ( videoData *vdata )
{
  /* wait vsync */
  rescWaitFlip () ;

  /* update text */
  sysSemWait ( vdata->fon_buffer->sem, NO_TIMEOUT ) ;
  fontBufferDraw ( vdata->context, vdata->fon_buffer, &vdata->rsx_buffers[vdata->currentBuffer] ) ;
  sysSemPost ( vdata->fon_buffer->sem, 1 ) ;

  /* flip buffer to screen */
  rescFlip ( vdata ) ;
}

/* video worker thread */
void
videoWorker ( void *arg )
{
  static s32 frames ;
  static time_t starttime ;
  dbgprintf ( "video thread starting" ) ;

  /* cast the void *arg to rsxData */
  videoData* vdata = ( videoData* )arg ;

  /* signal main thread is ready */
  sysCondSignal ( vdata->cond ) ;

  /* lock mutex */
  sysMutexLock ( vdata->mutex, NO_TIMEOUT ) ;

  dbgprintf ( "video thread waiting" ) ;

  /* wait for main to be ready */
  sysCondWait ( vdata->cond, NO_TIMEOUT ) ;

  /* release lock */
  sysMutexUnlock ( vdata->mutex ) ;

  starttime = time( NULL ) ;

  dbgprintf ( "video thread entering loop" ) ;

  /* render frames until exit */
  while ( *vdata->exitapp )
  {
    /* render frame */
    videoDrawFrame ( vdata ) ;
    frames++ ;
  }

  dbgprintf ( "video thread left loop" ) ;

  /* lock mutex */
  sysMutexLock ( vdata->mutex, NO_TIMEOUT ) ;

  /* signal main before exit */
  sysCondSignal ( vdata->cond ) ;

  /* release lock */
  sysMutexUnlock ( vdata->mutex ) ;

  argprintf ( "frame rate: %g frames/sec", ( ( double ) frames ) / difftime ( time ( NULL ) , starttime ) ) ;
  dbgprintf ( "video thread exiting" ) ;

  /* exit thread */
  sysThreadExit ( 0 ) ;
}

