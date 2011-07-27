/*
 * structs.h
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct _param_header
{
  uint32_t sfo_magic;
  uint32_t sfo_version;
  uint32_t keys_offset;
  uint32_t values_offset;
  uint32_t entries_count;
} paramHeader;

typedef struct _param_entry
{
  uint16_t key_offset;
  uint8_t unk1;
  uint8_t value_type;
  uint32_t value_len;
  uint32_t value_max;
  uint32_t value_offset;
} paramEntry ;

typedef struct _param_keys
{
  unsigned char *app_ver;
  unsigned char *attribute;
  unsigned char *bootable;
  unsigned char *category;
  unsigned char *license;
  unsigned char *parental_level;
  unsigned char *parental_level_a;
  unsigned char *parental_level_c;
  unsigned char *parental_level_e;
  unsigned char *parental_level_h;
  unsigned char *parental_level_j;
  unsigned char *parental_level_k;
  unsigned char *ps3_system_ver;
  unsigned char *region_deny;
  unsigned char *resolution;
  unsigned char *sound_format;
  unsigned char *title;
  unsigned char *title_id;
  unsigned char *version;
  unsigned char *padding;
} paramKeys;

typedef struct _param_values
{
  uint8_t *app_ver;
  uint32_t attribute;
  uint32_t bootable;
  uint8_t *category;
  uint8_t *license;
  uint32_t parental_level;
  uint32_t parental_level_a;
  uint32_t parental_level_c;
  uint32_t parental_level_e;
  uint32_t parental_level_h;
  uint32_t parental_level_j;
  uint32_t parental_level_k;
  uint8_t *ps3_system_ver;
  uint32_t region_deny;
  uint32_t resolution;
  uint32_t sound_format;
  uint8_t *title;
  uint8_t *title_id;
  uint8_t *version;
} paramValues;

typedef struct _param_SFO
{
  paramHeader header;
  paramEntry *entries;
  paramKeys keys;
  paramValues values ;
  uint32_t entry_count ;
  uint32_t entries_pos ;
  uint32_t keys_pos ;
  uint32_t values_pos ;
} paramSFO;

typedef struct _arg_options
{
  char *args[ARG_MAX] ;

  /* flags */
  int help ;
  int version ;
  int verbose ;
  int silent ;
  int list ;
  int debug ;
  int pretty ;

  /* filenames */
  char *src_xml ;
  char *dst_xml ;
  char *dst_sfo ;

  /* overrides */
  char *title ;
  char *title_id ;
  char *category ;
  int resolution ;
  int sound_format ;
  int attribute ;
} argOptions;

#endif /* __STRUCTS_H__ */

