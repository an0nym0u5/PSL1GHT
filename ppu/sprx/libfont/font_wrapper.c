
#include <stdio.h>
#include <malloc.h>
#include <ppu-asm.h>

#include <font/font.h>

/*
void *fontMalloc(void *obj, u32 size);
void *fontFree(void *obj, void *ptr);
void *fontRealloc(void *obj, void *ptr, u32 size);
void *fontCalloc(void *obj, u32 num, u32 size);
*/

/*
typedef struct _usb_ldd_ops_ex
{
  const char *name ATTRIBUTE_PRXPTR;
  opd32 *probe ATTRIBUTE_PRXPTR;
  opd32 *attach ATTRIBUTE_PRXPTR;
  opd32 *detach ATTRIBUTE_PRXPTR;
} usbLddOpsEx;
*/

/*
extern s32 usbControlTransferEx(s32 pipe_id, usbDeviceRequest *req, void *buf, opd32 *opd, void *arg);
extern s32 usbRegisterLddEx(usbLddOpsEx *lddops);
extern s32 usbUnregisterLddEx(usbLddOpsEx *lddops);
extern s32 usbUnregisterExtraLddEx(usbLddOpsEx *lddops);
*/

/*
s32 usbControlTransfer(s32 pipe_id, usbDeviceRequest *req, void *buf, usbDoneCallback cb, void *arg)
{
    return usbControlTransferEx(pipe_id, req, buf, (opd32*)__get_opd32(cb), arg);
}
*/
/*
s32 usbRegisterLdd(usbLddOps *ldd_ops)
{
    usbLddOpsEx ldd_ops_ex =
    {
        "desc",
        (opd32*)__get_opd32(ldd_ops->probe),
        (opd32*)__get_opd32(ldd_ops->attach),
        (opd32*)__get_opd32(ldd_ops->detach)
    };
    return usbRegisterLddEx(&ldd_ops_ex);
}
*/

void *fontMalloc(void *obj, u32 size)
{
    obj = NULL ;
    return memalign ( 16, size ) ;
}

void fontFree(void *obj, void *ptr)
{
    obj = NULL ;
    free ( ptr ) ;
}

void *fontRealloc(void *obj, void *ptr, u32 size)
{
    obj = NULL ;
    return realloc ( ptr, size ) ;
}

void *fontCalloc(void *obj, u32 num, u32 size)
{
    obj = NULL ;
    return calloc ( num, size ) ;
}

