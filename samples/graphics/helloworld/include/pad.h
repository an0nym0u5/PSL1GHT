/*
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef __PAD_H__
#define __PAD_H__


#include "common.h"
#include "event.h"


/* △  */
#define PAD_TRIANGLE   1
/* ◯  */
#define PAD_CIRCLE     2
/* ✕  */
#define PAD_CROSS      3
/* ☐  */
#define PAD_SQUARE     4
/* SELECT */
#define PAD_SELECT     5
/* START */
#define PAD_START      6
/* ▲  */ 
#define PAD_UP         7
/* ▶  */ 
#define PAD_RIGHT      8
/* ▼  */
#define PAD_DOWN       9
/* ◀  */ 
#define PAD_LEFT       10
/* BD Remote */
#define PAD_BDCODE     11


/* used to pass data between functions */
typedef struct _pad_btn_data
{
  int btn;
  int now;
  int last;
  int *exitapp;

  eventData *edata;

  sys_sem_t sem;
  sys_sem_attr_t sem_attr;

  sys_mutex_t mutex;
  sys_mutex_attr_t mutex_attr;

  sys_cond_t cond;
  sys_cond_attr_t cond_attr;
} padBtnData;


void padInitialization();
int padCheck(padBtnData *b);
int padCheckState(padBtnData *b);
void padWorker(void *arg);
void padFinish();

#endif /* __PAD_H__ */

