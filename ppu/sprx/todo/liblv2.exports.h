#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(console_getc, 0x8a2f159b); /* sysPrxForUser */
EXPORT(console_putc, 0xe66bac36); /* sysPrxForUser */
EXPORT(console_write, 0xf57e1d6f); /* sysPrxForUser */

EXPORT(_sys_free, 0xf7f7fb20); /* sysPrxForUser */

EXPORT(sys_game_board_storage_read, 0xe76964f5); /* sysPrxForUser */
EXPORT(sys_game_board_storage_write, 0x8bb03ab8); /* sysPrxForUser */
EXPORT(sys_game_get_rtc_status, 0x9f950780); /* sysPrxForUser */
EXPORT(sys_game_get_system_sw_version, 0x620e35a7); /* sysPrxForUser */
EXPORT(sys_game_get_temperature, 0x3172759d); /* sysPrxForUser */
EXPORT(sys_game_process_exitspawn, 0xfc52a7a9); /* sysPrxForUser */
EXPORT(sys_game_process_exitspawn2, 0x67f9fedb); /* sysPrxForUser */
EXPORT(sys_game_watchdog_clear, 0xacad8fb6); /* sysPrxForUser */
EXPORT(sys_game_watchdog_start, 0x9e0623b5); /* sysPrxForUser */
EXPORT(sys_game_watchdog_stop, 0x6e05231d); /* sysPrxForUser */

EXPORT(sys_get_random_number, 0x71a8472a); /* sysPrxForUser */

EXPORT(_sys_heap_alloc_heap_memory, 0xb9bf1078); /* sysPrxForUser */
EXPORT(_sys_heap_create_heap, 0xb2fcf2c8); /* sysPrxForUser */
EXPORT(_sys_heap_delete_heap, 0xaede4b03); /* sysPrxForUser */
EXPORT(_sys_heap_free, 0x8a561d92); /* sysPrxForUser */
EXPORT(_sys_heap_get_mallinfo, 0xd1ad4570); /* sysPrxForUser */
EXPORT(_sys_heap_get_total_free_size, 0xb6369393); /* sysPrxForUser */
EXPORT(_sys_heap_malloc, 0x35168520); /* sysPrxForUser */
EXPORT(_sys_heap_memalign, 0x44265c08); /* sysPrxForUser */
EXPORT(_sys_heap_stats, 0x8985b5b6); /* sysPrxForUser */

EXPORT(sys_initialize_tls, 0x744680a2); /* sysPrxForUser */

EXPORT(sys_interrupt_thread_disestablish, 0x4a071d98); /* sysPrxForUser */

EXPORT(sys_lwcond_create, 0xda0eb71a); /* sysPrxForUser */
EXPORT(sys_lwcond_destroy, 0x1c9a942c); /* sysPrxForUser */
EXPORT(sys_lwcond_signal, 0xef87a695); /* sysPrxForUser */
EXPORT(sys_lwcond_signal_all, 0xe9a1bd84); /* sysPrxForUser */
EXPORT(sys_lwcond_signal_to, 0x52aadadf); /* sysPrxForUser */
EXPORT(sys_lwcond_wait, 0x2a6d9d51); /* sysPrxForUser */

EXPORT(sys_lwmutex_create, 0x2f85c0ef); /* sysPrxForUser */
EXPORT(sys_lwmutex_destroy, 0xc3476d0c); /* sysPrxForUser */
EXPORT(sys_lwmutex_lock, 0x1573dc3f); /* sysPrxForUser */
EXPORT(sys_lwmutex_trylock, 0xaeb78725); /* sysPrxForUser */
EXPORT(sys_lwmutex_unlock, 0x1bc200f4); /* sysPrxForUser */

EXPORT(_sys_malloc, 0xbdb18f83); /* sysPrxForUser */

EXPORT(_sys_memalign, 0x318f17e1); /* sysPrxForUser */

EXPORT(_sys_memchr, 0x3bd53c7b); /* sysPrxForUser */
EXPORT(_sys_memcmp, 0xfb5db080); /* sysPrxForUser */
EXPORT(_sys_memcpy, 0x6bf66ea7); /* sysPrxForUser */
EXPORT(_sys_memmove, 0x27427742); /* sysPrxForUser */

EXPORT(sys_mempool_allocate_block, 0xa146a143); /* sysPrxForUser */
EXPORT(sys_mempool_create, 0xca9a60bf); /* sysPrxForUser */
EXPORT(sys_mempool_destroy, 0x9d3c0f81); /* sysPrxForUser */
EXPORT(sys_mempool_free_block, 0x608212fc); /* sysPrxForUser */
EXPORT(sys_mempool_get_count, 0x25596f51); /* sysPrxForUser */
EXPORT(sys_mempool_try_allocate_block, 0x05c65656); /* sysPrxForUser */

EXPORT(_sys_memset, 0x68b9b011); /* sysPrxForUser */

EXPORT(sys_mmapper_allocate_memory, 0xb257540b); /* sysPrxForUser */
EXPORT(sys_mmapper_allocate_memory_from_container, 0x70258515); /* sysPrxForUser */
EXPORT(sys_mmapper_free_memory, 0x409ad939); /* sysPrxForUser */
EXPORT(sys_mmapper_map_memory, 0xdc578057); /* sysPrxForUser */
EXPORT(sys_mmapper_unmap_memory, 0x4643ba6e); /* sysPrxForUser */

EXPORT(sys_ppu_thread_create, 0x24a1ea07); /* sysPrxForUser */
EXPORT(sys_ppu_thread_exit, 0xaff080a4); /* sysPrxForUser */
EXPORT(sys_ppu_thread_get_id, 0x350d454e); /* sysPrxForUser */
EXPORT(sys_ppu_thread_once, 0xa3e3be68); /* sysPrxForUser */
EXPORT(sys_ppu_thread_register_atexit, 0x3dd4a957); /* sysPrxForUser */
EXPORT(sys_ppu_thread_unregister_atexit, 0xac6fc404); /* sysPrxForUser */

EXPORT(_sys_printf, 0x9f04f7af); /* sysPrxForUser */

EXPORT(_sys_process_atexitspawn, 0x2c847572); /* sysPrxForUser */
EXPORT(_sys_process_at_Exitspawn, 0x96328741); /* sysPrxForUser */
EXPORT(sys_process_exit, 0xe6f2c1e7); /* sysPrxForUser */
EXPORT(sys_process_is_stack, 0x4f7172c9); /* sysPrxForUser */

EXPORT(sys_prx_exitspawn_with_level, 0xa2c7ba64); /* sysPrxForUser */
EXPORT(sys_prx_get_module_id_by_address, 0x0341bb97); /* sysPrxForUser */
EXPORT(sys_prx_get_module_id_by_name, 0xe0998dbf); /* sysPrxForUser */
EXPORT(sys_prx_get_module_info, 0x84bb6774); /* sysPrxForUser */
EXPORT(sys_prx_get_module_list, 0xa5d06bf0); /* sysPrxForUser */
EXPORT(sys_prx_get_my_module_id, 0x74311398); /* sysPrxForUser */
EXPORT(sys_prx_load_module, 0x26090058); /* sysPrxForUser */
EXPORT(sys_prx_load_module_by_fd, 0xef68c17c); /* sysPrxForUser */
EXPORT(sys_prx_load_module_list, 0xb27c8ae7); /* sysPrxForUser */
EXPORT(sys_prx_load_module_list_on_memcontainer, 0xe7ef3a80); /* sysPrxForUser */
EXPORT(sys_prx_load_module_on_memcontainer, 0xaa6d9bff); /* sysPrxForUser */
EXPORT(sys_prx_load_module_on_memcontainer_by_fd, 0xa330ad84); /* sysPrxForUser */
EXPORT(sys_prx_register_library, 0x42b23552); /* sysPrxForUser */
EXPORT(sys_prx_start_module, 0x9f18429d); /* sysPrxForUser */
EXPORT(sys_prx_stop_module, 0x80fb0c19); /* sysPrxForUser */
EXPORT(sys_prx_unload_module, 0xf0aece0d); /* sysPrxForUser */
EXPORT(sys_prx_unregister_library, 0xd0ea47a7); /* sysPrxForUser */

EXPORT(_sys_qsort, 0xc4fd6121); /* sysPrxForUser */

EXPORT(sys_raw_spu_image_load, 0xb995662e); /* sysPrxForUser */
EXPORT(sys_raw_spu_load, 0x893305fa); /* sysPrxForUser */

EXPORT(_sys_snprintf, 0x06574237); /* sysPrxForUser */

EXPORT(sys_spinlock_initialize, 0x8c2bb498); /* sysPrxForUser */
EXPORT(sys_spinlock_lock, 0xa285139d); /* sysPrxForUser */
EXPORT(sys_spinlock_trylock, 0x722a0254); /* sysPrxForUser */
EXPORT(sys_spinlock_unlock, 0x5267cb35); /* sysPrxForUser */

EXPORT(_sys_sprintf, 0xa1f9eafe); /* sysPrxForUser */

EXPORT(sys_spu_elf_get_information, 0x1ed454ce); /* sysPrxForUser */
EXPORT(sys_spu_elf_get_segments, 0xdb6b3250); /* sysPrxForUser */
EXPORT(sys_spu_image_close, 0xe0da8efd); /* sysPrxForUser */
EXPORT(sys_spu_image_import, 0xebe5f72f); /* sysPrxForUser */
EXPORT(_sys_spu_printf_attach_group, 0xdd0c1e09); /* sysPrxForUser */
EXPORT(_sys_spu_printf_attach_thread, 0x1ae10b92); /* sysPrxForUser */
EXPORT(_sys_spu_printf_detach_group, 0x5fdfb2fe); /* sysPrxForUser */
EXPORT(_sys_spu_printf_detach_thread, 0xb3bbcf2a); /* sysPrxForUser */
EXPORT(_sys_spu_printf_finalize, 0xdd3b27ac); /* sysPrxForUser */
EXPORT(_sys_spu_printf_initialize, 0x45fe2fce); /* sysPrxForUser */

EXPORT(_sys_strcat, 0x052d29a6); /* sysPrxForUser */
EXPORT(_sys_strchr, 0x7498887b); /* sysPrxForUser */
EXPORT(_sys_strcmp, 0x459b4393); /* sysPrxForUser */
EXPORT(_sys_strcpy, 0x99c88692); /* sysPrxForUser */
EXPORT(_sys_strlen, 0x2d36462b); /* sysPrxForUser */
EXPORT(_sys_strncasecmp, 0x1ca525a2); /* sysPrxForUser */
EXPORT(_sys_strncat, 0x996f7cf8); /* sysPrxForUser */
EXPORT(_sys_strncmp, 0x04e83d2c); /* sysPrxForUser */
EXPORT(_sys_strncpy, 0xd3039d4d); /* sysPrxForUser */
EXPORT(_sys_strrchr, 0x191f0c4a); /* sysPrxForUser */

EXPORT(sys_time_get_system_time, 0x8461e528); /* sysPrxForUser */

EXPORT(_sys_tolower, 0x4b2f301a); /* sysPrxForUser */
EXPORT(_sys_toupper, 0xeef75113); /* sysPrxForUser */

EXPORT(_sys_vprintf, 0xfa7f693d); /* sysPrxForUser */
EXPORT(_sys_vsnprintf, 0x0618936b); /* sysPrxForUser */
EXPORT(_sys_vsprintf, 0x791b9219); /* sysPrxForUser */


#endif
