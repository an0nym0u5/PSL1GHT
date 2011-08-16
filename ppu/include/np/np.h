#ifndef _SYS_NP_H_
#define _SYS_NP_H_


/*
 * constants
 */

#define SYS_NP_MIN_POOL_SIZE                     (128*1024) /* minimum pool size */
#define SYS_NP_OPEN_FLAG                         2          /* flag for opening */
#define SYS_NP_EXITSPAWN2_NO_FINISH              0x4000000000000000ULL /* exit without finish */
#define SYS_NP_TIME_INFO_ENDLESS                 0x7FFFFFFFFFFFFFFFULL /* */

/* init errors */
#define SYS_NP_INIT_ALREADY_INIT                 0x8002aa02 /* already initialized */
#define SYS_NP_INIT_INVALID_ARG                  0x8002aa03 /* invalid argument */
#define SYS_NP_INIT_INSUFF_BUF                   0x8002aa0f /* pool too small */

/* np authentication errors */
#define SYS_NP_AUTH_EINVAL                       0x8002a002 /* invalid timing */
#define SYS_NP_AUTH_ENOMEM                       0x8002a004 /* no memory */
#define SYS_NP_AUTH_ESRCH                        0x8002a005 /* invalid id */
#define SYS_NP_AUTH_EBUSY                        0x8002a00a /* utility busy */
#define SYS_NP_AUTH_EABORT                       0x8002a00c /* user cancelled */
#define SYS_NP_AUTH_EEXIST                       0x8002a014 /* key exists */
#define SYS_NP_AUTH_EINVALID_ARGUMENT            0x8002a015 /* invalid argument */

#define SYS_NP_ERROR_OUT_OF_MEMORY               0x80029501 /* no memory */
#define SYS_NP_ERROR_INVALID_PARAM               0x80029502 /* invalid argument */
#define SYS_NP_ERROR_SERVER_RESPONSE             0x80029509 /* server error */
#define SYS_NP_ERROR_NO_ENTITLEMENT              0x80029513 /* invalid rights */
#define SYS_NP_ERROR_BAD_ACT                     0x80029514 /* console not activated */
#define SYS_NP_ERROR_BAD_FORMAT                  0x80029515 /* invalid format access rights */
#define SYS_NP_ERROR_NO_LOGIN                    0x80029516 /* not logged on */
#define SYS_NP_ERROR_INTERNAL                    0x80029517 /* internal np access error */
#define SYS_NP_ERROR_BAD_PERM                    0x80029519 /* invalid permissions */
#define SYS_NP_ERROR_UNKNOWN_VERSION             0x8002951a /* invalid file version */
#define SYS_NP_ERROR_TIME_LIMIT                  0x8002951b /* time period expired */
#define SYS_NP_ERROR_DIFFERENT_ACCOUNT_ID        0x8002951c /* invalid accound info */
#define SYS_NP_ERROR_DIFFERENT_TYPE              0x8002951d /* invalid type */
#define SYS_NP_ERROR_SERVICE_NOT_STARTED         0x8002951e /* time period invalid */
#define SYS_NP_ERROR_BUSY                        0x80029520 /* utility busy */
#define SYS_NP_ERROR_LICENSE_NOT_FOUND           0x80029521 /* license not found */
#define SYS_NP_ERROR_IO                          0x80029525 /* read failure */
#define SYS_NP_ERROR_FORMAT                      0x80029530 /* invalid file format */
#define SYS_NP_ERROR_FILENAME                    0x80029533 /* invalid file extension */
#define SYS_NP_ERROR_K_LICENSEE                  0x80029534 /* invalid k_licensee */

#define SYS_NP_INSTALL_ERROR_FORMAT              0x80029563 /* invalid pkg format */
#define SYS_NP_INSTALL_ERROR_CHECK               0x80029564 /* invalid pkg */
#define SYS_NP_INSTALL_ERROR_UNSUPPORTED         0x80029566 /* filename exceeds 512 bytes */


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


/*
 * structures
 */
typedef struct _sys_np_key
{
  uint8_t key[16];
} sysNpKey;

typedef struct _sys_npdrm_open_arg
{
  u64 flag;
} sysNpOpenArg;


/*
 * functions
 */

s32 sceNpInit( u32 poolsize, void *poolptr );

s32 sceNpTerm( void ); 

/*  check */
s32 sysNpIsAvailable( const sysNpKey *k_licensee, const char *path );

/*  check (without callback polling) */
s32 sysNpIsAvailable2( const sysNpKey *k_licensee, const char *path );

/* license verification */
s32 sysNpVerifyUpgradeLicense( const char *content_id );

/* license verification (without callback polling) */
s32 sysNpVerifyUpgradeLicense2( const char *content_id );

/* execute gnp enabled self */
s32 sysNpExecuteGamePurchase( void );

/* remaining time (usec) */
s32 sysNpGetTimelimit( const char* path, u64* time_remain );

/*! \brief Terminate the running process and execute another program.
 *
 * This function returns only in case of error.
 * \param path Path and name of new program to be executed.
 * \param argv Commandline arguments for the new program.
 * \param envp Environment variables for the new program (may be \c NULL).
 * \param data Additional data (may be \c NULL).
 * \param size Size of additional data.
 * \param priority Priority.
 * \param flags Process flags. It contains an OR'ed combination of the following values:
 * - \ref SYS_PROCESS_SPAWN_STACK_SIZE_32K
 * - \ref SYS_PROCESS_SPAWN_STACK_SIZE_64K
 * - \ref SYS_PROCESS_SPAWN_STACK_SIZE_96K
 * - \ref SYS_PROCESS_SPAWN_STACK_SIZE_128K
 * - \ref SYS_PROCESS_SPAWN_STACK_SIZE_256K
 * - \ref SYS_PROCESS_SPAWN_STACK_SIZE_512K
 * - \ref SYS_PROCESS_SPAWN_STACK_SIZE_1M
 * - \ref SYS_NP_EXITSPAWN2_NO_FINISH
 */
s32 sysNpProcessExitSpawn2( const sysNpKey *k_licensee, /* key */
                            const char *path,           /* file path */
                            char const *argv[],         /* arguments (null term) */
                            char const *envp[],         /* env variables (null term) */
                            void *data,                 /* start addr of data */
                            u32 data_size,              /* size of data */
                            s32 priority,               /* priority of thread */
                            u64 flags                   /* creation flags */
                          );

/* legacy exitspawn() with gnp */
s32 sysNpProcessExitSpawn( const sysNpKey *k_licensee,  /* key */
                           const char *path,            /* file path */
                           char const *argv[],          /* arguments (null term) */
                           char const *envp[],          /* env variables (null term) */
                           void *data,                  /* start addr of data */
                           u32 data_size,               /* size of data */
                           s32 priority,                /* priority of thread */
                           u64 flags                    /* creation flags */
                         );

/* inline open np edata */
static __inline__ s32
sceNpDrmOpen( const sysNpKey *k_licensee,
              const char *path,
              s32 flags,
              s32 *fd,
              void * arg,
              u64 size
            )
{
  static s32 ret;

  sysNpOpenArg arg;
  sysFSStat stat;

  (void)arg;
  (void)size;

  /* file exists check */
  if ((ret = sysLv2FsStat(path, &stat))==0x80010006)
  {
    return ret;
  }

  /* check key */
  if ((ret = sysNpIsAvailable(k_licensee, path))!=0)
  {
    return ret;
  }

  /* open as np EDATA */
  arg.flag = SYS_NP_OPEN_FLAG;
  ret = sysFsOpen(path, flags, fd, &arg, sizeof(arg));

  return ret;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SYS_NP_H_ */

