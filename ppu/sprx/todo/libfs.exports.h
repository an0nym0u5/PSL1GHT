#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(fsAioCancel, 0x7f13fc8c); /* sys_fs */
EXPORT(fsAioFinish, 0x9f951810); /* sys_fs */
EXPORT(fsAioInit, 0xdb869f20); /* sys_fs */
EXPORT(fsAioRead, 0xc1c507e7); /* sys_fs */
EXPORT(fsAioWrite, 0x4cef342e); /* sys_fs */
EXPORT(fsAllocateFileAreaByFdWithInitialData, 0x3394f037); /* sys_fs */
EXPORT(fsAllocateFileAreaByFdWithoutZeroFill, 0x2cf1296b); /* sys_fs */
EXPORT(fsAllocateFileAreaWithInitialData, 0x103b8632); /* sys_fs */
EXPORT(fsAllocateFileAreaWithoutZeroFill, 0x7a0329a1); /* sys_fs */
EXPORT(fsArcadeHddSerialNumber, 0x1ea02e2f); /* sys_fs */
EXPORT(fsChangeFileSizeByFdWithoutAllocation, 0xe15939c3); /* sys_fs */
EXPORT(fsChangeFileSizeWithoutAllocation, 0x606f9f42); /* sys_fs */
EXPORT(fsChmod, 0x99406d0b); /* sys_fs */
EXPORT(fsClose, 0x2cb51f0d); /* sys_fs */
EXPORT(fsClosedir, 0xff42dcc3); /* sys_fs */
EXPORT(fsFGetBlockSize, 0xcb588dba); /* sys_fs */
EXPORT(fsFstat, 0xef3efa34); /* sys_fs */
EXPORT(fsFsync, 0x967a162b); /* sys_fs */
EXPORT(fsFtruncate, 0x0e2939e5); /* sys_fs */
EXPORT(fsGetBlockSize, 0x1a108ab7); /* sys_fs */
EXPORT(fsGetDirectoryEntries, 0x9b882495); /* sys_fs */
EXPORT(fsGetFreeSize, 0xaa3b4bcd); /* sys_fs */
EXPORT(fsLseek, 0xa397d042); /* sys_fs */
EXPORT(fsMkdir, 0xba901fe6); /* sys_fs */
EXPORT(fsOpen, 0x718bf5f8); /* sys_fs */
EXPORT(fsOpendir, 0x3f61245c); /* sys_fs */
EXPORT(fsRead, 0x4d5ff8e2); /* sys_fs */
EXPORT(fsReaddir, 0x5c74903d); /* sys_fs */
EXPORT(fsReadWithOffset, 0x0d5b4a14); /* sys_fs */
EXPORT(fsRegisterConversionCallback, 0xa01ee33a); /* sys_fs */
EXPORT(fsRename, 0xf12eecc8); /* sys_fs */
EXPORT(fsRmdir, 0x2796fdf3); /* sys_fs */
EXPORT(fsSdataOpen, 0xb1840b53); /* sys_fs */
EXPORT(fsSdataOpenByFd, 0x6d3bb15b); /* sys_fs */
EXPORT(fsSetDefaultContainer, 0x02671310); /* sys_fs */
EXPORT(fsSetDiscReadRetrySetting, 0x91a1beaa); /* sys_fs */
EXPORT(fsSetIoBuffer, 0x3140f6e1); /* sys_fs */
EXPORT(fsSetIoBufferFromDefaultContainer, 0x75f16dc5); /* sys_fs */
EXPORT(fsStat, 0x7de6dced); /* sys_fs */
EXPORT(fsStRead, 0x27800c6b); /* sys_fs */
EXPORT(fsStReadFinish, 0xd73938df); /* sys_fs */
EXPORT(fsStReadGetCurrentAddr, 0x190912f6); /* sys_fs */
EXPORT(fsStReadGetRegid, 0xbd273a88); /* sys_fs */
EXPORT(fsStReadGetRingBuf, 0xb3afee8b); /* sys_fs */
EXPORT(fsStReadGetStatus, 0xcf34969c); /* sys_fs */
EXPORT(fsStReadInit, 0x2664c8ae); /* sys_fs */
EXPORT(fsStReadPutCurrentAddr, 0x81f33783); /* sys_fs */
EXPORT(fsStReadStart, 0x8df28ff9); /* sys_fs */
EXPORT(fsStReadStop, 0xf8e5d9a0); /* sys_fs */
EXPORT(fsStReadWait, 0x8f71c5b2); /* sys_fs */
EXPORT(fsStReadWaitCallback, 0x866f6aec); /* sys_fs */
EXPORT(fsTruncate, 0xc9dc3ac5); /* sys_fs */
EXPORT(fsTruncate2, 0x3a1c8393); /* sys_fs */
EXPORT(fsUnlink, 0x7f4677a8); /* sys_fs */
EXPORT(fsUnregisterL10nCallbacks, 0xf94baa80); /* sys_fs */
EXPORT(fsUtime, 0xbef554a4); /* sys_fs */
EXPORT(fsWrite, 0xecdcf2ab); /* sys_fs */
EXPORT(fsWriteWithOffset, 0x8cb722d5); /* sys_fs */


#endif
