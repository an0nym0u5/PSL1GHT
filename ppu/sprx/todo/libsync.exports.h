#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(syncBarrierInitialize, 0x07254fda); /* cellSync */
EXPORT(syncBarrierNotify, 0xf06a6415); /* cellSync */
EXPORT(syncBarrierTryNotify, 0x268edd6d); /* cellSync */
EXPORT(syncBarrierTryWait, 0x6c272124); /* cellSync */
EXPORT(syncBarrierWait, 0x35f21355); /* cellSync */
EXPORT(_syncLFQueueAttachLv2EventQueue, 0x54fc2032); /* cellSync */
EXPORT(syncLFQueueClear, 0x2af0c515); /* cellSync */
EXPORT(_syncLFQueueCompletePopPointer, 0xfe74e8e7); /* cellSync */
EXPORT(_syncLFQueueCompletePopPointer2, 0x7a51deee); /* cellSync */
EXPORT(_syncLFQueueCompletePushPointer, 0x4e88c68d); /* cellSync */
EXPORT(_syncLFQueueCompletePushPointer2, 0x35bbdad2); /* cellSync */
EXPORT(syncLFQueueDepth, 0xe18c273c); /* cellSync */
EXPORT(_syncLFQueueDetachLv2EventQueue, 0x811d148e); /* cellSync */
EXPORT(syncLFQueueGetDirection, 0xd59aa307); /* cellSync */
EXPORT(syncLFQueueGetEntrySize, 0x0c7cb9f7); /* cellSync */
EXPORT(_syncLFQueueGetPopPointer, 0x74c37666); /* cellSync */
EXPORT(_syncLFQueueGetPopPointer2, 0x46356fe0); /* cellSync */
EXPORT(_syncLFQueueGetPushPointer, 0xe9bf2110); /* cellSync */
EXPORT(_syncLFQueueGetPushPointer2, 0x6bb4ef9d); /* cellSync */
EXPORT(_syncLFQueueGetSignalAddress, 0xaff7627a); /* cellSync */
EXPORT(syncLFQueueInitialize, 0xaa355278); /* cellSync */
EXPORT(_syncLFQueuePopBody, 0xe1bc7add); /* cellSync */
EXPORT(_syncLFQueuePushBody, 0xba5961ca); /* cellSync */
EXPORT(syncLFQueueSize, 0x167ea63e); /* cellSync */
EXPORT(syncMutexInitialize, 0xa9072dee); /* cellSync */
EXPORT(syncMutexLock, 0x1bb675c2); /* cellSync */
EXPORT(syncMutexTryLock, 0xd06918c4); /* cellSync */
EXPORT(syncMutexUnlock, 0x91f2b7b0); /* cellSync */
EXPORT(syncQueueClear, 0xa5362e73); /* cellSync */
EXPORT(syncQueueInitialize, 0x3929948d); /* cellSync */
EXPORT(syncQueuePeek, 0x48154c9b); /* cellSync */
EXPORT(syncQueuePop, 0x4da6d7e0); /* cellSync */
EXPORT(syncQueuePush, 0x5ae841e5); /* cellSync */
EXPORT(syncQueueSize, 0x4da349b2); /* cellSync */
EXPORT(syncQueueTryPeek, 0x68af923c); /* cellSync */
EXPORT(syncQueueTryPop, 0xa58df87f); /* cellSync */
EXPORT(syncQueueTryPush, 0x705985cd); /* cellSync */
EXPORT(syncRwmInitialize, 0xfc48b03f); /* cellSync */
EXPORT(syncRwmRead, 0xcece771f); /* cellSync */
EXPORT(syncRwmTryRead, 0xa6669751); /* cellSync */
EXPORT(syncRwmTryWrite, 0xba5bee48); /* cellSync */
EXPORT(syncRwmWrite, 0xed773f5f); /* cellSync */


#endif
