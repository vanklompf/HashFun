/*
 * MurmurHash3.h
 *
 *  Created on: Mar 5, 2017
 *      Author: fkorta
 */

#ifndef MURMURHASH3_H_
#define MURMURHASH3_H_
#include <cstdint>

uint32_t MurmurHash3_x86_32(const uint8_t* data, int len);

#endif /* MURMURHASH3_H_ */
