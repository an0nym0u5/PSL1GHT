#ifndef __SSL_H__
#define __SSL_H__


#include <ssl/cert.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define SSL_CIPHER_UNKNOWN                         (-1)
#define SSL_CIPHER_RSA_WITH_3DES_EDE_CBC_SHA       (0)
#define SSL_CIPHER_RSA_WITH_RC4_128_SHA            (1)
#define SSL_CIPHER_RSA_WITH_RC4_128_MD5            (2)
#define SSL_CIPHER_RSA_WITH_DES_CBC_SHA            (3)
#define SSL_CIPHER_RSA_EXPORT1024_WITH_DES_CBC_SHA (4)
#define SSL_CIPHER_RSA_EXPORT1024_WITH_RC4_56_SHA  (5)
#define SSL_CIPHER_RSA_EXPORT_WITH_DES40_CBC_SHA   (6)
#define SSL_CIPHER_RSA_EXPORT_WITH_RC2_CBC_40_MD5  (7)
#define SSL_CIPHER_RSA_EXPORT_WITH_RC4_40_MD5      (8)

#define SSL_VERSION_UNKNOWN (-1)
#define SSL_VERSION_TLS1    (0)
#define SSL_VERSION_SSL3    (1)

int sslInit(void *pool, size_t poolSize);
int sslEnd(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SSL_H__ */

