#include <ppu-asm.h>
#include <usb/usb.h>


extern s32 usbIsochronousTransferEx(s32 pipe_id, usbIsochRequest *req, opd32 *opd, void *arg);
extern s32 usbHSIsochronousTransferEx(s32 pipe_id, usbHSIsochRequest *req, opd32 *opd, void *arg);
extern s32 usbControlTransferEx(s32 pipe_id, usbDeviceRequest *req, void *buf, opd32 *opd, void *arg);
extern s32 usbBulkTransferEx(s32 pipe_id, void *buf, s32 len, opd32 *opd, void *arg);
extern s32 usbInterruptTransferEx(s32 pipe_id, void *buf, s32 len, opd32 *opd, void *arg);

s32 usbIsochronousTransfer(s32 pipe_id, usbIsochRequest *req, usbIsochDoneCallback cb, void *arg)
{
	return usbIsochronousTransferEx(pipe_id, req, (opd32*)__get_opd32(cb), arg);
}

s32 usbHSIsochronousTransfer(s32 pipe_id, usbHSIsochRequest *req, usbHSIsochDoneCallback cb, void *arg)
{
	return usbHSIsochronousTransferEx(pipe_id, req, (opd32*)__get_opd32(cb), arg);
}

s32 usbControlTransfer(s32 pipe_id, usbDeviceRequest *req, void *buf, usbDoneCallback cb, void *arg)
{
	return usbControlTransferEx(pipe_id, req, buf, (opd32*)__get_opd32(cb), arg);
}

s32 usbBulkTransfer(s32 pipe_id, void *buf, s32 len, usbDoneCallback cb, void *arg)
{
	return usbBulkTransferEx(pipe_id, buf, len, (opd32*)__get_opd32(cb), arg);
}

s32 usbInterruptTransfer(s32 pipe_id, void *buf, s32 len, usbDoneCallback cb, void *arg)
{
	return usbInterruptTransferEx(pipe_id, buf, len, (opd32*)__get_opd32(cb), arg);
}

