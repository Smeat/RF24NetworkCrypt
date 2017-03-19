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
 * FIXME: Vulnerable to replay attack
 */

#ifndef RF24NETWORKCRYPT_H_
#define RF24NETWORKCRYPT_H_

#include <RF24Network/RF24Network.h>

class RF24NetworkCrypt {
public:
	/**
	 *
	 * @param network RF24Network object
	 * @param encrypt pointer to a function for encryption
	 * @param decrypt pointer to a function for decryption
	 * @param blocksize blocksize of the used algorithm in bits
	 */
	RF24NetworkCrypt(RF24Network& network, void (*encrypt)(void*, const uint16_t), void (*decrypt)(void*, const uint16_t), uint16_t blocksize);

	/**
	 * Send an encrypted message
	 * @param header
	 * @param message
	 * @param length
	 * @return
	 */
	bool write(RF24NetworkHeader& header, const void* message, uint16_t length);

	/**
	 * Read an encrypted message
	 * @param header
	 * @param message
	 * @param length
	 * @return
	 */
	uint16_t read(RF24NetworkHeader& header, void* message, uint16_t length);


private:
	RF24Network& _network;
	void (*_encrypt)(void*, const uint16_t);
	void (*_decrypt)(void*, const uint16_t);
	uint16_t _blocksize;


};

#endif /* RF24NETWORKCRYPT_H_ */
