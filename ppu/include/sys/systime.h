/*! \file systime.h
 \brief System time management functions.
*/

#ifndef __SYS_SYSTIME_H__
#define __SYS_SYSTIME_H__

#include <ppu-lv2.h>
#include <lv2/systime.h>
#include <lv2/syscalls.h>

#ifdef __cplusplus
extern "C" {
#endif

LV2_INLINE u64 sysGetTimebaseFrequency()
{
	lv2syscall0(SYSCALL_TIME_GET_TIMEBASE_FREQUENCY);
	return_to_user_prog(u64);
}

LV2_SYSCALL sysGetCurrentTime(u64 *sec,u64 *nsec)
{
	lv2syscall2(SYSCALL_TIME_GET_CURRENT_TIME,(u64)sec,(u64)nsec);
	return_to_user_prog(s32);
}

LV2_SYSCALL sysSetCurrentTime(u64 sec,u64 nsec)
{
	lv2syscall2(SYSCALL_TIME_SET_CURRENT_TIME,sec,nsec);
	return_to_user_prog(s32);
}

LV2_SYSCALL sysSleep(u32 seconds)
{
	lv2syscall1(SYSCALL_TIMER_SLEEP,seconds);
	return_to_user_prog(s32);
}

LV2_SYSCALL sysUsleep(u32 useconds)
{
	lv2syscall1(SYSCALL_TIMER_USLEEP,useconds);
	return_to_user_prog(s32);
}

#ifdef __cplusplus
	}
#endif

#endif
