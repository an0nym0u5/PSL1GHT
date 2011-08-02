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

static void printDeviceDesc ( s32 dev_id, void *p ) ;
static void printConfigDesc ( s32 dev_id, void *p ) ;
static void printInterfaceDesc ( s32 dev_id, void *p ) ;
static void printEndpointDesc ( s32 dev_id, void *p ) ;
static void printClassSpecificDesc ( s32 dev_id, u8 *desc ) ;

typedef struct
{
  u8 descriptorType;
  void ( *dumpDescriptor )( s32 dev_id, void* desc ) ;
} descriptorTable_t;

descriptorTable_t descriptorTable[] =
{
  { 0x01, printDeviceDesc },
  { 0x02, printConfigDesc },
  { 0x04, printInterfaceDesc },
  { 0x05, printEndpointDesc },
};

#define DESCRIPTOR_TABLE_SIZE ( sizeof ( descriptorTable )/sizeof ( descriptorTable_t ) )

static u32 module_flag ;

SYS_PROCESS_PARAM ( 1001, 0x10000 )

static void printDeviceDesc ( s32 dev_id, void *p )
{
  ( void ) dev_id;

  usbDeviceDescriptor *desc = ( usbDeviceDescriptor* )p;
 
  dbgprintf ( stdout, "DEVICE DESCRIPTOR" ) ;
  argprintf ( stdout, "  length:                 0x%02X ( %d )", desc->length, desc->length ) ;
  argprintf ( stdout, "  descriptorType:         0x%02X ( %d )", desc->descriptorType, desc->descriptorType ) ;
  argprintf ( stdout, "  bcdUSB:                 0x%04X", swap16 ( &desc->bcdUSB ) ) ;
  argprintf ( stdout, "  deviceClass:            0x%02X ( %d )", desc->deviceClass, desc->deviceClass ) ;
  argprintf ( stdout, "  deviceSubclass:         0x%02X ( %d )", desc->deviceSubclass, desc->deviceSubclass ) ;
  argprintf ( stdout, "  deviceProtocol:         0x%02X ( %d )", desc->deviceProtocol, desc->deviceProtocol ) ;
  argprintf ( stdout, "  maxPacketSize0:         0x%02X ( %d )", desc->maxPacketSize0, desc->maxPacketSize0 ) ;
  argprintf ( stdout, "  idVendor:               0x%04X", swap16 ( &desc->idVendor ) ) ;
  argprintf ( stdout, "  idProduct:              0x%04X", swap16 ( &desc->idProduct ) ) ;
  argprintf ( stdout, "  bcdDevice:              0x%04X", swap16 ( &desc->bcdDevice ) ) ;
  argprintf ( stdout, "  manufacturer:           0x%02X ( %d )", desc->manufacturer, desc->manufacturer ) ;
  argprintf ( stdout, "  product:                0x%02X ( %d )", desc->product, desc->product ) ;
  argprintf ( stdout, "  serialNumber:           0x%02X ( %d )", desc->serialNumber, desc->serialNumber ) ;
  argprintf ( stdout, "  numConfigurations:      0x%02X ( %d )", desc->numConfigurations, desc->numConfigurations ) ;
  fprintf ( stdout, "\n" ) ;
}

static void printConfigDesc ( s32 dev_id, void *p )
{
  ( void ) dev_id;

  usbConfigurationDescriptor *desc = ( usbConfigurationDescriptor* )p;
  u16 totalLength;
 
  dbgprintf ( stdout, "CONFIGURATION DESCRIPTOR" ) ;
  argprintf ( stdout, "  length:                 0x%02X ( %d )", desc->length, desc->length ) ;
  argprintf ( stdout, "  descriptorType:         0x%02X ( %d )", desc->descriptorType, desc->descriptorType ) ;
  totalLength = swap16 ( &desc->totalLength ) ;
  argprintf ( stdout, "  totalLength:            0x%04X ( %d )", totalLength,totalLength ) ;
  argprintf ( stdout, "  numInterfaces:          0x%02X ( %d )", desc->numInterfaces, desc->numInterfaces ) ;
  argprintf ( stdout, "  configurationValue:     0x%02X ( %d )", desc->configurationValue, desc->configurationValue ) ;
  argprintf ( stdout, "  configuration:          0x%02X ( %d )", desc->configuration, desc->configuration ) ;
  argprintf ( stdout, "  attribute:              0x%02X ( %d )", desc->attributes, desc->attributes ) ;
  argprintf ( stdout, "  maxPower:               0x%02X ( %d )", desc->maxPower, desc->maxPower ) ;
  fprintf ( stdout, "\n" ) ;
}

static void printInterfaceDesc ( s32 dev_id, void *p )
{
  ( void ) dev_id;

  usbInterfaceDescriptor *desc = ( usbInterfaceDescriptor* )p;
 
  dbgprintf ( stdout, "INTERFACE DESCRIPTOR" ) ;
  argprintf ( stdout, "  length:                 0x%02X ( %d )", desc->length, desc->length ) ;
  argprintf ( stdout, "  descriptorType:         0x%02X ( %d )", desc->descriptorType, desc->descriptorType ) ;
  argprintf ( stdout, "  interfaceNumber:        0x%02X ( %d )", desc->interfaceNumber, desc->interfaceNumber ) ;
  argprintf ( stdout, "  alternateSetting:       0x%02X ( %d )", desc->alternateSetting, desc->alternateSetting ) ;
  argprintf ( stdout, "  numEndpoints:           0x%02X ( %d )", desc->numEndpoints, desc->numEndpoints ) ;
  argprintf ( stdout, "  interfaceClass:         0x%02X ( %d )", desc->interfaceClass, desc->interfaceClass ) ;
  argprintf ( stdout, "  interfaceSubClass:      0x%02X ( %d )", desc->interfaceSubclass, desc->interfaceSubclass ) ;
  argprintf ( stdout, "  interfaceProtocol:      0x%02X ( %d )", desc->interfaceProtocol, desc->interfaceProtocol ) ;
  argprintf ( stdout, "  interface:              0x%02X ( %d )", desc->interface, desc->interface ) ;
  fprintf ( stdout, "\n" ) ;
}

static void printEndpointDesc ( s32 dev_id, void *p )
{
  ( void ) dev_id;

  usbEndpointDescriptor *desc = ( usbEndpointDescriptor* )p;
  char string[128];
	
  dbgprintf ( stdout, "ENDPOINT DESCRIPTOR" ) ;
  argprintf ( stdout, "  length:                 0x%02X ( %d )", desc->length, desc->length ) ;
  argprintf ( stdout, "  descriptorType:         0x%02X ( %d )", desc->descriptorType, desc->descriptorType ) ;
  if ( desc->endpointAddress & 0x80 )
  {
    sprintf ( string,"In" ) ;
  }
  else
  {
    sprintf ( string,"Out" ) ;
  }
  argprintf ( stdout, "  endpointAddress:        0x%02X ( %d ) [%s]", desc->endpointAddress, desc->endpointAddress,string ) ;
  switch ( desc->attributes & 0x03 )
  {
    case 0:
      sprintf ( string,"Control" ) ;
      break;
    case 1:
      sprintf ( string,"Isochronous" ) ;
      break;
    case 2:
      sprintf ( string,"Bulk" ) ;
      break;
    case 3:
      sprintf ( string,"Interrupt" ) ;
      break;
  }

  argprintf ( stdout, "  attribute:              0x%02X ( %d ) [%s]", desc->attributes, desc->attributes,string ) ;
  argprintf ( stdout, "  maxPacketSize:          0x%04X ( %d )", swap16 ( &desc->maxPacketSize ), swap16 ( &desc->maxPacketSize ) ) ;
  argprintf ( stdout, "  interval:               0x%02X ( %d )", desc->interval, desc->interval ) ;
  fprintf ( stdout, "\n" ) ;
}

static void printClassSpecificDesc ( s32 dev_id, u8 *desc )
{
  int i ;
  ( void ) dev_id;

  dbgprintf ( stdout, "CLASS-SPECIFIC DESCRIPTOR" ) ;
  argprintf ( stdout, "  length:                 0x%02X ( %d )", desc[0], desc[0] ) ;
  argprintf ( stdout, "  descriptorType:         0x%02X ( %d )", desc[1], desc[1] ) ;
  for ( i = 2; i < desc[0]; i++ )
  {
    argprintf ( stdout, "                          0x%02X ( %d )", desc[i], desc[i] ) ;
  }
  fprintf ( stdout, "\n" ) ;
}

static int probe ( int dev_id )
{
  u8* desc = 0;
  u32 i;

  argprintf ( stdout, "probe dev_id=%d", dev_id ) ;

  while ( 1 )
  {
    if ( ( desc = usbScanStaticDescriptor ( dev_id, desc, 0 ) ) == 0 )
    {
      break;
    }
    for ( i = 0; i < DESCRIPTOR_TABLE_SIZE; i++ )
    {
      if ( descriptorTable[i].descriptorType == desc[1] )
      {
        break;
      }
    }
    if ( i != DESCRIPTOR_TABLE_SIZE )
    {
      descriptorTable[i].dumpDescriptor ( dev_id, desc ) ;
    }
    else
    {
      printClassSpecificDesc ( dev_id, desc ) ;
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

