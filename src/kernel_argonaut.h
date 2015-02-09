/*
 * Centaurean Density
 *
 * Copyright (c) 2015, Guillaume Voirin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Centaurean nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 5/02/15 20:57
 *
 * ------------------
 * Argonaut algorithm
 * ------------------
 *
 * Author(s)
 * Guillaume Voirin (https://github.com/gpnuma)
 *
 * Description
 * Word rank and predictions algorithm
 */

#ifndef DENSITY_ARGONAUT_H
#define DENSITY_ARGONAUT_H

#include <stdint.h>
#include "globals.h"

#define DENSITY_ARGONAUT_PREFERRED_BLOCK_SIGNATURES_SHIFT                    12
#define DENSITY_ARGONAUT_PREFERRED_BLOCK_SIGNATURES                          (1 << DENSITY_ARGONAUT_PREFERRED_BLOCK_SIGNATURES_SHIFT)

#define DENSITY_ARGONAUT_PREFERRED_EFFICIENCY_CHECK_SIGNATURES_SHIFT         8
#define DENSITY_ARGONAUT_PREFERRED_EFFICIENCY_CHECK_SIGNATURES               (1 << DENSITY_ARGONAUT_PREFERRED_EFFICIENCY_CHECK_SIGNATURES_SHIFT)

#define DENSITY_ARGONAUT_HASH32_MULTIPLIER                                   (uint32_t)0x9D6EF916lu
#define DENSITY_ARGONAUT_HASH64_MULTIPLIER                                   (uint32_t)0x9D6EF9169D6EF916llu

#define FORMAT(v)               0##v##llu

#define ISOLATE(b, p)           ((FORMAT(b) / p) & 0x1)

#define BINARY_TO_UINT(b)        ((ISOLATE(b, 1llu) ? 0x1 : 0)\
                                + (ISOLATE(b, 8llu) ? 0x2 : 0)\
                                + (ISOLATE(b, 64llu) ? 0x4 : 0)\
                                + (ISOLATE(b, 512llu) ? 0x8 : 0)\
                                + (ISOLATE(b, 4096llu) ? 0x10 : 0)\
                                + (ISOLATE(b, 32768llu) ? 0x20 : 0)\
                                + (ISOLATE(b, 262144llu) ? 0x40 : 0)\
                                + (ISOLATE(b, 2097152llu) ? 0x80 : 0)\
                                + (ISOLATE(b, 16777216llu) ? 0x100 : 0)\
                                + (ISOLATE(b, 134217728llu) ? 0x200 : 0)\
                                + (ISOLATE(b, 1073741824llu) ? 0x400 : 0)\
                                + (ISOLATE(b, 8589934592llu) ? 0x800 : 0)\
                                + (ISOLATE(b, 68719476736llu) ? 0x1000 : 0)\
                                + (ISOLATE(b, 549755813888llu) ? 0x2000 : 0)\
                                + (ISOLATE(b, 4398046511104llu) ? 0x4000 : 0)\
                                + (ISOLATE(b, 35184372088832llu) ? 0x8000 : 0)\
                                + (ISOLATE(b, 281474976710656llu) ? 0x10000 : 0)\
                                + (ISOLATE(b, 2251799813685248llu) ? 0x20000 : 0))

#define DENSITY_ARGONAUT_HUFFMAN_CODES {\
    {BINARY_TO_UINT(100), 3},\
    {BINARY_TO_UINT(001), 3},\
    {BINARY_TO_UINT(11111), 5},\
    {BINARY_TO_UINT(01010), 5},\
    {BINARY_TO_UINT(111010), 6},\
    {BINARY_TO_UINT(110101), 6},\
    {BINARY_TO_UINT(110011), 6},\
    {BINARY_TO_UINT(110010), 6},\
    {BINARY_TO_UINT(110000), 6},\
    {BINARY_TO_UINT(101100), 6},\
    {BINARY_TO_UINT(101000), 6},\
    {BINARY_TO_UINT(011110), 6},\
    {BINARY_TO_UINT(011101), 6},\
    {BINARY_TO_UINT(011001), 6},\
    {BINARY_TO_UINT(010000), 6},\
    {BINARY_TO_UINT(000110), 6},\
    {BINARY_TO_UINT(000011), 6},\
    {BINARY_TO_UINT(1111000), 7},\
    {BINARY_TO_UINT(1110110), 7},\
    {BINARY_TO_UINT(1110010), 7},\
    {BINARY_TO_UINT(1101111), 7},\
    {BINARY_TO_UINT(1101001), 7},\
    {BINARY_TO_UINT(1100010), 7},\
    {BINARY_TO_UINT(1011110), 7},\
    {BINARY_TO_UINT(1011101), 7},\
    {BINARY_TO_UINT(1010101), 7},\
    {BINARY_TO_UINT(1010010), 7},\
    {BINARY_TO_UINT(0111111), 7},\
    {BINARY_TO_UINT(0110101), 7},\
    {BINARY_TO_UINT(0110001), 7},\
    {BINARY_TO_UINT(0110000), 7},\
    {BINARY_TO_UINT(0100101), 7},\
    {BINARY_TO_UINT(0001111), 7},\
    {BINARY_TO_UINT(0001010), 7},\
    {BINARY_TO_UINT(0000001), 7},\
    {BINARY_TO_UINT(0000000), 7},\
    {BINARY_TO_UINT(11110111), 8},\
    {BINARY_TO_UINT(11110101), 8},\
    {BINARY_TO_UINT(11110011), 8},\
    {BINARY_TO_UINT(11101111), 8},\
    {BINARY_TO_UINT(11101110), 8},\
    {BINARY_TO_UINT(11100010), 8},\
    {BINARY_TO_UINT(11011101), 8},\
    {BINARY_TO_UINT(11011100), 8},\
    {BINARY_TO_UINT(11011011), 8},\
    {BINARY_TO_UINT(11011010), 8},\
    {BINARY_TO_UINT(11011000), 8},\
    {BINARY_TO_UINT(11000111), 8},\
    {BINARY_TO_UINT(10111111), 8},\
    {BINARY_TO_UINT(10111110), 8},\
    {BINARY_TO_UINT(10111000), 8},\
    {BINARY_TO_UINT(10110111), 8},\
    {BINARY_TO_UINT(10110101), 8},\
    {BINARY_TO_UINT(10101111), 8},\
    {BINARY_TO_UINT(10101110), 8},\
    {BINARY_TO_UINT(10101000), 8},\
    {BINARY_TO_UINT(10100110), 8},\
    {BINARY_TO_UINT(01111101), 8},\
    {BINARY_TO_UINT(01110001), 8},\
    {BINARY_TO_UINT(01101111), 8},\
    {BINARY_TO_UINT(01101110), 8},\
    {BINARY_TO_UINT(01101100), 8},\
    {BINARY_TO_UINT(01011111), 8},\
    {BINARY_TO_UINT(01011110), 8},\
    {BINARY_TO_UINT(01011011), 8},\
    {BINARY_TO_UINT(01011010), 8},\
    {BINARY_TO_UINT(01001111), 8},\
    {BINARY_TO_UINT(01001100), 8},\
    {BINARY_TO_UINT(01001001), 8},\
    {BINARY_TO_UINT(01001000), 8},\
    {BINARY_TO_UINT(01000110), 8},\
    {BINARY_TO_UINT(00011100), 8},\
    {BINARY_TO_UINT(00010011), 8},\
    {BINARY_TO_UINT(00010000), 8},\
    {BINARY_TO_UINT(00001010), 8},\
    {BINARY_TO_UINT(00001001), 8},\
    {BINARY_TO_UINT(00001000), 8},\
    {BINARY_TO_UINT(00000110), 8},\
    {BINARY_TO_UINT(111101101), 9},\
    {BINARY_TO_UINT(111101000), 9},\
    {BINARY_TO_UINT(111100101), 9},\
    {BINARY_TO_UINT(111001101), 9},\
    {BINARY_TO_UINT(111000111), 9},\
    {BINARY_TO_UINT(111000110), 9},\
    {BINARY_TO_UINT(111000010), 9},\
    {BINARY_TO_UINT(111000001), 9},\
    {BINARY_TO_UINT(110100011), 9},\
    {BINARY_TO_UINT(110100010), 9},\
    {BINARY_TO_UINT(110100001), 9},\
    {BINARY_TO_UINT(101110010), 9},\
    {BINARY_TO_UINT(101101001), 9},\
    {BINARY_TO_UINT(101101000), 9},\
    {BINARY_TO_UINT(101011010), 9},\
    {BINARY_TO_UINT(101011001), 9},\
    {BINARY_TO_UINT(101011000), 9},\
    {BINARY_TO_UINT(011111001), 9},\
    {BINARY_TO_UINT(011100101), 9},\
    {BINARY_TO_UINT(011100100), 9},\
    {BINARY_TO_UINT(011100001), 9},\
    {BINARY_TO_UINT(011010011), 9},\
    {BINARY_TO_UINT(010111010), 9},\
    {BINARY_TO_UINT(010111000), 9},\
    {BINARY_TO_UINT(010110010), 9},\
    {BINARY_TO_UINT(010110000), 9},\
    {BINARY_TO_UINT(010011100), 9},\
    {BINARY_TO_UINT(010011010), 9},\
    {BINARY_TO_UINT(010001011), 9},\
    {BINARY_TO_UINT(000111011), 9},\
    {BINARY_TO_UINT(000111010), 9},\
    {BINARY_TO_UINT(000101111), 9},\
    {BINARY_TO_UINT(000101101), 9},\
    {BINARY_TO_UINT(000100101), 9},\
    {BINARY_TO_UINT(000010111), 9},\
    {BINARY_TO_UINT(000010110), 9},\
    {BINARY_TO_UINT(000001011), 9},\
    {BINARY_TO_UINT(000001001), 9},\
    {BINARY_TO_UINT(1111011001), 10},\
    {BINARY_TO_UINT(1111011000), 10},\
    {BINARY_TO_UINT(1111010010), 10},\
    {BINARY_TO_UINT(1111001001), 10},\
    {BINARY_TO_UINT(1111001000), 10},\
    {BINARY_TO_UINT(1110011110), 10},\
    {BINARY_TO_UINT(1110011001), 10},\
    {BINARY_TO_UINT(1110000110), 10},\
    {BINARY_TO_UINT(1110000000), 10},\
    {BINARY_TO_UINT(1101000001), 10},\
    {BINARY_TO_UINT(1101000000), 10},\
    {BINARY_TO_UINT(1100011010), 10},\
    {BINARY_TO_UINT(1100011001), 10},\
    {BINARY_TO_UINT(1100011000), 10},\
    {BINARY_TO_UINT(1011100111), 10},\
    {BINARY_TO_UINT(1011100110), 10},\
    {BINARY_TO_UINT(1011011011), 10},\
    {BINARY_TO_UINT(1011011001), 10},\
    {BINARY_TO_UINT(1011011000), 10},\
    {BINARY_TO_UINT(1010100111), 10},\
    {BINARY_TO_UINT(1010100110), 10},\
    {BINARY_TO_UINT(1010100100), 10},\
    {BINARY_TO_UINT(1010011110), 10},\
    {BINARY_TO_UINT(1010011100), 10},\
    {BINARY_TO_UINT(0111110000), 10},\
    {BINARY_TO_UINT(0111001110), 10},\
    {BINARY_TO_UINT(0110110100), 10},\
    {BINARY_TO_UINT(0110100101), 10},\
    {BINARY_TO_UINT(0110100011), 10},\
    {BINARY_TO_UINT(0110100010), 10},\
    {BINARY_TO_UINT(0110100000), 10},\
    {BINARY_TO_UINT(0101110110), 10},\
    {BINARY_TO_UINT(0101110010), 10},\
    {BINARY_TO_UINT(0100111010), 10},\
    {BINARY_TO_UINT(0100110111), 10},\
    {BINARY_TO_UINT(0100011111), 10},\
    {BINARY_TO_UINT(0100011101), 10},\
    {BINARY_TO_UINT(0100011100), 10},\
    {BINARY_TO_UINT(0100010101), 10},\
    {BINARY_TO_UINT(0100010100), 10},\
    {BINARY_TO_UINT(0100010011), 10},\
    {BINARY_TO_UINT(0100010010), 10},\
    {BINARY_TO_UINT(0100010000), 10},\
    {BINARY_TO_UINT(0001011101), 10},\
    {BINARY_TO_UINT(0001011100), 10},\
    {BINARY_TO_UINT(0001011001), 10},\
    {BINARY_TO_UINT(0001001001), 10},\
    {BINARY_TO_UINT(0001001000), 10},\
    {BINARY_TO_UINT(0001000111), 10},\
    {BINARY_TO_UINT(0001000110), 10},\
    {BINARY_TO_UINT(0001000101), 10},\
    {BINARY_TO_UINT(0001000100), 10},\
    {BINARY_TO_UINT(0000011111), 10},\
    {BINARY_TO_UINT(0000011110), 10},\
    {BINARY_TO_UINT(0000011101), 10},\
    {BINARY_TO_UINT(0000011100), 10},\
    {BINARY_TO_UINT(0000010101), 10},\
    {BINARY_TO_UINT(0000010100), 10},\
    {BINARY_TO_UINT(0000010001), 10},\
    {BINARY_TO_UINT(0000010000), 10},\
    {BINARY_TO_UINT(11110100111), 11},\
    {BINARY_TO_UINT(11110100110), 11},\
    {BINARY_TO_UINT(11100111111), 11},\
    {BINARY_TO_UINT(11100111110), 11},\
    {BINARY_TO_UINT(11100111011), 11},\
    {BINARY_TO_UINT(11100111010), 11},\
    {BINARY_TO_UINT(11100111001), 11},\
    {BINARY_TO_UINT(11100111000), 11},\
    {BINARY_TO_UINT(11100110001), 11},\
    {BINARY_TO_UINT(11100110000), 11},\
    {BINARY_TO_UINT(11100001111), 11},\
    {BINARY_TO_UINT(11100001110), 11},\
    {BINARY_TO_UINT(11100000011), 11},\
    {BINARY_TO_UINT(11100000010), 11},\
    {BINARY_TO_UINT(11011001111), 11},\
    {BINARY_TO_UINT(11011001110), 11},\
    {BINARY_TO_UINT(11011001101), 11},\
    {BINARY_TO_UINT(11011001100), 11},\
    {BINARY_TO_UINT(11011001011), 11},\
    {BINARY_TO_UINT(11011001010), 11},\
    {BINARY_TO_UINT(11011001001), 11},\
    {BINARY_TO_UINT(11011001000), 11},\
    {BINARY_TO_UINT(11000110111), 11},\
    {BINARY_TO_UINT(11000110110), 11},\
    {BINARY_TO_UINT(10110110101), 11},\
    {BINARY_TO_UINT(10110110100), 11},\
    {BINARY_TO_UINT(10101101111), 11},\
    {BINARY_TO_UINT(10101101110), 11},\
    {BINARY_TO_UINT(10101101101), 11},\
    {BINARY_TO_UINT(10101101100), 11},\
    {BINARY_TO_UINT(10101001011), 11},\
    {BINARY_TO_UINT(10101001010), 11},\
    {BINARY_TO_UINT(10100111111), 11},\
    {BINARY_TO_UINT(10100111110), 11},\
    {BINARY_TO_UINT(10100111011), 11},\
    {BINARY_TO_UINT(10100111010), 11},\
    {BINARY_TO_UINT(01111100011), 11},\
    {BINARY_TO_UINT(01111100010), 11},\
    {BINARY_TO_UINT(01110011111), 11},\
    {BINARY_TO_UINT(01110011110), 11},\
    {BINARY_TO_UINT(01110011011), 11},\
    {BINARY_TO_UINT(01110011010), 11},\
    {BINARY_TO_UINT(01110011001), 11},\
    {BINARY_TO_UINT(01110011000), 11},\
    {BINARY_TO_UINT(01110000011), 11},\
    {BINARY_TO_UINT(01110000010), 11},\
    {BINARY_TO_UINT(01110000001), 11},\
    {BINARY_TO_UINT(01110000000), 11},\
    {BINARY_TO_UINT(01101101111), 11},\
    {BINARY_TO_UINT(01101101110), 11},\
    {BINARY_TO_UINT(01101101101), 11},\
    {BINARY_TO_UINT(01101101100), 11},\
    {BINARY_TO_UINT(01101101011), 11},\
    {BINARY_TO_UINT(01101101010), 11},\
    {BINARY_TO_UINT(01101001001), 11},\
    {BINARY_TO_UINT(01101001000), 11},\
    {BINARY_TO_UINT(01101000011), 11},\
    {BINARY_TO_UINT(01101000010), 11},\
    {BINARY_TO_UINT(01011101111), 11},\
    {BINARY_TO_UINT(01011101110), 11},\
    {BINARY_TO_UINT(01011100111), 11},\
    {BINARY_TO_UINT(01011100110), 11},\
    {BINARY_TO_UINT(01011001111), 11},\
    {BINARY_TO_UINT(01011001110), 11},\
    {BINARY_TO_UINT(01011001101), 11},\
    {BINARY_TO_UINT(01011001100), 11},\
    {BINARY_TO_UINT(01011000111), 11},\
    {BINARY_TO_UINT(01011000110), 11},\
    {BINARY_TO_UINT(01011000101), 11},\
    {BINARY_TO_UINT(01011000100), 11},\
    {BINARY_TO_UINT(01001110111), 11},\
    {BINARY_TO_UINT(01001110110), 11},\
    {BINARY_TO_UINT(01001101101), 11},\
    {BINARY_TO_UINT(01001101100), 11},\
    {BINARY_TO_UINT(01000111101), 11},\
    {BINARY_TO_UINT(01000111100), 11},\
    {BINARY_TO_UINT(01000100011), 11},\
    {BINARY_TO_UINT(01000100010), 11},\
    {BINARY_TO_UINT(00010110001), 11},\
    {BINARY_TO_UINT(00010110000), 11},\
}

typedef struct {
    uint_fast32_t code;
    uint_fast8_t bitSize;
} density_argonaut_huffman_code;

static const density_argonaut_huffman_code density_argonaut_huffman_codes[256] = DENSITY_ARGONAUT_HUFFMAN_CODES;

typedef enum {
    DENSITY_ARGONAUT_ENTITY_PREDICTIONS = 0,
    DENSITY_ARGONAUT_ENTITY_RANK = 1,
    DENSITY_ARGONAUT_ENTITY_DICTIONARY = 2,
    DENSITY_ARGONAUT_ENTITY_ENCODED = 3
} DENSITY_ARGONAUT_ENTITY;

typedef uint64_t density_argonaut_signature;

#endif