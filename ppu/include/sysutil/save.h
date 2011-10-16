#ifndef __LV2_SYSUTIL_SAVE_H__
#define __LV2_SYSUTIL_SAVE_H__

#include <ppu-types.h>
#include <time.h>

/* Maximum string/array sizes */
#define SYS_SAVE_MAX_DIRECTORY_NAME		32
#define SYS_SAVE_MAX_FILE_NAME			13
#define SYS_SAVE_DIRECTORY_LIST_MAX		2048
#define SYS_SAVE_CUSTOM_ERROR_MESSAGE_MAX	256
#define SYS_SAVE_MAX_LIST_PARAMETER		8
#define SYS_SAVE_MAX_TITLE			128
#define SYS_SAVE_MAX_SUBTITLE			128
#define SYS_SAVE_MAX_DETAIL			1024
#define SYS_SAVE_MAX_PROTECTED_FILE_ID		16

#define SYS_SAVE_DIRNAME_SIZE                   32
#define SYS_SAVE_FILENAME_SIZE                  13
#define SYS_SAVE_SECUREFILEID_SIZE              16
#define SYS_SAVE_PREFIX_SIZE                    256
#define SYS_SAVE_LISTITEM_MAX                   2048
#define SYS_SAVE_SECUREFILE_MAX                 113
#define SYS_SAVE_DIRLIST_MAX                    2048
#define SYS_SAVE_INVALID_MESSAGE_MAX            256
#define SYS_SAVE_INDICATORMSG_MAX		64

#define SYS_SAVE_SYSP_TITLE_SIZE		128
#define SYS_SAVE_SYSP_SUBTITLE_SIZE		128
#define SYS_SAVE_SYSP_DETAIL_SIZE		1024
#define SYS_SAVE_SYSP_LPARAM_SIZE		8

/* Current version value for the save data */
#define SYS_SAVE_CURRENT_VERSION 0

/* Result values for the callback */
#define SYS_SAVE_CALLBACK_RESULT_DONE_NOCONFIRM	2
#define SYS_SAVE_CALLBACK_RESULT_DONE		1
#define SYS_SAVE_CALLBACK_RESULT_CONTINUE 	0
#define SYS_SAVE_CALLBACK_RESULT_NO_SPACE_LEFT	-1
#define SYS_SAVE_CALLBACK_RESULT_ERROR		-2
#define SYS_SAVE_CALLBACK_RESULT_CORRUPTED	-3
#define SYS_SAVE_CALLBACK_RESULT_NOT_FOUND	-4
#define SYS_SAVE_CALLBACK_RESULT_ERROR_CUSTOM	-5

/* Flags for the binding information */
#define SYS_SAVE_BIND_NO_ERROR		0x00
#define SYS_SAVE_BIND_ANOTHER_CONSOLE	0x01
#define SYS_SAVE_BIND_ANOTHER_DISC	0x02
#define SYS_SAVE_BIND_ANOTHER_APP	0x04
#define SYS_SAVE_BIND_NO_USER_INFO	0x08
#define SYS_SAVE_BIND_OTHER_USER	0x10

#define SYS_SAVE_BIND_OK		0x00
#define SYS_SAVE_BIND_ERR_CONSOLE	0x01
#define SYS_SAVE_BIND_ERR_DISC		0x02
#define SYS_SAVE_BIND_ERR_APP		0x04
#define SYS_SAVE_BIND_ERR_NOACCOUNTID	0x08
#define SYS_SAVE_BIND_ERR_NOUSER	0x08
#define SYS_SAVE_BIND_ERR_ACCOUNTID	0x10
#define SYS_SAVE_BIND_ERR_OTHERS	0x10
#define SYS_SAVE_BIND_ERR_NOUSERID	0x20
#define SYS_SAVE_BIND_ERR_USERID	0x40
#define SYS_SAVE_BIND_ERR_NOOWNER	0x100
#define SYS_SAVE_BIND_ERR_OWNER		0x200
#define SYS_SAVE_BIND_ERR_LOCALOWNER	0x400

/* Return values from the API calls */
#define SYS_SAVE_RETURN_DONE			0
#define SYS_SAVE_RETURN_CANCELED		1

#define SYS_SAVE_RETURN_OK			0
#define SYS_SAVE_RETURN_CANCEL			1

#define SYS_SAVE_RETURN_ERROR			0x8002b400

#define SYS_SAVE_RETURN_ERROR_CALLBACK		(SYS_SAVE_RETURN_ERROR | 1)
#define SYS_SAVE_RETURN_ERROR_HDD_ERROR		(SYS_SAVE_RETURN_ERROR | 2)
#define SYS_SAVE_RETURN_ERROR_INTERNAL		(SYS_SAVE_RETURN_ERROR | 3)
#define SYS_SAVE_RETURN_ERROR_INVALID_ARG	(SYS_SAVE_RETURN_ERROR | 4)
#define SYS_SAVE_RETURN_ERROR_NO_SPACE_LEFT	(SYS_SAVE_RETURN_ERROR | 5)
#define SYS_SAVE_RETURN_ERROR_CORRUPTED		(SYS_SAVE_RETURN_ERROR | 6)
#define SYS_SAVE_RETURN_ERROR_FAILED		(SYS_SAVE_RETURN_ERROR | 7)
#define SYS_SAVE_RETURN_ERROR_ALREADY_IN_USE	(SYS_SAVE_RETURN_ERROR | 8)
#define SYS_SAVE_RETURN_ERROR_NOUSER		(SYS_SAVE_RETURN_ERROR | 9)
#define SYS_SAVE_RETURN_ERROR_SIZEOVER		(SYS_SAVE_RETURN_ERROR | a)
#define SYS_SAVE_RETURN_ERROR_NODATA		(SYS_SAVE_RETURN_ERROR | b)
#define SYS_SAVE_RETURN_ERROR_NOTSUPPORTED	(SYS_SAVE_RETURN_ERROR | c)

#define SYS_SAVE_OPTION_NONE                    (0)
#define SYS_SAVE_OPTION_NOCONFIRM               (1<<0)

#define SYS_SAVE_ATTR_NORMAL                    (0)
#define SYS_SAVE_ATTR_NODUPE                    (1)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  SYS_SAVE_SORT_TYPE_TIMESTAMP = 0,
  SYS_SAVE_SORT_TYPE_TITLE,
} sysSaveSortType;

typedef enum {
  SYS_SAVE_SORT_ORDER_DESCENDING = 0,
  SYS_SAVE_SORT_ORDER_ASCENDING,
} sysSaveSortOrder;

typedef enum {
  SYS_SAVE_FOCUS_POSITION_DIRECTORY_NAME = 0,
  SYS_SAVE_FOCUS_POSITION_LIST_HEAD,
  SYS_SAVE_FOCUS_POSITION_LIST_TAIL,
  SYS_SAVE_FOCUS_POSITION_LATEST,
  SYS_SAVE_FOCUS_POSITION_OLDEST,
  SYS_SAVE_FOCUS_POSITION_NEW_SAVE,
} sysSaveFocusPosition;

typedef enum {
  SYS_SAVE_NEW_SAVE_POSITION_TOP = 0,
  SYS_SAVE_NEW_SAVE_POSITION_BOTTOM,
} sysSaveNewSavePosition;

typedef enum {
  SYS_SAVE_FILETYPE_PROTECTED_FILE = 0,
  SYS_SAVE_FILETYPE_STANDARD_FILE,
  SYS_SAVE_FILETYPE_CONTENT_ICON0,
  SYS_SAVE_FILETYPE_CONTENT_ICON1,
  SYS_SAVE_FILETYPE_CONTENT_PIC1,
  SYS_SAVE_FILETYPE_CONTENT_SND0,
} sysSaveFileType;

typedef enum {
  SYS_SAVE_RECREATE_MODE_OVERWRITE_CORRUPTED = 0,
  SYS_SAVE_RECREATE_MODE_OVERWRITE_NOT_CORRUPTED,
  SYS_SAVE_RECREATE_MODE_DELETE
} sysSaveRecreateMode;

typedef enum {
  SYS_SAVE_FILE_OPERATION_READ = 0,
  SYS_SAVE_FILE_OPERATION_WRITE,
  SYS_SAVE_FILE_OPERATION_DELETE,
  SYS_SAVE_FILE_OPERATION_WRITE_NOTRUNC
} sysSaveFileOperation;

typedef enum {
  SYS_SAVE_ERROR_DIALOG_NONE = 0,
  SYS_SAVE_ERROR_DIALOG_SHOW,
  SYS_SAVE_ERROR_DIALOG_SHOW_ONCE,
} sysSaveErrorDialogMode;

typedef struct {
  sysSaveSortType sortType;
  sysSaveSortOrder sortOrder;
  char *pathPrefix ATTRIBUTE_PRXPTR;
  void *reserved ATTRIBUTE_PRXPTR;
} sysSaveListSettings;

typedef struct {
  u32 maxDirectories;
  u32 maxFiles;
  u32 reserved[6];
  u32 bufferSize;
  void *buffer ATTRIBUTE_PRXPTR;
} sysSaveBufferSettings;

typedef struct {
  s32 result;
  u32 incrementProgress;
  s32 missingSpaceKB;
  char *customErrorMessage ATTRIBUTE_PRXPTR;
  void *user_data ATTRIBUTE_PRXPTR;
} sysSaveCallbackResult;

typedef struct {
  char directoryName[SYS_SAVE_MAX_DIRECTORY_NAME];
  char listParameter[SYS_SAVE_MAX_LIST_PARAMETER];
  u8 reserved[8];
} sysSaveDirectoryList;

typedef struct {
  char *title ATTRIBUTE_PRXPTR;
  u32 iconBufferSize;
  void *iconBuffer ATTRIBUTE_PRXPTR;
  void *reserved ATTRIBUTE_PRXPTR;
} sysSaveNewSaveGameIcon;

typedef struct {
  sysSaveNewSavePosition position;
  char *directoryName ATTRIBUTE_PRXPTR;
  sysSaveNewSaveGameIcon *icon ATTRIBUTE_PRXPTR;
  void *reserved ATTRIBUTE_PRXPTR;
} sysSaveNewSaveGame;

typedef struct {
  /* total directories found */
  u32 maxDirectories;
  /* number of directories in directoryList */
  u32 numDirectories;
  /* list of directories found */
  sysSaveDirectoryList *directoryList ATTRIBUTE_PRXPTR;
  u8 reserved[64];
} sysSaveListIn;

typedef struct {
  /* Where to put the focus of the cursor */
  sysSaveFocusPosition focus;
  /* The name of the directory to focus to */
  char *focusDirectoryName ATTRIBUTE_PRXPTR;
  u32 numDirectories;
  sysSaveDirectoryList *directoryList ATTRIBUTE_PRXPTR;
  sysSaveNewSaveGame *newSaveGame ATTRIBUTE_PRXPTR;
  void *reserved ATTRIBUTE_PRXPTR;
} sysSaveListOut;

typedef struct {
  time_t atime;
  time_t mtime;
  time_t ctime;
  char directoryName[SYS_SAVE_MAX_DIRECTORY_NAME];
} sysSaveDirectoryStatus;

typedef struct {
  char title[SYS_SAVE_MAX_TITLE];
  char subtitle[SYS_SAVE_MAX_SUBTITLE];
  char detail[SYS_SAVE_MAX_DETAIL];
  u32 copyProtected;
  u32 parentalLevel;
  char listParameter[SYS_SAVE_MAX_LIST_PARAMETER];
  u8 reserved[256];
} sysSaveSystemFileParam;

typedef struct {
  sysSaveFileType fileType;
  u8 reserved1[4];
  u64 fileSize;
  time_t atime;
  time_t mtime;
  time_t ctime;
  char filename[SYS_SAVE_MAX_FILE_NAME];
  u8 reserved2[3];
} sysSaveFileStatus;

typedef struct {
  s32 freeSpaceKB;
  u32 isNew;
  sysSaveDirectoryStatus directoryStatus;
  sysSaveSystemFileParam getParam;
  u32 bindingInformation;
  /* Size of the save data */
  s32 sizeKB;
  /* Size of system file */
  s32 systemSizeKB;
  /* total files in the save data */
  u32 totalFiles;
  /* Number of files in the the file list */
  u32 numFiles;
  sysSaveFileStatus *fileList ATTRIBUTE_PRXPTR;
  u8 reserved[64];
} sysSaveStatusIn;

typedef struct {
  u32 dispPosition;
  u32 dispMode;
  char *dispMsg ATTRIBUTE_PRXPTR;
  u32 picBufSize;
  void *picBuf ATTRIBUTE_PRXPTR;
  void *reserved ATTRIBUTE_PRXPTR;
} sysSaveAutoIndicator;

typedef struct {
  sysSaveSystemFileParam *setParam ATTRIBUTE_PRXPTR;
  sysSaveRecreateMode recreateMode;
  sysSaveAutoIndicator *indicator ATTRIBUTE_PRXPTR;
} sysSaveStatusOut;

typedef struct {
  u32 previousOperationResultSize;
  u8 reserved[64];
} sysSaveFileIn;

typedef struct {
  sysSaveFileOperation fileOperation;
  void *reserved ATTRIBUTE_PRXPTR;
  sysSaveFileType fileType;
  u8 protectedFileID[SYS_SAVE_MAX_PROTECTED_FILE_ID];
  char *filename ATTRIBUTE_PRXPTR;
  u32 offset;
  u32 size;
  u32 bufferSize;
  void *buffer ATTRIBUTE_PRXPTR;
} sysSaveFileOut;

typedef struct {
  char *directoryName ATTRIBUTE_PRXPTR;
  sysSaveNewSaveGameIcon *icon ATTRIBUTE_PRXPTR;
  void *reserved ATTRIBUTE_PRXPTR;
} sysSaveFixedOut;

typedef struct {
  s32 result;
  char dirName[SYS_SAVE_DIRNAME_SIZE];
  s32 sizeKB;
  s32 hddFreeKB;
  char reserved[64];
} sysSaveDoneGet;


typedef void (* sysSaveListCallback) (sysSaveCallbackResult *result,
    sysSaveListIn *in, sysSaveListOut *out);

typedef void (* sysSaveStatusCallback) (sysSaveCallbackResult *result,
    sysSaveStatusIn *in, sysSaveStatusOut *out);

typedef void (* sysSaveFileCallback) (sysSaveCallbackResult *result,
    sysSaveFileIn *in, sysSaveFileOut *out);

typedef void (* sysSaveFixedCallback) (sysSaveCallbackResult *result,
    sysSaveListIn *in, sysSaveFixedOut *out);

typedef void (* sysSaveDoneCallback) (sysSaveCallbackResult *result,
    sysSaveDoneGet *get);


s32 sysSaveListLoad2 (u32 version,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveListCallback listCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data);

s32 sysSaveListSave2 (u32 version,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveListCallback listCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data);

s32 sysSaveListAutoLoad (u32 version,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveFixedCallback fixedCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data);

s32 sysSaveListAutoSave (u32 version,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveFixedCallback fixedCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data);

s32 sysSaveFixedLoad2 (u32 version,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveFixedCallback fixedCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data);

s32 sysSaveFixedSave2 (u32 version,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveFixedCallback fixedCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data);

s32 sysSaveAutoLoad2 (s32 version,
    const char *directoryName,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveBufferSettings *bufferSettings,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data);

s32 sysSaveAutoSave2 (s32 version,
    const char *directoryName,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveBufferSettings *bufferSettings,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data);

s32 sysSaveDelete2(sys_mem_container_t container);

s32 sysSaveListDelete(sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveListCallback listCb,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveFixedDelete(sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserListSave(u32 version,
      u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveListCallback listCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserListLoad(u32 version,
      u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveListCallback listCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserFixedSave(u32 version,
      u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserFixedLoad(u32 version,
      u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserAutoSave(u32 version,
      u32 userId,
      const char *dirName,
      u32 errDialog,
      sysSaveBufferSettings *bufferSettings,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserAutoLoad(u32 version,
      u32 userId,
      const char *dirName,
      u32 errDialog,
      sysSaveBufferSettings *bufferSettings,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserListAutoSave(u32 version,
      u32 userId,
      u32 errDialog,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserListAutoLoad(u32 version,
      u32 userId,
      u32 errDialog,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserListImport(u32 userId,
      sysSaveListSettings *listSettings,
      u32 maxSizeKB,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserListExport(u32 userId,
      sysSaveListSettings *listSettings,
      u32 maxSizeKB,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserFixedImport(u32 userId,
      const char *dirName,
      u32 maxSizeKB,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserFixedExport(u32 userId,
      const char *dirName,
      u32 maxSizeKB,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserListDelete(u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveListCallback listCb,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data);

s32 sysSaveUserFixedDelete(u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data);

#ifdef __cplusplus
	}
#endif

#endif
