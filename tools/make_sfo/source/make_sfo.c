#line 1 "make_sfo.c"
/*
 * make_sfo.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 * gcc -g -O make_sfo.c -lm -o make_sfo
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <errno.h>
#include <getopt.h>

#include <inttypes.h>
#include <sys/types.h>

#include "common.h"
#include "structs.h"

#include "xml_parse_lib/xml_parse_lib.c"


static void
version ()
{
  fprintf ( stdout, "%s %s\n", MAKE_SFO_TITLE, MAKE_SFO_VERSION ) ;
}

static void
usage (const char *prog )
{
  fprintf ( stderr, "Usage:\n\t%s [OPTIONS]... --fromxml [PARAM.XML] [PARAM.SFO]\n\n", prog ) ;
  fprintf ( stderr, "\n  -h, --help\twhat you are reading now\n" ) ;
  fprintf ( stderr, "  -v, --verbose\tdisplay entries table\n" ) ;
  fprintf ( stderr, "  -s, --silent\tminimal output\n" ) ;
/*
  fprintf ( stderr, "  -t, --toxml\tdest xml file\n" ) ;
*/
  fprintf ( stderr, "  -t, --title\toverride TITLE\n" ) ;
  fprintf ( stderr, "  -a, --appid\toverride TITLE_ID\n" ) ;
  fprintf ( stderr, "  -f, --fromxml\tsource xml file\n" ) ;
  fprintf ( stderr, "\n\tlast argument must be path to PARAM.SFO being created.\n" ) ;

  fprintf ( stderr, "\nExample:\n" ) ;
  fprintf ( stderr, "\n\t%s --title some_title --appid some_title_id --fromxml sfo.xml PARAM.SFO\n", prog ) ;
}

static void
error ()
{
  fprintf ( stderr, "FATAL ERROR: exiting..." ) ;
  exit ( EXIT_FAILURE ) ;
}

void
initHeader ( paramSFO *paramsfo )
{
  paramsfo->header.sfo_magic =     ntohl ( HDR_SFO_MAGIC ) ;
  paramsfo->header.sfo_version =   ntohl ( HDR_SFO_VERSION ) ;
  paramsfo->header.keys_offset =   ntohl ( HDR_KEYS_OFFSET ) ;
  paramsfo->header.values_offset = ntohl ( HDR_VALUES_OFFSET ) ;
  paramsfo->header.entries_count = ntohl ( HDR_ENTRIES_COUNT ) ;
}

void
initEntries ( paramSFO *paramsfo )
{
  paramsfo->entry_count = 0 ;
  paramsfo->entries_pos = ENTRY_OFFSET ;
  paramsfo->entries = calloc ( paramsfo->header.entries_count, sizeof ( paramEntry ) ) ;
  CHECK_ERRNO( paramsfo->entries, "paramsfo->entries" ) ;
}

void
initKeys ( paramSFO *paramsfo )
{
  paramsfo->keys_pos = 0 ;

  paramsfo->keys.app_ver = malloc ( KEY_APP_VER_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.app_ver, "paramsfo->keys.app_ver" ) ;
  memset ( paramsfo->keys.app_ver, 0x00, sizeof ( KEY_APP_VER_LEN ) ) ;

  paramsfo->keys.attribute = malloc ( KEY_ATTRIBUTE_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.attribute, "paramsfo->keys.attribute" ) ;
  memset ( paramsfo->keys.attribute, 0x00, sizeof ( KEY_ATTRIBUTE_LEN ) ) ;

  paramsfo->keys.bootable = malloc ( KEY_BOOTABLE_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.bootable, "paramsfo->keys.bootable" ) ;
  memset ( paramsfo->keys.bootable, 0x00, sizeof ( KEY_BOOTABLE_LEN ) ) ;

  paramsfo->keys.category = malloc ( KEY_CATEGORY_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.category, "paramsfo->keys.category" ) ;
  memset ( paramsfo->keys.category, 0x00, sizeof ( KEY_CATEGORY_LEN ) ) ;

  paramsfo->keys.license = malloc ( KEY_LICENSE_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.license, "paramsfo->keys.license" ) ;
  memset ( paramsfo->keys.license, 0x00, sizeof ( KEY_LICENSE_LEN ) ) ;

  paramsfo->keys.parental_level = malloc ( KEY_PARENTAL_LEVEL_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.parental_level, "paramsfo->keys.parental_level" ) ;
  memset ( paramsfo->keys.parental_level, 0x00, sizeof ( KEY_PARENTAL_LEVEL_LEN ) ) ;

  paramsfo->keys.parental_level_a = malloc ( KEY_PARENTAL_LEVEL_A_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.parental_level_a, "paramsfo->keys.parental_level" ) ;
  memset ( paramsfo->keys.parental_level_a, 0x00, sizeof ( KEY_PARENTAL_LEVEL_A_LEN ) ) ;

  paramsfo->keys.parental_level_c = malloc ( KEY_PARENTAL_LEVEL_C_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.parental_level_c, "paramsfo->keys.parental_level" ) ;
  memset ( paramsfo->keys.parental_level_c, 0x00, sizeof ( KEY_PARENTAL_LEVEL_C_LEN ) ) ;

  paramsfo->keys.parental_level_e = malloc ( KEY_PARENTAL_LEVEL_E_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.parental_level_e, "paramsfo->keys.parental_level" ) ;
  memset ( paramsfo->keys.parental_level_e, 0x00, sizeof ( KEY_PARENTAL_LEVEL_E_LEN ) ) ;

  paramsfo->keys.parental_level_h = malloc ( KEY_PARENTAL_LEVEL_H_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.parental_level_h, "paramsfo->keys.parental_level" ) ;
  memset ( paramsfo->keys.parental_level_h, 0x00, sizeof ( KEY_PARENTAL_LEVEL_H_LEN ) ) ;

  paramsfo->keys.parental_level_j = malloc ( KEY_PARENTAL_LEVEL_J_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.parental_level_j, "paramsfo->keys.parental_level" ) ;
  memset ( paramsfo->keys.parental_level_j, 0x00, sizeof ( KEY_PARENTAL_LEVEL_J_LEN ) ) ;

  paramsfo->keys.parental_level_k = malloc ( KEY_PARENTAL_LEVEL_K_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.parental_level_k, "paramsfo->keys.parental_level" ) ;
  memset ( paramsfo->keys.parental_level_k, 0x00, sizeof ( KEY_PARENTAL_LEVEL_K_LEN ) ) ;

  paramsfo->keys.ps3_system_ver = malloc ( KEY_PS3_SYSTEM_VER_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.ps3_system_ver, "paramsfo->keys.ps3_system_ver" ) ;
  memset ( paramsfo->keys.ps3_system_ver, 0x00, sizeof ( KEY_PS3_SYSTEM_VER_LEN ) ) ;

  paramsfo->keys.region_deny = malloc ( KEY_REGION_DENY_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.region_deny, "paramsfo->keys.region_deny" ) ;
  memset ( paramsfo->keys.region_deny, 0x00, sizeof ( KEY_REGION_DENY_LEN ) ) ;

  paramsfo->keys.resolution = malloc ( KEY_RESOLUTION_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.resolution, "paramsfo->keys.resolution" ) ;
  memset ( paramsfo->keys.resolution, 0x00, sizeof ( KEY_RESOLUTION_LEN ) ) ;

  paramsfo->keys.sound_format = malloc ( KEY_SOUND_FORMAT_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.sound_format, "paramsfo->keys.sound_format" ) ;
  memset ( paramsfo->keys.sound_format, 0x00, sizeof ( KEY_SOUND_FORMAT_LEN ) ) ;

  paramsfo->keys.title = malloc ( KEY_TITLE_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.title, "paramsfo->keys.title" ) ;
  memset ( paramsfo->keys.title, 0x00, sizeof ( KEY_TITLE_LEN ) ) ;

  paramsfo->keys.title_id = malloc ( KEY_TITLE_ID_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.title_id, "paramsfo->keys.title_id" ) ;
  memset ( paramsfo->keys.title_id, 0x00, sizeof ( KEY_TITLE_ID_LEN ) ) ;

  paramsfo->keys.version = malloc ( KEY_VERSION_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.version, "paramsfo->keys.version" ) ;
  memset ( paramsfo->keys.version, 0x00, sizeof ( KEY_VERSION_LEN ) ) ;

  paramsfo->keys.padding = malloc ( KEY_PADDING_LEN ) ;
  CHECK_ERRNO( paramsfo->keys.padding, "paramsfo->keys.padding" ) ;
  memset ( paramsfo->keys.padding, 0x00, sizeof ( KEY_PADDING_LEN ) ) ;
}

void
initValues ( paramSFO *paramsfo )
{
  paramsfo->values_pos = 0 ;

  paramsfo->values.app_ver = malloc ( VALUE_APP_VER_MAX ) ;
  CHECK_ERRNO( paramsfo->values.app_ver, "paramsfo->values.app_ver" ) ;
  memset ( paramsfo->values.app_ver, 0x00, sizeof ( VALUE_APP_VER_MAX ) ) ;

  paramsfo->values.attribute = 0 ;

  paramsfo->values.bootable = 0 ;

  paramsfo->values.category = malloc ( VALUE_CATEGORY_MAX ) ;
  CHECK_ERRNO( paramsfo->values.category, "paramsfo->values.category" ) ;
  memset ( paramsfo->values.category, 0x00, sizeof ( VALUE_CATEGORY_MAX ) ) ;

  paramsfo->values.license = malloc ( VALUE_LICENSE_MAX ) ;
  CHECK_ERRNO( paramsfo->values.license, "paramsfo->values.license" ) ;
  memset ( paramsfo->values.license, 0x00, sizeof ( VALUE_LICENSE_MAX ) ) ;

  paramsfo->values.parental_level = 0 ;
  paramsfo->values.parental_level_a = 0 ;
  paramsfo->values.parental_level_c = 0 ;
  paramsfo->values.parental_level_e = 0 ;
  paramsfo->values.parental_level_h = 0 ;
  paramsfo->values.parental_level_j = 0 ;
  paramsfo->values.parental_level_k = 0 ;

  paramsfo->values.ps3_system_ver = malloc ( VALUE_PS3_SYSTEM_VER_MAX ) ;
  CHECK_ERRNO( paramsfo->values.ps3_system_ver, "paramsfo->values.ps3_system_ver" ) ;
  memset ( paramsfo->values.ps3_system_ver, 0x00, sizeof ( VALUE_PS3_SYSTEM_VER_MAX ) ) ;

  paramsfo->values.region_deny = 0 ;

  paramsfo->values.resolution = 0 ;

  paramsfo->values.sound_format = 0 ;

  paramsfo->values.title = malloc ( VALUE_TITLE_MAX ) ;
  CHECK_ERRNO( paramsfo->values.title, "paramsfo->values.title" ) ;
  memset ( paramsfo->values.title, 0x00, sizeof ( VALUE_TITLE_MAX ) ) ;

  paramsfo->values.title_id = malloc ( VALUE_TITLE_ID_MAX ) ;
  CHECK_ERRNO( paramsfo->values.title_id, "paramsfo->values.title_id" ) ;
  memset ( paramsfo->values.title_id, 0x00, sizeof ( VALUE_TITLE_ID_MAX ) ) ;

  paramsfo->values.version = malloc ( VALUE_VERSION_MAX ) ;
  CHECK_ERRNO( paramsfo->values.version, "paramsfo->values.version" ) ;
  memset ( paramsfo->values.version, 0x00, sizeof ( VALUE_VERSION_MAX ) ) ;
}

static void
freeMemory ( paramSFO *paramsfo )
{
  free ( paramsfo->entries ) ;

  free ( paramsfo->keys.app_ver ) ;
  free ( paramsfo->keys.attribute ) ;
  free ( paramsfo->keys.bootable ) ;
  free ( paramsfo->keys.category ) ;
  free ( paramsfo->keys.license ) ;
  free ( paramsfo->keys.parental_level ) ;
  free ( paramsfo->keys.parental_level_a ) ;
  free ( paramsfo->keys.parental_level_c ) ;
  free ( paramsfo->keys.parental_level_e ) ;
  free ( paramsfo->keys.parental_level_h ) ;
  free ( paramsfo->keys.parental_level_j ) ;
  free ( paramsfo->keys.parental_level_k ) ;
  free ( paramsfo->keys.ps3_system_ver ) ;
  free ( paramsfo->keys.region_deny ) ;
  free ( paramsfo->keys.resolution ) ;
  free ( paramsfo->keys.sound_format ) ;
  free ( paramsfo->keys.title ) ;
  free ( paramsfo->keys.title_id ) ;
  free ( paramsfo->keys.version ) ;
  free ( paramsfo->keys.padding ) ;

  free ( paramsfo->values.app_ver ) ;
  free ( paramsfo->values.category ) ;
  free ( paramsfo->values.license ) ;
  free ( paramsfo->values.ps3_system_ver ) ;
  free ( paramsfo->values.title ) ;
  free ( paramsfo->values.title_id ) ;
  free ( paramsfo->values.version ) ;
}

static void
setEntry ( int id, paramSFO *paramsfo )
{
  paramsfo->entries[paramsfo->entry_count].key_offset =   (uint16_t)paramsfo->keys_pos ;
  paramsfo->entries[paramsfo->entry_count].unk1 =         (uint8_t)ENTRY_UNK1 ;
  paramsfo->entries[paramsfo->entry_count].value_offset = (uint32_t)paramsfo->values_pos ;

  switch ( id )
  {
    case ENTRY_APP_VER:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE2 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_APP_VER_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_APP_VER_MAX ;

      paramsfo->keys_pos += KEY_APP_VER_LEN ;
      paramsfo->values_pos += VALUE_APP_VER_MAX ;
      break ;

    case ENTRY_ATTRIBUTE:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_ATTRIBUTE_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_ATTRIBUTE_MAX ;

      paramsfo->keys_pos += KEY_ATTRIBUTE_LEN ;
      paramsfo->values_pos += VALUE_ATTRIBUTE_MAX ;
      break ;

    case ENTRY_BOOTABLE:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_BOOTABLE_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_BOOTABLE_MAX ;

      paramsfo->keys_pos += KEY_BOOTABLE_LEN ;
      paramsfo->values_pos += VALUE_BOOTABLE_MAX ;
      break ;

    case ENTRY_CATEGORY:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE2 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_CATEGORY_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_CATEGORY_MAX ;

      paramsfo->keys_pos += KEY_CATEGORY_LEN ;
      paramsfo->values_pos += VALUE_CATEGORY_MAX ;
      break ;

    case ENTRY_LICENSE:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE2 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_LICENSE_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_LICENSE_MAX ;

      paramsfo->keys_pos += KEY_LICENSE_LEN ;
      paramsfo->values_pos += VALUE_LICENSE_MAX ;
      break ;

    case ENTRY_PARENTAL_LEVEL:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_PARENTAL_LEVEL_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_PARENTAL_LEVEL_MAX ;

      paramsfo->keys_pos += KEY_PARENTAL_LEVEL_LEN ;
      paramsfo->values_pos += VALUE_PARENTAL_LEVEL_MAX ;
      break ;

    case ENTRY_PARENTAL_LEVEL_A:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_PARENTAL_LEVEL_A_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_PARENTAL_LEVEL_A_MAX ;

      paramsfo->keys_pos += KEY_PARENTAL_LEVEL_A_LEN ;
      paramsfo->values_pos += VALUE_PARENTAL_LEVEL_A_MAX ;
      break ;

    case ENTRY_PARENTAL_LEVEL_C:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_PARENTAL_LEVEL_C_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_PARENTAL_LEVEL_C_MAX ;

      paramsfo->keys_pos += KEY_PARENTAL_LEVEL_C_LEN ;
      paramsfo->values_pos += VALUE_PARENTAL_LEVEL_C_MAX ;
      break ;

    case ENTRY_PARENTAL_LEVEL_E:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_PARENTAL_LEVEL_E_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_PARENTAL_LEVEL_E_MAX ;

      paramsfo->keys_pos += KEY_PARENTAL_LEVEL_E_LEN ;
      paramsfo->values_pos += VALUE_PARENTAL_LEVEL_E_MAX ;
      break ;

    case ENTRY_PARENTAL_LEVEL_H:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_PARENTAL_LEVEL_H_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_PARENTAL_LEVEL_H_MAX ;

      paramsfo->keys_pos += KEY_PARENTAL_LEVEL_H_LEN ;
      paramsfo->values_pos += VALUE_PARENTAL_LEVEL_H_MAX ;
      break ;

    case ENTRY_PARENTAL_LEVEL_J:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_PARENTAL_LEVEL_J_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_PARENTAL_LEVEL_J_MAX ;

      paramsfo->keys_pos += KEY_PARENTAL_LEVEL_J_LEN ;
      paramsfo->values_pos += VALUE_PARENTAL_LEVEL_J_MAX ;
      break ;

    case ENTRY_PARENTAL_LEVEL_K:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_PARENTAL_LEVEL_K_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_PARENTAL_LEVEL_K_MAX ;

      paramsfo->keys_pos += KEY_PARENTAL_LEVEL_K_LEN ;
      paramsfo->values_pos += VALUE_PARENTAL_LEVEL_K_MAX ;
      break ;

    case ENTRY_PS3_SYSTEM_VER:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE2 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_PS3_SYSTEM_VER_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_PS3_SYSTEM_VER_MAX ;

      paramsfo->keys_pos += KEY_PS3_SYSTEM_VER_LEN ;
      paramsfo->values_pos += VALUE_PS3_SYSTEM_VER_MAX ;
      break ;

    case ENTRY_REGION_DENY:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE2 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_REGION_DENY_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_REGION_DENY_MAX ;

      paramsfo->keys_pos += KEY_REGION_DENY_LEN ;
      paramsfo->values_pos += VALUE_REGION_DENY_MAX ;
      break ;

    case ENTRY_RESOLUTION:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_RESOLUTION_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_RESOLUTION_MAX ;

      paramsfo->keys_pos += KEY_RESOLUTION_LEN ;
      paramsfo->values_pos += VALUE_RESOLUTION_MAX ;
      break ;

    case ENTRY_SOUND_FORMAT:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE4 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_SOUND_FORMAT_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_SOUND_FORMAT_MAX ;

      paramsfo->keys_pos += KEY_SOUND_FORMAT_LEN ;
      paramsfo->values_pos += VALUE_SOUND_FORMAT_MAX ;
      break ;

    case ENTRY_TITLE:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE2 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_TITLE_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_TITLE_MAX ;

      paramsfo->keys_pos += KEY_TITLE_LEN ;
      paramsfo->values_pos += VALUE_TITLE_MAX ;
      break ;

    case ENTRY_TITLE_ID:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE2 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_TITLE_ID_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_TITLE_ID_MAX ;

      paramsfo->keys_pos += KEY_TITLE_ID_LEN ;
      paramsfo->values_pos += VALUE_TITLE_ID_MAX ;
      break ;

    case ENTRY_VERSION:
      paramsfo->entries[paramsfo->entry_count].value_type =   (uint8_t)ENTRY_TYPE2 ;
      paramsfo->entries[paramsfo->entry_count].value_len =    (uint32_t)VALUE_VERSION_LEN ;
      paramsfo->entries[paramsfo->entry_count].value_max =    (uint32_t)VALUE_VERSION_MAX ;

      paramsfo->keys_pos += KEY_VERSION_LEN ;
      paramsfo->values_pos += VALUE_VERSION_MAX ;
      break ;

    default:
      fprintf ( stderr, "ERROR: unknown entry [%d]", id ) ;
      break ;
  }

  paramsfo->entry_count++ ;
  paramsfo->entries_pos += ENTRY_LEN ;
}

static void
setEntries ( paramSFO *paramsfo )
{
  if ( strncmp ( (const char*)paramsfo->keys.app_ver , "\0", 1 ) )
  {
    setEntry ( ENTRY_APP_VER, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.attribute , "\0", 1 ) )
  {
    setEntry ( ENTRY_ATTRIBUTE, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.bootable , "\0", 1 ) )
  {
    setEntry ( ENTRY_BOOTABLE, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.category , "\0", 1 ) )
  {
    setEntry ( ENTRY_CATEGORY, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.license , "\0", 1 ) )
  {
    setEntry ( ENTRY_LICENSE, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.parental_level , "\0", 1 ) )
  {
    setEntry ( ENTRY_PARENTAL_LEVEL, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.parental_level_a , "\0", 1 ) )
  {
    setEntry ( ENTRY_PARENTAL_LEVEL_A, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.parental_level_c , "\0", 1 ) )
  {
    setEntry ( ENTRY_PARENTAL_LEVEL_C, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.parental_level_e , "\0", 1 ) )
  {
    setEntry ( ENTRY_PARENTAL_LEVEL_E, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.parental_level_h , "\0", 1 ) )
  {
    setEntry ( ENTRY_PARENTAL_LEVEL_H, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.parental_level_j , "\0", 1 ) )
  {
    setEntry ( ENTRY_PARENTAL_LEVEL_J, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.parental_level_k , "\0", 1 ) )
  {
    setEntry ( ENTRY_PARENTAL_LEVEL_K, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.ps3_system_ver , "\0", 1 ) )
  {
    setEntry ( ENTRY_PS3_SYSTEM_VER, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.region_deny , "\0", 1 ) )
  {
    setEntry ( ENTRY_REGION_DENY, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.resolution , "\0", 1 ) )
  {
    setEntry ( ENTRY_RESOLUTION, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.sound_format , "\0", 1 ) )
  {
    setEntry ( ENTRY_SOUND_FORMAT, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.title , "\0", 1 ) )
  {
    setEntry ( ENTRY_TITLE, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.title_id , "\0", 1 ) )
  {
    setEntry ( ENTRY_TITLE_ID, paramsfo ) ;
  }

  if ( strncmp ( (const char*)paramsfo->keys.version , "\0", 1 ) )
  {
    setEntry ( ENTRY_VERSION, paramsfo ) ;
  }
}

static void
setKeyValue ( char key[STR_MAX], char type[STR_MAX], char value[STR_MAX], paramSFO *paramsfo ) 
{
  if ( !strncmp ( type, "string", 6 ) || !strncmp ( type, "String", 6 ) )
  {
    if ( !strncmp( key, KEY_APP_VER, KEY_APP_VER_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.app_ver, key, strlen ( key ) ) ; 
      strncpy ( (char*)paramsfo->values.app_ver, value, strlen ( value ) ) ;
    }
    else if ( !strncmp( key, KEY_CATEGORY, KEY_CATEGORY_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.category, key, strlen ( key ) ) ; 
      strncpy ( (char*)paramsfo->values.category, value, strlen ( value ) ) ;
    }
    else if ( !strncmp( key, KEY_LICENSE, KEY_LICENSE_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.license, key, strlen ( key ) ) ; 
      strncpy ( (char*)paramsfo->values.license, value, strlen ( value ) ) ;
    }
    else if ( !strncmp( key, KEY_PS3_SYSTEM_VER, KEY_PS3_SYSTEM_VER_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.ps3_system_ver, key, strlen ( key ) ) ; 
      strncpy ( (char*)paramsfo->values.ps3_system_ver, value, strlen ( value ) ) ;
    }
    else if ( !strncmp( key, KEY_TITLE, KEY_TITLE_LEN ) )
    {
      strncpy ( (char*)paramsfo->keys.title, key, strlen ( key ) ) ;
      strncpy ( (char*)paramsfo->values.title, value, strlen ( value ) ) ;
    }
    else if ( !strncmp( key, KEY_TITLE_ID, KEY_TITLE_ID_LEN ) )
    {
      strncpy ( (char*)paramsfo->keys.title_id, key, strlen ( key ) ) ;
      strncpy ( (char*)paramsfo->values.title_id, value, strlen ( value ) ) ;
    }
    else if ( !strncmp( key, KEY_VERSION, KEY_VERSION_LEN ) )
    {
      strncpy ( (char*)paramsfo->keys.version, key, strlen ( key ) ) ;
      strncpy ( (char*)paramsfo->values.version, value, strlen ( value ) ) ;
    }
    else
    {
      fprintf ( stderr, "ERROR: Unknown string key %s\n", key ) ; 
    }
  }
  else if ( !strncmp ( type, "integer", 7 ) || !strncmp ( type, "Integer", 7 ) )
  {
    if ( !strncmp( key, KEY_ATTRIBUTE, KEY_ATTRIBUTE_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.attribute, key, strlen ( key ) ) ; 
      paramsfo->values.attribute = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_BOOTABLE, KEY_BOOTABLE_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.bootable, key, strlen ( key ) ) ; 
      paramsfo->values.bootable = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_PARENTAL_LEVEL, KEY_PARENTAL_LEVEL_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.parental_level, key, strlen ( key ) ) ; 
      paramsfo->values.parental_level = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_PARENTAL_LEVEL_A, KEY_PARENTAL_LEVEL_A_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.parental_level_a, key, strlen ( key ) ) ; 
      paramsfo->values.parental_level_a = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_PARENTAL_LEVEL_C, KEY_PARENTAL_LEVEL_C_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.parental_level_c, key, strlen ( key ) ) ; 
      paramsfo->values.parental_level_c = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_PARENTAL_LEVEL_E, KEY_PARENTAL_LEVEL_E_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.parental_level_e, key, strlen ( key ) ) ; 
      paramsfo->values.parental_level_e = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_PARENTAL_LEVEL_H, KEY_PARENTAL_LEVEL_H_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.parental_level_h, key, strlen ( key ) ) ; 
      paramsfo->values.parental_level_h = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_PARENTAL_LEVEL_J, KEY_PARENTAL_LEVEL_J_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.parental_level_j, key, strlen ( key ) ) ; 
      paramsfo->values.parental_level_j = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_PARENTAL_LEVEL_K, KEY_PARENTAL_LEVEL_K_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.parental_level_k, key, strlen ( key ) ) ; 
      paramsfo->values.parental_level_k = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_RESOLUTION, KEY_RESOLUTION_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.resolution, key, strlen ( key ) ) ; 
      paramsfo->values.resolution = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_SOUND_FORMAT, KEY_SOUND_FORMAT_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.sound_format, key, strlen ( key ) ) ; 
      paramsfo->values.sound_format = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else if ( !strncmp( key, KEY_REGION_DENY, KEY_REGION_DENY_LEN ) ) 
    {
      strncpy ( (char*)paramsfo->keys.region_deny, key, strlen ( key ) ) ; 
      paramsfo->values.region_deny = ( strtoul ( value, NULL, 10 ) ) ;
    }
    else
    {
      fprintf ( stderr, "ERROR: Unknown integer key %s\n", key ) ; 
    }
  }
  else
  {
    fprintf ( stderr, "ERROR: Unknown key %s\n", key ) ; 
  }
}

static void
readXML ( char *filename, paramSFO *paramsfo )
{
  char tag[STR_MAX], tagname[STR_MAX], attrname[STR_MAX], key[STR_MAX], lastkey[STR_MAX], lasttype[STR_MAX], value[STR_MAX] ;
  int linum = 0 ;
  FILE *fp = 0 ;

  fp = fopen ( filename, "r" ) ;
  if ( fp == 0 )
  {
    fprintf ( stderr, "Error: Cannot open input file '%s'.\n", filename ) ;
    exit ( 1 ) ;
  }

  xml_parse ( fp, tag, value, STR_MAX, &linum ) ;

  while ( tag[0] != '\0' )
  {
    xml_grab_tag_name ( tag, tagname, STR_MAX ) ; /* Get tag name. */

    xml_grab_attrib ( tag, attrname, key, STR_MAX ) ; /* Get next attribute, if any. */

    memset ( &lastkey, 0x00, sizeof ( lastkey ) ) ;
    memset ( &lasttype, 0x00, sizeof ( lasttype ) ) ;

    while ( key[0] != '\0' ) 
    {
      if ( !strncmp ( attrname, "name", 4 ) )
      {
        strncpy ( lastkey, key, sizeof ( key ) ) ; 
      }
      else if ( !strncmp ( attrname, "type", 4 ) )
      {
        strncpy ( lasttype, key, sizeof ( key ) ) ;
      }

      xml_grab_attrib ( tag, attrname, key, STR_MAX ) ; /* Get next attribute, if any. */
    }

    if ( !strncmp ( tagname, "value", 5 ) ) 
    {
      paramsfo->header.entries_count++ ;
      setKeyValue ( lastkey, lasttype, value, paramsfo ) ;
    }

    xml_parse ( fp, tag, value, STR_MAX, &linum ) ; /* Get next tag, if any. */ 
  }

  fclose( fp ) ;
}

static void
writeHeader ( FILE *fp, paramSFO *paramsfo )
{
  int ret ;

  paramsfo->header.keys_offset =   paramsfo->entries_pos ;
  paramsfo->header.values_offset = paramsfo->entries_pos + paramsfo->keys_pos + KEY_PADDING_LEN ;

  ret = fwrite ( &paramsfo->header, 1, sizeof ( paramHeader ), fp ) ;
  if ( ret != sizeof ( paramHeader ) )
  {
    fprintf ( stderr, "ERROR: writing param.sfo header: %d != %ld\n", ret, sizeof ( paramHeader ) ) ;
    error () ;
  }
}

static void
writeEntries ( FILE *fp, paramSFO *paramsfo )
{
  int i, ret ;

  for ( i = 0; i < paramsfo->header.entries_count; i++ )
  {
    ret = fwrite ( &paramsfo->entries[i], 1, sizeof ( paramEntry ), fp ) ;
    if ( ret != sizeof ( paramEntry ) )
    {
      fprintf ( stderr, "ERROR: writing param.sfo entry[%d]: %d != %ld\n", i, ret, sizeof ( paramEntry ) ) ;
      error () ;
    }
  }
}

static void
writeKeys ( FILE *fp, paramSFO *paramsfo )
{
  int ret ;

  WRITE_KEY( fp, ret, paramsfo->keys.app_ver,          KEY_APP_VER_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.attribute,        KEY_ATTRIBUTE_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.bootable,         KEY_BOOTABLE_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.category,         KEY_CATEGORY_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.license,          KEY_LICENSE_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.parental_level,   KEY_PARENTAL_LEVEL_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.parental_level_a, KEY_PARENTAL_LEVEL_A_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.parental_level_c, KEY_PARENTAL_LEVEL_C_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.parental_level_e, KEY_PARENTAL_LEVEL_E_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.parental_level_h, KEY_PARENTAL_LEVEL_H_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.parental_level_j, KEY_PARENTAL_LEVEL_J_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.parental_level_k, KEY_PARENTAL_LEVEL_K_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.ps3_system_ver,   KEY_PS3_SYSTEM_VER_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.region_deny,      KEY_REGION_DENY_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.resolution,       KEY_RESOLUTION_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.sound_format,     KEY_SOUND_FORMAT_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.title,            KEY_TITLE_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.title_id,         KEY_TITLE_ID_LEN ) ;
  WRITE_KEY( fp, ret, paramsfo->keys.version,          KEY_VERSION_LEN ) ;

  WRITE_PADDING( fp, ret, paramsfo->keys.padding, KEY_PADDING_LEN ) ;
}

static void
writeValues ( FILE *fp, paramSFO *paramsfo )
{
  int ret ;

  WRITE_VALUE_STR ( fp, ret, paramsfo->keys.app_ver,          paramsfo->values.app_ver,           VALUE_APP_VER_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.attribute,        &paramsfo->values.attribute,        VALUE_ATTRIBUTE_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.bootable,         &paramsfo->values.bootable,         VALUE_BOOTABLE_MAX ) ;
  WRITE_VALUE_STR ( fp, ret, paramsfo->keys.category,         paramsfo->values.category,          VALUE_CATEGORY_MAX ) ;
  WRITE_VALUE_STR ( fp, ret, paramsfo->keys.license,          paramsfo->values.license,           VALUE_LICENSE_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.parental_level,   &paramsfo->values.parental_level,   VALUE_PARENTAL_LEVEL_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.parental_level_a, &paramsfo->values.parental_level_a, VALUE_PARENTAL_LEVEL_A_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.parental_level_c, &paramsfo->values.parental_level_c, VALUE_PARENTAL_LEVEL_C_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.parental_level_e, &paramsfo->values.parental_level_e, VALUE_PARENTAL_LEVEL_E_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.parental_level_h, &paramsfo->values.parental_level_h, VALUE_PARENTAL_LEVEL_H_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.parental_level_j, &paramsfo->values.parental_level_j, VALUE_PARENTAL_LEVEL_J_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.parental_level_k, &paramsfo->values.parental_level_k, VALUE_PARENTAL_LEVEL_K_MAX ) ;
  WRITE_VALUE_STR ( fp, ret, paramsfo->keys.ps3_system_ver,   paramsfo->values.ps3_system_ver,    VALUE_PS3_SYSTEM_VER_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.region_deny,      &paramsfo->values.region_deny,      VALUE_REGION_DENY_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.resolution,       &paramsfo->values.resolution,       VALUE_RESOLUTION_MAX ) ;
  WRITE_VALUE_INT ( fp, ret, paramsfo->keys.sound_format,     &paramsfo->values.sound_format,     VALUE_SOUND_FORMAT_MAX ) ;
  WRITE_VALUE_STR ( fp, ret, paramsfo->keys.title,            paramsfo->values.title,             VALUE_TITLE_MAX ) ;
  WRITE_VALUE_STR ( fp, ret, paramsfo->keys.title_id,         paramsfo->values.title_id,          VALUE_TITLE_ID_MAX ) ;
  WRITE_VALUE_STR ( fp, ret, paramsfo->keys.version,          paramsfo->values.version,           VALUE_VERSION_MAX ) ;
}

static void
createSFO ( char *filename, paramSFO *paramsfo )
{
  FILE *fp = fopen ( filename, "wb" ) ;

  if ( fp == NULL )
  {
    fprintf ( stderr, "ERROR: opening file: %s\n", filename ) ;
    error () ;
  }

  if ( fp )
  {
    writeHeader ( fp, paramsfo ) ;
    writeEntries ( fp, paramsfo ) ;
    writeKeys ( fp, paramsfo ) ;
    writeValues ( fp, paramsfo ) ;
    fclose ( fp ) ;
  }
}

static void
printHeader ( paramSFO *paramsfo )
{
  fprintf ( stdout, "[X] Magic:         0x%08x\n", paramsfo->header.sfo_magic ) ;
  fprintf ( stdout, "[ ] Version:       0x%08x\n", paramsfo->header.sfo_version ) ;
  fprintf ( stdout, "[X] Keys Offset:   0x%08x\n", paramsfo->header.keys_offset ) ;
  fprintf ( stdout, "[X] Values Offset: 0x%08x\n", paramsfo->header.values_offset ) ;
  fprintf ( stdout, "[X] Entries Count: 0x%08x\n\n", paramsfo->header.entries_count ) ;
}

static void
printEntries ( paramSFO *paramsfo )
{
  int i ;

  for ( i = 0; i < paramsfo->header.entries_count; i++ )
  {
    fprintf ( stdout, "[X] Key Offset:    0x%04x\n",   paramsfo->entries[i].key_offset ) ;
    fprintf ( stdout, "[ ] Unk1:          0x%02x\n",   paramsfo->entries[i].unk1 ) ;
    fprintf ( stdout, "[/] Value Type:    0x%02x\n",   paramsfo->entries[i].value_type ) ;
    fprintf ( stdout, "[X] Value Length:  0x%08x\n",   paramsfo->entries[i].value_len ) ;
    fprintf ( stdout, "[X] Value Max Len: 0x%08x\n",   paramsfo->entries[i].value_max ) ;
    fprintf ( stdout, "[X] Value Offset:  0x%08x\n\n", paramsfo->entries[i].value_offset ) ;
  }
}

static void
printKeysValues ( paramSFO *paramsfo )
{
  fprintf ( stdout, "[X] %-14s %s\n",     paramsfo->keys.title,          paramsfo->values.title ) ;
  fprintf ( stdout, "[X] %-14s %s\n",     paramsfo->keys.title_id,       paramsfo->values.title_id ) ;
  fprintf ( stdout, "[X] %-14s %s\n",     paramsfo->keys.app_ver,        paramsfo->values.app_ver ) ;
  fprintf ( stdout, "[X] %-14s %s\n",     paramsfo->keys.category,       paramsfo->values.category ) ;
  fprintf ( stdout, "[X] %-14s 0x%08x\n", paramsfo->keys.resolution,     paramsfo->values.resolution ) ;
  fprintf ( stdout, "[X] %-14s 0x%08x\n", paramsfo->keys.sound_format,   paramsfo->values.sound_format ) ;
  fprintf ( stdout, "[X] %-14s %s\n",     paramsfo->keys.ps3_system_ver, paramsfo->values.ps3_system_ver ) ;
  fprintf ( stdout, "[X] %-14s %s\n",     paramsfo->keys.version,        paramsfo->values.version ) ;
  fprintf ( stdout, "[X] %-14s 0x%08x\n", paramsfo->keys.attribute,      paramsfo->values.attribute ) ;
  fprintf ( stdout, "[X] %-14s 0x%08x\n", paramsfo->keys.bootable,       paramsfo->values.bootable ) ;
  fprintf ( stdout, "[X] %-14s 0x%08x\n", paramsfo->keys.parental_level, paramsfo->values.parental_level ) ;
  fprintf ( stdout, "[X] %-14s %s\n",     paramsfo->keys.license,        paramsfo->values.license ) ;
}

int
main ( int argc, char **argv )
{
  paramSFO paramsfo ;
  paramsfo.entries = NULL ;

  argOptions args ;
  args.verbose = 0 ;
  args.silent = 0 ;
  args.title = NULL ;
  args.title_id = NULL ;
  args.dst_xml = NULL ;
  args.src_xml = NULL ;
  args.dst_sfo = NULL ;

  static int c ;
  static int option_index ;

  version () ;

  while ( 1 )
  {
    static struct option long_options[] =
    {
      { "help",         no_argument,       0, 'h' },
      { "verbose",      no_argument,       0, 'v' },
      { "silent",       no_argument,       0, 's' },
      { "title",        required_argument, 0, 't' },
      { "appid",        required_argument, 0, 'a' },
/*
      { "category",     required_argument, 0, 0 },
      { "resolution",   required_argument, 0, 0 },
      { "sound_format", required_argument, 0, 0 },
      { "attribute",    required_argument, 0, 0 },
*/
      { "toxml",        required_argument, 0, 'x' },
      { "fromxml",      required_argument, 0, 'f' },
      { 0, 0, 0, 0 },
    };

    c = getopt_long ( argc, argv, "hvst:a:x:f:", long_options, &option_index ) ;
    if ( c == -1 )
    {
      break ;
    }

    switch ( c )
    {
      case 0:
        break ;
      case 'h':
        usage ( argv[0] ) ;
        exit ( EXIT_SUCCESS ) ;
      case 'v':
        args.verbose = c ;
        break ;
      case 's':
        args.silent = c ;
        break ;
      case 't':
        args.title = optarg ;
        break ;
      case 'a':
        args.title_id = optarg ;
        break ;
      case 'x':
        args.dst_xml = optarg ;
        break ;
      case 'f':
        args.src_xml = optarg ;
        break ;
      default:
        usage ( argv[0] ) ;
        exit ( EXIT_FAILURE ) ;
    }
  }

  args.dst_sfo = argv[optind] ;
  if ( args.dst_sfo == NULL )
  {
    usage ( argv[0] ) ;
    fprintf ( stderr, "***YOU MUST SUPPLY PARAM.SFO***\n" ) ;
    exit ( EXIT_FAILURE ) ;
  }

  initHeader ( &paramsfo ) ;
  initKeys ( &paramsfo ) ;
  initValues ( &paramsfo ) ;

  readXML ( args.src_xml, &paramsfo ) ;

  initEntries ( &paramsfo ) ;

  setEntries ( &paramsfo ) ;

  createSFO ( args.dst_sfo, &paramsfo ) ;

  if ( args.silent == 0 )
  {
    printHeader ( &paramsfo ) ;
  }
  if ( args.verbose != 0 && args.silent == 0 )
  {
    printEntries ( &paramsfo ) ;
  }
  if ( args.silent == 0 )
  {
    printKeysValues ( &paramsfo ) ;
  }

  freeMemory ( &paramsfo ) ;

  exit ( EXIT_SUCCESS ) ;
}

