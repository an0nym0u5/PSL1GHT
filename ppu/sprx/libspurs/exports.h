#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(spursAttributeInitialize, 0x95180230); /* cellSpurs */
EXPORT(spursEventFlagInitialize, 0x5ef96465); /* cellSpurs */
EXPORT(spursJobChainAttributeInitialize, 0x3548f483); /* cellSpurs */
EXPORT(spursLFQueueInitialize, 0x011ee38b); /* cellSpurs */
EXPORT(spursLFQueuePopBody, 0x35dae22b); /* cellSpurs */
EXPORT(spursLFQueuePushBody, 0x8a85674d); /* cellSpurs */
EXPORT(spursQueueInitialize, 0x082bfb09); /* cellSpurs */
EXPORT(spursSemaphoreInitialize, 0x77cdac0c); /* cellSpurs */
EXPORT(spursSendSignal, 0xe0a6dbe4); /* cellSpurs */
EXPORT(spursTaskAttribute2Initialize, 0x8adadf65); /* cellSpurs */
EXPORT(spursTaskAttributeInitialize, 0xb8474eff); /* cellSpurs */
EXPORT(spursTasksetAttribute2Initialize, 0xc2acdf43); /* cellSpurs */
EXPORT(spursTasksetAttributeInitialize, 0x16394a4e); /* cellSpurs */
EXPORT(spursWorkloadAttributeInitialize, 0xefeb2679); /* cellSpurs */
EXPORT(spursWorkloadFlagReceiver, 0xa73bf47e); /* cellSpurs */
EXPORT(spursWorkloadFlagReceiver2, 0x2ddbcc0a); /* cellSpurs */
EXPORT(spursAddUrgentCall, 0x8fdf50b2); /* cellSpurs */
EXPORT(spursAddUrgentCommand, 0x17001000); /* cellSpurs */
EXPORT(spursAddWorkload, 0x69726aa2); /* cellSpurs */
EXPORT(spursAddWorkloadWithAttribute, 0xc0158d8b); /* cellSpurs */
EXPORT(spursAttachLv2EventQueue, 0xb9bc6207); /* cellSpurs */
EXPORT(spursAttributeEnableSpuPrintfIfAvailable, 0x1051d134); /* cellSpurs */
EXPORT(spursAttributeEnableSystemWorkload, 0x9dcbcb5d); /* cellSpurs */
EXPORT(spursAttributeSetMemoryContainerForSpuThread, 0x82275c1c); /* cellSpurs */
EXPORT(spursAttributeSetNamePrefix, 0x07529113); /* cellSpurs */
EXPORT(spursAttributeSetSpuThreadGroupType, 0xa839a4d9); /* cellSpurs */
EXPORT(spursBarrierGetTasksetAddress, 0x9aeb5432); /* cellSpurs */
EXPORT(spursBarrierInitialize, 0x7fdf4fef); /* cellSpurs */
EXPORT(spursCreateJobChainWithAttribute, 0x303c19cd); /* cellSpurs */
EXPORT(spursCreateTask, 0xbeb600ac); /* cellSpurs */
EXPORT(spursCreateTask2, 0xe14ca62d); /* cellSpurs */
EXPORT(spursCreateTask2WithBinInfo, 0xe4944a1c); /* cellSpurs */
EXPORT(spursCreateTaskWithAttribute, 0x1d46fedf); /* cellSpurs */
EXPORT(spursCreateTaskset, 0x52cc6c82); /* cellSpurs */
EXPORT(spursCreateTaskset2, 0x4a6465e3); /* cellSpurs */
EXPORT(spursCreateTasksetWithAttribute, 0xc10931cb); /* cellSpurs */
EXPORT(spursDestroyTaskset2, 0x1ebcf459); /* cellSpurs */
EXPORT(spursDetachLv2EventQueue, 0x4e66d483); /* cellSpurs */
EXPORT(spursEnableExceptionEventHandler, 0x32b94add); /* cellSpurs */
EXPORT(spursEventFlagAttachLv2EventQueue, 0x87630976); /* cellSpurs */
EXPORT(spursEventFlagClear, 0x4ac7bae4); /* cellSpurs */
EXPORT(spursEventFlagDetachLv2EventQueue, 0x22aab31d); /* cellSpurs */
EXPORT(spursEventFlagGetClearMode, 0x4d1e9373); /* cellSpurs */
EXPORT(spursEventFlagGetDirection, 0x890f9e5a); /* cellSpurs */
EXPORT(spursEventFlagGetTasksetAddress, 0x947efb0b); /* cellSpurs */
EXPORT(spursEventFlagSet, 0xf5507729); /* cellSpurs */
EXPORT(spursEventFlagTryWait, 0x6d2d9339); /* cellSpurs */
EXPORT(spursEventFlagWait, 0x373523d4); /* cellSpurs */
EXPORT(spursFinalize, 0xca4c4600); /* cellSpurs */
EXPORT(spursGetInfo, 0x1f402f8f); /* cellSpurs */
EXPORT(spursGetJobChainId, 0x86c864a2); /* cellSpurs */
EXPORT(spursGetJobChainInfo, 0x4ceb9694); /* cellSpurs */
EXPORT(spursGetJobPipelineInfo, 0xd86380d8); /* cellSpurs */
EXPORT(spursGetNumSpuThread, 0xc56defb5); /* cellSpurs */
EXPORT(spursGetSpuGuid, 0x6fcdf6e3); /* cellSpurs */
EXPORT(spursGetSpuThreadGroupId, 0x39c173fb); /* cellSpurs */
EXPORT(spursGetSpuThreadId, 0x6c960f6d); /* cellSpurs */
EXPORT(spursGetTasksetId, 0xe7dd87e1); /* cellSpurs */
EXPORT(spursGetTasksetInfo, 0x9fcb567b); /* cellSpurs */
EXPORT(spursGetWorkloadData, 0xa7f9e716); /* cellSpurs */
EXPORT(spursGetWorkloadFlag, 0xc765b995); /* cellSpurs */
EXPORT(spursGetWorkloadInfo, 0x4e153e3e); /* cellSpurs */
EXPORT(spursInitialize, 0xacfc8dbc); /* cellSpurs */
EXPORT(spursInitializeWithAttribute, 0xaa6269a8); /* cellSpurs */
EXPORT(spursInitializeWithAttribute2, 0x30aa96c4); /* cellSpurs */
EXPORT(spursJobChainAttributeSetHaltOnError, 0xbb68d76e); /* cellSpurs */
EXPORT(spursJobChainAttributeSetJobTypeMemoryCheck, 0x2cfccb99); /* cellSpurs */
EXPORT(spursJobChainAttributeSetName, 0x9fef70c2); /* cellSpurs */
EXPORT(spursJobChainGetError, 0x161da6a7); /* cellSpurs */
EXPORT(spursJobChainGetSpursAddress, 0x494613c7); /* cellSpurs */
EXPORT(spursJobChainSetExceptionEventHandler, 0x5202e53b); /* cellSpurs */
EXPORT(spursJobChainUnsetExceptionEventHandler, 0x6aa76999); /* cellSpurs */
EXPORT(spursJobGuardInitialize, 0x68aaeba9); /* cellSpurs */
EXPORT(spursJobGuardNotify, 0xd5d0b256); /* cellSpurs */
EXPORT(spursJobGuardReset, 0x00af2519); /* cellSpurs */
EXPORT(spursJobHeaderSetJobbin2Param, 0x97a2f6c8); /* cellSpurs */
EXPORT(spursJobSetMaxGrab, 0xe7b0e69a); /* cellSpurs */
EXPORT(spursJoinJobChain, 0xa7c066de); /* cellSpurs */
EXPORT(spursJoinTask2, 0xa7a94892); /* cellSpurs */
EXPORT(spursJoinTaskset, 0x9f72add3); /* cellSpurs */
EXPORT(spursLFQueueAttachLv2EventQueue, 0x1656d49f); /* cellSpurs */
EXPORT(spursLFQueueDetachLv2EventQueue, 0x73e06f91); /* cellSpurs */
EXPORT(spursLFQueueGetTasksetAddress, 0xb792ca1a); /* cellSpurs */
EXPORT(spursLookUpTasksetAddress, 0x4cce88a9); /* cellSpurs */
EXPORT(spursQueueAttachLv2EventQueue, 0xe5443be7); /* cellSpurs */
EXPORT(spursQueueClear, 0x247414d0); /* cellSpurs */
EXPORT(spursQueueDepth, 0x35f02287); /* cellSpurs */
EXPORT(spursQueueDetachLv2EventQueue, 0x039d70b7); /* cellSpurs */
EXPORT(spursQueueGetDirection, 0xec68442c); /* cellSpurs */
EXPORT(spursQueueGetEntrySize, 0x369fe03d); /* cellSpurs */
EXPORT(spursQueueGetTasksetAddress, 0x2093252b); /* cellSpurs */
EXPORT(spursQueuePopBody, 0x91066667); /* cellSpurs */
EXPORT(spursQueuePushBody, 0x92cff6ed); /* cellSpurs */
EXPORT(spursQueueSize, 0x54876603); /* cellSpurs */
EXPORT(spursReadyCountAdd, 0x75211196); /* cellSpurs */
EXPORT(spursReadyCountCompareAndSwap, 0xf1d3552d); /* cellSpurs */
EXPORT(spursReadyCountStore, 0xf843818d); /* cellSpurs */
EXPORT(spursReadyCountSwap, 0x49a3426d); /* cellSpurs */
EXPORT(spursRemoveWorkload, 0x57e4dec3); /* cellSpurs */
EXPORT(spursRequestIdleSpu, 0x182d9890); /* cellSpurs */
EXPORT(spursRunJobChain, 0xf31731bb); /* cellSpurs */
EXPORT(spursSemaphoreGetTasksetAddress, 0x568b2352); /* cellSpurs */
EXPORT(spursSendWorkloadSignal, 0x1d2bca4b); /* cellSpurs */
EXPORT(spursSetExceptionEventHandler, 0xd2e23fa9); /* cellSpurs */
EXPORT(spursSetGlobalExceptionEventHandler, 0x7517724a); /* cellSpurs */
EXPORT(spursSetMaxContention, 0x84d2f6d5); /* cellSpurs */
EXPORT(spursSetPreemptionVictimHints, 0x4de203e2); /* cellSpurs */
EXPORT(spursSetPriorities, 0x80a29e27); /* cellSpurs */
EXPORT(spursSetPriority, 0xb52e1bda); /* cellSpurs */
EXPORT(spursShutdownJobChain, 0x738e40e6); /* cellSpurs */
EXPORT(spursShutdownTaskset, 0xa789e631); /* cellSpurs */
EXPORT(spursShutdownWorkload, 0x98d5b343); /* cellSpurs */
EXPORT(spursTaskAttributeSetExitCodeContainer, 0xa121a224); /* cellSpurs */
EXPORT(spursTaskExitCodeGet, 0x13ae18f3); /* cellSpurs */
EXPORT(spursTaskExitCodeInitialize, 0x34552fa6); /* cellSpurs */
EXPORT(spursTaskExitCodeTryGet, 0xe717ac73); /* cellSpurs */
EXPORT(spursTaskGenerateLsPattern, 0x9197915f); /* cellSpurs */
EXPORT(spursTaskGetContextSaveAreaSize, 0x9034e538); /* cellSpurs */
EXPORT(spursTaskGetLoadableSegmentPattern, 0x1d344406); /* cellSpurs */
EXPORT(spursTaskGetReadOnlyAreaPattern, 0x7cb33c2e); /* cellSpurs */
EXPORT(spursTasksetAttributeEnableClearLS, 0xdca13593); /* cellSpurs */
EXPORT(spursTasksetAttributeSetName, 0x652b70e2); /* cellSpurs */
EXPORT(spursTasksetAttributeSetTasksetSize, 0x8f122ef8); /* cellSpurs */
EXPORT(spursTasksetGetSpursAddress, 0x58d58fcf); /* cellSpurs */
EXPORT(spursTasksetSetExceptionEventHandler, 0x2edcff92); /* cellSpurs */
EXPORT(spursTasksetUnsetExceptionEventHandler, 0x94034c95); /* cellSpurs */
EXPORT(spursTraceFinalize, 0x7b9cbb74); /* cellSpurs */
EXPORT(spursTraceInitialize, 0x569674e3); /* cellSpurs */
EXPORT(spursTraceStart, 0xce853fbf); /* cellSpurs */
EXPORT(spursTraceStop, 0xddc81b5a); /* cellSpurs */
EXPORT(spursTryJoinTask2, 0x838fa4f0); /* cellSpurs */
EXPORT(spursUnsetExceptionEventHandler, 0x4c75deb8); /* cellSpurs */
EXPORT(spursUnsetGlobalExceptionEventHandler, 0x861237f8); /* cellSpurs */
EXPORT(spursWaitForWorkloadShutdown, 0x5fd43fe4); /* cellSpurs */
EXPORT(spursWakeUp, 0x7e4ea023); /* cellSpurs */
EXPORT(spursWorkloadAttributeSetName, 0x4a5eab63); /* cellSpurs */
EXPORT(spursWorkloadAttributeSetShutdownCompletionEventHook, 0x0eb4bc38); /* cellSpurs */


#endif