#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(sailFeederAudioFinalize, 0x899d1587); /* cellSailRec */
EXPORT(sailFeederAudioInitialize, 0xbd591197); /* cellSailRec */
EXPORT(sailFeederAudioNotifyCallCompleted, 0xc2e2f30d); /* cellSailRec */
EXPORT(sailFeederAudioNotifyFrameOut, 0x3c775cea); /* cellSailRec */
EXPORT(sailFeederAudioNotifySessionEnd, 0x999c0dc5); /* cellSailRec */
EXPORT(sailFeederAudioNotifySessionError, 0xaf310ae6); /* cellSailRec */
EXPORT(sailFeederVideoFinalize, 0x81bfeae8); /* cellSailRec */
EXPORT(sailFeederVideoInitialize, 0x57415dd3); /* cellSailRec */
EXPORT(sailFeederVideoNotifyCallCompleted, 0xd84daeb9); /* cellSailRec */
EXPORT(sailFeederVideoNotifyFrameOut, 0xe5e0572a); /* cellSailRec */
EXPORT(sailFeederVideoNotifySessionEnd, 0xbff6e8d3); /* cellSailRec */
EXPORT(sailFeederVideoNotifySessionError, 0x86cae679); /* cellSailRec */
EXPORT(sailProfileSetEsAudioParameter, 0xe14cae97); /* cellSailRec */
EXPORT(sailProfileSetEsVideoParameter, 0x1422a425); /* cellSailRec */
EXPORT(sailProfileSetStreamParameter, 0xe8d86c43); /* cellSailRec */
EXPORT(sailRecorderBoot, 0xc4617ddc); /* cellSailRec */
EXPORT(sailRecorderCancel, 0xd37fb694); /* cellSailRec */
EXPORT(sailRecorderCloseStream, 0xe3f56f62); /* cellSailRec */
EXPORT(sailRecorderCreateProfile, 0x50affdc1); /* cellSailRec */
EXPORT(sailRecorderCreateVideoConverter, 0x49476a3d); /* cellSailRec */
EXPORT(sailRecorderDestroyProfile, 0x376c3926); /* cellSailRec */
EXPORT(sailRecorderDestroyVideoConverter, 0x455c4709); /* cellSailRec */
EXPORT(sailRecorderDumpImage, 0x37aad85f); /* cellSailRec */
EXPORT(sailRecorderFinalize, 0xf57d74e3); /* cellSailRec */
EXPORT(sailRecorderGetParameter, 0xff20157b); /* cellSailRec */
EXPORT(sailRecorderInitialize, 0x7a52bf69); /* cellSailRec */
EXPORT(sailRecorderOpenStream, 0x10c81457); /* cellSailRec */
EXPORT(sailRecorderReplaceEventHandler, 0xe12a2fbe); /* cellSailRec */
EXPORT(sailRecorderSetFeederAudio, 0x3deae857); /* cellSailRec */
EXPORT(sailRecorderSetFeederVideo, 0x4fec43a9); /* cellSailRec */
EXPORT(sailRecorderSetParameter, 0x0a3ea2a9); /* cellSailRec */
EXPORT(sailRecorderStart, 0x4830faf8); /* cellSailRec */
EXPORT(sailRecorderStop, 0x18ecc741); /* cellSailRec */
EXPORT(sailRecorderSubscribeEvent, 0x551a95fc); /* cellSailRec */
EXPORT(sailRecorderUnsubscribeEvent, 0x54cfb78b); /* cellSailRec */
EXPORT(sailVideoConverterCanGetResult, 0xe16de678); /* cellSailRec */
EXPORT(sailVideoConverterCanProcess, 0xb3d30b0d); /* cellSailRec */
EXPORT(sailVideoConverterGetResult, 0xe15679fe); /* cellSailRec */
EXPORT(sailVideoConverterProcess, 0x855da8c6); /* cellSailRec */


#endif
