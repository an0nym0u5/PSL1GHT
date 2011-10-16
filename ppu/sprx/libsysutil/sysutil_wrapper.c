#include <stdio.h>
#include <stdlib.h>
#include <ppu-asm.h>

#include <sysutil/sysutil.h>

/* sysUtil functions */
extern s32 sysUtilRegisterCallbackEx(s32 slot,opd32 *opd,void *usrdata);

/* sysUtil wrapper functions */
s32 sysUtilRegisterCallback(s32 slot,sysutilCallback cb,void *usrdata)
{
	return sysUtilRegisterCallbackEx(slot,(opd32*)__get_opd32(cb),usrdata);
}

