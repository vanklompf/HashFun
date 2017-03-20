/*
 * MurmurHash1.h
 *
 *  Created on: Mar 5, 2017
 *      Author: fkorta
 */

#ifndef HASH_MURMURHASH1_H_
#define HASH_MURMURHASH1_H_
#include <cstdint>

uint32_t MurmurHash1 (const uint8_t* data, int len);
uint32_t MurmurHash1Aligned(const uint8_t* data, int len);


#endif /* HASH_MURMURHASH1_H_ */
