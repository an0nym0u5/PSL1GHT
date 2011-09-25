#line 1 "source/event.c"
/*
 * event.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#include <stdio.h>

#include <sysutil/sysutil.h>      // sysUtilRegisterCallback, sysUtilCheckCallback

#include "event.h"


/* init event handler */
void
eventInitialization ( eventData *edata )
{
  /* initialize variables */
  edata->menu = 1 ;
  edata->exitapp = 1 ;
  edata->xmbopen = 0 ;

  /* register eventHandler */
  sysUtilRegisterCallback ( SYSUTIL_EVENT_SLOT0, eventHandler, edata ) ;
}

/* event handler for in-game XMB */
inline void
eventHandler ( u64 status, u64 param, void *userdata )
{
  eventData* edata = (eventData*)userdata;

  switch ( status )
  {
    case SYSUTIL_EXIT_GAME:
      eventFinish ( edata ) ;
      edata->exitapp = 0 ;
      break ;
    case SYSUTIL_DRAW_BEGIN:
      edata->xmbopen = 1 ;
      break ;
    case SYSUTIL_DRAW_END:
      edata->xmbopen = 0 ;
      break ;
    case SYSUTIL_MENU_OPEN:
      edata->menu = 1 ;
      break ;
    case SYSUTIL_MENU_CLOSE:
      edata->menu = 0 ;
      break ;
    default:
      break ;
  }

  return ;
}

void
eventFinish ( eventData *edata )
{
  sysUtilUnregisterCallback ( SYSUTIL_EVENT_SLOT0 ) ;
}

