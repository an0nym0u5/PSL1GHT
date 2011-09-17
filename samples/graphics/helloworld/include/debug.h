/*
 * debug.h
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */


#ifndef __DEBUG_H__
#define __DEBUG_H__


#define dbgprintf(format) \
fprintf ( stdout, "\033[0;33m%s:%s():#%d :: "format"\033[0m\n", __FILE__, __func__, __LINE__+1 ) ;

#define argprintf(format,args...) \
fprintf ( stdout, "\033[0;33m%s:%s():#%d :: "format"\033[0m\n", __FILE__, __func__, __LINE__+1, args ) ;

#define errprintf(format,args...) \
fprintf ( stderr, "\033[0;31m%s:%s():#%d :: "format"\033[0m\n", __FILE__, __func__, __LINE__+1, args ) ;


#endif /* __DEBUG_H__ */

