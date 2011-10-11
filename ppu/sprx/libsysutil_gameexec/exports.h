#ifndef __EXPORTS_H__
#define __EXPORTS_H__


/* Game Exec utility support */
EXPORT(sysGameExecGetBootGameInfo, 0xf6acd0bc); /* cellGameExec */
EXPORT(sysGameExecGetHomeDataExportPath, 0x59b1ede1); /* cellGameExec */
EXPORT(sysGameExecGetHomeDataImportPath, 0x72cc6cf7); /* cellGameExec */
EXPORT(sysGameExecGetHomeLaunchOptionPath, 0x94e9f81d); /* cellGameExec */
EXPORT(sysGameExecGetHomePath, 0x59bbebd4); /* cellGameExec */
EXPORT(sysGameExecSetExitParam, 0x38579ec9); /* cellGameExec */


#endif
