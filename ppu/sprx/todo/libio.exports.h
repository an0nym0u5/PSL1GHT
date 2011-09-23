#ifndef __EXPORTS_H__
#define __EXPORTS_H__

/* Pad */
EXPORT(ioPadInit, 0x1cf98800); /* sys_io */
EXPORT(ioPadEnd, 0x4d9b75d5); /* sys_io */
EXPORT(ioPadClearBuf, 0x0d5f2c14); /* sys_io */

EXPORT(ioPadLddRegisterController, 0x20a97ba2); /* sys_io */


EXPORT(ioPadGetDataExtra, 0x6bc09c61); /* sys_io */

EXPORT(ioPadGetData, 0x8b72cda1); /* sys_io */
EXPORT(ioPadLddGetPortNo, 0x8b8231e5); /* sys_io */
EXPORT(ioPadLddDataInsert, 0xbafd6409); /* sys_io */


EXPORT(ioPadLddUnregisterController, 0xe442faa8); /* sys_io */
EXPORT(ioPadSetActDirect, 0xf65544ee); /* sys_io */

EXPORT(ioPadPeriphGetInfo, 0x4cc9b68d); /* sys_io */
EXPORT(ioPadSetPortSetting, 0x578e3c98); /* sys_io */
EXPORT(ioPadPeriphGetData, 0x8a00f264); /* sys_io */
EXPORT(ioPadGetInfo2, 0xa703a51d); /* sys_io */
EXPORT(ioPadDbgGetData, 0xcf3051f7); /* sys_io */
EXPORT(ioPadDbgLddRegisterController, 0xa74396e5); /* sys_io */
EXPORT(ioPadDbgLddSetDataInsertMode, 0x94b98e39); /* sys_io */
EXPORT(ioPadDbgPeriphRegisterDevice, 0x7c5d5fc1); /* sys_io */

/* Mouse */
EXPORT(ioMouseInit, 0xc9030138); /* sys_io */
EXPORT(ioMouseEnd, 0xe10183ce); /* sys_io */
EXPORT(ioMouseClearBuf, 0x3ef66b95); /* sys_io */
EXPORT(ioMouseGetInfo, 0x5baf30fb); /* sys_io */
EXPORT(ioMouseGetTabletDataList, 0x21a62e9b); /* sys_io */
EXPORT(ioMouseSetTabletMode, 0x2d16da4f); /* sys_io */
EXPORT(ioMouseGetData, 0x3138e632); /* sys_io */
EXPORT(ioMouseInfoTabletMode, 0x4d0b3b1f); /* sys_io */
EXPORT(ioMouseGetRawData, 0xa328cc35); /* sys_io */
EXPORT(ioMouseGetDataList, 0x6bd131f0); /* sys_io */

/* Keyboard */
EXPORT(ioKbInit, 0x433f6ec0); /* sys_io */
EXPORT(ioKbEnd, 0xbfce3285); /* sys_io */
EXPORT(ioKbRead, 0xff0a21b7); /* sys_io */
EXPORT(ioKbSetReadMode, 0xdeefdfa7); /* sys_io */
EXPORT(ioKbSetCodeType, 0xa5f85e4d); /* sys_io */
EXPORT(ioKbCnvRawCode, 0x4ab1fa77); /* sys_io */
EXPORT(ioKbSetLEDStatus, 0x3f72c56e); /* sys_io */
EXPORT(ioKbGetInfo, 0x2f1774d5); /* sys_io */
EXPORT(ioKbGetConfiguration, 0x1f71ecbe); /* sys_io */
EXPORT(ioKbClearBuf, 0x2073b7f6); /* sys_io */

/* SysConfig */
EXPORT(ioSysConfigAddServiceListener, 0x6ae10596); /* sys_io */
EXPORT(ioSysConfigRegisterService, 0x78f058a2); /* sys_io */
EXPORT(ioSysConfigRemoveServiceListener, 0xf5d9d571); /* sys_io */
EXPORT(ioSysConfigStart, 0x068fcbc6); /* sys_io */
EXPORT(ioSysConfigStop, 0x6d367953); /* sys_io */
EXPORT(ioSysConfigUnregisterService, 0x5f81900c); /* sys_io */


#endif
