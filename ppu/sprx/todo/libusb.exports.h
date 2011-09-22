#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(usbdAllocateMemory, 0x074dbb39); /* cellUsbd */
EXPORT(usbdBulkTransfer, 0xac77eb78); /* cellUsbd */
EXPORT(usbdClosePipe, 0x9763e962); /* cellUsbd */
EXPORT(usbdControlTransfer, 0x97cf128e); /* cellUsbd */
EXPORT(usbdEnd, 0x35f22ac3); /* cellUsbd */
EXPORT(usbdFreeMemory, 0x4e456e81); /* cellUsbd */
EXPORT(usbdGetDeviceLocation, 0xdb819e03); /* cellUsbd */
EXPORT(usbdGetDeviceSpeed, 0xbdbd2428); /* cellUsbd */
EXPORT(usbdGetPrivateData, 0x5de3af36); /* cellUsbd */
EXPORT(usbdGetThreadPriority, 0xd5263dea); /* cellUsbd */
EXPORT(usbdHSIsochronousTransfer, 0x7a1b6eab); /* cellUsbd */
EXPORT(usbdInit, 0xd0e766fe); /* cellUsbd */
EXPORT(usbdInterruptTransfer, 0x0f411262); /* cellUsbd */
EXPORT(usbdIsochronousTransfer, 0xde58c4c2); /* cellUsbd */
EXPORT(usbdOpenPipe, 0x254289ac); /* cellUsbd */
EXPORT(usbdRegisterExtraLdd, 0x7fe92c54); /* cellUsbd */
EXPORT(usbdRegisterExtraLdd2, 0xbd554bcb); /* cellUsbd */
EXPORT(usbdRegisterLdd, 0x359befba); /* cellUsbd */
EXPORT(usbdScanStaticDescriptor, 0x2fb08e1e); /* cellUsbd */
EXPORT(usbdSetPrivateData, 0x63bfdb97); /* cellUsbd */
EXPORT(usbdSetThreadPriority, 0xc24af1d7); /* cellUsbd */
EXPORT(usbdSetThreadPriority2, 0x5c832bd7); /* cellUsbd */
EXPORT(usbdUnregisterExtraLdd, 0x90460081); /* cellUsbd */
EXPORT(usbdUnregisterLdd, 0x64951ac7); /* cellUsbd */


#endif
