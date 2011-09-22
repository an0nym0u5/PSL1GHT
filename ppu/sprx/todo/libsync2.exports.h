#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(_sync2CondAttributeInitialize, 0xdf3c532a); /* cellSync2 */
EXPORT(sync2CondEstimateBufferSize, 0x5b1e4d7a); /* cellSync2 */
EXPORT(sync2CondFinalize, 0x63062249); /* cellSync2 */
EXPORT(sync2CondInitialize, 0x58be9a0f); /* cellSync2 */
EXPORT(sync2CondSignal, 0x871af804); /* cellSync2 */
EXPORT(sync2CondSignalAll, 0x8aae07c2); /* cellSync2 */
EXPORT(sync2CondWait, 0xbc96d751); /* cellSync2 */
EXPORT(_sync2MutexAttributeInitialize, 0x55836e73); /* cellSync2 */
EXPORT(sync2MutexEstimateBufferSize, 0xd51bfae7); /* cellSync2 */
EXPORT(sync2MutexFinalize, 0x27f2d61c); /* cellSync2 */
EXPORT(sync2MutexInitialize, 0xeb81a467); /* cellSync2 */
EXPORT(sync2MutexLock, 0xa400d82e); /* cellSync2 */
EXPORT(sync2MutexTryLock, 0xa69c749c); /* cellSync2 */
EXPORT(sync2MutexUnlock, 0x0080fe88); /* cellSync2 */
EXPORT(_sync2QueueAttributeInitialize, 0x5e00d433); /* cellSync2 */
EXPORT(sync2QueueEstimateBufferSize, 0xc08cc0f9); /* cellSync2 */
EXPORT(sync2QueueFinalize, 0x6af85cdf); /* cellSync2 */
EXPORT(sync2QueueGetDepth, 0xf0e1471c); /* cellSync2 */
EXPORT(sync2QueueGetSize, 0x12f0a27d); /* cellSync2 */
EXPORT(sync2QueueInitialize, 0xf125e044); /* cellSync2 */
EXPORT(sync2QueuePop, 0xd83ab0c9); /* cellSync2 */
EXPORT(sync2QueuePush, 0x7d967d91); /* cellSync2 */
EXPORT(sync2QueueTryPop, 0x0c9a0ea9); /* cellSync2 */
EXPORT(sync2QueueTryPush, 0x7fd479fe); /* cellSync2 */
EXPORT(sync2SemaphoreAcquire, 0xd1b0d146); /* cellSync2 */
EXPORT(_sync2SemaphoreAttributeInitialize, 0x2d77fe17); /* cellSync2 */
EXPORT(sync2SemaphoreEstimateBufferSize, 0x74c2780f); /* cellSync2 */
EXPORT(sync2SemaphoreFinalize, 0x164843a7); /* cellSync2 */
EXPORT(sync2SemaphoreGetCount, 0x4e2ee031); /* cellSync2 */
EXPORT(sync2SemaphoreInitialize, 0xc5dee254); /* cellSync2 */
EXPORT(sync2SemaphoreRelease, 0x0c2983ac); /* cellSync2 */
EXPORT(sync2SemaphoreTryAcquire, 0x5e4b0f87); /* cellSync2 */


#endif
