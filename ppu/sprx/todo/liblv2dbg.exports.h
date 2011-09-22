#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(sysLv2Dbg_disable_floating_point_enabled_exception, 0xf254768c); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_enable_floating_point_enabled_exception, 0x3147c6ca); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_finalize_ppu_exception_handler, 0xc0eb9266); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_address_from_dabr, 0xbb0ae221); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_cond_information, 0x63bd413e); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_coredump_params, 0xb9da87d3); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_event_flag_information, 0xdf856979); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_event_queue_information, 0x381ae33e); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_lwcond_information, 0x7bdadb01); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_lwmutex_information, 0xcb377e36); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_mutex_information, 0x50453aa8); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_ppu_thread_ids, 0x113b0bea); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_ppu_thread_name, 0x4b55f456); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_ppu_thread_status, 0x6b413178); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_rwlock_information, 0x9794bb53); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_semaphore_information, 0xa2d6cbd2); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_spu_thread_group_ids, 0x08ef08a9); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_spu_thread_group_name, 0xbd69e584); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_spu_thread_group_status, 0x9ddb9dc3); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_spu_thread_ids, 0x1860f909); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_get_spu_thread_name, 0x3e5eed36); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_initialize_ppu_exception_handler, 0xc353353a); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_mat_get_condition, 0x590a276e); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_mat_set_condition, 0x24a3d413); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_read_ppu_thread_context, 0xc5eef17f); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_read_spu_thread_context, 0xc21ee635); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_read_spu_thread_context2, 0x266c2bd3); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_register_ppu_exception_handler, 0x22916f45); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_set_address_to_dabr, 0xdb14b37b); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_set_mask_to_ppu_exception_handler, 0xab475d53); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_set_stacksize_ppu_exception_handler, 0x06a840f5); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_signal_to_coredump_handler, 0xd830062a); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_signal_to_ppu_exception_handler, 0x4ded9f6c); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_unregister_ppu_exception_handler, 0xc6d7ec13); /* sys_lv2dbg */
EXPORT(sysLv2Dbg_vm_get_page_information, 0x580f8203); /* sys_lv2dbg */


#endif
