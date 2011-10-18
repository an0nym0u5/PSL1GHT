#include <stdio.h>
#include <stdlib.h>
#include <ppu-asm.h>

#include <sysutil/sysutil.h>
#include <sysutil/savedata.h>

/* sysSaveData functions */
extern s32 sysSaveDataListLoad2Ex (u32 version, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *listCb, opd32 *statCb,
    opd32 *fileCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataListSave2Ex (u32 version, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *listCb, opd32 *statCb,
    opd32 *fileCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataListAutoLoadEx (u32 version, u32 errDialog,
    sysSaveDataSetList *setList, sysSaveDataSetBuf *setBuf,
    opd32 *fixedCb, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container,  void *userdata);

extern s32 sysSaveDataListAutoSaveEx (u32 version, u32 errDialog,
    sysSaveDataSetList *setList, sysSaveDataSetBuf *setBuf,
    opd32 *fixedCb, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataFixedLoad2Ex (u32 version, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *fixedCb, opd32 *statCb,
    opd32 *fileCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataFixedSave2Ex (u32 version, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *fixedCb, opd32 *statCb,
    opd32 *fileCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataAutoLoad2Ex (s32 version, const char *dirName,
    u32 errDialog,
    sysSaveDataSetBuf *setBuf, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataAutoSave2Ex (s32 version, const char *dirName,
    u32 errDialog,
    sysSaveDataSetBuf *setBuf,
    opd32 *statCb, opd32 *fileCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataListDeleteEx(sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *listCb, opd32 *doneCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataFixedDeleteEx(sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *fixedCb, opd32 *doneCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserListSaveEx(u32 version, u32 userId, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *listCb, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserListLoadEx(u32 version, u32 userId, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *listCb, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserFixedSaveEx(u32 version, u32 userId, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *fixedCb, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserFixedLoadEx(u32 version, u32 userId, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *fixedCb, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserAutoSaveEx(u32 version, u32 userId, const char *dirName, u32 errDialog,
    sysSaveDataSetBuf *setBuf, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserAutoLoadEx(u32 version, u32 userId, const char *dirName, u32 errDialog,
    sysSaveDataSetBuf *setBuf, opd32 *statCb, opd32 *fileCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserListAutoSaveEx(u32 version, u32 userId, u32 errDialog,
    sysSaveDataSetList *setList, sysSaveDataSetBuf *setBuf, opd32 *fixedCb,
    opd32 *statCb, opd32 *fileCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserListAutoLoadEx(u32 version, u32 userId, u32 errDialog,
    sysSaveDataSetList *setList, sysSaveDataSetBuf *setBuf, opd32 *fixedCb,
    opd32 *statCb, opd32 *fileCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserListImportEx(u32 userId, sysSaveDataSetList *setList, u32 maxSizeKB,
    opd32 *doneCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserListExportEx(u32 userId, sysSaveDataSetList *setList, u32 maxSizeKB,
    opd32 *doneCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserFixedImportEx(u32 userId, const char *dirName, u32 maxSizeKB,
    opd32 *doneCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserFixedExportEx(u32 userId, const char *dirName, u32 maxSizeKB,
    opd32 *doneCb, sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserListDeleteEx(u32 userId, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *listCb, opd32 *doneCb,
    sys_mem_container_t container, void *userdata);

extern s32 sysSaveDataUserFixedDeleteEx(u32 userId, sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf, opd32 *fixedCb, opd32 *doneCb,
    sys_mem_container_t container, void *userdata);

/* sysSaveData wrapper functions */
s32 sysSaveDataListLoad2 (u32 version,
    sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf,
    sysSaveDataListCallback listCb,
    sysSaveDataStatCallback statCb,
    sysSaveDataFileCallback fileCb,
    sys_mem_container_t container,
    void *userdata)
{
  return sysSaveDataListLoad2Ex(version,
      setList, setBuf,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataListSave2 (u32 version,
    sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf,
    sysSaveDataListCallback listCb,
    sysSaveDataStatCallback statCb,
    sysSaveDataFileCallback fileCb,
    sys_mem_container_t container,
    void *userdata)
{
  return sysSaveDataListSave2Ex (version,
      setList, setBuf,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataListAutoLoad (u32 version,
    u32 errDialog,
    sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf,
    sysSaveDataFixedCallback fixedCb,
    sysSaveDataStatCallback statCb,
    sysSaveDataFileCallback fileCb,
    sys_mem_container_t container,
    void *userdata)
{
  return sysSaveDataListAutoLoadEx (version,
      errDialog,setList, setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataListAutoSave (u32 version,
    u32 errDialog,
    sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf,
    sysSaveDataFixedCallback fixedCb,
    sysSaveDataStatCallback statCb,
    sysSaveDataFileCallback fileCb,
    sys_mem_container_t container,
    void *userdata)
{
  return sysSaveDataListAutoSaveEx (version,
      errDialog, setList, setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataFixedLoad2 (u32 version,
    sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf,
    sysSaveDataFixedCallback fixedCb,
    sysSaveDataStatCallback statCb,
    sysSaveDataFileCallback fileCb,
    sys_mem_container_t container,
    void *userdata)
{
  return sysSaveDataFixedLoad2Ex (version,
      setList, setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataFixedSave2 (u32 version,
    sysSaveDataSetList *setList,
    sysSaveDataSetBuf *setBuf,
    sysSaveDataFixedCallback fixedCb,
    sysSaveDataStatCallback statCb,
    sysSaveDataFileCallback fileCb,
    sys_mem_container_t container,
    void *userdata)
{
  return sysSaveDataFixedSave2Ex (version,
      setList, setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataAutoLoad2 (u32 version,
    const char *dirName,
    u32 errDialog,
    sysSaveDataSetBuf *setBuf,
    sysSaveDataStatCallback statCb,
    sysSaveDataFileCallback fileCb,
    sys_mem_container_t container,
    void *userdata)
{
  return sysSaveDataAutoLoad2Ex (version,
      dirName, errDialog, setBuf,
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataAutoSave2 (u32 version,
    const char *dirName,
    u32 errDialog,
    sysSaveDataSetBuf *setBuf,
    sysSaveDataStatCallback statCb,
    sysSaveDataFileCallback fileCb,
    sys_mem_container_t container,
    void *userdata)
{
  return sysSaveDataAutoSave2Ex (version,
      dirName, errDialog, setBuf,
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataListDelete(sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataListCallback listCb,
      sysSaveDataDoneCallback doneCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataListDeleteEx(setList, setBuf,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(doneCb),
      container, userdata);
}

s32 sysSaveDataFixedDelete(sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataFixedCallback fixedCb,
      sysSaveDataDoneCallback doneCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataFixedDeleteEx(setList, setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(doneCb),
      container, userdata);
}

s32 sysSaveDataUserListSave(u32 version,
      u32 userId,
      sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataListCallback listCb,
      sysSaveDataStatCallback statCb,
      sysSaveDataFileCallback fileCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserListSaveEx(version, userId, setList,
      setBuf,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataUserListLoad(u32 version,
      u32 userId,
      sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataListCallback listCb,
      sysSaveDataStatCallback statCb,
      sysSaveDataFileCallback fileCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserListLoadEx(version, userId, setList,
      setBuf,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataUserFixedSave(u32 version,
      u32 userId,
      sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataFixedCallback fixedCb,
      sysSaveDataStatCallback statCb,
      sysSaveDataFileCallback fileCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserFixedSaveEx(version, userId, setList,
      setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataUserFixedLoad(u32 version,
      u32 userId,
      sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataFixedCallback fixedCb,
      sysSaveDataStatCallback statCb,
      sysSaveDataFileCallback fileCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserFixedLoadEx(version, userId, setList,
      setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataUserAutoSave(u32 version,
      u32 userId,
      const char *dirName,
      u32 errDialog,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataStatCallback statCb,
      sysSaveDataFileCallback fileCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserAutoSaveEx(version, userId, dirName,
      errDialog, setBuf,
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataUserAutoLoad(u32 version,
      u32 userId,
      const char *dirName,
      u32 errDialog,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataStatCallback statCb,
      sysSaveDataFileCallback fileCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserAutoLoadEx(version, userId, dirName,
      errDialog, setBuf,
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataUserListAutoSave(u32 version,
      u32 userId,
      u32 errDialog,
      sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataFixedCallback fixedCb,
      sysSaveDataStatCallback statCb,
      sysSaveDataFileCallback fileCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserListAutoSaveEx(version, userId, errDialog,
      setList, setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataUserListAutoLoad(u32 version,
      u32 userId,
      u32 errDialog,
      sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataFixedCallback fixedCb,
      sysSaveDataStatCallback statCb,
      sysSaveDataFileCallback fileCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserListAutoLoadEx(version, userId, errDialog,
      setList, setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(statCb),
      (opd32*) __get_opd32(fileCb),
      container, userdata);
}

s32 sysSaveDataUserListImport(u32 userId,
      sysSaveDataSetList *setList,
      u32 maxSizeKB,
      sysSaveDataDoneCallback doneCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserListImportEx(userId, setList,
      maxSizeKB,
      (opd32*) __get_opd32(doneCb),
      container, userdata);
}

s32 sysSaveDataUserListExport(u32 userId,
      sysSaveDataSetList *setList,
      u32 maxSizeKB,
      sysSaveDataDoneCallback doneCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserListExportEx(userId, setList,
      maxSizeKB,
      (opd32*) __get_opd32(doneCb),
      container, userdata);
}

s32 sysSaveDataUserFixedImport(u32 userId,
      const char *dirName,
      u32 maxSizeKB,
      sysSaveDataDoneCallback doneCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserFixedImportEx(userId, dirName,
      maxSizeKB,
      (opd32*) __get_opd32(doneCb),
      container, userdata);
}

s32 sysSaveDataUserFixedExport(u32 userId,
      const char *dirName,
      u32 maxSizeKB,
      sysSaveDataDoneCallback doneCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserFixedExportEx(userId, dirName,
      maxSizeKB,
      (opd32*) __get_opd32(doneCb),
      container, userdata);
}

s32 sysSaveDataUserListDelete(u32 userId,
      sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataListCallback listCb,
      sysSaveDataDoneCallback doneCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserListDeleteEx(userId, setList,
      setBuf,
      (opd32*) __get_opd32(listCb),
      (opd32*) __get_opd32(doneCb),
      container, userdata);
}

s32 sysSaveDataUserFixedDelete(u32 userId,
      sysSaveDataSetList *setList,
      sysSaveDataSetBuf *setBuf,
      sysSaveDataFixedCallback fixedCb,
      sysSaveDataDoneCallback doneCb,
      sys_mem_container_t container,
      void *userdata)
{
  return sysSaveDataUserFixedDeleteEx(userId, setList,
      setBuf,
      (opd32*) __get_opd32(fixedCb),
      (opd32*) __get_opd32(doneCb),
      container, userdata);
}

