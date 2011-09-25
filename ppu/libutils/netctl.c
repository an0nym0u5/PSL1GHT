//#line 1 "netctl.c"
/*
 * netctl.c
 *
 * Copyright (C) an0nym0us
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */


#include <utils/netctl.h>


inline s32
netCtlInitialize ()
{
  return netCtlInit () ;
}

inline void
netCtlFinish ()
{
  netCtlTerm () ;
}

inline s32
netCtlGetInfoDevice ( u32 *device )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_DEVICE);
  *device = info.device ;

  return ret;
}

inline s32
netCtlGetInfoEtherAddr ( u8 *ether_addr )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_ETHER_ADDR);
  memcpy (ether_addr, info.ether_addr.data, sizeof (info.ether_addr.data));

  return ret;
}

inline s32
netCtlGetInfoMtu ( u32 *mtu )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_MTU);
  *mtu = info.mtu ;

  return ret;
}

inline s32
netCtlGetInfoLink ( u32 *link )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_LINK);
  *link = info.link ;

  return ret;
}

inline s32
netCtlGetInfoLinkType ( u32 *link_type )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_LINK_TYPE);
  *link_type = info.link_type ;

  return ret;
}

inline s32
netCtlGetInfoBssid ( u8 *bssid )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_BSSID);
  memcpy (bssid, info.bssid.data, sizeof (info.bssid.data));

  return ret;
}

inline s32
netCtlGetInfoSsid ( u8 *ssid, u8 *term )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_SSID);
  memcpy (ssid, info.ssid.data, sizeof (info.ssid.data)) ;
  *term = info.ssid.term ;

  return ret;
}

inline s32
netCtlGetInfoWlanSecurity ( u32 *wlan_security )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_WLAN_SECURITY);
  *wlan_security = info.wlan_security ;

  return ret;
}

inline s32
netCtlGetInfo8021xType ( u32 *auth_8021x_type )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_8021X_TYPE);
  *auth_8021x_type = info.auth_8021x_type ;

  return ret;
}

inline s32
netCtlGetInfo8021xAuthName ( char *auth_8021x_auth_name )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_8021X_AUTH_NAME);
  memcpy (auth_8021x_auth_name, info.auth_8021x_auth_name, sizeof (info.auth_8021x_auth_name)) ;

  return ret;
}

inline s32
netCtlGetInfoRssi ( u8 *rssi )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_RSSI);
  *rssi = info.rssi ;

  return ret;
}

inline s32
netCtlGetInfoChannel ( u8 *channel )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_CHANNEL);
  *channel = info.channel ;

  return ret;
}

inline s32
netCtlGetInfoIpConfig ( u32 *ip_config )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_IP_CONFIG);
  *ip_config = info.ip_config ;

  return ret;
}

inline s32
netCtlGetInfoDhcpHostname ( char *dhcp_hostname )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_DHCP_HOSTNAME);
  memcpy (dhcp_hostname, info.dhcp_hostname, sizeof (info.dhcp_hostname)) ;

  return ret;
}

inline s32
netCtlGetInfoPppoeAuthName ( char *pppoe_auth_name )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_PPPOE_AUTH_NAME);
  memcpy (pppoe_auth_name, info.pppoe_auth_name, sizeof (info.pppoe_auth_name)) ;

  return ret;
}

inline s32
netCtlGetInfoIpAddress ( char *ip_address )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_IP_ADDRESS);
  memcpy (ip_address, info.ip_address, sizeof (info.ip_address)) ;

  return ret;
}

inline s32
netCtlGetInfoNetmask ( char *netmask )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_NETMASK);
  memcpy (netmask, info.netmask, sizeof (info.netmask)) ;

  return ret;
}

inline s32
netCtlGetInfoDefaultRoute ( char *default_route )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_DEFAULT_ROUTE);
  memcpy (default_route, info.default_route, sizeof (info.default_route)) ;

  return ret;
}

inline s32
netCtlGetInfoPrimaryDns ( char *primary_dns )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_PRIMARY_DNS);
  memcpy (primary_dns, info.primary_dns, sizeof (info.primary_dns)) ;

  return ret;
}

inline s32
netCtlGetInfoSecondaryDns ( char *secondary_dns )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_SECONDARY_DNS);
  memcpy (secondary_dns, info.secondary_dns, sizeof (info.secondary_dns)) ;

  return ret;
}

inline s32
netCtlGetInfoHttpProxyConfig ( u32 *http_proxy_config )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_HTTP_PROXY_CONFIG);
  *http_proxy_config = info.http_proxy_config ;

  return ret;
}

inline s32
netCtlGetInfoHttpProxyServer ( char *http_proxy_server )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_HTTP_PROXY_SERVER);
  memcpy (http_proxy_server, info.http_proxy_server, sizeof (info.http_proxy_server)) ;

  return ret;
}

inline s32
netCtlGetInfoHttpProxyPort ( u16 *http_proxy_port )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_HTTP_PROXY_PORT);
  *http_proxy_port = info.http_proxy_port ;

  return ret;
}

inline s32
netCtlGetInfoUpnpConfig ( u32 *upnp_config )
{
  NET_CTL_GET_INFO(NET_CTL_INFO_UPNP_CONFIG);
  *upnp_config = info.upnp_config ;

  return ret;
}

