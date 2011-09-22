#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(kbClearBuf, 0x2073b7f6); /* sys_io */
EXPORT(kbCnvRawCode, 0x4ab1fa77); /* sys_io */
EXPORT(kbEnd, 0xbfce3285); /* sys_io */
EXPORT(kbGetConfiguration, 0x1f71ecbe); /* sys_io */
EXPORT(kbGetInfo, 0x2f1774d5); /* sys_io */
EXPORT(kbInit, 0x433f6ec0); /* sys_io */
EXPORT(kbRead, 0xff0a21b7); /* sys_io */
EXPORT(kbSetCodeType, 0xa5f85e4d); /* sys_io */
EXPORT(kbSetLEDStatus, 0x3f72c56e); /* sys_io */
EXPORT(kbSetReadMode, 0xdeefdfa7); /* sys_io */

EXPORT(mouseClearBuf, 0x3ef66b95); /* sys_io */
EXPORT(mouseEnd, 0xe10183ce); /* sys_io */
EXPORT(mouseGetData, 0x3138e632); /* sys_io */
EXPORT(mouseGetDataList, 0x6bd131f0); /* sys_io */
EXPORT(mouseGetInfo, 0x5baf30fb); /* sys_io */
EXPORT(mouseGetRawData, 0xa328cc35); /* sys_io */
EXPORT(mouseGetTabletDataList, 0x21a62e9b); /* sys_io */
EXPORT(mouseInfoTabletMode, 0x4d0b3b1f); /* sys_io */
EXPORT(mouseInit, 0xc9030138); /* sys_io */
EXPORT(mouseSetTabletMode, 0x2d16da4f); /* sys_io */

EXPORT(padClearBuf, 0x0d5f2c14); /* sys_io */
EXPORT(padDbgGetData, 0xcf3051f7); /* sys_io */
EXPORT(padDbgLddRegisterController, 0xa74396e5); /* sys_io */
EXPORT(padDbgLddSetDataInsertMode, 0x94b98e39); /* sys_io */
EXPORT(padDbgPeriphRegisterDevice, 0x7c5d5fc1); /* sys_io */
EXPORT(padEnd, 0x4d9b75d5); /* sys_io */
EXPORT(padGetData, 0x8b72cda1); /* sys_io */
EXPORT(padGetDataExtra, 0x6bc09c61); /* sys_io */
EXPORT(padGetInfo2, 0xa703a51d); /* sys_io */
EXPORT(padInit, 0x1cf98800); /* sys_io */
EXPORT(padLddDataInsert, 0xbafd6409); /* sys_io */
EXPORT(padLddGetPortNo, 0x8b8231e5); /* sys_io */
EXPORT(padLddRegisterController, 0x20a97ba2); /* sys_io */
EXPORT(padLddUnregisterController, 0xe442faa8); /* sys_io */
EXPORT(padPeriphGetData, 0x8a00f264); /* sys_io */
EXPORT(padPeriphGetInfo, 0x4cc9b68d); /* sys_io */
EXPORT(padSetActDirect, 0xf65544ee); /* sys_io */
EXPORT(padSetPortSetting, 0x578e3c98); /* sys_io */

EXPORT(ioSysConfigAddServiceListener, 0x6ae10596); /* sys_io */
EXPORT(ioSysConfigRegisterService, 0x78f058a2); /* sys_io */
EXPORT(ioSysConfigRemoveServiceListener, 0xf5d9d571); /* sys_io */
EXPORT(ioSysConfigStart, 0x068fcbc6); /* sys_io */
EXPORT(ioSysConfigStop, 0x6d367953); /* sys_io */
EXPORT(ioSysConfigUnregisterService, 0x5f81900c); /* sys_io */


#endif
