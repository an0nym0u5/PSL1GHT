#ifndef _SYSUTIL_GAME_EXEC_H_
#define _SYSUTIL_GAME_EXEC_H_

#include <ppu-types.h>
#include <ppu-asm.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * functions
 */

s32 sysGameExecGetBootGameInfo(u32 *type, char *dir, u32 *data);
s32 sysGameExecSetExitParam(u32 data);
s32 sysGameExecGetHomeLaunchOptionPath(char *common, char *personal) ;
s32 sysGameExecGetHomeDataExportPath(char *path);
s32 sysGameExecGetHomeDataImportPath(char *path);


#ifdef __cplusplus
    }
#endif

#endif /* __SYSUTIL_GAME_EXEC_H__ */

