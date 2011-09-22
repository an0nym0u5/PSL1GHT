#ifndef __EXPORTS_H__
#define __EXPORTS_H__


EXPORT(pamfEpIteratorGetEp, 0x1abeb9d6); /* cellPamf */
EXPORT(pamfEpIteratorMove, 0x50b83205); /* cellPamf */
EXPORT(pamfGetHeaderSize, 0xca8181c1); /* cellPamf */
EXPORT(pamfGetHeaderSize2, 0x90fc9a59); /* cellPamf */
EXPORT(pamfGetStreamOffsetAndSize, 0x44f5c9e3); /* cellPamf */
EXPORT(pamfReaderGetEpIteratorWithIndex, 0xe8586ec6); /* cellPamf */
EXPORT(pamfReaderGetEpIteratorWithTimeStamp, 0x439fba17); /* cellPamf */
EXPORT(pamfReaderGetEsFilterId, 0x71df326a); /* cellPamf */
EXPORT(pamfReaderGetMuxRateBound, 0xdb70296c); /* cellPamf */
EXPORT(pamfReaderGetNumberOfEp, 0xd9ea3457); /* cellPamf */
EXPORT(pamfReaderGetNumberOfSpecificStreams, 0xd0230671); /* cellPamf */
EXPORT(pamfReaderGetNumberOfStreams, 0x37f723f7); /* cellPamf */
EXPORT(pamfReaderGetPresentationEndTime, 0xf61609d6); /* cellPamf */
EXPORT(pamfReaderGetPresentationStartTime, 0x4de501b1); /* cellPamf */
EXPORT(pamfReaderGetStreamIndex, 0x041cc708); /* cellPamf */
EXPORT(pamfReaderGetStreamInfo, 0x67fd273b); /* cellPamf */
EXPORT(pamfReaderGetStreamTypeAndChannel, 0x9ab20793); /* cellPamf */
EXPORT(pamfReaderInitialize, 0xb8436ee5); /* cellPamf */
EXPORT(pamfReaderSetStreamWithIndex, 0x461534b4); /* cellPamf */
EXPORT(pamfReaderSetStreamWithTypeAndChannel, 0x03fd2caa); /* cellPamf */
EXPORT(pamfReaderSetStreamWithTypeAndIndex, 0x28b4e2c1); /* cellPamf */
EXPORT(pamfStreamTypeToEsFilterId, 0x01067e22); /* cellPamf */
EXPORT(pamfVerify, 0xd1a40ef4); /* cellPamf */


#endif
