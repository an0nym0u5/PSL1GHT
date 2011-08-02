#line 1 "event.c"
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
  fprintf ( stdout, "event initializing\n" ) ;

  /* initialize variables */
  edata->menu = 1 ;
  edata->exitapp = 1 ;
  edata->xmbopen = 0 ;

  /* register eventHandler */
  sysUtilRegisterCallback ( SYSUTIL_EVENT_SLOT0, eventHandler, &edata ) ;
}

/* event handler for in-game XMB */
inline void
eventHandler ( u64 status, u64 param, void *userdata )
{
  eventData* event = (eventData*)userdata;

  switch ( status )
  {
    case SYSUTIL_EXIT_GAME:
      event->exitapp = 0 ;
      break ;
    case SYSUTIL_MENU_OPEN:
      event->xmbopen = 1 ;
      break ;
    case SYSUTIL_MENU_CLOSE:
      event->xmbopen = 0 ;
      break ;
    default:
      break ;
  }

  return ;
}

