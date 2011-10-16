#include <stdio.h>
#include <stdlib.h>
#include <ppu-asm.h>

#include <sysutil/sysutil.h>
#include <sysutil/disc.h>

/* Disc utility support */
extern s32 sysDiscRegisterDiscChangeCallbackEx(opd32 *cbEject,opd32 *cbInsert);

/* Disc utility support */
s32 sysDiscRegisterDiscChangeCallback(sysDiscEjectCallback cbEject,sysDiscInsertCallback cbInsert)
{
	return sysDiscRegisterDiscChangeCallbackEx((opd32*)__get_opd32(cbEject),(opd32*)__get_opd32(cbInsert));
}

