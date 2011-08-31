/*
 */

#ifndef __SYSCALL_SPU_SYSCALLS_H__
#define __SYSCALL_SPU_SYSCALLS_H__


/* SPU library functions */
#define SYSCALL_SPU_THREAD_EXIT                                 1
#define SYSCALL_SPU_THREAD_GROUP_EXIT                           2
#define SYSCALL_SPU_THREAD_YIELD                                3
#define SYSCALL_SPU_THREAD_RECEIVE_EVENT                        4
#define SYSCALL_SPU_THREAD_TRYRECEIVE_EVENT                     5
#define SYSCALL_SPU_THREAD_SEND_EVENT                           6
#define SYSCALL_SPU_THREAD_THROW_EVENT                          7
#define SYSCALL_SPU_THREAD_SWITCH_TO_SYSTEM_MODULE              10

#define SYSCALL_SPU_EVENT_FLAG_SET_BIT                          8
#define SYSCALL_SPU_EVENT_FLAG_SET_BIT_IMPATIENT                9


#endif /* __SYSCALL_SPU_SYSCALLS_H__ */

