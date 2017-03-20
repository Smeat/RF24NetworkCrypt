/*
 * EncryptionAES.h
 *
 *  Created on: 20.03.2017
 *      Author: kevin
 */

#ifndef SRC_ENCRYPTIONAES_H_
#define SRC_ENCRYPTIONAES_H_

#include <aes/aes.h>

namespace EncryptionAES{

extern aes256_ctx_t _ctx;

extern void init(const void* key);

extern void encrypt(void* message, const uint16_t len);
extern void decrypt(void* message, const uint16_t len);
}

#endif /* SRC_ENCRYPTIONAES_H_ */
