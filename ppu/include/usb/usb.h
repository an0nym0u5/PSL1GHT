/*! \file usb.h
 \brief USB low level management.
 */

#ifndef __USB_H__
#define __USB_H__

#include <ppu-types.h>
#include <ppu-asm.h>

/*
 * constants
 */

/* request types */
#define USB_REQTYPE_DIR_BITS                     0x80
#define USB_REQTYPE_DIR_TO_DEVICE                0x00
#define USB_REQTYPE_DIR_TO_HOST                  0x80
#define USB_REQTYPE_TYPE_BITS                    0x60
#define USB_REQTYPE_TYPE_STANDARD                0x00
#define USB_REQTYPE_TYPE_CLASS                   0x20
#define USB_REQTYPE_TYPE_VENDOR                  0x40
#define USB_REQTYPE_TYPE_RESERVED                0x60
#define USB_REQTYPE_RECIP_BITS                   0x1f
#define USB_REQTYPE_RECIP_DEVICE                 0x00
#define USB_REQTYPE_RECIP_INTERFACE              0x01
#define USB_REQTYPE_RECIP_ENDPOINT               0x02
#define USB_REQTYPE_RECIP_OTHER                  0x03

/* request */
#define USB_REQUEST_GET_STATUS                   0x00
#define USB_REQUEST_CLEAR_FEATURE                0x01
#define USB_REQUEST_SET_FEATURE                  0x03
#define USB_REQUEST_SET_ADDRESS                  0x05
#define USB_REQUEST_GET_DESCRIPTOR               0x06
#define USB_REQUEST_SET_DESCRIPTOR               0x07
#define USB_REQUEST_GET_CONFIGURATION            0x08
#define USB_REQUEST_SET_CONFIGURATION            0x09
#define USB_REQUEST_GET_INTERFACE                0x0a
#define USB_REQUEST_SET_INTERFACE                0x0b
#define USB_REQUEST_SYNCH_FRAME                  0x0c

/* descriptor types */
#define USB_DESCRIPTOR_TYPE_DEVICE               0x01
#define USB_DESCRIPTOR_TYPE_CONFIGURATION        0x02
#define USB_DESCRIPTOR_TYPE_STRING               0x03
#define USB_DESCRIPTOR_TYPE_INTERFACE            0x04
#define USB_DESCRIPTOR_TYPE_ENDPOINT             0x05
#define USB_DESCRIPTOR_TYPE_HID                  0x21
#define USB_DESCRIPTOR_TYPE_REPORT               0x22

/* features */
#define USB_FEATURE_ENDPOINT_HALT                0x00
#define USB_FEATURE_DEVICE_REMOTE_WAKEUP         0x01

/* device classes */
#define USB_CLASS_PER_INTERFACE                  0x00
#define USB_CLASS_AUDIO                          0x01
#define USB_CLASS_COMMUNICATIONS                 0x02
#define USB_CLASS_HID                            0x03
#define USB_CLASS_MONITOR                        0x04
#define USB_CLASS_PHYSICAL                       0x05
#define USB_CLASS_POWER                          0x06
#define USB_CLASS_PRINTER                        0x07
#define USB_CLASS_STORAGE                        0x08
#define USB_CLASS_HUB                            0x09
#define USB_CLASS_DATA                           0x0a
#define USB_CLASS_VENDOR_SPECIFIC                0xff

/* configuration */
#define USB_CONFIGURATION_RESERVED_ZERO          0x1f
#define USB_CONFIGURATION_REMOTE_WAKEUP          0x20
#define USB_CONFIGURATION_SELF_POWERED           0x40
#define USB_CONFIGURATION_RESERVED_ONE           0x80

/* bmAttribute */
#define USB_ENDPOINT_TRANSFER_TYPE_BITS          0x03
#define USB_ENDPOINT_TRANSFER_TYPE_SHIFT         0
#define USB_ENDPOINT_TRANSFER_TYPE_CONTROL       0x00
#define USB_ENDPOINT_TRANSFER_TYPE_ISOCHRONOUS   0x01
#define USB_ENDPOINT_TRANSFER_TYPE_BULK          0x02
#define USB_ENDPOINT_TRANSFER_TYPE_INTERRUPT     0x03

/* bEndpointAddress */
#define USB_ENDPOINT_NUMBER_BITS                 0x1f
#define USB_ENDPOINT_NUMBER_SHIFT                0
#define USB_ENDPOINT_DIRECTION_BITS              0x80
#define USB_ENDPOINT_DIRECTION_SHIFT             7
#define USB_ENDPOINT_DIRECTION_OUT               0x00
#define USB_ENDPOINT_DIRECTION_IN                0x80

/* packet sizes */
#define USB_MAX_LS_CONTROL_PACKET_SIZE           8     /* low speed */
#define USB_MAX_LS_INTERRUPT_PACKET_SIZE         8     /* low speed */
#define USB_MAX_FS_CONTROL_PACKET_SIZE           64    /* full speed */
#define USB_MAX_FS_INTERRUPT_PACKET_SIZE         64    /* full speed */
#define USB_MAX_BULK_PACKET_SIZE                 64    /* full speed only */
#define USB_MAX_ISOCHRONOUS_PACKET_SIZE          1023  /* full speed only */
	
/* OHCI completion codes */
#define USB_HC_CC_NOERR                          0x0
#define USB_OHCI_CC_CRC                          0x1
#define USB_OHCI_CC_BFV                          0x2
#define USB_OHCI_CC_DTM                          0x3
#define USB_OHCI_CC_STALL                        0x4
#define USB_OHCI_CC_NOTRESP                      0x5
#define USB_OHCI_CC_PIDCF                        0x6
#define USB_OHCI_CC_UEPID                        0x7
#define USB_OHCI_CC_DOR                          0x8
#define USB_OHCI_CC_DUR                          0x9
#define USB_OHCI_CC_RSVDA                        0xa
#define USB_OHCI_CC_RSVDB                        0xb
#define USB_OHCI_CC_BOR                          0xc
#define USB_OHCI_CC_BUR                          0xd
#define USB_OHCI_CC_NOTACC1                      0xe
#define USB_OHCI_CC_NOTACC2                      0xf
#define USB_EHCI_CC_MISSMF                       0x10
#define USB_EHCI_CC_XACT                         0x20
#define USB_EHCI_CC_BABBLE                       0x30
#define USB_EHCI_CC_DATABUF                      0x40
#define USB_EHCI_CC_HALTED                       0x50

/* PSW isochronous transfer completion codes */
#define USB_CC_NOERR                             0x0
#define USB_CC_MISSMF                            0x1
#define USB_CC_XACT                              0x2
#define USB_CC_BABBLE                            0x4
#define USB_CC_DATABUF                           0x8

/* return codes */
#define USB_PROBE_FAILED                         (-1)
#define USB_ATTACH_FAILED                        (-1)
#define USB_DETACH_FAILED                        (-1)
#define USB_PROBE_SUCCEEDED                      (0)
#define USB_ATTACH_SUCCEEDED                     (0)
#define USB_DETACH_SUCCEEDED                     (0)

#define USB_MAX_ISOCH_PACKETS                    (8)

/* device speed */
#define USB_DEVICE_SPEED_LS                      (0)
#define USB_DEVICE_SPEED_FS                      (1)
#define USB_DEVICE_SPEED_HS                      (2)

/* thread type */
#define USB_THREAD_TYPE_EVENT_HANDLER            (0)
#define USB_THREAD_TYPE_USBD_THREAD              (1)
#define USB_THREAD_TYPE_CALLBACK_THREAD          (2)

/* errors */
#define USB_OK                                   0x00
#define USB_ERR_NOT_INITIALIZED                  (0x80110001)
#define USB_ERR_ALREADY_INITIALIZED              (0x80110002)
#define USB_ERR_NO_MEMORY                        (0x80110003)
#define USB_ERR_INVALID_PARAM                    (0x80110004)
#define USB_ERR_INVALID_TRANSFER_TYPE            (0x80110005)
#define USB_ERR_LDD_ALREADY_REGISTERED           (0x80110006)
#define USB_ERR_LDD_NOT_ALLOCATED                (0x80110007)
#define USB_ERR_LDD_NOT_RELEASED                 (0x80110008)
#define USB_ERR_LDD_NOT_FOUND                    (0x80110009)
#define USB_ERR_DEVICE_NOT_FOUND                 (0x8011000a)
#define USB_ERR_PIPE_NOT_ALLOCATED               (0x8011000b)
#define USB_ERR_PIPE_NOT_RELEASED                (0x8011000c)
#define USB_ERR_PIPE_NOT_FOUND                   (0x8011000d)
#define USB_ERR_IOREQ_NOT_ALLOCATED              (0x8011000e)
#define USB_ERR_IOREQ_NOT_RELEASED               (0x8011000f)
#define USB_ERR_IOREQ_NOT_FOUND                  (0x80110010)
#define USB_ERR_CANNOT_GET_DESCRIPTOR            (0x80110011)
#define USB_ERR_FATAL                            (0x801100ff)


/*
 * structs
 */

/* device request */
typedef struct _usb_device_request
{
  u8 requestType;
  u8 request;
  u16 value;
  u16 index;
  u16 length;
} usbDeviceRequest;

/* device descriptor */
typedef struct _usb_device_descriptor
{
  u8 length;
  u8 descriptorType;
  u16 bcdUSB;
  u8 deviceClass;
  u8 deviceSubclass;
  u8 deviceProtocol;
  u8 maxPacketSize0;
  u16 idVendor;
  u16 idProduct;
  u16 bcdDevice;
  u8 manufacturer;
  u8 product;
  u8 serialNumber;
  u8 numConfigurations;
} usbDeviceDescriptor;

/* configuration descriptor */
typedef struct _usb_configuration_descriptor
{
  u8 length;
  u8 descriptorType;
  u16 totalLength;
  u8 numInterfaces;
  u8 configurationValue;
  u8 configuration;
  u8 attributes;
  u8 maxPower;
} usbConfigurationDescriptor;

/* interface descriptor */
typedef struct _usb_interface_descriptor
{
  u8 length;
  u8 descriptorType;
  u8 interfaceNumber;
  u8 alternateSetting;
  u8 numEndpoints;
  u8 interfaceClass;
  u8 interfaceSubclass;
  u8 interfaceProtocol;
  u8 interface;
} usbInterfaceDescriptor;

/* endpoint descriptor */
typedef struct _usb_endpoint_descriptor
{
  u8 length;
  u8 descriptorType;
  u8 endpointAddress;
  u8 attributes;
  u16 maxPacketSize;
  u8 interval;
} usbEndpointDescriptor;

/* string descriptor */
typedef struct _usb_string_descriptor
{
  u8 length;
  u8 descriptorType;
  u8 string[0];
} usbStringDescriptor;

/* HID descriptor info (class specific descriptor) */
typedef struct _usb_hid_sub_descriptor_info
{
  u8 descriptorType;
  u8 descriptorLength0;
  u8 descriptorLength1;
} usbHidSubDescriptorInfo;

/* HID descriptor */
typedef struct _usb_hid_descriptor
{
  u8 length;
  u8 descriptorType;
  u8 bcdHID0;
  u8 bcdHID1;
  u8 countryCode;
  u8 numDescriptors;  /* number of subdescriptor */
  usbHidSubDescriptorInfo subDescriptorInfo[0];
} usbHidDescriptor;

/* */
typedef struct _usb_isoch_psw_len
{
  u16 len:11;
  u16 reserved:1;
  u16 PSW:4;
} usbIsochPswLen;

/* */
typedef struct _usb_hs_isoch_psw_len
{
  u16 len:12;
  u16 PSW:4;
} usbHSIsochPswLen;

/* */
typedef struct _usb_hs_isoch_request
{
  void *buffer_base ATTRIBUTE_PRXPTR;
  s32 relative_start_frame;
  s32 num_packets;
  usbHSIsochPswLen packets[USB_MAX_ISOCH_PACKETS];
} usbHSIsochRequest;

/* */
typedef struct _usb_isoch_request
{
  void *buffer_base ATTRIBUTE_PRXPTR;
  s32 relative_start_frame;
  s32 num_packets;
  usbIsochPswLen packets[USB_MAX_ISOCH_PACKETS];
} usbIsochRequest;

/*
 * callbacks
 */

/* Logical Device Driver (ldd) operations */
typedef struct _usb_ldd_ops
{
  const char *name;
  s32 (*probe)(s32 dev_id);
  s32 (*attach)(s32 dev_id);
  s32 (*detach)(s32 dev_id);
} usbLddOps;

/* transfer done */
typedef void (*usbDoneCallback)(s32 result, s32 count, void* arg);

/* isochronous transfer done */
typedef void (*usbIsochDoneCallback)(s32 result, usbIsochRequest *req, void *arg);

/* HS isochronous transfer done */
typedef void (*usbHSIsochDoneCallback)(s32 result, usbHSIsochRequest *req, void *arg);


/*
 * functions
 */ 

s32 usbInit(void);
s32 usbEnd(void);

s32 usbOpenPipe(s32 device_id, usbEndpointDescriptor *end_desc);
s32 usbClosePipe(s32 pipe_id);

s32 usbAllocateMemory(void **ptr, size_t size);
s32 usbFreeMemory(void *ptr);

void *usbScanStaticDescriptor(s32 device_id, void *ptr, unsigned char type);

s32 usbGetDeviceLocation(s32 device_id, unsigned char *location);
s32 usbGetDeviceSpeed(s32 device_id, u8 *speed);

void *usbGetPrivateData(s32 device_id);
s32 usbSetPrivateData(s32 device_id, void *priv);

s32 usbGetThreadPriority(s32 thread_type);
//s32 usbSetThreadPriority(UNKNOWN);
s32 usbSetThreadPriority2(s32 event_prio, s32 usb_prio, s32 callback_priority);

s32 usbRegisterLdd(usbLddOps *lddops);
s32 usbUnregisterLdd(usbLddOps *lddops);
s32 usbRegisterExtraLdd(usbLddOps *lddops, u16 vendor_id, u16 product_id);
s32 usbRegisterExtraLdd2(usbLddOps *lddops, u16 vendor_id, u16 product_id_min, u16 product_id_max);
s32 usbUnregisterExtraLdd(usbLddOps *lddops);

s32 usbBulkTransfer(s32 pipe_id, void *buf, s32 len, usbDoneCallback cb, void* arg);
s32 usbControlTransfer(s32 pipe_id, usbDeviceRequest *req, void *buf, usbDoneCallback cb, void *arg);
s32 usbInterruptTransfer(s32 pipe_id, void *buf, s32 len, usbDoneCallback cb, void *arg);
s32 usbIsochronousTransfer(s32 pipe_id, usbIsochRequest *req, usbIsochDoneCallback cb, void *arg);
s32 usbHSIsochronousTransfer(s32 pipe_id, usbHSIsochRequest *req, usbHSIsochDoneCallback cb, void *arg);


/*
 * standard control xfer macros
 */

#define usbClearDeviceFeature(pid, fs, cb, arg) ({  \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x00; \
  device_request.request = USB_REQUEST_CLEAR_FEATURE; \
  device_request.value = (fs); \
  device_request.index = 0; \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbClearInterfaceFeature(pid, fs, interface, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x01; \
  device_request.request = USB_REQUEST_CLEAR_FEATURE; \
  device_request.value = (fs); \
  device_request.index = (interface); \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbClearEndpointFeature(pid, fs, endpoint, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x02; \
  device_request.request = USB_REQUEST_CLEAR_FEATURE; \
  device_request.value = (fs); \
  device_request.index = (endpoint); \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbGetConfiguration(pid, ptr, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x80; \
  device_request.request = USB_REQUEST_GET_CONFIGURATION; \
  device_request.value = 0; \
  device_request.index = 0; \
  device_request.length = 1; \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbGetDescriptor(pid, type, index, lang_id, ptr, len, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x80; \
  device_request.request = USB_REQUEST_GET_DESCRIPTOR; \
  device_request.value = ((type) << 8) | (index); \
  device_request.index = (lang_id); \
  device_request.length = (len); \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbGetInterface(pid, interface, ptr, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x81; \
  device_request.request = USB_REQUEST_GET_INTERFACE; \
  device_request.value = 0; \
  device_request.index = (interface); \
  device_request.length = 1; \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbGetDeviceStatus(pid, ptr, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x80; \
  device_request.request = USB_REQUEST_GET_STATUS; \
  device_request.value = 0; \
  device_request.index = 0; \
  device_request.length = 2; \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbGetInterfaceStatus(pid, interface, ptr, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x81; \
  device_request.request = USB_REQUEST_GET_STATUS; \
  device_request.value = 0; \
  device_request.index = (interface); \
  device_request.length = 2; \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbGetEndpointStatus(pid, endpoint, ptr, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x82; \
  device_request.request = USB_REQUEST_GET_STATUS; \
  device_request.value = 0; \
  device_request.index = (endpoint); \
  device_request.length = 2; \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbSetAddress(pid, address, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x00; \
  device_request.request = USB_REQUEST_SET_ADDRESS; \
  device_request.value = (address); \
  device_request.index = 0; \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbSetConfiguration(pid, config, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x00; \
  device_request.request = USB_REQUEST_SET_CONFIGURATION; \
  device_request.value = (config); \
  device_request.index = 0; \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbSetDeviceDescriptor(pid, type, index, lang_id, ptr, len, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x00; \
  device_request.request = USB_REQUEST_SET_DESCRIPTOR; \
  device_request.value = ((type) << 8) | (index); \
  device_request.index = (lang_id); \
  device_request.length = (len); \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbSetInterfaceDescriptor(pid, type, index, lang_id, ptr, len, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x01; \
  device_request.request = USB_REQUEST_SET_DESCRIPTOR; \
  device_request.value = ((type) << 8) | (index); \
  device_request.index = (lang_id); \
  device_request.length = (len); \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbSetEndpointDescriptor(pid, type, index, lang_id, ptr, len, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x02; \
  device_request.request = USB_REQUEST_SET_DESCRIPTOR; \
  device_request.value = ((type) << 8) | (index); \
  device_request.index = (lang_id); \
  device_request.length = (len); \
  usbControlTransfer((pid), (&device_request), (ptr), (cb), (arg)); })

#define usbSetDeviceFeature(pid, fs, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x00; \
  device_request.request = USB_REQUEST_SET_FEATURE; \
  device_request.value = (fs); \
  device_request.index = 0; \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbSetInterfaceFeature(pid, fs, interface, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x01; \
  device_request.request = USB_REQUEST_SET_FEATURE; \
  device_request.value = (fs); \
  device_request.index = (interface); \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbSetEndpointFeature(pid, fs, endpoint, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x02; \
  device_request.request = USB_REQUEST_SET_FEATURE; \
  device_request.value = (fs); \
  device_request.index = (endpoint); \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbSetInterface(pid, interface, alt_setting, cb, arg) ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x01; \
  device_request.request = USB_REQUEST_SET_INTERFACE; \
  device_request.value = (alt_setting); \
  device_request.index = (interface); \
  device_request.length = 0; \
  usbControlTransfer((pid), (&device_request), NULL, (cb), (arg)); })

#define usbSynchFrame(pid, endpoint, pfn, cb, arg)  ({ \
  usbDeviceRequest device_request; \
  device_request.requestType = 0x82; \
  device_request.request = USB_REQUEST_SYNCH_FRAME; \
  device_request.value = 0; \
  device_request.index = (endpoint); \
  device_request.length = 2; \
  usbControlTransfer((pid), (&device_request), pfn, (cb), (arg)); })


#endif /* __USB_H__ */

