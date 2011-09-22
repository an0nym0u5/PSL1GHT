#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(sheapBarrierDelete, 0xf6f5fbca); /* cellSheap */
EXPORT(sheapBarrierNew, 0xe897c835); /* cellSheap */
EXPORT(sheapBufferDelete, 0xe6b37362); /* cellSheap */
EXPORT(sheapBufferNew, 0x4a5b9659); /* cellSheap */
EXPORT(sheapInitialize, 0xa1b25841); /* cellSheap */
EXPORT(sheapMutexDelete, 0x2452679f); /* cellSheap */
EXPORT(sheapMutexNew, 0x3478e1e6); /* cellSheap */
EXPORT(sheapQueueDelete, 0x79a6abd0); /* cellSheap */
EXPORT(sheapQueueNew, 0x987e260e); /* cellSheap */
EXPORT(sheapRwmDelete, 0xed136702); /* cellSheap */
EXPORT(sheapRwmNew, 0xf01ac471); /* cellSheap */
EXPORT(sheapSemaphoreDelete, 0x73a45cf8); /* cellSheap */
EXPORT(sheapSemaphoreNew, 0x69a5861d); /* cellSheap */

EXPORT(sheapAllocate, 0x4b1383fb); /* cellSheap */
EXPORT(sheapFree, 0x5c5994bd); /* cellSheap */
EXPORT(sheapInitialize, 0xbbb47cd8); /* cellSheap */
EXPORT(sheapQueryFree, 0x7fa23275); /* cellSheap */
EXPORT(sheapQueryMax, 0x37968718); /* cellSheap */


#endif
