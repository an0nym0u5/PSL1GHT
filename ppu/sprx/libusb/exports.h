#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(usbInit, 0xd0e766fe);
EXPORT(usbEnd, 0x35f22ac3);
EXPORT(usbOpenPipe, 0x254289ac);
EXPORT(usbClosePipe, 0x9763e962);
EXPORT(usbAllocateMemory, 0x074dbb39);
EXPORT(usbFreeMemory, 0x4e456e81);
EXPORT(usbScanStaticDescriptor, 0x2fb08e1e);
EXPORT(usbGetDeviceLocation, 0xdb819e03);
EXPORT(usbGetDeviceSpeed, 0xbdbd2428);
EXPORT(usbGetPrivateData, 0x5de3af36);
EXPORT(usbSetPrivateData, 0x63bfdb97);
EXPORT(usbGetThreadPriority, 0xd5263dea);
EXPORT(usbSetThreadPriority, 0xc24af1d7);
EXPORT(usbSetThreadPriority2, 0x5c832bd7);
EXPORT(usbRegisterLdd, 0x359befba);
EXPORT(usbUnregisterLdd, 0x64951ac7);
EXPORT(usbRegisterExtraLdd, 0x7fe92c54);
EXPORT(usbRegisterExtraLdd2, 0xbd554bcb);
EXPORT(usbUnregisterExtraLdd, 0x90460081);
EXPORT(usbIsochronousTransfer, 0xde58c4c2);
EXPORT(usbHSIsochronousTransfer, 0x7a1b6eab);
EXPORT(usbControlTransfer, 0x97cf128e);
EXPORT(usbBulkTransfer, 0xac77eb78);
EXPORT(usbInterruptTransfer, 0x0f411262);


#endif
