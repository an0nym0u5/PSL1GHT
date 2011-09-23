#ifndef __EXPORTS_H__
#define __EXPORTS_H__

EXPORT(pngEncOpen, 0x19256dc5);
EXPORT(pngEncOpenEx, 0xc82558ce);
EXPORT(pngEncClose, 0x117cd726);
EXPORT(pngEncEncodePicture, 0x5b546ca4);
EXPORT(pngEncGetStreamInfo, 0x585269bc);
EXPORT(pngEncReset, 0x6ac91de3);
EXPORT(pngEncQueryAttr, 0x496cfcd0);
EXPORT(pngEncWaitForInput, 0x662bd637);
EXPORT(pngEncWaitForOutput, 0x90ef2963);

#endif
