/*******************************************************************************
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License version 2 as published by
 *     the Free Software Foundation.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/
#include "EncryptionXTEA.h"

    uint8_t EncryptionXTEA::_cycles = 32;
    uint32_t EncryptionXTEA::_key[4] = {0,0,0,0};

	void EncryptionXTEA::setKey(uint32_t k0, uint32_t k1, uint32_t k2, uint32_t k3){
		_key[0] = k0;
		_key[1] = k1;
		_key[2] = k2;
		_key[3] = k3;
	}
	void EncryptionXTEA::setCycles(uint8_t cylces){
		_cycles = cylces;
	}

	void EncryptionXTEA::encipher (uint8_t num_cycles, uint32_t v[2], uint32_t const k[4]) {
		unsigned int i;
		const uint32_t delta = 0x9E3779B9;
		uint32_t v0 = v[0], v1 = v[1], sum = 0;
		for (i=0; i < num_cycles; i++) {
			v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
			sum += delta;
			v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
		}
		v[0] = v0; v[1] = v1;
	}

	void EncryptionXTEA::decipher (uint8_t num_cycles, uint32_t v[2], uint32_t const k[4]) {
		unsigned int i;
		const uint32_t delta = 0x9E3779B9;
		uint32_t v0 = v[0], v1 = v[1], sum = delta * num_cycles;
		for (i=0; i < num_cycles; i++) {
			v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
			sum -= delta;
			v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
		}
		v[0] = v0; v[1] = v1;
	}


	void EncryptionXTEA::xtea_loop(void* message, const uint16_t len, void (*function)(uint8_t, uint32_t*, const uint32_t*)){ //saves about 36 bytes
		for(uint16_t i = 0; i < len; ++i){
			uint32_t* msg_uint = (uint32_t*) message;
			function(_cycles, msg_uint + i*2,_key); //pass msg as pointer pointing to next block
		}
	}

	/**
	 *
	 * @param message
	 * @param encrypted
	 * @param len length in blocks
	 */
	void EncryptionXTEA::encrypt(void* message, const uint16_t len){
		xtea_loop(message, len, &encipher);
	}
	void EncryptionXTEA::decrypt(void* message, const uint16_t len){
		xtea_loop(message, len, &decipher);
	}
