#ifndef __EXPORTS_H__
#define __EXPORTS_H__

/* video support */
EXPORT(videoGetResolution, 0xe558748d);
EXPORT(videoConfigure, 0x0bae8772);
EXPORT(videoGetState, 0x887572d5);
EXPORT(videoGetDeviceInfo, 0x1e930eef);
EXPORT(videoGetConfiguration, 0x15b0b0cd);
EXPORT(videoGetResolutionAvailability, 0xa322db75);
EXPORT(videoDebugSetMonitorType, 0xcfdf24bb);
EXPORT(videoRegisterCallbackEx, 0x8e8bc444);
EXPORT(videoUnregisterCallback, 0x7871bed4);
EXPORT(videoGetNumberOfDevice, 0x75bbb672);
EXPORT(videoGetConvertCursorColorInfo, 0x55e425c3);

/* message dialog support */
EXPORT(msgDialogClose, 0x20543730);
EXPORT(msgDialogOpenErrorCodeEx, 0x3e22cb4b);
EXPORT(msgDialogOpenEx, 0xf81eca25);
EXPORT(msgDialogProgressBarInc, 0x94862702);
EXPORT(msgDialogAbort, 0x62b0f803);
EXPORT(msgDialogOpen2Ex, 0x7603d3db);
EXPORT(msgDialogProgressBarReset, 0x7bc2c8a8);
EXPORT(msgDialogProgressBarSetMsg, 0x9d6af72a);

/* on-screen-keyboard support */
EXPORT(oskGetInputText, 0x1d99c3ee);
EXPORT(oskSetInitialInputDevice, 0xf3b4b43e);
EXPORT(oskGetSize, 0x35beade0);
EXPORT(oskUnloadAsync, 0x3d1e1931);
EXPORT(oskDisableDimmer, 0x41f20828);
EXPORT(oskSetKeyLayoutOption, 0xb53c54fa);
EXPORT(oskAbort, 0xb6d84526);
EXPORT(oskSetDeviceMask, 0xd3790a86);
EXPORT(oskSetSeparateWindowOption, 0x53e39df3);
EXPORT(oskAddSupportLanguage, 0x7f21c918);
EXPORT(oskLoadAsync, 0x7fcfc915);
EXPORT(oskSetInitialKeyLayout, 0xc427890c);
EXPORT(oskSetLayoutMode, 0xf0ec3ccc);

/* system utility support */
EXPORT(sysUtilRegisterCallbackEx, 0x9d98afa0);
EXPORT(sysUtilCheckCallback, 0x189a74da);
EXPORT(sysUtilUnregisterCallback, 0x02ff3c1b);

/* Save utility support */
EXPORT(sysSaveListLoad2Ex, 0x1dfbfdd6);
EXPORT(sysSaveListSave2Ex, 0x2de0d663);
EXPORT(sysSaveListAutoLoadEx, 0x21425307);
EXPORT(sysSaveListAutoSaveEx, 0x4dd03a4e);
EXPORT(sysSaveFixedLoad2Ex, 0x2a8eada2);
EXPORT(sysSaveFixedSave2Ex, 0x2aae9ef5);
EXPORT(sysSaveAutoLoad2Ex, 0xfbd5c856);
EXPORT(sysSaveAutoSave2Ex, 0x8b7ed64b);
EXPORT(sysSaveDelete2, 0xedadd797);

/* NEW save data */
EXPORT(sysSaveDataListLoad2Ex, 0x1dfbfdd6);
EXPORT(sysSaveDataListSave2Ex, 0x2de0d663);
EXPORT(sysSaveDataListAutoLoadEx, 0x21425307);
EXPORT(sysSaveDataListAutoSaveEx, 0x4dd03a4e);
EXPORT(sysSaveDataFixedLoad2Ex, 0x2a8eada2);
EXPORT(sysSaveDataFixedSave2Ex, 0x2aae9ef5);
EXPORT(sysSaveDataAutoLoad2Ex, 0xfbd5c856);
EXPORT(sysSaveDataAutoSave2Ex, 0x8b7ed64b);
EXPORT(sysSaveDataAutoLoadEx, 0xc22c79b5); /* cellSysutil */
EXPORT(sysSaveDataAutoSaveEx, 0xf8a175ec); /* cellSysutil */
EXPORT(sysSaveDataFixedDeleteEx, 0xced17573); /* cellSysutil */
EXPORT(sysSaveDataFixedExportEx, 0x46a2d878); /* sysSaveData */
EXPORT(sysSaveDataFixedImportEx, 0x52541151); /* sysSaveData */
EXPORT(sysSaveDataListDeleteEx, 0x27cb8bc2); /* sysSaveData */
EXPORT(sysSaveDataListExportEx, 0x491cc554); /* sysSaveData */
EXPORT(sysSaveDataListImportEx, 0x6b4e0de6); /* sysSaveData */
EXPORT(sysSaveDataUserAutoLoadEx, 0xcdc6aefd); /* cellSysutil */
EXPORT(sysSaveDataUserAutoSaveEx, 0x52aac4fa); /* cellSysutil */
EXPORT(sysSaveDataUserFixedDeleteEx, 0x8b8a2f48); /* cellSysutil */
EXPORT(sysSaveDataUserFixedExportEx, 0x95ae2cde); /* sysSaveData */
EXPORT(sysSaveDataUserFixedImportEx, 0x529231b0); /* sysSaveData */
EXPORT(sysSaveDataUserFixedLoadEx, 0x6e7264ed); /* cellSysutil */
EXPORT(sysSaveDataUserFixedSaveEx, 0x40b34847); /* cellSysutil */
EXPORT(sysSaveDataUserListAutoLoadEx, 0x248bd1d8); /* cellSysutil */
EXPORT(sysSaveDataUserListAutoSave, 0x0e091c36); /* cellSysutil */
EXPORT(sysSaveDataUserListDeleteEx, 0x7048a9ba); /* sysSaveData */
EXPORT(sysSaveDataUserListExportEx, 0x273d116a); /* sysSaveData */
EXPORT(sysSaveDataUserListImportEx, 0x39d6ee43); /* sysSaveData */
EXPORT(sysSaveDataUserListLoadEx, 0x39dd8425); /* cellSysutil */
EXPORT(sysSaveDataUserListSaveEx, 0x0f03cfb0); /* cellSysutil */
EXPORT(sysSaveDataDelete2, 0xedadd797);
EXPORT(sysSaveDataEnableOverlay, 0xe7fa820b); /* cellSysutil */
EXPORT(sysSaveDataGetListItem, 0x04c06fc2); /* sysSaveData */
EXPORT(sysSaveDataUserGetListItem, 0xf6482036); /* sysSaveData */
EXPORT(sysSaveDataListLoad, 0xef5a353d); /* cellSysutil */
EXPORT(sysSaveDataListSave, 0x3dbd2314); /* cellSysutil */
EXPORT(sysSaveDataFixedLoad, 0x50183b44); /* cellSysutil */
EXPORT(sysSaveDataFixedSave, 0x41bc2ca1); /* cellSysutil */
EXPORT(sysSaveDataDelete, 0xa4ed7dfe); /* cellSysutil */

/* Disc utility support */
EXPORT(sysDiscRegisterDiscChangeCallbackEx, 0xdfdd302e);
EXPORT(sysDiscUnregisterDiscChangeCallback, 0xedc34e1a);

/* trophy utility support */
EXPORT(sysTrophyInit, 0x39567781);
EXPORT(sysTrophyAbortHandle, 0x48bd97c7);
EXPORT(sysTrophyCreateContext, 0xe3bf9a28);
EXPORT(sysTrophyCreateHandle, 0x1c25470d);
EXPORT(sysTrophyDestroyContext, 0x3741ecc7);
EXPORT(sysTrophyDestroyHandle, 0x623cd2dc);
EXPORT(sysTrophyGetGameIcon, 0xff299e03);
EXPORT(sysTrophyGetGameInfo, 0x49d18217);
EXPORT(sysTrophyGetGameProgress, 0x079f0e87);
EXPORT(sysTrophyGetRequiredDiskSpace, 0x370136fe);
EXPORT(sysTrophyGetTrophyIcon, 0xbaedf689);
EXPORT(sysTrophyGetTrophyInfo, 0xfce6d30a);
EXPORT(sysTrophyGetTrophyUnlockState, 0xb3ac3478);
EXPORT(sysTrophyRegisterContextEx, 0x1197b52c);
EXPORT(sysTrophySetSoundLevel, 0x27deda93);
EXPORT(sysTrophyTerm, 0xa7fabf4d);
EXPORT(sysTrophyUnlockTrophy, 0x8ceedd21);

/* system cache support */
EXPORT(sysCacheClear, 0x744c1544); /* cellSysutil */
EXPORT(sysCacheMount, 0x1e7bff94); /* cellSysutil */


#endif
