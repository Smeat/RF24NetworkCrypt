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
/**
 * Example of an encryption algorithm to use with this library.
 *
 * FIXME: Seems a little bit hacky
 */
#ifndef ENCRYPTIONXTEA_H_
#define ENCRYPTIONXTEA_H_

#include <stdint.h>

namespace EncryptionXTEA {

	extern uint8_t _cycles;
	extern uint32_t _key[4];

	extern void encipher (uint8_t num_cycles, uint32_t v[2], uint32_t const k[4]);

	extern void decipher (uint8_t num_cycles, uint32_t v[2], uint32_t const k[4]);


	extern void xtea_loop(void* message, const uint16_t len, void (*function)(uint8_t, uint32_t*, const uint32_t*));

	/**
	 *
	 * @param message
	 * @param encrypted
	 * @param len length in blocks
	 */
	extern void encrypt(void* message, const uint16_t len);
	extern void decrypt(void* message, const uint16_t len);

	extern void setKey(uint32_t k0, uint32_t k1, uint32_t k2, uint32_t k3);
	extern void setCycles(uint8_t cylces);

}

#endif
