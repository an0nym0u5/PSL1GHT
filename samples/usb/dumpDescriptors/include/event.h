/*
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef __EVENT_H__
#define __EVENT_H__


/* used to pass data between functions */
typedef struct _event_data
{
  int exitapp;
  int xmbopen;
  int menu;
} eventData;


void eventInitialization(eventData *edata);
void eventHandler (u64 status, u64 param, void *userdata);


#endif /* __EVENT_H__ */

