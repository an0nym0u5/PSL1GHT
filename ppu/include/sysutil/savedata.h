#ifndef __SYSUTIL_SAVEDATA_H__
#define __SYSUTIL_SAVEDATA_H__

#include <ppu-types.h>
#include <time.h>


/*
 * defines
 */

/* Success / Failure */
#define SYS_SAVEDATA_OK                          (0)
#define SYS_SAVEDATA_CANCEL                      (1)

/* Error Codes */
#define SYS_SAVEDATA_ERROR                       0x8002b400
#define SYS_SAVEDATA_ERROR_CBRESULT              (SYS_SAVEDATA_ERROR | 1)
#define SYS_SAVEDATA_ERROR_ACCESS_ERROR          (SYS_SAVEDATA_ERROR | 2)
#define SYS_SAVEDATA_ERROR_INTERNAL              (SYS_SAVEDATA_ERROR | 3)
#define SYS_SAVEDATA_ERROR_PARAM                 (SYS_SAVEDATA_ERROR | 4)
#define SYS_SAVEDATA_ERROR_NOSPACE               (SYS_SAVEDATA_ERROR | 5)
#define SYS_SAVEDATA_ERROR_BROKEN                (SYS_SAVEDATA_ERROR | 6)
#define SYS_SAVEDATA_ERROR_FAILURE               (SYS_SAVEDATA_ERROR | 7)
#define SYS_SAVEDATA_ERROR_BUSY                  (SYS_SAVEDATA_ERROR | 8)
#define SYS_SAVEDATA_ERROR_NOUSER                (SYS_SAVEDATA_ERROR | 9)
#define SYS_SAVEDATA_ERROR_SIZEOVER              (SYS_SAVEDATA_ERROR | a)
#define SYS_SAVEDATA_ERROR_NODATA                (SYS_SAVEDATA_ERROR | b)
#define SYS_SAVEDATA_ERROR_NOTSUPPORTED          (SYS_SAVEDATA_ERROR | c)

#define SYS_SAVEDATA_ATTR_NORMAL                 (0)
#define SYS_SAVEDATA_ATTR_NODUPLICATE            (1)

/* Flags for the binding information */
#define SYS_SAVEDATA_BINDSTAT_OK                 0x00
#define SYS_SAVEDATA_BINDSTAT_ERR_CONSOLE        0x01
#define SYS_SAVEDATA_BINDSTAT_ERR_DISC           0x02
#define SYS_SAVEDATA_BINDSTAT_ERR_APP            0x04
#define SYS_SAVEDATA_BINDSTAT_ERR_NOACCOUNTID    0x08
#define SYS_SAVEDATA_BINDSTAT_ERR_NOUSER         0x08
#define SYS_SAVEDATA_BINDSTAT_ERR_ACCOUNTID      0x10
#define SYS_SAVEDATA_BINDSTAT_ERR_OTHERS         0x10
#define SYS_SAVEDATA_BINDSTAT_ERR_NOUSERID       0x20
#define SYS_SAVEDATA_BINDSTAT_ERR_USERID         0x40
#define SYS_SAVEDATA_BINDSTAT_ERR_NOOWNER        0x100
#define SYS_SAVEDATA_BINDSTAT_ERR_OWNER          0x200
#define SYS_SAVEDATA_BINDSTAT_ERR_LOCALOWNER     0x400

#define SYS_SAVEDATA_OPTION_NONE                 (0)
#define SYS_SAVEDATA_OPTION_NOCONFIRM            (1)

#define SYS_SAVEDATA_DISABLE_TROPHY_OWNERSHIP_CHECK    (1<<16)

/* Result values for the callback */
#define SYS_SAVEDATA_CBRESULT_OK_LAST_NOCONFIRM  (2)
#define SYS_SAVEDATA_CBRESULT_OK_LAST            (1)
#define SYS_SAVEDATA_CBRESULT_OK_NEXT            (0)
#define SYS_SAVEDATA_CBRESULT_ERR_NOSPACE        (-1)
#define SYS_SAVEDATA_CBRESULT_ERR_FAILURE        (-2)
#define SYS_SAVEDATA_CBRESULT_ERR_BROKEN         (-3)
#define SYS_SAVEDATA_CBRESULT_ERR_NODATA         (-4)
#define SYS_SAVEDATA_CBRESULT_ERR_INVALID        (-5)


/*
 * enums
 */

/* Current version value for the save data */
typedef enum
{
    SYS_SAVEDATA_VERSION_CURRENT                 = 0
} sysSaveDataVersion;

/* Filenames of SaveData */
typedef enum
{
    SYS_SAVEDATA_DIRNAME_SIZE                    = 32,
    SYS_SAVEDATA_FILENAME_SIZE                   = 13,
    SYS_SAVEDATA_SECUREFILEID_SIZE               = 16,
    SYS_SAVEDATA_PREFIX_SIZE                     = 256,
    SYS_SAVEDATA_LISTITEM_MAX                    = 2048,
    SYS_SAVEDATA_SECUREFILE_MAX                  = 113,
    SYS_SAVEDATA_DIRLIST_MAX                     = 2048,
    SYS_SAVEDATA_INVALID_MESSAGE_MAX             = 256,
    SYS_SAVEDATA_INDICATORMSG_MAX                = 64
} sysSaveDataParamSize;

/* System Param Size */
typedef enum
{
    SYS_SAVEDATA_SYSP_TITLE_SIZE                 = 128,
    SYS_SAVEDATA_SYSP_SUBTITLE_SIZE              = 128,
    SYS_SAVEDATA_SYSP_DETAIL_SIZE                = 1024,
    SYS_SAVEDATA_SYSP_LPARAM_SIZE                = 8
} sysSaveDataSystemParamSize;

/* List Sort Type */
typedef enum
{
    SYS_SAVEDATA_SORTTYPE_MODIFIEDTIME           = 0,
    SYS_SAVEDATA_SORTTYPE_SUBTITLE               = 1
} SysSaveDataSortType;

/* List Sort Order */
typedef enum
{
    SYS_SAVEDATA_SORTORDER_DESCENT              = 0,
    SYS_SAVEDATA_SORTORDER_ASCENT               = 1
} sysSaveDataSortOrder;

typedef enum
{
    SYS_SAVEDATA_ICONPOS_HEAD                    = 0,
    SYS_SAVEDATA_ICONPOS_TAIL                    = 1
} sysSaveDataIconPosition;

typedef enum
{
    SYS_SAVEDATA_FOCUSPOS_DIRNAME                = 0,
    SYS_SAVEDATA_FOCUSPOS_LISTHEAD               = 1,
    SYS_SAVEDATA_FOCUSPOS_LISTTAIL               = 2,
    SYS_SAVEDATA_FOCUSPOS_LATEST                 = 3,
    SYS_SAVEDATA_FOCUSPOS_OLDEST                 = 4,
    SYS_SAVEDATA_FOCUSPOS_NEWDATA                = 5
} sysSaveDataFocusPosition;

typedef enum
{
    SYS_SAVEDATA_ISNEWDATA_NO                    = 0,
    SYS_SAVEDATA_ISNEWDATA_YES                   = 1
} sysSaveDataIsNewData;

typedef enum
{
    SYS_SAVEDATA_ERRDIALOG_NONE                  = 0,
    SYS_SAVEDATA_ERRDIALOG_ALWAYS                = 1,
    SYS_SAVEDATA_ERRDIALOG_NOREPEAT              = 2
} sysSaveDataErrDialog;

typedef enum
{
    SYS_SAVEDATA_RECREATE_NO                     = 0,
    SYS_SAVEDATA_RECREATE_NO_NOBROKEN            = 1,
    SYS_SAVEDATA_RECREATE_YES                    = 2,
    SYS_SAVEDATA_RECREATE_YES_RESET_OWNER        = 3
} sysSaveDataReCreateMode;

typedef enum
{
    SYS_SAVEDATA_FILETYPE_SECUREFILE             = 0,
    SYS_SAVEDATA_FILETYPE_NORMALFILE             = 1,
    SYS_SAVEDATA_FILETYPE_CONTENT_ICON0          = 2,
    SYS_SAVEDATA_FILETYPE_CONTENT_ICON1          = 3,
    SYS_SAVEDATA_FILETYPE_CONTENT_PIC1           = 4,
    SYS_SAVEDATA_FILETYPE_CONTENT_SND0           = 5
} sysSaveDataFileType;

typedef enum
{
    SYS_SAVEDATA_FILEOP_READ                     = 0,
    SYS_SAVEDATA_FILEOP_WRITE                    = 1,
    SYS_SAVEDATA_FILEOP_DELETE                   = 2,
    SYS_SAVEDATA_FILEOP_WRITE_NOTRUNC            = 3
} sysSaveDataFileOperation;

typedef enum
{
    SYS_SAVEDATA_INDICATORPOS_LOWER_RIGHT        = 0,
    SYS_SAVEDATA_INDICATORPOS_LOWER_LEFT         = 1,
    SYS_SAVEDATA_INDICATORPOS_UPPER_RIGHT        = 2,
    SYS_SAVEDATA_INDICATORPOS_UPPER_LEFT         = 3,
    SYS_SAVEDATA_INDICATORPOS_CENTER             = 4
} sysSaveDataAutoIndicatorDispPosition;

typedef enum
{
    SYS_SAVEDATA_INDICATORPOS_MSGALIGN_LEFT      = 0<<4,
    SYS_SAVEDATA_INDICATORPOS_MSGALIGN_RIGHT     = 1<<4,
    SYS_SAVEDATA_INDICATORPOS_MSGALIGN_CENTER    = 2<<4
} sysSaveDataAutoIndicatorDispMsgAlign;

typedef enum
{
    SYS_SAVEDATA_INDICATORMODE_FIXED             = 0,
    SYS_SAVEDATA_INDICATORMODE_BLINK             = 1,
    SYS_SAVEDATA_INDICATORMODE_BLINK_FAST        = 2,
    SYS_SAVEDATA_INDICATORMODE_BLINK_SLOW        = 3
} sysSaveDataAutoIndicatorDispMode;


#ifdef __cplusplus
extern "C" {
#endif


/*
 * structs
 */

typedef struct
{
    u32 sortType;
    u32 sortOrder;
    char *dirNamePrefix ATTRIBUTE_PRXPTR;
    void *reserved ATTRIBUTE_PRXPTR;
} sysSaveDataSetList;

typedef struct
{
    u32 dirListMax;
    u32 fileListMax;
    u32 reserved[6];
    u32 bufSize;
    void *buf ATTRIBUTE_PRXPTR;
} sysSaveDataSetBuf;

typedef struct
{
    char *title ATTRIBUTE_PRXPTR;
    u32 iconBufSize;
    void *iconBuf ATTRIBUTE_PRXPTR;
    void *reserved ATTRIBUTE_PRXPTR;
} sysSaveDataNewDataIcon;

typedef struct
{
    u32 dispPosition;
    u32 dispMode;
    char *dispMsg ATTRIBUTE_PRXPTR;
    u32 picBufSize;
    void *picBuf ATTRIBUTE_PRXPTR;
    void *reserved ATTRIBUTE_PRXPTR;
} sysSaveDataAutoIndicator;

typedef struct
{
    char dirName[SYS_SAVEDATA_DIRNAME_SIZE];
    char listParam[SYS_SAVEDATA_SYSP_LPARAM_SIZE];
    char reserved[8];
} sysSaveDataDirList;

typedef struct
{
    u32 iconPosition;
    char *dirName ATTRIBUTE_PRXPTR;
    sysSaveDataNewDataIcon *icon ATTRIBUTE_PRXPTR;
    void *reserved ATTRIBUTE_PRXPTR;
} sysSaveDataListNewData;

typedef struct
{
    u32 dirNum;
    u32 dirListNum;
    sysSaveDataDirList *dirList ATTRIBUTE_PRXPTR;
    char reserved[64];
} sysSaveDataListGet;

typedef struct
{
    u32 focusPosition;
    char *focusDirName ATTRIBUTE_PRXPTR;
    u32 fixedListNum;
    sysSaveDataDirList *fixedList ATTRIBUTE_PRXPTR;
    sysSaveDataListNewData *newData ATTRIBUTE_PRXPTR;
    void *reserved ATTRIBUTE_PRXPTR;
} sysSaveDataListSet;

typedef struct
{
    char *dirName ATTRIBUTE_PRXPTR;
    sysSaveDataNewDataIcon *newIcon ATTRIBUTE_PRXPTR;
    u32 option;
} sysSaveDataFixedSet;

typedef struct
{
    char title[SYS_SAVEDATA_SYSP_TITLE_SIZE];
    char subTitle[SYS_SAVEDATA_SYSP_SUBTITLE_SIZE];
    char detail[SYS_SAVEDATA_SYSP_DETAIL_SIZE];
    u32 attribute;
    char reserved2[4];
    char listParam[SYS_SAVEDATA_SYSP_LPARAM_SIZE];
    char reserved[256];
} sysSaveDataSystemFileParam;

typedef struct
{
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
    char dirName[SYS_SAVEDATA_DIRNAME_SIZE];
} sysSaveDataDirStat;

typedef struct
{
    u32 fileType;
    char reserved1[4];
    uint64_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
    char fileName[SYS_SAVEDATA_FILENAME_SIZE];
    char reserved2[3];
} sysSaveDataFileStat;

typedef struct
{
    s32 hddFreeSizeKB;
    u32 isNewData;
    sysSaveDataDirStat dir;
    sysSaveDataSystemFileParam getParam;
    u32 bind;
    s32 sizeKB;
    s32 sysSizeKB;
    u32 fileNum;
    u32 fileListNum;
    sysSaveDataFileStat *fileList ATTRIBUTE_PRXPTR;
    char reserved[64];
} sysSaveDataStatGet;

typedef struct
{
    sysSaveDataSystemFileParam *setParam ATTRIBUTE_PRXPTR;
    u32 reCreateMode;
    sysSaveDataAutoIndicator *indicator ATTRIBUTE_PRXPTR;
} sysSaveDataStatSet;

typedef struct
{
    u32 excSize;
    char reserved[64];
} sysSaveDataFileGet;

typedef struct
{
    u32 fileOperation;
    void *reserved ATTRIBUTE_PRXPTR;
    u32 fileType;
    unsigned char secureFileId[SYS_SAVEDATA_SECUREFILEID_SIZE];
    char *fileName ATTRIBUTE_PRXPTR;
    u32 fileOffset;
    u32 fileSize;
    u32 fileBufSize;
    void *fileBuf ATTRIBUTE_PRXPTR;
} sysSaveDataFileSet;

typedef struct
{
    s32 excResult;
    char dirName[SYS_SAVEDATA_DIRNAME_SIZE];
    s32 sizeKB;
    s32 hddFreeSizeKB;
    char reserved[64];
} sysSaveDataDoneGet;

typedef struct
{
    s32 result;
    u32 progressBarInc;
    s32 errNeedSizeKB;
    char *invalidMsg ATTRIBUTE_PRXPTR;
    void *userdata ATTRIBUTE_PRXPTR;
} sysSaveDataCBResult;


/*
 * callbacks
 */

typedef void (*sysSaveDataListCallback)(sysSaveDataCBResult *resultCb,
                                        sysSaveDataListGet *get,
                                        sysSaveDataListSet *set );


typedef void (*sysSaveDataFixedCallback)(sysSaveDataCBResult *resultCb,
                                         sysSaveDataListGet *get,
                                         sysSaveDataFixedSet *set );


typedef void (*sysSaveDataStatCallback)(sysSaveDataCBResult *resultCb,
                                        sysSaveDataStatGet *get,
                                        sysSaveDataStatSet *set );


typedef void (*sysSaveDataFileCallback)(sysSaveDataCBResult *resultCb,
                                        sysSaveDataFileGet *get,
                                        sysSaveDataFileSet *set );


typedef void (*sysSaveDataDoneCallback)(sysSaveDataCBResult *resultCb,
                                        sysSaveDataDoneGet *get );


/*
 * functions
 */

s32 sysSaveDataListSave2(u32 version,
                         sysSaveDataSetList *setList,
                         sysSaveDataSetBuf *setBuf,
                         sysSaveDataListCallback listCb,
                         sysSaveDataStatCallback statCb,
                         sysSaveDataFileCallback fileCb,
                         sys_mem_container_t container,
                         void *userdata);

s32 sysSaveDataListLoad2(u32 version,
                         sysSaveDataSetList *setList,
                         sysSaveDataSetBuf *setBuf,
                         sysSaveDataListCallback listCb,
                         sysSaveDataStatCallback statCb,
                         sysSaveDataFileCallback fileCb,
                         sys_mem_container_t container,
                         void *userdata);

s32 sysSaveDataFixedSave2(u32 version,
                          sysSaveDataSetList *setList,
                          sysSaveDataSetBuf *setBuf,
                          sysSaveDataFixedCallback fixedCb,
                          sysSaveDataStatCallback statCb,
                          sysSaveDataFileCallback fileCb,
                          sys_mem_container_t container,
                          void *userdata);

s32 sysSaveDataFixedLoad2(u32 version,
                          sysSaveDataSetList *setList,
                          sysSaveDataSetBuf *setBuf,
                          sysSaveDataFixedCallback fixedCb,
                          sysSaveDataStatCallback statCb,
                          sysSaveDataFileCallback fileCb,
                          sys_mem_container_t container,
                          void *userdata);

s32 sysSaveDataAutoSave2(u32 version,
                         const char *dirName,
                         u32 errDialog,
                         sysSaveDataSetBuf *setBuf,
                         sysSaveDataStatCallback statCb,
                         sysSaveDataFileCallback fileCb,
                         sys_mem_container_t container,
                         void *userdata);

s32 sysSaveDataAutoLoad2(u32 version,
                         const char *dirName,
                         u32 errDialog,
                         sysSaveDataSetBuf *setBuf,
                         sysSaveDataStatCallback statCb,
                         sysSaveDataFileCallback fileCb,
                         sys_mem_container_t container,
                         void *userdata);

s32 sysSaveDataListAutoSave(u32 version,
                            u32 errDialog,
                            sysSaveDataSetList *setList,
                            sysSaveDataSetBuf *setBuf,
                            sysSaveDataFixedCallback fixedCb,
                            sysSaveDataStatCallback statCb,
                            sysSaveDataFileCallback fileCb,
                            sys_mem_container_t container,
                            void *userdata);

s32 sysSaveDataListAutoLoad(u32 version,
                            u32 errDialog,
                            sysSaveDataSetList *setList,
                            sysSaveDataSetBuf *setBuf,
                            sysSaveDataFixedCallback fixedCb,
                            sysSaveDataStatCallback statCb,
                            sysSaveDataFileCallback fileCb,
                            sys_mem_container_t container,
                            void *userdata);

s32 sysSaveDataDelete2(sys_mem_container_t container);

s32 sysSaveDataListImport(sysSaveDataSetList *setList,
                          u32 maxSizeKB,
                          sysSaveDataDoneCallback doneCb,
                          sys_mem_container_t container,
                          void *userdata);

s32 sysSaveDataListExport(sysSaveDataSetList *setList,
                          u32 maxSizeKB,
                          sysSaveDataDoneCallback doneCb,
                          sys_mem_container_t container,
                          void *userdata);

s32 sysSaveDataFixedImport(const char *dirName,
                           u32 maxSizeKB,
                           sysSaveDataDoneCallback doneCb,
                           sys_mem_container_t container,
                           void *userdata);

s32 sysSaveDataFixedExport(const char *dirName,
                           u32 maxSizeKB,
                           sysSaveDataDoneCallback doneCb,
                           sys_mem_container_t container,
                           void *userdata);

s32 sysSaveDataListDelete(sysSaveDataSetList *setList,
                          sysSaveDataSetBuf *setBuf,
                          sysSaveDataListCallback listCb,
                          sysSaveDataDoneCallback doneCb,
                          sys_mem_container_t container,
                          void *userdata);

s32 sysSaveDataFixedDelete(sysSaveDataSetList *setList,
                           sysSaveDataSetBuf *setBuf,
                           sysSaveDataFixedCallback fixedCb,
                           sysSaveDataDoneCallback doneCb,
                           sys_mem_container_t container,
                           void *userdata);

s32 sysSaveDataGetListItem(const char *dirName,
                           sysSaveDataDirStat *dir,
                           sysSaveDataSystemFileParam *sysFileParam,
                           u32 *bind,
                           s32 *sizeKB);

s32 sysSaveDataUserListSave(u32 version,
                            u32 userId,
                            sysSaveDataSetList *setList,
                            sysSaveDataSetBuf *setBuf,
                            sysSaveDataListCallback listCb,
                            sysSaveDataStatCallback statCb,
                            sysSaveDataFileCallback fileCb,
                            sys_mem_container_t container,
                            void *userdata);

s32 sysSaveDataUserListLoad(u32 version,
                            u32 userId,
                            sysSaveDataSetList *setList,
                            sysSaveDataSetBuf *setBuf,
                            sysSaveDataListCallback listCb,
                            sysSaveDataStatCallback statCb,
                            sysSaveDataFileCallback fileCb,
                            sys_mem_container_t container,
                            void *userdata);

s32 sysSaveDataUserFixedSave(u32 version,
                             u32 userId,
                             sysSaveDataSetList *setList,
                             sysSaveDataSetBuf *setBuf,
                             sysSaveDataFixedCallback fixedCb,
                             sysSaveDataStatCallback statCb,
                             sysSaveDataFileCallback fileCb,
                             sys_mem_container_t container,
                             void *userdata);

s32 sysSaveDataUserFixedLoad(u32 version,
                             u32 userId,
                             sysSaveDataSetList *setList,
                             sysSaveDataSetBuf *setBuf,
                             sysSaveDataFixedCallback fixedCb,
                             sysSaveDataStatCallback statCb,
                             sysSaveDataFileCallback fileCb,
                             sys_mem_container_t container,
                             void *userdata);

s32 sysSaveDataUserAutoSave(u32 version,
                            u32 userId,
                            const char *dirName,
                            u32 errDialog,
                            sysSaveDataSetBuf *setBuf,
                            sysSaveDataStatCallback statCb,
                            sysSaveDataFileCallback fileCb,
                            sys_mem_container_t container,
                            void *userdata);

s32 sysSaveDataUserAutoLoad(u32 version,
                            u32 userId,
                            const char *dirName,
                            u32 errDialog,
                            sysSaveDataSetBuf *setBuf,
                            sysSaveDataStatCallback statCb,
                            sysSaveDataFileCallback fileCb,
                            sys_mem_container_t container,
                            void *userdata);

s32 sysSaveDataUserListAutoSave(u32 version,
                                u32 userId,
                                u32 errDialog,
                                sysSaveDataSetList *setList,
                                sysSaveDataSetBuf *setBuf,
                                sysSaveDataFixedCallback fixedCb,
                                sysSaveDataStatCallback statCb,
                                sysSaveDataFileCallback fileCb,
                                sys_mem_container_t container,
                                void *userdata);

s32 sysSaveDataUserListAutoLoad(u32 version,
                                u32 userId,
                                u32 errDialog,
                                sysSaveDataSetList *setList,
                                sysSaveDataSetBuf *setBuf,
                                sysSaveDataFixedCallback fixedCb,
                                sysSaveDataStatCallback statCb,
                                sysSaveDataFileCallback fileCb,
                                sys_mem_container_t container,
                                void *userdata);

s32 sysSaveDataUserListImport(u32 userId,
                              sysSaveDataSetList *setList,
                              u32 maxSizeKB,
                              sysSaveDataDoneCallback doneCb,
                              sys_mem_container_t container,
                              void *userdata);

s32 sysSaveDataUserListExport(u32 userId,
                               sysSaveDataSetList *setList,
                               u32 maxSizeKB,
                               sysSaveDataDoneCallback doneCb,
                               sys_mem_container_t container,
                               void *userdata);

s32 sysSaveDataUserFixedImport(u32 userId,
                               const char *dirName,
                               u32 maxSizeKB,
                               sysSaveDataDoneCallback doneCb,
                               sys_mem_container_t container,
                               void *userdata);

s32 sysSaveDataUserFixedExport(u32 userId,
                               const char *dirName,
                               u32 maxSizeKB,
                               sysSaveDataDoneCallback doneCb,
                               sys_mem_container_t container,
                               void *userdata);

s32 sysSaveDataUserListDelete(u32 userId,
                               sysSaveDataSetList *setList,
                               sysSaveDataSetBuf *setBuf,
                               sysSaveDataListCallback listCb,
                               sysSaveDataDoneCallback doneCb,
                               sys_mem_container_t container,
                               void *userdata);

s32 sysSaveDataUserFixedDelete(u32 userId,
                               sysSaveDataSetList *setList,
                               sysSaveDataSetBuf *setBuf,
                               sysSaveDataFixedCallback fixedCb,
                               sysSaveDataDoneCallback doneCb,
                               sys_mem_container_t container,
                               void *userdata);

s32 sysSaveDataUserGetListItem(u32 userId,
                               const char *dirName,
                               sysSaveDataDirStat *dir,
                               sysSaveDataSystemFileParam *sysFileParam,
                               u32 *bind,
                               s32 *sizeKB);

void sysSaveDataEnableOverlay(s32 enable);


#ifdef __cplusplus
	}
#endif

#endif
