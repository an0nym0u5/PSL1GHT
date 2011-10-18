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

