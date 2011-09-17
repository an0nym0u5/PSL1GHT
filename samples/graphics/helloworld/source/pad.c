#line 1 "source/pad.c"
/*
 * pad.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#include <stdio.h>

#include <sys/sem.h>
#include <sys/mutex.h>
#include <sys/cond.h>
#include <sys/thread.h>           /* for threads */

#include <io/pad.h> // ioPadInit, ioPadCheck, ioPadEnd

#include "common.h"
#include "debug.h"
#include "pad.h"


/* initialize controller */
void
padInitialization (padBtnData *pdata )
{
  dbgprintf ( "initializing" ) ;

  /* initialize state variables */
  pdata->btn = 0 ;
  pdata->now = 0 ;
  pdata->last = 0 ;

  /* initialize semaphore attributes */
  pdata->sem_attr.key            = PAD_KEY ;
  pdata->sem_attr.attr_protocol  = SYS_SEM_ATTR_PROTOCOL ;
  pdata->sem_attr.attr_pshared   = SYS_SEM_ATTR_PSHARED ;

  /* initialize mutex attributes */
  pdata->mutex_attr.key              = PAD_KEY ;
  pdata->mutex_attr.attr_protocol    = SYS_MUTEX_PROTOCOL_FIFO ;
  pdata->mutex_attr.attr_pshared     = SYS_MUTEX_ATTR_PSHARED ;
  pdata->mutex_attr.attr_recursive   = SYS_MUTEX_ATTR_RECURSIVE ;
  pdata->mutex_attr.attr_adaptive    = SYS_MUTEX_ATTR_ADAPTIVE ;

  /* initialize condition attributes */
  pdata->cond_attr.key               = PAD_KEY ;
  pdata->cond_attr.attr_pshared      = SYS_COND_ATTR_PSHARED ;

  /* create semaphore */
  sysSemCreate ( &pdata->sem, &pdata->sem_attr, 1, SEM_CONSUMERS ) ;

  /* create mutex */
  sysMutexCreate ( &pdata->mutex, &pdata->mutex_attr ) ;

  /* create cond */
  sysCondCreate ( &pdata->cond, pdata->mutex, &pdata->cond_attr ) ;

  ioPadInit ( 7 ) ;

  dbgprintf ( "initialized" ) ;
}

/* release controller */
inline void
padFinish ( padBtnData *pdata )
{
  dbgprintf ( "pad finishing" ) ;

  /* destroy semaphore */
  sysSemDestroy ( pdata->sem ) ;

  /* destroy cond */
  sysCondDestroy ( pdata->cond ) ;

  /* destroy mutex */
  sysMutexDestroy ( pdata->mutex ) ;

  ioPadEnd () ;

  dbgprintf ( "pad finished" ) ;
}

/* check controller for input */
inline int
padCheck ( padBtnData *pdata )
{
  static int i ;
  padInfo padinfo ;
  padData paddata ;

  pdata->btn = 0 ;

  ioPadGetInfo ( &padinfo ) ;
  for ( i = 0 ; i < MAX_PADS ; i++ )
  {
    if ( !padinfo.status[i] )
    {
      continue ;
    }
    else
    {
      ioPadGetData ( i, &paddata ) ;
      if ( paddata.BTN_TRIANGLE )
      {
        pdata->btn = PAD_TRIANGLE ;
      }
      else if ( paddata.BTN_CIRCLE )
      {
        pdata->btn = PAD_CIRCLE ;
      }
      else if ( paddata.BTN_CROSS )
      {
        pdata->btn = PAD_CROSS ;
      }
      else if ( paddata.BTN_SQUARE )
      {
        pdata->btn = PAD_SQUARE ;
      }
      else if ( paddata.BTN_SELECT )
      {
        pdata->btn = PAD_SELECT ;
      }
      else if ( paddata.BTN_START )
      {
        pdata->btn = PAD_START ;
      }
      else if ( paddata.BTN_UP )
      {
        pdata->btn = PAD_UP ;
      }
      else if ( paddata.BTN_RIGHT )
      {
        pdata->btn = PAD_RIGHT ;
      }
      else if ( paddata.BTN_DOWN )
      {
        pdata->btn = PAD_DOWN ;
      }
      else if ( paddata.BTN_LEFT )
      {
        pdata->btn = PAD_LEFT ;
      }
      else
      {
        pdata->btn = 0 ;
      }
    }
  }

  pdata->now = pdata->btn & ( ~pdata->last ) ;
  pdata->last = pdata->btn ;

  return pdata->now ;
}

/* check controller buttons */
inline int
padCheckState ( padBtnData *pdata )
{
  s32 ret = padCheck ( pdata ) ;
  switch ( ret )
  {
    case 0:
      break ;
    case PAD_TRIANGLE:
      dbgprintf ( "PAD_TRIANGLE" ) ;
      *pdata->exitapp = 1 ;
      break ;
    case PAD_CIRCLE:
      dbgprintf ( "PAD_CIRCLE" ) ;
      *pdata->exitapp = 1 ;
      break ;
    case PAD_CROSS:
      dbgprintf ( "PAD_CROSS" ) ;
      *pdata->exitapp = 0 ;
      break ;
    case PAD_SQUARE:
      dbgprintf ( "PAD_SQUARE" ) ;
      *pdata->exitapp = 1 ;
      break ;
    case PAD_SELECT:
      dbgprintf ( "PAD_SELECT" ) ;
      *pdata->exitapp = 1 ;
      break ;
    case PAD_START:
      dbgprintf ( "PAD_START" ) ;
      *pdata->exitapp = 0 ;
      break ;
    default:
      argprintf ( "default: %d", ret ) ;
      break ;
  }
  return 0 ;
}

/* pad worker thread */
void
padWorker ( void *arg )
{
  dbgprintf ( "pad thread starting" ) ;

  /* cast the void *arg to rsxData */
  padBtnData* pdata = ( padBtnData* )arg ;

  /* signal main thread is ready */
  sysCondSignal ( pdata->cond ) ;

  /* lock mutex */
  sysMutexLock ( pdata->mutex, NO_TIMEOUT ) ;

  dbgprintf ( "pad thread waiting" ) ;

  /* wait for main to be ready */
  sysCondWait ( pdata->cond, NO_TIMEOUT ) ;

  /* release lock */
  sysMutexUnlock ( pdata->mutex ) ;

  dbgprintf ( "pad thread entering loop" ) ;

  /* render frames until exit */
  while ( *pdata->exitapp )
  {
    /* check pads */
    padCheckState ( pdata ) ;
  }

  dbgprintf ( "pad thread left loop" ) ;

  /* lock mutex */
  sysMutexLock ( pdata->mutex, NO_TIMEOUT ) ;

  /* signal main before exit */
  sysCondSignal ( pdata->cond ) ;

  /* release lock */
  sysMutexUnlock ( pdata->mutex ) ;

  dbgprintf ( "pad thread exiting" ) ;

  /* exit thread */
  sysThreadExit ( 0 ) ;
}

