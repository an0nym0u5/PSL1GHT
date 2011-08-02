#line 1 "main.c"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/process.h>
#include <sys/types.h>

#include <ppu-asm.h>
#include <ppu_intrinsics.h>

#include <usb/usb.h>
#include <sysutil/sysutil.h> 
#include <sysmodule/sysmodule.h>

#include "pad.h"
#include "event.h"

#define swap16( x )   ( ( u16 ) ( __lhbrx ( x ) ) )
#define dbgprintf( stream,format ) fprintf ( stream, "\033[0;33m%s:%s ():#%d :: "format"\033[0m\n", __FILE__, __func__, __LINE__ ) ;
#define argprintf( stream,format,args... ) fprintf ( stream, "\033[0;33m%s:%s ():#%d :: "format"\033[0m\n", __FILE__, __func__, __LINE__, args ) ;

static int probe ( int dev_id ) ;
static int attach ( int dev_id ) ;
static int detach ( int dev_id ) ;

static void printDeviceDesc ( s32 dev_id, void *ptr ) ;
static void printConfigDesc ( s32 dev_id, void *ptr ) ;
static void printInterfaceDesc ( s32 dev_id, void *ptr ) ;
static void printEndpointDesc ( s32 dev_id, void *ptr ) ;
static void printClassSpecificDesc ( s32 dev_id, u8 *descriptor ) ;

typedef struct
{
  u8 descriptorType;
  void ( *dumpDescriptor )( s32 dev_id, void* descriptor ) ;
} descriptorTable_t;

descriptorTable_t descriptorTable[] =
{
  { 0x01, printDeviceDesc },
  { 0x02, printConfigDesc },
  { 0x04, printInterfaceDesc },
  { 0x05, printEndpointDesc },
};

static u32 module_flag ;

SYS_PROCESS_PARAM ( 1001, 0x10000 )

static void printDeviceDesc ( s32 dev_id, void *ptr )
{
  ( void ) dev_id;

  usbDeviceDescriptor *descriptor = ( usbDeviceDescriptor* )ptr ;
  enum usbDescriptorType descriptorType = descriptor->bDescriptorType ;
  enum usbClassCode deviceClassCode = descriptor->bDeviceClass ;
  char string[128];
 
  dbgprintf ( stdout, "DEVICE DESCRIPTOR" ) ;
  argprintf ( stdout, "  bLength:                0x%02X ( %d )", descriptor->bLength, descriptor->bLength ) ;

  switch ( descriptorType )
  {
    case DT_DEVICE:
      sprintf ( string, "Device" ) ;
      break ;
    case DT_CONFIG:
      sprintf ( string, "Configuration" ) ;
      break ;
    case DT_STRING:
      sprintf ( string, "String" ) ;
      break ;
    case DT_INTERFACE:
      sprintf ( string, "Interface" ) ;
      break ;
    case DT_ENDPOINT:
      sprintf ( string, "Endpoint" ) ;
      break ;
    case DT_HID:
      sprintf ( string, "HID" ) ;
      break ;
    case DT_REPORT:
      sprintf ( string, "Report" ) ;
      break ;
    case DT_PHYSICAL:
      sprintf ( string, "Physical" ) ;
      break ;
    case DT_HUB:
      sprintf ( string, "Hub" ) ;
      break ;
    default:
      sprintf ( string, "Unknown" ) ;
      break ;
  }
  argprintf ( stdout, "  bDescriptorType:        0x%02X ( %d ) [%s]", descriptor->bDescriptorType, descriptor->bDescriptorType, string ) ;

  argprintf ( stdout, "  bcdUSB:                 0x%04X", swap16 ( &descriptor->bcdUSB ) ) ;

  switch ( deviceClassCode )
  {
    case CLASS_PER_INTERFACE:
      sprintf ( string, "Per Interface" ) ;
      break ;
    case CLASS_AUDIO:
      sprintf ( string, "Audio" ) ;
      break ;
    case CLASS_COMM:
      sprintf ( string, "Communication" ) ;
      break ;
    case CLASS_HID:
      sprintf ( string, "HID" ) ;
      break ;
    case CLASS_MONITOR:
      sprintf ( string, "Monitor" ) ;
      break ;
    case CLASS_PHYSICAL:
      sprintf ( string, "Physical" ) ;
      break ;
    case CLASS_PTP:
      sprintf ( string, "Power" ) ;
      break ;
    case CLASS_PRINTER:
      sprintf ( string, "Printer" ) ;
      break ;
    case CLASS_STORAGE:
      sprintf ( string, "Mass Storage" ) ;
      break ;
    case CLASS_HUB:
      sprintf ( string, "Hub" ) ;
      break ;
    case CLASS_DATA:
      sprintf ( string, "Data" ) ;
      break ;
    case CLASS_APPLICATION:
      sprintf ( string, "Application" ) ;
      break ;
    case CLASS_VENDOR_SPEC:
      sprintf ( string, "Vendor Specific" ) ;
      break ;
    default:
      sprintf ( string, "Unknown" ) ;
      break ;
  }
  argprintf ( stdout, "  bDeviceClass:           0x%02X ( %d ) [%s]", descriptor->bDeviceClass, descriptor->bDeviceClass, string ) ;

  argprintf ( stdout, "  bDeviceSubClass:        0x%02X ( %d )", descriptor->bDeviceSubClass, descriptor->bDeviceSubClass ) ;
  argprintf ( stdout, "  bDeviceProtocol:        0x%02X ( %d )", descriptor->bDeviceProtocol, descriptor->bDeviceProtocol ) ;
  argprintf ( stdout, "  bMaxPacketSize0:        0x%02X ( %d )", descriptor->bMaxPacketSize0, descriptor->bMaxPacketSize0 ) ;
  argprintf ( stdout, "  idVendor:               0x%04X", swap16 ( &descriptor->idVendor ) ) ;
  argprintf ( stdout, "  idProduct:              0x%04X", swap16 ( &descriptor->idProduct ) ) ;
  argprintf ( stdout, "  bcdDevice:              0x%04X", swap16 ( &descriptor->bcdDevice ) ) ;
  argprintf ( stdout, "  iManufacturer:          0x%02X ( %d )", descriptor->iManufacturer, descriptor->iManufacturer ) ;
  argprintf ( stdout, "  iProduct:               0x%02X ( %d )", descriptor->iProduct, descriptor->iProduct ) ;
  argprintf ( stdout, "  iSerialNumber:          0x%02X ( %d )", descriptor->iSerialNumber, descriptor->iSerialNumber ) ;
  argprintf ( stdout, "  bNumConfigurations:     0x%02X ( %d )", descriptor->bNumConfigurations, descriptor->bNumConfigurations ) ;
  fprintf ( stdout, "\n" ) ;
}

static void printConfigDesc ( s32 dev_id, void *ptr )
{
  ( void ) dev_id;

  usbConfigurationDescriptor *descriptor = ( usbConfigurationDescriptor* )ptr ;
  enum usbDescriptorType descriptorType = descriptor->bDescriptorType ;
  char string[128];
 
  dbgprintf ( stdout, "CONFIGURATION DESCRIPTOR" ) ;
  argprintf ( stdout, "  bLength:                0x%02X ( %d )", descriptor->bLength, descriptor->bLength ) ;

  switch ( descriptorType )
  {
    case DT_DEVICE:
      sprintf ( string, "Device" ) ;
      break ;
    case DT_CONFIG:
      sprintf ( string, "Configuration" ) ;
      break ;
    case DT_STRING:
      sprintf ( string, "String" ) ;
      break ;
    case DT_INTERFACE:
      sprintf ( string, "Interface" ) ;
      break ;
    case DT_ENDPOINT:
      sprintf ( string, "Endpoint" ) ;
      break ;
    case DT_HID:
      sprintf ( string, "HID" ) ;
      break ;
    case DT_REPORT:
      sprintf ( string, "Report" ) ;
      break ;
    case DT_PHYSICAL:
      sprintf ( string, "Physical" ) ;
      break ;
    case DT_HUB:
      sprintf ( string, "Hub" ) ;
      break ;
    default:
      sprintf ( string, "Unknown" ) ;
      break ;
  }
  argprintf ( stdout, "  bDescriptorType:        0x%02X ( %d ) [%s]", descriptor->bDescriptorType, descriptor->bDescriptorType, string ) ;

  argprintf ( stdout, "  wTotalLength:           0x%04X ( %d )", swap16 ( &descriptor->wTotalLength ), swap16 ( &descriptor->wTotalLength ) ) ;
  argprintf ( stdout, "  bNumInterfaces:         0x%02X ( %d )", descriptor->bNumInterfaces, descriptor->bNumInterfaces ) ;
  argprintf ( stdout, "  bConfigurationValue:    0x%02X ( %d )", descriptor->bConfigurationValue, descriptor->bConfigurationValue ) ;
  argprintf ( stdout, "  iConfiguration:         0x%02X ( %d )", descriptor->iConfiguration, descriptor->iConfiguration ) ;
  argprintf ( stdout, "  bmAttributes:           0x%02X ( %d )", descriptor->bmAttributes, descriptor->bmAttributes ) ;
  argprintf ( stdout, "  MaxPower:               0x%02X ( %d )", descriptor->MaxPower, descriptor->MaxPower ) ;
  fprintf ( stdout, "\n" ) ;
}

static void printInterfaceDesc ( s32 dev_id, void *ptr )
{
  ( void ) dev_id;

  usbInterfaceDescriptor *descriptor = ( usbInterfaceDescriptor* )ptr ;
  enum usbDescriptorType descriptorType = descriptor->bDescriptorType ;
  char string[128] ;
 
  dbgprintf ( stdout, "INTERFACE DESCRIPTOR" ) ;
  argprintf ( stdout, "  bLength:                0x%02X ( %d )", descriptor->bLength, descriptor->bLength ) ;

  switch ( descriptorType )
  {
    case DT_DEVICE:
      sprintf ( string, "Device" ) ;
      break ;
    case DT_CONFIG:
      sprintf ( string, "Configuration" ) ;
      break ;
    case DT_STRING:
      sprintf ( string, "String" ) ;
      break ;
    case DT_INTERFACE:
      sprintf ( string, "Interface" ) ;
      break ;
    case DT_ENDPOINT:
      sprintf ( string, "Endpoint" ) ;
      break ;
    case DT_HID:
      sprintf ( string, "HID" ) ;
      break ;
    case DT_REPORT:
      sprintf ( string, "Report" ) ;
      break ;
    case DT_PHYSICAL:
      sprintf ( string, "Physical" ) ;
      break ;
    case DT_HUB:
      sprintf ( string, "Hub" ) ;
      break ;
    default:
      sprintf ( string, "Unknown" ) ;
      break ;
  }
  argprintf ( stdout, "  bDescriptorType:        0x%02X ( %d ) [%s]", descriptor->bDescriptorType, descriptor->bDescriptorType, string ) ;

  argprintf ( stdout, "  bInterfaceNumber:       0x%02X ( %d )", descriptor->bInterfaceNumber, descriptor->bInterfaceNumber ) ;
  argprintf ( stdout, "  bAlternateSetting:      0x%02X ( %d )", descriptor->bAlternateSetting, descriptor->bAlternateSetting ) ;
  argprintf ( stdout, "  bNumEndpoints:          0x%02X ( %d )", descriptor->bNumEndpoints, descriptor->bNumEndpoints ) ;
  argprintf ( stdout, "  bInterfaceClass:        0x%02X ( %d )", descriptor->bInterfaceClass, descriptor->bInterfaceClass ) ;
  argprintf ( stdout, "  bInterfaceSubClass:     0x%02X ( %d )", descriptor->bInterfaceSubClass, descriptor->bInterfaceSubClass ) ;
  argprintf ( stdout, "  bInterfaceProtocol:     0x%02X ( %d )", descriptor->bInterfaceProtocol, descriptor->bInterfaceProtocol ) ;
  argprintf ( stdout, "  iInterface:             0x%02X ( %d )", descriptor->iInterface, descriptor->iInterface ) ;
  fprintf ( stdout, "\n" ) ;
}

static void printEndpointDesc ( s32 dev_id, void *ptr )
{
  ( void ) dev_id;

  usbEndpointDescriptor *descriptor = ( usbEndpointDescriptor* )ptr ;
  enum usbDescriptorType descriptorType = descriptor->bDescriptorType ;
  enum usbEndpointDirection endpointAddressDirection = descriptor->bEndpointAddress ;
  enum usbTransferType attributesTransferType = descriptor->bmAttributes ;
  char string[128];
	
  dbgprintf ( stdout, "ENDPOINT DESCRIPTOR" ) ;
  argprintf ( stdout, "  length:                 0x%02X ( %d )", descriptor->bLength, descriptor->bLength ) ;

  switch ( descriptorType )
  {
    case DT_DEVICE:
      sprintf ( string, "Device" ) ;
      break ;
    case DT_CONFIG:
      sprintf ( string, "Configuration" ) ;
      break ;
    case DT_STRING:
      sprintf ( string, "String" ) ;
      break ;
    case DT_INTERFACE:
      sprintf ( string, "Interface" ) ;
      break ;
    case DT_ENDPOINT:
      sprintf ( string, "Endpoint" ) ;
      break ;
    case DT_HID:
      sprintf ( string, "HID" ) ;
      break ;
    case DT_REPORT:
      sprintf ( string, "Report" ) ;
      break ;
    case DT_PHYSICAL:
      sprintf ( string, "Physical" ) ;
      break ;
    case DT_HUB:
      sprintf ( string, "Hub" ) ;
      break ;
    default:
      sprintf ( string, "Unknown" ) ;
      break ;
  }
  argprintf ( stdout, "  bDescriptorType:        0x%02X ( %d ) [%s]", descriptor->bDescriptorType, descriptor->bDescriptorType, string ) ;

  switch ( endpointAddressDirection )
  {
    case ENDPOINT_IN:
      sprintf ( string,"In" ) ;
      break ;
    case ENDPOINT_OUT:
      sprintf ( string,"Out" ) ;
      break ;
    default:
      sprintf ( string, "Unknown" ) ;
      break ;
  }
  argprintf ( stdout, "  bEndpointAddress:       0x%02X ( %d ) [%s]", descriptor->bEndpointAddress, descriptor->bEndpointAddress, string ) ;

  switch ( attributesTransferType )
  {
    case TRANSFER_TYPE_CONTROL:
      sprintf ( string, "Control" ) ;
      break ;
    case TRANSFER_TYPE_ISOCHRONOUS:
      sprintf ( string, "Isochronous" ) ;
      break ;
    case TRANSFER_TYPE_BULK:
      sprintf ( string, "Bulk" ) ;
      break ;
    case TRANSFER_TYPE_INTERRUPT:
      sprintf ( string, "Interrupt" ) ;
      break ;
    default:
      sprintf ( string, "Unknown" ) ;
      break ;
  }
  argprintf ( stdout, "  attribute:              0x%02X ( %d ) [%s]", descriptor->bmAttributes, descriptor->bmAttributes, string ) ;

  argprintf ( stdout, "  wMaxPacketSize:         0x%04X ( %d )", swap16 ( &descriptor->wMaxPacketSize ), swap16 ( &descriptor->wMaxPacketSize ) ) ;
  argprintf ( stdout, "  interval:               0x%02X ( %d )", descriptor->bInterval, descriptor->bInterval ) ;
  fprintf ( stdout, "\n" ) ;
}

static void printClassSpecificDesc ( s32 dev_id, u8 *descriptor )
{
  int i ;
  ( void ) dev_id;
  enum usbDescriptorType descriptorType = descriptor[1] ;
  char string[128] ;

  dbgprintf ( stdout, "CLASS-SPECIFIC DESCRIPTOR" ) ;
  argprintf ( stdout, "  length:                 0x%02X ( %d )", descriptor[0], descriptor[0] ) ;

  switch ( descriptorType )
  {
    case DT_DEVICE:
      sprintf ( string, "Device" ) ;
      break ;
    case DT_CONFIG:
      sprintf ( string, "Configuration" ) ;
      break ;
    case DT_STRING:
      sprintf ( string, "String" ) ;
      break ;
    case DT_INTERFACE:
      sprintf ( string, "Interface" ) ;
      break ;
    case DT_ENDPOINT:
      sprintf ( string, "Endpoint" ) ;
      break ;
    case DT_HID:
      sprintf ( string, "HID" ) ;
      break ;
    case DT_REPORT:
      sprintf ( string, "Report" ) ;
      break ;
    case DT_PHYSICAL:
      sprintf ( string, "Physical" ) ;
      break ;
    case DT_HUB:
      sprintf ( string, "Hub" ) ;
      break ;
    default:
      sprintf ( string, "Unknown" ) ;
      break ;
  }
  argprintf ( stdout, "  bDescriptorType:        0x%02X ( %d ) [%s]", descriptor[1], descriptor[1], string ) ;

  for ( i = 2; i < descriptor[0]; i++ )
  {
    argprintf ( stdout, "                          0x%02X ( %d )", descriptor[i], descriptor[i] ) ;
  }
  fprintf ( stdout, "\n" ) ;
}

static int probe ( int dev_id )
{
  u8* descriptor = 0;
  u32 i;

  argprintf ( stdout, "probe dev_id=%d", dev_id ) ;

  while ( 1 )
  {
    if ( ( descriptor = usbScanStaticDescriptor ( dev_id, descriptor, 0 ) ) == 0 )
    {
      break;
    }
    for ( i = 0; i < ( sizeof ( descriptorTable ) / sizeof ( descriptorTable_t ) ); i++ )
    {
      if ( descriptorTable[i].descriptorType == descriptor[1] )
      {
        break;
      }
    }
    if ( i != ( sizeof ( descriptorTable ) / sizeof ( descriptorTable_t ) ) )
    {
      descriptorTable[i].dumpDescriptor ( dev_id, descriptor ) ;
    }
    else
    {
      printClassSpecificDesc ( dev_id, descriptor ) ;
    }
  }

  return USB_PROBE_SUCCEEDED;
}

static int attach ( int dev_id )
{
  argprintf ( stdout, "attach dev_id=%d", dev_id ) ;

  return USB_ATTACH_SUCCEEDED;
}

static int detach ( int dev_id )
{
  argprintf ( stdout, "detach dev_id=%d", dev_id ) ;

  return USB_DETACH_SUCCEEDED;
}

/* load sysmodule if not loaded */
void
sysmoduleLoad ( int flag, sysModuleId id )
{
  static int ret ;

  if ( ( ret = sysModuleIsLoaded ( id ) ) != SYSMODULE_OK )
  {
    if ( ( ret = sysModuleLoad ( id ) ) != SYSMODULE_OK )
    {
      argprintf ( stderr, "ERROR: cannot load flag: %d, id:%x, ret:%x", flag, id, ret ) ;
      exit ( EXIT_FAILURE ) ;
    }
    module_flag |= flag ;
  }
  else
  {
    argprintf ( stderr, "ERROR: (%x)", ret ) ;
  }
}

/* unload sysmodule if loaded */
void
sysmoduleUnload ( int flag, sysModuleId id )
{
  static int ret ;

  if ( module_flag & flag )
  {
    if ( ( ret = sysModuleIsLoaded ( id ) ) == SYSMODULE_OK )
    {
      if ( ( ret = sysModuleUnload ( id ) ) != SYSMODULE_OK )
      {
        argprintf ( stdout, "ERROR: cannot unload flag: %d, id:%x, ret:%x", flag, id, ret ) ;
      }
    }
    else
    {
      argprintf ( stderr, "ERROR: (%x)", ret ) ;
    }
  }
}

int main ( void )
{
  static int ret;

  static usbLddOps ldd_ops =
  {
    "desc",
    probe,
    attach,
    detach
  };

  /* data structs */
  eventData evt_data ;
  padBtnData pad_data ;

  dbgprintf ( stdout, "main initializing" ) ;

  /* register eventHandler */
  eventInitialization ( &evt_data ) ;

  /* initialize controller io */
  padInitialization ( &pad_data ) ;

  /* pointer to exitapp */
  pad_data.exitapp = &evt_data.exitapp;

  sysmoduleLoad ( 1, SYSMODULE_USB ) ;

  if ( ( ret = usbInit () ) != USB_OK )
  {
    argprintf ( stderr, "### ERROR ### (%x)", ret ) ;
    goto exit ;
  }

  if ( ( ret = usbSetThreadPriority2 ( 500, 501, 502 ) ) != USB_OK )
  {
    argprintf ( stderr, "### ERROR ### (%x)", ret ) ;
    goto exit ;
  }

  //argprintf ( stdout, "usbRegisterLdd(%p) = probe=%p, attach=%p, detach=%p", &ldd_ops, ldd_ops.probe, ldd_ops.attach, ldd_ops.detach ) ;
  if ( ( ret = usbRegisterLdd ( &ldd_ops ) ) != USB_OK )
  {
    switch ( ret )
    {
      case USB_ERR_NOT_INITIALIZED: /* 80110001 */
        argprintf ( stderr, "ERROR: usb library not initialized (0x%x)", ret ) ;
        goto exit ;
      case USB_ERR_INVALID_PARAM: /* 80110004 */
        argprintf ( stderr, "ERROR: invalid parameter (0x%x)", ret ) ;
        goto exit ;
      case USB_ERR_LDD_ALREADY_REGISTERED: /* 80110006 */
        argprintf ( stderr, "ERROR: ldd already registered (0x%x)", ret ) ;
        goto exit ;
      case USB_ERR_LDD_NOT_ALLOCATED: /* 80110007 */
        argprintf ( stderr, "ERROR: ldd not allocated (0x%x)", ret ) ;
        goto exit ;
      case USB_ERR_FATAL: /* 801100ff */
        argprintf ( stderr, "ERROR: fatal error (0x%x)", ret ) ;
        goto exit ;
      default:
        argprintf ( stderr, "UNKNOWN: (0x%x)", ret ) ;
        break;
    }
  }
  else
  {
    dbgprintf ( stdout, "logical device driver registered" ) ;
  }

  while ( evt_data.exitapp )
  {
    /* check for controller input */
    padCheckState ( &pad_data ) ;

    /* check if XMB open or quit via XMB */
    sysUtilCheckCallback () ;

    sleep ( 1 ) ;
  }

exit:
  if ( ( ret = usbUnregisterLdd ( &ldd_ops ) ) != USB_OK )
  {
    switch ( ret )
    {
      case USB_ERR_NOT_INITIALIZED: /* 80110001 */
        argprintf ( stderr, "ERROR: usb library not initialized (0x%x)", ret ) ;
        break ;
      case USB_ERR_INVALID_PARAM: /* 80110004 */
        argprintf ( stderr, "ERROR: invalid parameter (0x%x)", ret ) ;
        break ;
      case USB_ERR_LDD_NOT_FOUND: /* 80110009 */
        argprintf ( stderr, "ERROR: ldd not found (0x%x)", ret ) ;
        break ;
      default:
        argprintf ( stderr, "UNKNOWN: (0x%x)", ret ) ;
        break ;
    }
  }

  if ( ( ret = usbEnd () ) != USB_OK )
  {
    switch ( ret )
    {
      case USB_ERR_NOT_INITIALIZED: /* 80110001 */
        argprintf ( stderr, "ERROR: usb library not initialized (0x%x)", ret ) ;
        break ;
      default:
        argprintf ( stderr, "UNKNOWN: (0x%x)", ret ) ;
        break ;
    }
  }

  sysmoduleUnload ( 1, SYSMODULE_USB ) ;

  dbgprintf ( stdout, "exiting" ) ;

  return 0;
}

