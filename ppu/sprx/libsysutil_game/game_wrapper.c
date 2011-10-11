#include <stdio.h>
#include <stdlib.h>
#include <ppu-asm.h>

#include <sysutil/sysutil.h>
#include <sysutil/game.h>
#include <sysutil/disc.h>

/* sysGame functions */
extern s32 sysGameThemeInstallFromBufferEx(u32 fileSize, u32 bufSize, void *buf, opd32 *themeCb, u32 option);
extern s32 sysGameRegisterDiscChangeCallbackEx(opd32 *cbEject,opd32 *cbInsert);


/* game utility support */
s32 sysGameThemeInstallFromBuffer(u32 fileSize, u32 bufSize, void *buf, sysGameThemeInstallCallback themeCb, u32 option)
{
	return sysGameThemeInstallFromBufferEx(fileSize,bufSize,buf,(opd32*)__get_opd32(themeCb),option);
}

s32 sysGameRegisterDiscChangeCallback(sysDiscEjectCallback cbEject,sysDiscInsertCallback cbInsert)
{
	return sysGameRegisterDiscChangeCallbackEx((opd32*)__get_opd32(cbEject),(opd32*)__get_opd32(cbInsert));
}

