#ifndef __LV2_SYSUTIL_CACHE_H__
#define __LV2_SYSUTIL_CACHE_H__

#include <ppu-types.h>

#define SYSUTIL_CACHE_OK_CLEAR                          (0)
#define SYSUTIL_CACHE_OK_RELAY                          (1)

#define SYSUTIL_CACHE_ERR_ACCESS                        (0x8002bc01)
#define SYSUTIL_CACHE_ERR_INTERNAL                      (0x8002bc02)

#define SYSUTIL_CACHE_ERR_PARAM                         (0x8002bc03)
#define SYSUTIL_CACHE_ERR_NOTMOUNTED                    (0x8002bc04)

typedef enum
{
  SYSUTIL_CACHE_ID_SIZE          = 32,
  SYSUTIL_CACHE_PATH_MAX         = 1055
} sysCacheParamSize;

typedef struct _sys_cache_param
{
  char cacheId[SYSUTIL_CACHE_ID_SIZE];
  char getCachePath[SYSUTIL_CACHE_PATH_MAX];
  void *reserved ATTRIBUTE_PRXPTR;
} sysCacheParam;

#ifdef __cplusplus
extern "C" {
#endif

s32 sysCacheMount(sysCacheParam *param);
s32 sysCacheClear(void);

#ifdef __cplusplus
	}
#endif

#endif
