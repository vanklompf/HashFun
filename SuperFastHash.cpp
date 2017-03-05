/*
 * SuperFastHash.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: fkorta
 */

#include "hash/SuperFastHash.h"
#include <stdint.h>

// Taken from http://www.azillionmonkeys.com/qed/hash.html
// known as the 'Hsieh' hash or 'SuperFastHash'
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )

// set hash to 'len' if you don't want to merge an existing hash value
uint32_t SuperFastHash(const uint8_t * data, int len)
{
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || data == nullptr)
        return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (; len > 0; len--)
    {
        hash += get16bits(data);
        tmp = (get16bits (data+2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        data += 2 * sizeof(uint16_t);
        hash += hash >> 11;
    }

    /* Handle end cases */
    switch (rem)
    {
    case 3:
        hash += get16bits(data);
        hash ^= hash << 16;
        hash ^= data[sizeof(uint16_t)] << 18;
        hash += hash >> 11;
        break;
    case 2:
        hash += get16bits(data);
        hash ^= hash << 11;
        hash += hash >> 17;
        break;
    case 1:
        hash += *data;
        hash ^= hash << 10;
        hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

