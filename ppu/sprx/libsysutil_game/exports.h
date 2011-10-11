#ifndef __EXPORTS_H__
#define __EXPORTS_H__

/* Game Content utility support */
EXPORT(sysGameDataCheck, 0xdb9819f3);
EXPORT(sysGameBootCheck, 0xf52639ea);
EXPORT(sysGamePatchCheck, 0xce4374f6);
EXPORT(sysGameCreateGameData, 0x42a2e133);
EXPORT(sysGameGetParamInt, 0xb7a45caf);
EXPORT(sysGameGetParamString, 0x3a5d726a);
EXPORT(sysGameGetSizeKB, 0xef9d42d5);
EXPORT(sysGameSetParamString, 0xdaa5cd20);
EXPORT(sysGameGetDiscContentInfoUpdatePath, 0x2a8e6b92);
EXPORT(sysGameContentPermit, 0x70acec67);
EXPORT(sysGameContentErrorDialog, 0xb0a1f8c6);
EXPORT(sysGameThemeInstall, 0xd24e3928);
EXPORT(sysGameThemeInstallFromBufferEx, 0x87406734);
EXPORT(sysGameGetLocalWebContentPath, 0xa80bf223);
EXPORT(sysGameDeleteGameData, 0xb367c6e3);
EXPORT(sysGameRegisterDiscChangeCallbackEx, 0xf8115d69);
EXPORT(sysGameUnregisterDiscChangeCallback, 0x21fc0c71);


#endif
