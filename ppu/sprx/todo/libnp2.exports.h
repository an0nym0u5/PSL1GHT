#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(np2Init, 0x41251f74); /* sceNp2 */
EXPORT(np2Term, 0xaadb7c12); /* sceNp2 */
EXPORT(np2Matching2AbortContextStart, 0x430ce063); /* sceNp2 */
EXPORT(np2Matching2AbortRequest, 0x2ed909dc); /* sceNp2 */
EXPORT(np2Matching2ClearEventData, 0xaa6c2c43); /* sceNp2 */
EXPORT(np2Matching2ContextStart, 0x12d0b0f9); /* sceNp2 */
EXPORT(np2Matching2ContextStartAsync, 0x6ba4c668); /* sceNp2 */
EXPORT(np2Matching2ContextStop, 0xf43c647a); /* sceNp2 */
EXPORT(np2Matching2CreateContext, 0x9cbce3f2); /* sceNp2 */
EXPORT(np2Matching2CreateJoinRoom, 0xe7a3bc7a); /* sceNp2 */
EXPORT(np2Matching2CreateServerContext, 0x16b3e5a4); /* sceNp2 */
EXPORT(np2Matching2DeleteServerContext, 0xc6b63b7e); /* sceNp2 */
EXPORT(np2Matching2DestroyContext, 0x01379fd7); /* sceNp2 */
EXPORT(np2Matching2GetCbQueueInfo, 0x62d446ac); /* sceNp2 */
EXPORT(np2Matching2GetClanLobbyId, 0x12034412); /* sceNp2 */
EXPORT(np2Matching2GetEventData, 0x3c00c9d4); /* sceNp2 */
EXPORT(np2Matching2GetLobbyInfoList, 0xefbd9357); /* sceNp2 */
EXPORT(np2Matching2GetLobbyMemberDataInternal, 0x129663d0); /* sceNp2 */
EXPORT(np2Matching2GetLobbyMemberDataInternalList, 0x0b2218a3); /* sceNp2 */
EXPORT(np2Matching2GetLobbyMemberIdListLocal, 0xeffe5a16); /* sceNp2 */
EXPORT(np2Matching2GetMemoryInfo, 0x196a06f9); /* sceNp2 */
EXPORT(np2Matching2GetRoomDataExternalList, 0xe4ac32ca); /* sceNp2 */
EXPORT(np2Matching2GetRoomDataInternal, 0x8b209ca2); /* sceNp2 */
EXPORT(np2Matching2GetRoomMemberDataExternalList, 0x2c5b7fc9); /* sceNp2 */
EXPORT(np2Matching2GetRoomMemberDataInternal, 0xb0c51412); /* sceNp2 */
EXPORT(np2Matching2GetRoomMemberDataInternalLocal, 0x58a04247); /* sceNp2 */
EXPORT(np2Matching2GetRoomMemberIdListLocal, 0x490124fd); /* sceNp2 */
EXPORT(np2Matching2GetRoomPasswordLocal, 0xde6d308b); /* sceNp2 */
EXPORT(np2Matching2GetRoomSlotInfoLocal, 0x3cc27344); /* sceNp2 */
EXPORT(np2Matching2GetServerIdListLocal, 0x8e5cfe9f); /* sceNp2 */
EXPORT(np2Matching2GetServerInfo, 0x3457c0db); /* sceNp2 */
EXPORT(np2Matching2GetSignalingOptParamLocal, 0xa2b01449); /* sceNp2 */
EXPORT(np2Matching2GetUserInfoList, 0xac98b03a); /* sceNp2 */
EXPORT(np2Matching2GetWorldInfoList, 0x05bf2fbd); /* sceNp2 */
EXPORT(np2Matching2GrantRoomOwner, 0x9344d41f); /* sceNp2 */
EXPORT(np2Matching2Init, 0x3f62c759); /* sceNp2 */
EXPORT(np2Matching2Init2, 0xf4babd3f); /* sceNp2 */
EXPORT(np2Matching2JoinLobby, 0x29e78389); /* sceNp2 */
EXPORT(np2Matching2JoinProhibitiveRoom, 0xba578d19); /* sceNp2 */
EXPORT(np2Matching2JoinRoom, 0x5721e711); /* sceNp2 */
EXPORT(np2Matching2KickoutRoomMember, 0x66f19527); /* sceNp2 */
EXPORT(np2Matching2LeaveLobby, 0x02065e3d); /* sceNp2 */
EXPORT(np2Matching2LeaveRoom, 0x1f372697); /* sceNp2 */
EXPORT(np2Matching2RegisterContextCallback, 0x748029a2); /* sceNp2 */
EXPORT(np2Matching2RegisterLobbyEventCallback, 0x0884fc95); /* sceNp2 */
EXPORT(np2Matching2RegisterLobbyMessageCallback, 0x03a2f42a); /* sceNp2 */
EXPORT(np2Matching2RegisterRoomEventCallback, 0xdcb6b27d); /* sceNp2 */
EXPORT(np2Matching2RegisterRoomMessageCallback, 0xfee11e72); /* sceNp2 */
EXPORT(np2Matching2RegisterSignalingCallback, 0xa9e6103e); /* sceNp2 */
EXPORT(np2Matching2SearchRoom, 0x0d22867f); /* sceNp2 */
EXPORT(np2Matching2SendLobbyChatMessage, 0x3f3bd413); /* sceNp2 */
EXPORT(np2Matching2SendLobbyInvitation, 0xefff8779); /* sceNp2 */
EXPORT(np2Matching2SendRoomChatMessage, 0x7bf6e152); /* sceNp2 */
EXPORT(np2Matching2SendRoomMessage, 0x28cad8b3); /* sceNp2 */
EXPORT(np2Matching2SetDefaultRequestOptParam, 0xdb87b088); /* sceNp2 */
EXPORT(np2Matching2SetLobbyMemberDataInternal, 0xfa0583c6); /* sceNp2 */
EXPORT(np2Matching2SetRoomDataExternal, 0x215b0d75); /* sceNp2 */
EXPORT(np2Matching2SetRoomDataInternal, 0x817d1090); /* sceNp2 */
EXPORT(np2Matching2SetRoomMemberDataInternal, 0xb851aacf); /* sceNp2 */
EXPORT(np2Matching2SetSignalingOptParam, 0x6fcd84c1); /* sceNp2 */
EXPORT(np2Matching2SetUserInfo, 0x1022e6d6); /* sceNp2 */
EXPORT(np2Matching2SignalingGetConnectionInfo, 0x26ae9ff8); /* sceNp2 */
EXPORT(np2Matching2SignalingGetConnectionStatus, 0x0ebe4c6b); /* sceNp2 */
EXPORT(np2Matching2SignalingGetCtxOpt, 0xe9946648); /* sceNp2 */
EXPORT(np2Matching2SignalingGetPingInfo, 0x8d3f8d49); /* sceNp2 */
EXPORT(np2Matching2SignalingSetCtxOpt, 0xbf014813); /* sceNp2 */
EXPORT(np2Matching2Term, 0x2fe0da7d); /* sceNp2 */
EXPORT(np2Matching2Term2, 0x23009d07); /* sceNp2 */
EXPORT(np2UtilBuildCdnUrl, 0x8e930999); /* sceNp2 */


#endif
