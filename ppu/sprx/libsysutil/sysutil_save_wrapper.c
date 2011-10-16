#include <stdio.h>
#include <stdlib.h>
#include <ppu-asm.h>

#include <sysutil/sysutil.h>
#include <sysutil/save.h>

/* sysSave functions */
extern s32 sysSaveListLoad2Ex (u32 version, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *listCb, opd32 *statusCb,
    opd32 *fileCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveListSave2Ex (u32 version, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *listCb, opd32 *statusCb,
    opd32 *fileCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveListAutoLoadEx (u32 version, sysSaveErrorDialogMode errorDialogMode,
    sysSaveListSettings *listSettings, sysSaveBufferSettings *bufferSettings,
    opd32 *fixedCb, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container,  void *user_data);
extern s32 sysSaveListAutoSaveEx (u32 version, sysSaveErrorDialogMode errorDialogMode,
    sysSaveListSettings *listSettings, sysSaveBufferSettings *bufferSettings,
    opd32 *fixedCb, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveFixedLoad2Ex (u32 version, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *fixedCb, opd32 *statusCb,
    opd32 *fileCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveFixedSave2Ex (u32 version, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *fixedCb, opd32 *statusCb,
    opd32 *fileCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveAutoLoad2Ex (s32 version, const char *directoryName,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveBufferSettings *bufferSettings, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveAutoSave2Ex (s32 version, const char *directoryName,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveBufferSettings *bufferSettings,
    opd32 *statusCb, opd32 *fileCb, sys_mem_container_t container, void *user_data);
/* NEW */
extern s32 sysSaveListDeleteEx(sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *listCb, opd32 *doneCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveFixedDeleteEx(sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *fixedCb, opd32 *doneCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserListSaveEx(u32 version, u32 userId, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *listCb, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserListLoadEx(u32 version, u32 userId, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *listCb, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserFixedSaveEx(u32 version, u32 userId, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *fixedCb, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserFixedLoadEx(u32 version, u32 userId, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *fixedCb, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserAutoSaveEx(u32 version, u32 userId, const char *dirName, u32 errDialog,
    sysSaveBufferSettings *bufferSettings, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserAutoLoadEx(u32 version, u32 userId, const char *dirName, u32 errDialog,
    sysSaveBufferSettings *bufferSettings, opd32 *statusCb, opd32 *fileCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserListAutoSaveEx(u32 version, u32 userId, u32 errDialog,
    sysSaveListSettings *listSettings, sysSaveBufferSettings *bufferSettings, opd32 *fixedCb,
    opd32 *statusCb, opd32 *fileCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserListAutoLoadEx(u32 version, u32 userId, u32 errDialog,
    sysSaveListSettings *listSettings, sysSaveBufferSettings *bufferSettings, opd32 *fixedCb,
    opd32 *statusCb, opd32 *fileCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserListImportEx(u32 userId, sysSaveListSettings *listSettings, u32 maxSizeKB,
    opd32 *doneCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserListExportEx(u32 userId, sysSaveListSettings *listSettings, u32 maxSizeKB,
    opd32 *doneCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserFixedImportEx(u32 userId, const char *dirName, u32 maxSizeKB,
    opd32 *doneCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserFixedExportEx(u32 userId, const char *dirName, u32 maxSizeKB,
    opd32 *doneCb, sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserListDeleteEx(u32 userId, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *listCb, opd32 *doneCb,
    sys_mem_container_t container, void *user_data);
extern s32 sysSaveUserFixedDeleteEx(u32 userId, sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings, opd32 *fixedCb, opd32 *doneCb,
    sys_mem_container_t container, void *user_data);
/* NEW */

/* sysSave wrapper functions */
s32 sysSaveListLoad2 (u32 version,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveListCallback listCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data)
{
  return sysSaveListLoad2Ex(version,
      listSettings, bufferSettings,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveListSave2 (u32 version,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveListCallback listCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data)
{
  return sysSaveListSave2Ex (version,
      listSettings, bufferSettings,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveListAutoLoad (u32 version,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveFixedCallback fixedCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data)
{
  return sysSaveListAutoLoadEx (version,
      errorDialogMode,listSettings, bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveListAutoSave (u32 version,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveFixedCallback fixedCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data)
{
  return sysSaveListAutoSaveEx (version,
      errorDialogMode, listSettings, bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveFixedLoad2 (u32 version,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveFixedCallback fixedCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data)
{
  return sysSaveFixedLoad2Ex (version,
      listSettings, bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveFixedSave2 (u32 version,
    sysSaveListSettings *listSettings,
    sysSaveBufferSettings *bufferSettings,
    sysSaveFixedCallback fixedCb,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data)
{
  return sysSaveFixedSave2Ex (version,
      listSettings, bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveAutoLoad2 (s32 version,
    const char *directoryName,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveBufferSettings *bufferSettings,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data)
{
  return sysSaveAutoLoad2Ex (version,
      directoryName, errorDialogMode, bufferSettings,
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveAutoSave2 (s32 version,
    const char *directoryName,
    sysSaveErrorDialogMode errorDialogMode,
    sysSaveBufferSettings *bufferSettings,
    sysSaveStatusCallback statusCb,
    sysSaveFileCallback fileCb,
    sys_mem_container_t container,
    void *user_data)
{
  return sysSaveAutoSave2Ex (version,
      directoryName, errorDialogMode, bufferSettings,
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}


/* NEW */
s32 sysSaveListDelete(sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveListCallback listCb,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveListDeleteEx(listSettings, bufferSettings,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(doneCb),
      container, user_data);
}

s32 sysSaveFixedDelete(sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveFixedDeleteEx(listSettings, bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(doneCb),
      container, user_data);
}

s32 sysSaveUserListSave(u32 version,
      u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveListCallback listCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserListSaveEx(version, userId, listSettings,
      bufferSettings,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveUserListLoad(u32 version,
      u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveListCallback listCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserListLoadEx(version, userId, listSettings,
      bufferSettings,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveUserFixedSave(u32 version,
      u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserFixedSaveEx(version, userId, listSettings,
      bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveUserFixedLoad(u32 version,
      u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserFixedLoadEx(version, userId, listSettings,
      bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveUserAutoSave(u32 version,
      u32 userId,
      const char *dirName,
      u32 errDialog,
      sysSaveBufferSettings *bufferSettings,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserAutoSaveEx(version, userId, dirName,
      errDialog, bufferSettings,
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveUserAutoLoad(u32 version,
      u32 userId,
      const char *dirName,
      u32 errDialog,
      sysSaveBufferSettings *bufferSettings,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserAutoLoadEx(version, userId, dirName,
      errDialog, bufferSettings,
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveUserListAutoSave(u32 version,
      u32 userId,
      u32 errDialog,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserListAutoSaveEx(version, userId, errDialog,
      listSettings, bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveUserListAutoLoad(u32 version,
      u32 userId,
      u32 errDialog,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveStatusCallback statusCb,
      sysSaveFileCallback fileCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserListAutoLoadEx(version, userId, errDialog,
      listSettings, bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statusCb),
      (opd32*) __get_opd32(fileCb),
      container, user_data);
}

s32 sysSaveUserListImport(u32 userId,
      sysSaveListSettings *listSettings,
      u32 maxSizeKB,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserListImportEx(userId, listSettings,
      maxSizeKB,
      (opd32*) __get_opd32(doneCb),
      container, user_data);
}

s32 sysSaveUserListExport(u32 userId,
      sysSaveListSettings *listSettings,
      u32 maxSizeKB,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserListExportEx(userId, listSettings,
      maxSizeKB,
      (opd32*) __get_opd32(doneCb),
      container, user_data);
}

s32 sysSaveUserFixedImport(u32 userId,
      const char *dirName,
      u32 maxSizeKB,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserFixedImportEx(userId, dirName,
      maxSizeKB,
      (opd32*) __get_opd32(doneCb),
      container, user_data);
}

s32 sysSaveUserFixedExport(u32 userId,
      const char *dirName,
      u32 maxSizeKB,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserFixedExportEx(userId, dirName,
      maxSizeKB,
      (opd32*) __get_opd32(doneCb),
      container, user_data);
}

s32 sysSaveUserListDelete(u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveListCallback listCb,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserListDeleteEx(userId, listSettings,
      bufferSettings,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(doneCb),
      container, user_data);
}

s32 sysSaveUserFixedDelete(u32 userId,
      sysSaveListSettings *listSettings,
      sysSaveBufferSettings *bufferSettings,
      sysSaveFixedCallback fixedCb,
      sysSaveDoneCallback doneCb,
      sys_mem_container_t container,
      void *user_data)
{
  return sysSaveUserFixedDeleteEx(userId, listSettings,
      bufferSettings,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(doneCb),
      container, user_data);
}
/* NEW */

