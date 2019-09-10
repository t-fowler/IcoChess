#include <iostream>
#include "IcoUtil.h"
#include <intrin.h>

#include "BitManipulation.h"

#pragma intrinsic(_BitScanForward64)
#pragma intrinsic(_BitScanReverse64)

void printBB(bb64 bitboard)
{
	for (int rank = 7; rank >= 0; rank--) {
		for (int file = 0; file < 8; file++) {
			if (bbBitTest(bitboard, (8 * rank + file))) {
				std::cout << "1" << " ";
			}
			else {
				std::cout << ". ";
			}
		}
		std::cout << std::endl;
	}
}

int popCount64(bb64 bitset) {
	unsigned long long	k1 = 0x5555555555555555ULL,
						k2 = 0x3333333333333333ULL,
						k3 = 0x0f0f0f0f0f0f0f0fULL,
						k4 = 0x0101010101010101ULL;

	/* First put the count of each duo of bits into that duo. */
	bitset = bitset - ((bitset >> 1) & k1);

	/* Next put count of each nibble into the nibble */
	bitset = (bitset & k2) + ((bitset >> 2) & k2);

	/* Put count of each byte into that byte */
	bitset = (bitset + (bitset >> 4)) & k3;

	/* put the final result in the the most significant byte */
	bitset = (bitset * k4) >> 56;

	return int(bitset);
}

int bitScanForward(unsigned long long bitset)
{
	unsigned long index;
	_BitScanForward64(&index, bitset);		//Visual C++ intrinsic
	return index;
}

int bitScanReverse(unsigned long long bitset)
{
	unsigned long index;
	_BitScanReverse64(&index, bitset);		//Visual C++ intrinsic
	return index;
}

bb64 northOne(bb64 bb) { return bb << 8; }

bb64 norEastOne(bb64 bb) { return northOne(eastOne(bb)); }

bb64 eastOne(bb64 bb) { return (bb << 1) & ~FILES[aFile]; }

bb64 southOne(bb64 bb) { return bb >> 8; }

bb64 souEastOne(bb64 bb) { return southOne(eastOne(bb)); }

bb64 westOne(bb64 bb) { return (bb >> 1) & ~FILES[hFile]; }

bb64 norWestOne(bb64 bb) { return northOne(westOne(bb)); }

bb64 souWestOne(bb64 bb) { return southOne(westOne(bb)); }