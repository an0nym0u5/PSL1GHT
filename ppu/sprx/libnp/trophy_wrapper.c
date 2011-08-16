#include <stdio.h>
#include <stdlib.h>
#include <ppu-asm.h>

#include <np/trophy.h>

/* sysUtil trophy support */
extern s32 sysTrophyInit(void *pool, size_t poolSize, sys_mem_container_t container, uint64_t options);
extern s32 sysTrophyTerm(void);
extern s32 sysTrophyCreateHandle(sysTrophyHandle *handle);
extern s32 sysTrophyDestroyHandle(sysTrophyHandle handle);
extern s32 sysTrophyAbortHandle(sysTrophyHandle handle);
extern s32 sysTrophyCreateContext(sysTrophyContext *context, const sysCommunicationId *commId, const sysCommunicationSignature *commSign, uint64_t options);
extern s32 sysTrophyGetRequiredDiskSpace(sysTrophyContext context, sysTrophyHandle handle, uint64_t *reqspace, uint64_t options);
extern s32 sysTrophyRegisterContextEx(sysTrophyContext context,sysTrophyHandle handle, opd32 *statusCb, void *arg, uint64_t options);
extern s32 sysTrophyDestroyContext(sysTrophyContext context);
extern s32 sysTrophyGetGameInfo(sysTrophyContext context, sysTrophyHandle handle, sysTrophyGameDetails *details, sysTrophyGameData *data);
extern s32 sysTrophyGetUnlockState(sysTrophyContext context, sysTrophyHandle handle, sysTrophyFlagArray *flags, size_t *count);
extern s32 sysTrophyGetInfo(sysTrophyContext context, sysTrophyHandle handle, sysTrophyId trophyId, sysTrophyDetails *details, sysTrophyData *data);
extern s32 sysTrophyGetGameIcon(sysTrophyContext context, sysTrophyHandle handle, void *buffer, size_t *size);
extern s32 sysTrophyGetIcon(sysTrophyContext context, sysTrophyHandle handle, sysTrophyId trophyId, void *buffer, size_t *size);
extern s32 sysTrophySetSoundLevel(sysTrophyContext context, sysTrophyHandle handle, uint32_t level, uint64_t options);
extern s32 sysTrophyUnlock(sysTrophyContext context, sysTrophyHandle handle, sysTrophyId trophyId, sysTrophyId *platinumId);
extern s32 sysTrophyGetGameProgress(sysTrophyContext context, sysTrophyHandle handle, int32_t *percentage);

/* sysTrophy wrapper function */
s32 sysTrophyRegisterContext(sysTrophyContext context,
       sysTrophyHandle handle,
       sysTrophyStatusCallback statusCb,
       void *arg,
       uint64_t options
       )
{
  return sysTrophyRegisterContextEx (context, handle, (opd32*) __get_opd32(statusCb), arg, options);
}

