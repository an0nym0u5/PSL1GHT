/*
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 */

#ifndef __NETCTL_H__
#define __NETCTL_H__


#include <stdio.h>
#include <string.h>
#include <net/netctl.h>


#define NET_CTL_ERROR printf ( "\033[0;33m%s:%s():#%d :: netCtlGetInfo()\033[0m\n", __FILE__, __func__, __LINE__ ) ;
#define NET_CTL_GET_INFO(type) static s32 ret;                   \
                               static union net_ctl_info info;   \
                               ret = netCtlGetInfo(type, &info); \
                               if(ret < 0) NET_CTL_ERROR;        \

s32 netCtlInitialize(void);
void netCtlFinish(void);
s32 netCtlGetInfoDevice(u32 *device);
s32 netCtlGetInfoEtherAddr(u8 *ether_addr);
s32 netCtlGetInfoMtu(u32 *mtu);
s32 netCtlGetInfoLink(u32 *link);
s32 netCtlGetInfoLinkType(u32 *link_type);
s32 netCtlGetInfoBssid(u8 *bssid);
s32 netCtlGetInfoSsid(u8 *ssid, u8 *term);
s32 netCtlGetInfoWlanSecurity(u32 *wlan_security);
s32 netCtlGetInfo8021xType(u32 *auth_8021x_type);
s32 netCtlGetInfo8021xAuthName(char *auth_8021x_auth_name);
s32 netCtlGetInfoRssi(u8 *rssi);
s32 netCtlGetInfoChannel(u8 *channel);
s32 netCtlGetInfoIpConfig(u32 *ip_config);
s32 netCtlGetInfoDhcpHostname(char *dhcp_hostname);
s32 netCtlGetInfoPppoeAuthName(char *pppoe_auth_name);
s32 netCtlGetInfoIpAddress(char *ip_address);
s32 netCtlGetInfoNetmask(char *netmask);
s32 netCtlGetInfoDefaultRoute(char *default_route);
s32 netCtlGetInfoPrimaryDns(char *primary_dns);
s32 netCtlGetInfoSecondaryDns(char *secondary_dns);
s32 netCtlGetInfoHttpProxyConfig(u32 *http_proxy_config);
s32 netCtlGetInfoHttpProxyServer(char *http_proxy_server);
s32 netCtlGetInfoHttpProxyPort(u16 *http_proxy_port);
s32 netCtlGetInfoUpnpConfig(u32 *upnp_config);

#endif /* __NETCTL_H__ */

