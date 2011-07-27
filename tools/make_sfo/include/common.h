/*
 * common.h
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#define STR_MAX                           2000
#define ARG_MAX                           15

#define MAKE_SFO_VERSION                  "v0.01"
#define MAKE_SFO_TITLE                    "make_sfo"

#define HDR_SFO_MAGIC                     0x00505346
#define HDR_SFO_VERSION                   0x01010000
#define HDR_KEYS_OFFSET                   0x00000000
#define HDR_VALUES_OFFSET                 0x00000000
#define HDR_ENTRIES_COUNT                 0x00000000

#define ENTRY_OFFSET                      0x14
#define ENTRY_LEN                         0x10
#define ENTRY_UNK1                        0x04
#define ENTRY_TYPE2                       0x02
#define ENTRY_TYPE4                       0x04
#define ENTRY_STR                         "string"
#define ENTRY_INT                         "integer"

#define ENTRY_APP_VER                     0
#define ENTRY_ATTRIBUTE                   1
#define ENTRY_BOOTABLE                    2
#define ENTRY_CATEGORY                    3
#define ENTRY_LICENSE                     4
#define ENTRY_PARENTAL_LEVEL              5
#define ENTRY_PARENTAL_LEVEL_A            6
#define ENTRY_PARENTAL_LEVEL_C            7
#define ENTRY_PARENTAL_LEVEL_E            8
#define ENTRY_PARENTAL_LEVEL_H            9
#define ENTRY_PARENTAL_LEVEL_J            10
#define ENTRY_PARENTAL_LEVEL_K            11
#define ENTRY_PS3_SYSTEM_VER              12
#define ENTRY_REGION_DENY                 13
#define ENTRY_RESOLUTION                  14
#define ENTRY_SOUND_FORMAT                15
#define ENTRY_TITLE                       16
#define ENTRY_TITLE_ID                    17
#define ENTRY_VERSION                     18

#define KEY_APP_VER                       "APP_VER"
#define KEY_ATTRIBUTE                     "ATTRIBUTE"
#define KEY_BOOTABLE                      "BOOTABLE"
#define KEY_CATEGORY                      "CATEGORY"
#define KEY_LICENSE                       "LICENSE"
#define KEY_PARENTAL_LEVEL                "PARENTAL_LEVEL"
#define KEY_PARENTAL_LEVEL_A              "PARENTAL_LEVEL_A"
#define KEY_PARENTAL_LEVEL_C              "PARENTAL_LEVEL_C"
#define KEY_PARENTAL_LEVEL_E              "PARENTAL_LEVEL_E"
#define KEY_PARENTAL_LEVEL_H              "PARENTAL_LEVEL_H"
#define KEY_PARENTAL_LEVEL_J              "PARENTAL_LEVEL_J"
#define KEY_PARENTAL_LEVEL_K              "PARENTAL_LEVEL_K"
#define KEY_PS3_SYSTEM_VER                "PS3_SYSTEM_VER"
#define KEY_REGION_DENY                   "REGION_DENY"
#define KEY_RESOLUTION                    "RESOLUTION"
#define KEY_SOUND_FORMAT                  "SOUND_FORMAT"
#define KEY_TITLE                         "TITLE"
#define KEY_TITLE_ID                      "TITLE_ID"
#define KEY_VERSION                       "VERSION"

#define KEY_APP_VER_LEN                   0x08
#define KEY_ATTRIBUTE_LEN                 0x0a
#define KEY_BOOTABLE_LEN                  0x09
#define KEY_CATEGORY_LEN                  0x09
#define KEY_LICENSE_LEN                   0x08
#define KEY_PARENTAL_LEVEL_LEN            0x0f
#define KEY_PARENTAL_LEVEL_A_LEN          0x11
#define KEY_PARENTAL_LEVEL_C_LEN          0x11
#define KEY_PARENTAL_LEVEL_E_LEN          0x11
#define KEY_PARENTAL_LEVEL_H_LEN          0x11
#define KEY_PARENTAL_LEVEL_J_LEN          0x11
#define KEY_PARENTAL_LEVEL_K_LEN          0x11
#define KEY_PS3_SYSTEM_VER_LEN            0x0f
#define KEY_REGION_DENY_LEN               0x0c
#define KEY_RESOLUTION_LEN                0x0b
#define KEY_SOUND_FORMAT_LEN              0x0d
#define KEY_TITLE_LEN                     0x06
#define KEY_TITLE_ID_LEN                  0x09
#define KEY_VERSION_LEN                   0x07
#define KEY_PADDING_LEN                   0x04

#define VALUE_APP_VER_LEN                 0x06
#define VALUE_ATTRIBUTE_LEN               0x04
#define VALUE_BOOTABLE_LEN                0x04
#define VALUE_CATEGORY_LEN                0x03
#define VALUE_LICENSE_LEN                 0x113
#define VALUE_PARENTAL_LEVEL_LEN          0x04
#define VALUE_PARENTAL_LEVEL_A_LEN        0x04
#define VALUE_PARENTAL_LEVEL_C_LEN        0x04
#define VALUE_PARENTAL_LEVEL_E_LEN        0x04
#define VALUE_PARENTAL_LEVEL_H_LEN        0x04
#define VALUE_PARENTAL_LEVEL_J_LEN        0x04
#define VALUE_PARENTAL_LEVEL_K_LEN        0x04
#define VALUE_PS3_SYSTEM_VER_LEN          0x08
#define VALUE_REGION_DENY_LEN             0x04
#define VALUE_RESOLUTION_LEN              0x04
#define VALUE_SOUND_FORMAT_LEN            0x04
#define VALUE_TITLE_LEN                   0x12
#define VALUE_TITLE_ID_LEN                0x08
#define VALUE_VERSION_LEN                 0x06

#define VALUE_APP_VER_MAX                 0x08
#define VALUE_ATTRIBUTE_MAX               0x04
#define VALUE_BOOTABLE_MAX                0x04
#define VALUE_CATEGORY_MAX                0x04
#define VALUE_LICENSE_MAX                 0x200
#define VALUE_PARENTAL_LEVEL_MAX          0x04
#define VALUE_PARENTAL_LEVEL_A_MAX        0x04
#define VALUE_PARENTAL_LEVEL_C_MAX        0x04
#define VALUE_PARENTAL_LEVEL_E_MAX        0x04
#define VALUE_PARENTAL_LEVEL_H_MAX        0x04
#define VALUE_PARENTAL_LEVEL_J_MAX        0x04
#define VALUE_PARENTAL_LEVEL_K_MAX        0x04
#define VALUE_PS3_SYSTEM_VER_MAX          0x08
#define VALUE_REGION_DENY_MAX             0x04
#define VALUE_RESOLUTION_MAX              0x04
#define VALUE_SOUND_FORMAT_MAX            0x04
#define VALUE_TITLE_MAX                   0x80
#define VALUE_TITLE_ID_MAX                0x10
#define VALUE_VERSION_MAX                 0x08

#define dbgprintf(stream,format,args...) fprintf(stream,"\033[0;33m%s:%s():#%d::"format"\033[0m\n",__FILE__,__func__,__LINE__,##args);
#define errprintf(stream,format,args...) fprintf(stream,"\033[0;31m%s:%s():#%d::"format"\033[0m\n",__FILE__,__func__,__LINE__,##args);
#define CHECK_ERRNO(variable,text) if((variable)==NULL)fprintf(stderr,"%s():%d::ERROR: %s for %s...\n",__func__,__LINE__,strerror(errno),text);
#define WRITE_KEY(fp,ret,key,size) if(strncmp((const char*)key,"\0",1)){ret=fwrite(key,1,size,fp);if(ret!=size){fprintf(stderr,"%s():%d::ERROR: writing param.sfo keys [%s]: %x != %x (%s)\n",__func__,__LINE__,key,ret,size,strerror(errno));error();}}
#define WRITE_VALUE_STR(fp,ret,key,value,size) if(strncmp((const char*)key,"\0",1)&&strncmp((const char*)value,"\0",1)){ret=fwrite(value,1,size,fp);if(ret!=size){fprintf(stderr,"%s():%d::ERROR: writing param.sfo string value[%s=%s]: %x != %x (%s)\n",__func__,__LINE__,key,value,ret,size,strerror(errno));error();}}
#define WRITE_VALUE_INT(fp,ret,key,value,size) if(strncmp((const char*)key,"\0",1)&&value!=0){ret=fwrite(value,1,size,fp);if(ret!=size){fprintf(stderr,"%s():%d::ERROR: writing param.sfo integer value[%s=0x%x]: %x != %x (%s)\n",__func__,__LINE__,key,*value,ret,size,strerror(errno));error();}}
#define WRITE_PADDING(fp,ret,pad,size) ret=fwrite(pad,1,size,fp);if(ret!=size){fprintf(stderr,"%s():%d::ERROR: writing param.sfo keys padding: %x != %x (%s)\n",__func__,__LINE__,ret,size,strerror(errno));error();}

#ifdef __BIG_ENDIAN__
#define ntohll(x) (x)
#define htonll(x) (x)
#define htons(x) (x)
#define htonl(x) (x)
#define ntohs(x) (x)
#define ntohl(x) (x)
#else
#define htons(x) ((((uint16_t)(x) & 0xff00) >> 8) | \
                 (((uint16_t)(x) & 0x00ff) << 8))
#define htonl(x) ((((uint32_t)(x) & 0xff000000) >> 24) | \
                 (((uint32_t)(x) & 0x00ff0000) >> 8)  | \
                 (((uint32_t)(x) & 0x0000ff00) << 8)  | \
                 (((uint32_t)(x) & 0x000000ff) << 24))
#define ntohs  htons
#define ntohl  htonl
#endif

#endif /* __COMMON_H__ */

