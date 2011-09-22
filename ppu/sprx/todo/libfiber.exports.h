#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(_fiberPpuAttributeInitialize, 0xc11f8056); /* cellFiber */
EXPORT(fiberPpuCheckFlags, 0xf6c6900c); /* cellFiber */
EXPORT(fiberPpuCheckStackLimit, 0xf3e81219); /* cellFiber */
EXPORT(_fiberPpuContextAttributeInitialize, 0x31252ec3); /* cellFiber */
EXPORT(fiberPpuContextCheckStackLimit, 0xb90c871b); /* cellFiber */
EXPORT(fiberPpuContextEnterScheduler, 0x0a25b6c8); /* cellFiber */
EXPORT(fiberPpuContextFinalize, 0xb3a48079); /* cellFiber */
EXPORT(fiberPpuContextInitialize, 0x72086315); /* cellFiber */
EXPORT(fiberPpuContextReturnToThread, 0x01036193); /* cellFiber */
EXPORT(fiberPpuContextRun, 0xaba1c563); /* cellFiber */
EXPORT(fiberPpuContextRunScheduler, 0x081c98be); /* cellFiber */
EXPORT(fiberPpuContextSelf, 0x34a81091); /* cellFiber */
EXPORT(fiberPpuContextSwitch, 0xd0066b17); /* cellFiber */
EXPORT(fiberPpuCreateFiber, 0x7c2f4034); /* cellFiber */
EXPORT(fiberPpuExit, 0xfa8d5f95); /* cellFiber */
EXPORT(fiberPpuFinalizeScheduler, 0x8b6baa01); /* cellFiber */
EXPORT(fiberPpuGetScheduler, 0xb0594b2d); /* cellFiber */
EXPORT(fiberPpuHasRunnableFiber, 0xe492a675); /* cellFiber */
EXPORT(_fiberPpuInitialize, 0x55870804); /* cellFiber */
EXPORT(fiberPpuInitializeScheduler, 0xee3b604d); /* cellFiber */
EXPORT(fiberPpuJoinFiber, 0xa6004249); /* cellFiber */
EXPORT(fiberPpuRunFibers, 0x12b1acf0); /* cellFiber */
EXPORT(_fiberPpuSchedulerAttributeInitialize, 0x9e25c72d); /* cellFiber */
EXPORT(fiberPpuSchedulerTraceFinalize, 0x3860a12a); /* cellFiber */
EXPORT(fiberPpuSchedulerTraceInitialize, 0xbf9cd933); /* cellFiber */
EXPORT(fiberPpuSchedulerTraceStart, 0xadedbebf); /* cellFiber */
EXPORT(fiberPpuSchedulerTraceStop, 0xe665f9a9); /* cellFiber */
EXPORT(fiberPpuSelf, 0x5d9a7034); /* cellFiber */
EXPORT(fiberPpuSendSignal, 0x8afb8356); /* cellFiber */
EXPORT(fiberPpuSetPriority, 0xfbf5fe40); /* cellFiber */
EXPORT(_fiberPpuUtilWorkerControlAttributeInitialize, 0x68ba4568); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlCheckFlags, 0xea6dc1ad); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlConnectEventQueueToSpurs, 0x62a20f0d); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlCreateFiber, 0xbfca88d3); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlDisconnectEventQueue, 0x4fc86b2c); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlFinalize, 0xa27c95ca); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlInitialize, 0x3204b146); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlInitializeWithAttribute, 0xf2ccad4f); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlJoinFiber, 0x3b417f82); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlRunFibers, 0x1e7a247a); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlSendSignal, 0x5d3992dd); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlSetPollingMode, 0x392c5aa5); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlShutdown, 0xc04e2438); /* cellFiber */
EXPORT(fiberPpuUtilWorkerControlWakeup, 0xbabf714b); /* cellFiber */
EXPORT(fiberPpuWaitFlag, 0xa4599cf3); /* cellFiber */
EXPORT(fiberPpuWaitSignal, 0x6c164b3b); /* cellFiber */
EXPORT(fiberPpuYield, 0x0c44f441); /* cellFiber */


#endif
