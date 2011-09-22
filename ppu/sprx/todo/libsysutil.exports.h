#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(sysutilAudioOutConfigure, 0x4692ab35); /* cellSysutil */
EXPORT(sysutilAudioOutGetConfiguration, 0xed5d96af); /* cellSysutil */
EXPORT(sysutilAudioOutGetDeviceInfo, 0x7663e368); /* cellSysutil */
EXPORT(sysutilAudioOutGetNumberOfDevice, 0xe5e2b09d); /* cellSysutil */
EXPORT(sysutilAudioOutGetSoundAvailability, 0xc01b4e7c); /* cellSysutil */
EXPORT(sysutilAudioOutGetSoundAvailability2, 0x2beac488); /* cellSysutil */
EXPORT(sysutilAudioOutGetState, 0xf4e3caa0); /* cellSysutil */
EXPORT(sysutilAudioOutRegisterCallback, 0x68bc4ff3); /* cellSysutil */
EXPORT(sysutilAudioOutSetCopyControl, 0xc96e89e9); /* cellSysutil */
EXPORT(sysutilAudioOutUnregisterCallback, 0x9dfdad46); /* cellSysutil */

EXPORT(sysutilDiscGameGetBootDiscInfo, 0xb72bc4e6); /* cellSysutil */
EXPORT(sysutilDiscGameRegisterDiscChangeCallback, 0xdfdd302e); /* cellSysutil */
EXPORT(sysutilDiscGameUnregisterDiscChangeCallback, 0xedc34e1a); /* cellSysutil */

EXPORT(sysutilGameDataCheckCreate, 0xe7951dee); /* cellSysutil */
EXPORT(sysutilGameDataCheckCreate2, 0xc9645c41); /* cellSysutil */
EXPORT(sysutilGameDataExitBroken, 0x9949bf82); /* cellSysutil */
EXPORT(sysutilGameDataGetSizeKB, 0xa9b0c1d9); /* cellSysutil */
EXPORT(sysutilGameRegisterDiscChangeCallback, 0xf8115d69); /* cellSysutil */
EXPORT(sysutilGameUnregisterDiscChangeCallback, 0x21fc0c71); /* cellSysutil */

EXPORT(sysutilHddGameCheck, 0x9117df20); /* cellSysutil */
EXPORT(sysutilHddGameCheck2, 0x4bdec82a); /* cellSysutil */
EXPORT(sysutilHddGameExitBroken, 0xafd605b3); /* cellSysutil */
EXPORT(sysutilHddGameGetSizeKB, 0xf82e2ef7); /* cellSysutil */

EXPORT(sysutilMsgDialogAbort, 0x62b0f803); /* cellSysutil */
EXPORT(sysutilMsgDialogClose, 0x20543730); /* cellSysutil */
EXPORT(sysutilMsgDialogOpen, 0xf81eca25); /* cellSysutil */
EXPORT(sysutilMsgDialogOpen2, 0x7603d3db); /* cellSysutil */
EXPORT(sysutilMsgDialogOpenErrorCode, 0x3e22cb4b); /* cellSysutil */
EXPORT(sysutilMsgDialogProgressBarInc, 0x94862702); /* cellSysutil */
EXPORT(sysutilMsgDialogProgressBarReset, 0x7bc2c8a8); /* cellSysutil */
EXPORT(sysutilMsgDialogProgressBarSetMsg, 0x9d6af72a); /* cellSysutil */

EXPORT(sysutilOskDialogAbort, 0xb6d84526); /* cellSysutil */
EXPORT(sysutilOskDialogAddSupportLanguage, 0x7f21c918); /* cellSysutil */
EXPORT(sysutilOskDialogDisableDimmer, 0x41f20828); /* cellSysutil */
EXPORT(sysutilOskDialogGetInputText, 0x1d99c3ee); /* cellSysutil */
EXPORT(sysutilOskDialogGetSize, 0x35beade0); /* cellSysutil */
EXPORT(sysutilOskDialogLoadAsync, 0x7fcfc915); /* cellSysutil */
EXPORT(sysutilOskDialogSetDeviceMask, 0xd3790a86); /* cellSysutil */
EXPORT(sysutilOskDialogSetInitialInputDevice, 0xf3b4b43e); /* cellSysutil */
EXPORT(sysutilOskDialogSetInitialKeyLayout, 0xc427890c); /* cellSysutil */
EXPORT(sysutilOskDialogSetKeyLayoutOption, 0xb53c54fa); /* cellSysutil */
EXPORT(sysutilOskDialogSetLayoutMode, 0xf0ec3ccc); /* cellSysutil */
EXPORT(sysutilOskDialogSetSeparateWindowOption, 0x53e39df3); /* cellSysutil */
EXPORT(sysutilOskDialogUnloadAsync, 0x3d1e1931); /* cellSysutil */

EXPORT(sysutilSaveDataAutoLoad, 0xc22c79b5); /* cellSysutil */
EXPORT(sysutilSaveDataAutoLoad2, 0xfbd5c856); /* cellSysutil */
EXPORT(sysutilSaveDataAutoSave, 0xf8a175ec); /* cellSysutil */
EXPORT(sysutilSaveDataAutoSave2, 0x8b7ed64b); /* cellSysutil */
EXPORT(sysutilSaveDataDelete, 0xa4ed7dfe); /* cellSysutil */
EXPORT(sysutilSaveDataDelete2, 0xedadd797); /* cellSysutil */
EXPORT(sysutilSaveDataEnableOverlay, 0xe7fa820b); /* cellSysutil */
EXPORT(sysutilSaveDataFixedDelete, 0xced17573); /* cellSysutil */
EXPORT(sysutilSaveDataFixedLoad, 0x50183b44); /* cellSysutil */
EXPORT(sysutilSaveDataFixedLoad2, 0x2a8eada2); /* cellSysutil */
EXPORT(sysutilSaveDataFixedSave, 0x41bc2ca1); /* cellSysutil */
EXPORT(sysutilSaveDataFixedSave2, 0x2aae9ef5); /* cellSysutil */
EXPORT(sysutilSaveDataListAutoLoad, 0x21425307); /* cellSysutil */
EXPORT(sysutilSaveDataListAutoSave, 0x4dd03a4e); /* cellSysutil */
EXPORT(sysutilSaveDataListLoad, 0xef5a353d); /* cellSysutil */
EXPORT(sysutilSaveDataListLoad2, 0x1dfbfdd6); /* cellSysutil */
EXPORT(sysutilSaveDataListSave, 0x3dbd2314); /* cellSysutil */
EXPORT(sysutilSaveDataListSave2, 0x2de0d663); /* cellSysutil */
EXPORT(sysutilSaveDataUserAutoLoad, 0xcdc6aefd); /* cellSysutil */
EXPORT(sysutilSaveDataUserAutoSave, 0x52aac4fa); /* cellSysutil */
EXPORT(sysutilSaveDataUserFixedDelete, 0x8b8a2f48); /* cellSysutil */
EXPORT(sysutilSaveDataUserFixedLoad, 0x6e7264ed); /* cellSysutil */
EXPORT(sysutilSaveDataUserFixedSave, 0x40b34847); /* cellSysutil */
EXPORT(sysutilSaveDataUserListAutoLoad, 0x248bd1d8); /* cellSysutil */
EXPORT(sysutilSaveDataUserListAutoSave, 0x0e091c36); /* cellSysutil */
EXPORT(sysutilSaveDataUserListLoad, 0x39dd8425); /* cellSysutil */
EXPORT(sysutilSaveDataUserListSave, 0x0f03cfb0); /* cellSysutil */

EXPORT(sysutilStorageDataExport, 0xabc3cd2c); /* cellSysutil */
EXPORT(sysutilStorageDataImport, 0x918288fb); /* cellSysutil */
EXPORT(sysutilStorageDataImportMove, 0x27ac51e4); /* cellSysutil */

EXPORT(sysutilSysCacheClear, 0x744c1544); /* cellSysutil */
EXPORT(sysutilSysCacheMount, 0x1e7bff94); /* cellSysutil */

EXPORT(sysutilSysconfAbort, 0x76948bfc); /* cellSysutil */
EXPORT(sysutilSysconfOpen, 0xb2b6cdd0); /* cellSysutil */

EXPORT(sysutilSysutilAvcByeRequest, 0xf2c4a425); /* cellSysutil */
EXPORT(sysutilSysutilAvcCancelByeRequest, 0xf4aa8b27); /* cellSysutil */
EXPORT(sysutilSysutilAvcCancelJoinRequest, 0xbccd70dd); /* cellSysutil */
EXPORT(sysutilSysutilAvcEnumPlayers, 0x5e91bc26); /* cellSysutil */
EXPORT(sysutilSysutilAvcGetAttribute, 0xf481967f); /* cellSysutil */
EXPORT(sysutilSysutilAvcGetLayoutMode, 0xeb9d78d8); /* cellSysutil */
EXPORT(sysutilSysutilAvcGetShowStatus, 0x08269f37); /* cellSysutil */
EXPORT(sysutilSysutilAvcGetSpeakerVolumeLevel, 0x073b89d5); /* cellSysutil */
EXPORT(sysutilSysutilAvcGetVideoMuting, 0x7d94ca36); /* cellSysutil */
EXPORT(sysutilSysutilAvcGetVoiceMuting, 0x5ee3bc26); /* cellSysutil */
EXPORT(sysutilSysutilAvcHidePanel, 0xd9ea5709); /* cellSysutil */
EXPORT(sysutilSysutilAvcJoinRequest, 0x17dbe8b3); /* cellSysutil */
EXPORT(sysutilSysutilAvcLoadAsync, 0x15df71ed); /* cellSysutil */
EXPORT(sysutilSysutilAvcSetAttribute, 0xeca938ca); /* cellSysutil */
EXPORT(sysutilSysutilAvcSetLayoutMode, 0x018a1381); /* cellSysutil */
EXPORT(sysutilSysutilAvcSetSpeakerVolumeLevel, 0xaffdadc0); /* cellSysutil */
EXPORT(sysutilSysutilAvcSetVideoMuting, 0x71acb8d3); /* cellSysutil */
EXPORT(sysutilSysutilAvcSetVoiceMuting, 0x4056c932); /* cellSysutil */
EXPORT(sysutilSysutilAvcShowPanel, 0x2dbc92c7); /* cellSysutil */
EXPORT(sysutilSysutilAvcUnloadAsync, 0x6c673f78); /* cellSysutil */

EXPORT(sysutilSysutilDisableBgmPlayback, 0xcfdd8e87); /* cellSysutil */
EXPORT(sysutilSysutilDisableBgmPlaybackEx, 0xa36335a5); /* cellSysutil */
EXPORT(sysutilSysutilEnableBgmPlayback, 0x220894e3); /* cellSysutil */
EXPORT(sysutilSysutilEnableBgmPlaybackEx, 0xac58ad2b); /* cellSysutil */
EXPORT(sysutilSysutilGetBgmPlaybackStatus, 0xa11552f6); /* cellSysutil */
EXPORT(sysutilSysutilGetBgmPlaybackStatus2, 0x6cfd856f); /* cellSysutil */
EXPORT(sysutilSysutilSetBgmPlaybackExtraParam, 0xf3dbf5a7); /* cellSysutil */

EXPORT(sysutilSysutilGameDataAssignVmc, 0x9997e6b6); /* cellSysutil */
EXPORT(sysutilSysutilGameDataExit, 0x1dfcce99); /* cellSysutil */
EXPORT(sysutilSysutilGameExit_I, 0x2a95d8bc); /* cellSysutil */
EXPORT(sysutilSysutilGamePowerOff_I, 0x01f04d94); /* cellSysutil */
EXPORT(sysutilSysutilGameReboot_I, 0x30d3d12b); /* cellSysutil */

EXPORT(sysutilSysutilGetSystemParamInt, 0x40e895d3); /* cellSysutil */
EXPORT(sysutilSysutilGetSystemParamString, 0x938013a0); /* cellSysutil */

EXPORT(sysutilSysutilCheckCallback, 0x189a74da); /* cellSysutil */
EXPORT(sysutilSysutilRegisterCallback, 0x9d98afa0); /* cellSysutil */
EXPORT(sysutilSysutilUnregisterCallback, 0x02ff3c1b); /* cellSysutil */

EXPORT(sysutilVideoOutConfigure, 0x0bae8772); /* cellSysutil */
EXPORT(sysutilVideoOutDebugSetMonitorType, 0xcfdf24bb); /* cellSysutil */
EXPORT(sysutilVideoOutGetConfiguration, 0x15b0b0cd); /* cellSysutil */
EXPORT(sysutilVideoOutGetConvertCursorColorInfo, 0x55e425c3); /* cellSysutil */
EXPORT(sysutilVideoOutGetDeviceInfo, 0x1e930eef); /* cellSysutil */
EXPORT(sysutilVideoOutGetNumberOfDevice, 0x75bbb672); /* cellSysutil */
EXPORT(sysutilVideoOutGetResolution, 0xe558748d); /* cellSysutil */
EXPORT(sysutilVideoOutGetResolutionAvailability, 0xa322db75); /* cellSysutil */
EXPORT(sysutilVideoOutGetState, 0x887572d5); /* cellSysutil */
EXPORT(sysutilVideoOutRegisterCallback, 0x8e8bc444); /* cellSysutil */
EXPORT(sysutilVideoOutUnregisterCallback, 0x7871bed4); /* cellSysutil */

EXPORT(sysutilWebBrowserActivate, 0x6d7444e6); /* cellSysutil */
EXPORT(sysutilWebBrowserConfig, 0x83668b8e); /* cellSysutil */
EXPORT(sysutilWebBrowserConfig2, 0x7fb3c6a5); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigGetHeapSize, 0xa4dd11cc); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigGetHeapSize2, 0x0c316b87); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetCustomExit, 0x7f896a1f); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetDisableTabs, 0x3261a9c8); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetErrorHook2, 0x1f6629e4); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetFullScreen2, 0x1a91874b); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetFullVersion2, 0x52d9457a); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetFunction, 0x9c9fe6a4); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetFunction2, 0xe22ed55d); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetHeapSize, 0x76fc8fb1); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetHeapSize2, 0xfe669845); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetMimeSet, 0x0f8a3b6b); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetNotifyHook2, 0x93c523c6); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetRequestHook2, 0xee7528f3); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetStatusHook2, 0xac16777e); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetTabCount2, 0x619b1427); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetUnknownMIMETypeHook2, 0xa9a439e0); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetVersion, 0x60a4daab); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetViewCondition2, 0xd7a617f5); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigSetViewRect2, 0xa9b62ac8); /* cellSysutil */
EXPORT(sysutilWebBrowserConfigWithVer, 0x6c1082aa); /* cellSysutil */
EXPORT(sysutilWebBrowserCreate, 0x7f881be1); /* cellSysutil */
EXPORT(sysutilWebBrowserCreate2, 0xa5f12145); /* cellSysutil */
EXPORT(sysutilWebBrowserCreateRender2, 0xf1a443e7); /* cellSysutil */
EXPORT(sysutilWebBrowserCreateRenderWithRect2, 0x4b6e8560); /* cellSysutil */
EXPORT(sysutilWebBrowserCreateWithConfig, 0x8a4cb646); /* cellSysutil */
EXPORT(sysutilWebBrowserCreateWithConfigFull, 0xb53b3d42); /* cellSysutil */
EXPORT(sysutilWebBrowserCreateWithRect2, 0xa58943f8); /* cellSysutil */
EXPORT(sysutilWebBrowserDeactivate, 0x46a0285d); /* cellSysutil */
EXPORT(sysutilWebBrowserDestroy, 0xbed85cb8); /* cellSysutil */
EXPORT(sysutilWebBrowserDestroy2, 0xe8dee79c); /* cellSysutil */
EXPORT(sysutilWebBrowserEstimate, 0x58c89c4a); /* cellSysutil */
EXPORT(sysutilWebBrowserEstimate2, 0x6d087930); /* cellSysutil */
EXPORT(sysutilWebBrowserGetUsrdataOnGameExit, 0x10cabeff); /* cellSysutil */
EXPORT(sysutilWebBrowserInitialize, 0x749c9b5f); /* cellSysutil */
EXPORT(sysutilWebBrowserNavigate2, 0x9fb97b10); /* cellSysutil */
EXPORT(sysutilWebBrowserSetLocalContentsAdditionalTitleID, 0xc8971db5); /* cellSysutil */
EXPORT(sysutilWebBrowserSetSystemCallbackUsrdata, 0x6dfff31d); /* cellSysutil */
EXPORT(sysutilWebBrowserShutdown, 0x93ced48d); /* cellSysutil */
EXPORT(sysutilWebBrowserUpdatePointerDisplayPos2, 0x425fef23); /* cellSysutil */
EXPORT(sysutilWebBrowserWakeupWithGameExit, 0x24644561); /* cellSysutil */

EXPORT(sysutilWebComponentCreate, 0x8a5dbb58); /* cellSysutil */
EXPORT(sysutilWebComponentCreateAsync, 0x6144f033); /* cellSysutil */
EXPORT(sysutilWebComponentDestroy, 0xdce51399); /* cellSysutil */


#endif
