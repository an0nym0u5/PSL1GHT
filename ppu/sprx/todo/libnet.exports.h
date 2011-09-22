#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(accept, 0xc94f6939); /* sys_net */
EXPORT(bind, 0xb0a59804); /* sys_net */
EXPORT(connect, 0x64f66d35); /* sys_net */
EXPORT(gethostbyaddr, 0xf7ac8941); /* sys_net */
EXPORT(gethostbyname, 0x71f4c717); /* sys_net */
EXPORT(getpeername, 0xf9ec2db6); /* sys_net */
EXPORT(getsockname, 0x13efe7f5); /* sys_net */
EXPORT(getsockopt, 0x5a045bd1); /* sys_net */
EXPORT(inet_addr, 0xdabbc2c0); /* sys_net */
EXPORT(inet_aton, 0xa9a079e0); /* sys_net */
EXPORT(inet_lnaof, 0x566893ce); /* sys_net */
EXPORT(inet_makeaddr, 0xb4152c74); /* sys_net */
EXPORT(inet_netof, 0xe39a62a7); /* sys_net */
EXPORT(inet_network, 0x506ad863); /* sys_net */
EXPORT(inet_ntoa, 0x858a930b); /* sys_net */
EXPORT(inet_ntop, 0xc98a3146); /* sys_net */
EXPORT(inet_pton, 0x8af3825e); /* sys_net */
EXPORT(listen, 0x28e208bb); /* sys_net */
EXPORT(recv, 0xfba04f37); /* sys_net */
EXPORT(recvfrom, 0x1f953b9f); /* sys_net */
EXPORT(recvmsg, 0xc9d09c34); /* sys_net */
EXPORT(send, 0xdc751b40); /* sys_net */
EXPORT(sendmsg, 0xad09481b); /* sys_net */
EXPORT(sendto, 0x9647570b); /* sys_net */
EXPORT(setsockopt, 0x88f03575); /* sys_net */
EXPORT(shutdown, 0xa50777c6); /* sys_net */
EXPORT(socket, 0x9c056962); /* sys_net */
EXPORT(socketclose, 0x6db6e8cd); /* sys_net */
EXPORT(socketpoll, 0x051ee3ee); /* sys_net */
EXPORT(socketselect, 0x3f09e20a); /* sys_net */
EXPORT(sys_net_abort_resolver, 0x8ccf05ed); /* sys_net */
EXPORT(sys_net_abort_socket, 0x8d1b77fb); /* sys_net */
EXPORT(sys_net_close_dump, 0x44328aa2); /* sys_net */
EXPORT(_sys_net_errno_loc, 0x6005cde1); /* sys_net */
EXPORT(sys_net_finalize_network, 0xb68d5625); /* sys_net */
EXPORT(sys_net_free_thread_context, 0xfdb8f926); /* sys_net */
EXPORT(sys_net_get_lib_name_server, 0x1d14d6e4); /* sys_net */
EXPORT(sys_net_get_netemu_test_param, 0x368823c0); /* sys_net */
EXPORT(sys_net_get_sockinfo, 0x3b27c780); /* sys_net */
EXPORT(sys_net_get_sockinfo_ex, 0xa765d029); /* sys_net */
EXPORT(sys_net_get_test_param, 0xa5a86557); /* sys_net */
EXPORT(sys_net_get_udpp2p_test_param, 0x05bd4438); /* sys_net */
EXPORT(_sys_net_h_errno_loc, 0xc9157d30); /* sys_net */
EXPORT(sys_net_if_ctl, 0x27fb339d); /* sys_net */
EXPORT(sys_net_initialize_network_ex, 0x139a9e9b); /* sys_net */
EXPORT(sys_net_open_dump, 0xab447704); /* sys_net */
EXPORT(sys_net_read_dump, 0x89c9917c); /* sys_net */
EXPORT(sys_net_set_lib_name_server, 0x9a318259); /* sys_net */
EXPORT(sys_net_set_netemu_test_param, 0xe2434507); /* sys_net */
EXPORT(sys_net_set_resolver_configurations, 0x7687d48c); /* sys_net */
EXPORT(sys_net_set_test_param, 0x4ab0b9b9); /* sys_net */
EXPORT(sys_net_set_udpp2p_test_param, 0x10b81ed6); /* sys_net */
EXPORT(sys_net_show_ifconfig, 0xb48636c4); /* sys_net */
EXPORT(sys_net_show_nameserver, 0x5420e419); /* sys_net */
EXPORT(sys_net_show_route, 0x79b61646); /* sys_net */


#endif
