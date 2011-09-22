#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(spursCreateJobQueue, 0xf244e799); /* cellSpursJq */
EXPORT(spursCreateJobQueueWithJobDescriptorPool, 0x983be7fc); /* cellSpursJq */
EXPORT(spursJobQueueAllocateJobDescriptorBody, 0x0d69929e); /* cellSpursJq */
EXPORT(spursJobQueuePort2CopyPushJobBody, 0xc39173a4); /* cellSpursJq */
EXPORT(spursJobQueuePort2PushAndReleaseJobBody, 0xe1731df3); /* cellSpursJq */
EXPORT(spursJobQueuePort2PushJobBody, 0xcf89f218); /* cellSpursJq */
EXPORT(spursJobQueuePort2PushJobListBody, 0xb53436e7); /* cellSpursJq */
EXPORT(spursJobQueuePortCopyPushBody, 0x46c3fb5a); /* cellSpursJq */
EXPORT(spursJobQueuePortCopyPushJobBody, 0x1917359d); /* cellSpursJq */
EXPORT(spursJobQueuePortCopyPushJobBody2, 0xef66c4b7); /* cellSpursJq */
EXPORT(spursJobQueuePortPushBody, 0x4e1a17a6); /* cellSpursJq */
EXPORT(spursJobQueuePortPushFlush, 0xbd1c5d6b); /* cellSpursJq */
EXPORT(spursJobQueuePortPushJobBody, 0x85cd04cd); /* cellSpursJq */
EXPORT(spursJobQueuePortPushJobBody2, 0x90e392cf); /* cellSpursJq */
EXPORT(spursJobQueuePortPushJobListBody, 0x1b6eea7e); /* cellSpursJq */
EXPORT(spursJobQueuePortPushSync, 0x9396be1d); /* cellSpursJq */
EXPORT(spursJobQueuePushAndReleaseJobBody, 0x1da890c7); /* cellSpursJq */
EXPORT(spursJobQueuePushBody, 0x99316997); /* cellSpursJq */
EXPORT(spursJobQueuePushFlush, 0xdf0120c2); /* cellSpursJq */
EXPORT(spursJobQueuePushJob2Body, 0x36d0a53c); /* cellSpursJq */
EXPORT(spursJobQueuePushJobBody, 0xc4843b74); /* cellSpursJq */
EXPORT(spursJobQueuePushJobBody2, 0x98203e3c); /* cellSpursJq */
EXPORT(spursJobQueuePushJobListBody, 0xaf1c7a1d); /* cellSpursJq */
EXPORT(spursJobQueuePushSync, 0x701fd8a9); /* cellSpursJq */
EXPORT(spursGetJobQueueId, 0xc343ee10); /* cellSpursJq */
EXPORT(spursJobQueueAttributeInitialize, 0x43ddab4f); /* cellSpursJq */
EXPORT(spursJobQueueAttributeSetDoBusyWaiting, 0x0582338a); /* cellSpursJq */
EXPORT(spursJobQueueAttributeSetGrabParameters, 0xe70f874e); /* cellSpursJq */
EXPORT(spursJobQueueAttributeSetIsHaltOnError, 0xff03cc79); /* cellSpursJq */
EXPORT(spursJobQueueAttributeSetIsJobTypeMemoryCheck, 0x742cec0d); /* cellSpursJq */
EXPORT(spursJobQueueAttributeSetMaxGrab, 0x5fb9b05d); /* cellSpursJq */
EXPORT(spursJobQueueAttributeSetMaxSizeJobDescriptor, 0x1686957e); /* cellSpursJq */
EXPORT(spursJobQueueAttributeSetSubmitWithEntryLock, 0x0f03f712); /* cellSpursJq */
EXPORT(spursJobQueueClose, 0x29c2acc5); /* cellSpursJq */
EXPORT(spursJobQueueGetError, 0x2e775550); /* cellSpursJq */
EXPORT(spursJobQueueGetHandleCount, 0x840c5239); /* cellSpursJq */
EXPORT(spursJobQueueGetMaxSizeJobDescriptor, 0x5659da82); /* cellSpursJq */
EXPORT(spursJobQueueGetSpurs, 0x01bbf2e0); /* cellSpursJq */
EXPORT(spursJobQueueGetSuspendedJobSize, 0x15934401); /* cellSpursJq */
EXPORT(spursJobQueueOpen, 0xff7a7bd2); /* cellSpursJq */
EXPORT(spursJobQueuePort2AllocateJobDescriptor, 0x934abb00); /* cellSpursJq */
EXPORT(spursJobQueuePort2Create, 0xf11fe0f1); /* cellSpursJq */
EXPORT(spursJobQueuePort2Destroy, 0xc485d207); /* cellSpursJq */
EXPORT(spursJobQueuePort2GetJobQueue, 0x435bff07); /* cellSpursJq */
EXPORT(spursJobQueuePort2PushFlush, 0xbfea28ab); /* cellSpursJq */
EXPORT(spursJobQueuePort2PushSync, 0xfc526b72); /* cellSpursJq */
EXPORT(spursJobQueuePort2Sync, 0xfacb3ced); /* cellSpursJq */
EXPORT(spursJobQueuePortFinalize, 0x26fa81b4); /* cellSpursJq */
EXPORT(spursJobQueuePortGetJobQueue, 0x90c88f84); /* cellSpursJq */
EXPORT(spursJobQueuePortInitialize, 0x3d1294fc); /* cellSpursJq */
EXPORT(spursJobQueuePortInitializeWithDescriptorBuffer, 0xf5de6363); /* cellSpursJq */
EXPORT(spursJobQueuePortSync, 0x634b1502); /* cellSpursJq */
EXPORT(spursJobQueuePortTrySync, 0x80a0264c); /* cellSpursJq */
EXPORT(spursJobQueueSemaphoreAcquire, 0x6c93ea18); /* cellSpursJq */
EXPORT(spursJobQueueSemaphoreInitialize, 0x677027af); /* cellSpursJq */
EXPORT(spursJobQueueSemaphoreTryAcquire, 0x97409f67); /* cellSpursJq */
EXPORT(spursJobQueueSendSignal, 0x915455b3); /* cellSpursJq */
EXPORT(spursJobQueueSetExceptionEventHandler, 0x9c300489); /* cellSpursJq */
EXPORT(spursJobQueueSetExceptionEventHandler2, 0x6c61bf87); /* cellSpursJq */
EXPORT(spursJobQueueSetWaitingMode, 0x13671514); /* cellSpursJq */
EXPORT(spursJobQueueUnsetExceptionEventHandler, 0x93248b92); /* cellSpursJq */
EXPORT(spursJoinJobQueue, 0x8ce4cffa); /* cellSpursJq */
EXPORT(spursShutdownJobQueue, 0x8c97a96c); /* cellSpursJq */


#endif
