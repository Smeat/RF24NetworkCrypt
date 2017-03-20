#include "EncryptionAES.h"


extern aes256_ctx_t EncryptionAES::_ctx;

void EncryptionAES::init(const void* key){
	aes256_init(key, &_ctx);
}

void EncryptionAES::encrypt(void* message, const uint16_t len){
	for(uint16_t i = 0; i < len; ++i){
		uint32_t* msg_uint = (uint32_t*) message;
		aes256_enc(msg_uint + i*4, &_ctx);
	}

}
void EncryptionAES::decrypt(void* message, const uint16_t len){
	for(uint16_t i = 0; i < len; ++i){
		uint32_t* msg_uint = (uint32_t*) message;
		aes256_dec(msg_uint + i*4, &_ctx);
	}
}
