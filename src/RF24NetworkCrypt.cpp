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
/*
 * RF24NetworkCrypt.cpp
 *
 *  Created on: 18.12.2014
 *      Author: kevin
 */

#include "RF24NetworkCrypt.h"

#include <stdlib.h>

RF24NetworkCrypt::RF24NetworkCrypt(RF24Network& network, void (*encrypt)(void*, const uint16_t), void (*decrypt)(void*, const uint16_t), uint16_t blocksize) : _network(network), _encrypt(encrypt), _decrypt(decrypt), _blocksizeByte(blocksize/8){

}

bool RF24NetworkCrypt::write(RF24NetworkHeader& header, const void* message, uint16_t length) {
	//fill block
	uint16_t neededLength = _blocksizeByte * (((length-1)/_blocksizeByte) + 1);
	void* data = calloc(neededLength,1);
	memcpy(data, message, length);
	uint8_t blocks = neededLength/_blocksizeByte;

	_encrypt(data, blocks);
	bool ret = _network.write(header, data, neededLength);

	free(data);

	return ret;
}

uint16_t RF24NetworkCrypt::read(RF24NetworkHeader& header, void* message, uint16_t maxlen) {
	uint16_t neededLength = _blocksizeByte * (((maxlen-1)/_blocksizeByte) + 1);
	void* data = calloc(neededLength,1);
	_network.read(header, data, neededLength); //TODO: check size received
	uint8_t blocks = neededLength/_blocksizeByte;

	_decrypt(data, blocks);

	memcpy(message, data, maxlen);

	free(data);

	return maxlen;
}
