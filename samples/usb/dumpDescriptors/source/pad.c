#include <stdio.h> // printf

#include <io/pad.h> // ioPadInit, ioPadCheck, ioPadEnd

#include "pad.h"


/* initialize controller */
inline void
padInitialization (padBtnData *pdata )
{
  fprintf ( stdout, "pad initializing...\n" ) ;

  /* initialize state variables */
  pdata->now = 0 ;
  pdata->last = 0 ;

  ioPadInit ( 7 ) ;
}

/* release controller */
inline void
padFinish ( padBtnData *pdata )
{
  fprintf ( stdout, "pad finishing...\n" ) ;

  ioPadEnd () ;
}

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

  pdata->now = pdata->btn & (~pdata->last) ;
  pdata->last = pdata->btn ;

  return pdata->now ;
}

/* check controller buttons */
inline int
padCheckState ( padBtnData *pdata )
{
  switch ( padCheck ( pdata ) )
  {
    case 0:
      break ;
    case PAD_TRIANGLE:
      fprintf ( stdout, "PAD_TRIANGLE\n" ) ;
      *pdata->exitapp = 1;
      break;
    case PAD_CIRCLE:
      fprintf ( stdout, "PAD_CIRCLE\n" ) ;
      *pdata->exitapp = 1;
      break ;
    case PAD_CROSS:
      fprintf ( stdout, "PAD_CROSS\n" ) ;
      *pdata->exitapp = 1;
      break ;
    case PAD_SQUARE:
      fprintf ( stdout, "PAD_SQUARE\n" ) ;
      *pdata->exitapp = 1;
      break;
    case PAD_SELECT:
      fprintf ( stdout, "PAD_SELECT\n" ) ;
      *pdata->exitapp = 1;
      break;
    case PAD_START:
      fprintf ( stdout, "PAD_START\n" ) ;
      *pdata->exitapp = 0;
      break;
    default:
      fprintf ( stdout, "default\n" ) ;
      break ;
  }
  return 0 ;
}

