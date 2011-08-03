#ifndef __LV2_SYSUTIL_TROPHY_H__
#define __LV2_SYSUTIL_TROPHY_H__

#include <ppu-types.h>
#include <time.h>

/* type */
#define SYS_TROPHY_GRADE_UNKNOWN			(0)
#define SYS_TROPHY_GRADE_PLATINUM			(1)
#define SYS_TROPHY_GRADE_GOLD				(2)
#define SYS_TROPHY_GRADE_SILVER				(3)
#define SYS_TROPHY_GRADE_BRONZE				(4)

/* status */
#define SYS_TROPHY_STATUS_UNKNOWN			(0)
#define SYS_TROPHY_STATUS_NOT_INSTALLED			(1)
#define SYS_TROPHY_STATUS_DATA_CORRUPT			(2)
#define SYS_TROPHY_STATUS_INSTALLED			(3)
#define SYS_TROPHY_STATUS_REQUIRES_UPDATE		(4)
#define SYS_TROPHY_STATUS_PROCESSING_SETUP		(5)
#define SYS_TROPHY_STATUS_PROCESSING_PROGRESS		(6)
#define SYS_TROPHY_STATUS_PROCESSING_FINALIZE		(7)
#define SYS_TROPHY_STATUS_PROCESSING_COMPLETE		(8)
#define SYS_TROPHY_STATUS_CHANGES_DETECTED		(9)

/* sizes */
#define SYS_TROPHY_TITLE_MAX_SIZE			(128)
#define SYS_TROPHY_GAME_DESCR_MAX_SIZE			(1024)
#define SYS_TROPHY_NAME_MAX_SIZE			(128)
#define SYS_TROPHY_DESCR_MAX_SIZE			(1024)

#define SYS_TROPHY_INVALID_CONTEXT			(0)
#define SYS_TROPHY_INVALID_HANDLE			(0)
#define SYS_TROPHY_INVALID_TROPHY_ID			(-1)
#define SYS_COMMUNICATION_SIGNATURE_SIZE		(160)

/* options */
#define SYS_TROPHY_OPTIONS_CREATE_CONTEXT_READ_ONLY		(0x0000000000000001)
#define SYS_TROPHY_OPTIONS_REGISTER_CONTEXT_SHOW_ERROR_EXIT	(0x0000000000000001)

/* trophy flag array */
#define SYS_TROPHY_FLAG_SETSIZE				(128)
#define SYS_TROPHY_FLAG_BITS				(sizeof(sysTrophyFlagMask) * 8)
#define SYS_TROPHY_FLAG_BITS_ALL			((sysTrophyFlagMask)-1)
#define SYS_TROPHY_FLAG_BITS_SHIFT			(5)
#define SYS_TROPHY_FLAG_BITS_MASK			(SYS_TROPHY_FLAG_BITS - 1)
#define SYS_TROPHY_FLAG_BITS_MAX			(SYS_TROPHY_FLAG_SETSIZE - 1)

#define SYS_TROPHY_FLAG_SET(n, p) \
	((p)->flag_bits[(n) >> SYS_TROPHY_FLAG_BITS_SHIFT] |= (1 << ((n) & SYS_TROPHY_FLAG_BITS_MASK)))
#define SYS_TROPHY_FLAG_CLR(n, p) \
	((p)->flag_bits[(n) >> SYS_TROPHY_FLAG_BITS_SHIFT] &= ~(1 << ((n) & SYS_TROPHY_FLAG_BITS_MASK)))
#define SYS_TROPHY_FLAG_ISSET(n, p) \
	((p)->flag_bits[(n) >> SYS_TROPHY_FLAG_BITS_SHIFT] & (1 << ((n) & SYS_TROPHY_FLAG_BITS_MASK)))
#define SYS_TROPHY_FLAG_ZERO(p) do { \
	sysTrophyFlagArray *__fa = (p); \
	uint32_t __i; \
	for(__i = 0; __i < (SYS_TROPHY_FLAG_SETSIZE >> SYS_TROPHY_FLAG_BITS_SHIFT); __i++) \
		__fa->flag_bits[__i] = 0; \
	} while(0)
#define SYS_TROPHY_FLAG_SET_ALL(p) do { \
	sysTrophyFlagArray *__fa = (p); \
	uint32_t __i; \
	for(__i = 0; __i < (SYS_TROPHY_FLAG_SETSIZE >> SYS_TROPHY_FLAG_BITS_SHIFT); __i++) \
		__fa->flag_bits[__i] = SYS_TROPHY_FLAG_BITS_ALL; \
	} while(0)

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t sysTrophyFlagMask;

typedef struct sysTrophyFlagArray {
	sysTrophyFlagMask flag_bits[SYS_TROPHY_FLAG_SETSIZE >> SYS_TROPHY_FLAG_BITS_SHIFT];
} sysTrophyFlagArray;

typedef int32_t sysTrophyId;
typedef uint32_t sysTrophyContext;
typedef uint32_t sysTrophyHandle;
typedef uint32_t sysTrophyStatus;
typedef uint32_t sysTrophyGrade;

typedef struct sysRtcTick {
	uint64_t tick;
} sysRtcTick;

typedef struct sysCommunicationId {
	char data[9];
	char term;
	uint8_t num;
	char dummy;
} sysCommunicationId;
typedef sysCommunicationId sysTitleId;

typedef struct sysCommunicationSignature {
	uint8_t data[SYS_COMMUNICATION_SIGNATURE_SIZE];
} sysCommunicationSignature;

typedef struct sysTrophyGameDetails {
	size_t numTrophies;
	size_t numPlatinum;
	size_t numGold;
	size_t numSilver;
	size_t numBronze;
	char title[SYS_TROPHY_TITLE_MAX_SIZE];
	char description[SYS_TROPHY_GAME_DESCR_MAX_SIZE];
	uint8_t reserved[4];
} sysTrophyGameDetails;

typedef struct sysTrophyGameData {
	size_t unlockedTrophies;
	size_t unlockedPlatinum;
	size_t unlockedGold;
	size_t unlockedSilver;
	size_t unlockedBronze;
} sysTrophyGameData;

typedef struct sysTrophyDetails {
	sysTrophyId trophyId;
	sysTrophyGrade trophyGrade;
	char name[SYS_TROPHY_NAME_MAX_SIZE];
	char description[SYS_TROPHY_DESCR_MAX_SIZE];
	bool hidden;
	uint8_t reserved[3];
} sysTrophyDetails;

typedef struct sysTrophyData {
	sysRtcTick timestamp;
	sysTrophyId trophyId;
	bool unlocked;
	uint8_t reserved[3];
} sysTrophyData;

typedef int (*sysTrophyStatusCallback)(
	sysTrophyContext context,
	sysTrophyStatus status,
	int completed,
	int total,
	void *arg
	);

/* sysTrophy functions */
s32 sysTrophyInit(void *pool, size_t poolSize,
    sys_mem_container_t container, uint64_t options);
s32 sysTrophyTerm(void);
s32 sysTrophyCreateHandle(sysTrophyHandle *handle);
s32 sysTrophyDestroyHandle(sysTrophyHandle handle);
s32 sysTrophyAbortHandle(sysTrophyHandle handle);
s32 sysTrophyCreateContext(sysTrophyContext *context,
    const sysCommunicationId *commId, const sysCommunicationSignature *commSign,
    uint64_t options);
s32 sysTrophyGetRequiredDiskSpace(sysTrophyContext context,
    sysTrophyHandle handle, uint64_t *reqspace, uint64_t options);
s32 sysTrophyRegisterContext(sysTrophyContext context,sysTrophyHandle handle,
    sysTrophyStatusCallback statusCb, void *arg, uint64_t options);
s32 sysTrophyDestroyContext(sysTrophyContext context);
s32 sysTrophyGetGameInfo(sysTrophyContext context, sysTrophyHandle handle,
    sysTrophyGameDetails *details, sysTrophyGameData *data);
s32 sysTrophyGetUnlockState(sysTrophyContext context,
    sysTrophyHandle handle, sysTrophyFlagArray *flags, size_t *count);
s32 sysTrophyGetInfo(sysTrophyContext context, sysTrophyHandle handle,
    sysTrophyId trophyId, sysTrophyDetails *details, sysTrophyData *data);
s32 sysTrophyGetGameIcon(sysTrophyContext context, sysTrophyHandle handle,
    void *buffer, size_t *size);
s32 sysTrophyGetIcon(sysTrophyContext context, sysTrophyHandle handle,
    sysTrophyId trophyId, void *buffer, size_t *size);
s32 sysTrophySetSoundLevel(sysTrophyContext context, sysTrophyHandle handle,
    uint32_t level, uint64_t options);
s32 sysTrophyUnlock(sysTrophyContext context, sysTrophyHandle handle,
    sysTrophyId trophyId, sysTrophyId *platinumId);
s32 sysTrophyGetGameProgress(sysTrophyContext context, sysTrophyHandle handle,
    int32_t *percentage);

#ifdef __cplusplus
        }
#endif

#endif

