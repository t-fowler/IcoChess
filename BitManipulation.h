#pragma once
#ifndef BIT_MANIP_H
#define BIT_MANIP_H
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <iostream>

namespace IcoChess
{

/****************************************************************
*		This file includes names and inline functions for		*
*	manipulating bitboards in the IcoChess program.				*
****************************************************************/

/****************************************************************
*		bbBitTest checks if a bit at a particular index is set	*
*	in a bitboard.												*
*																*
*	@param bb64 bb		-- the 64 bit bitboard to be tested.	*
*	@param int index	-- the position of the bit to be tested.*
*																*
*	@return bool		-- True if the bit is set,				*
*							False otherwise.					*
****************************************************************/
inline bool bbBitTest(bb64 bb, int index)
{
	if (index < 0 || index > 63) {
		throw std::out_of_range("bbBitSet index out of range");
	}
	return (bb & (1ULL << index));
}


/****************************************************************
*		bbSetBit uses reference semantics to set the bit at a	*
*	particular index in a bitboard.								*
*																*
*	@param bb64 &bb		-- the 64 bit bitboard.					*
*	@param int index	-- the position of the bit to be set.	*
****************************************************************/
inline void bbSetBit(bb64& bb, int index)
{
	if (index < 0 || index > 63) {
		throw std::out_of_range("bbBitSet index out of range");
	}
	bb |= (1LL << index);
}


/****************************************************************
*		bbSetBit uses reference semantics to reset the bit at a	*
*	particular index in a bitboard.								*
*																*
*	@param bb64 &bb		-- the 64 bit bitboard.					*
*	@param int index	-- the position of the bit to be reset.	*
****************************************************************/
inline void bbResetBit(bb64& bb, int index)
{
	if (index < 0 || index > 63) {
		throw std::out_of_range("bbBitSet index out of range");
	}
	bb &= ~(1LL << index);
}

inline bb64 bbReverse(bb64 bb)
{
	bb64 ans = 0;
	for (int i = 63; i >= 0; i--) {
		ans |= (bb & 1) << i;
		bb >>= 1;
	}
	return ans;
}

/****************************************************************
*   msb returns only the most significant bit of the bitboard	*
*																*
*	@param bb64 bitset	-- the 64 bit bitboard.					*
****************************************************************/
inline bb64 msb(bb64 bitset)
{
	if (bitset == 0) return -1;

	int msb = 0;
	while (bitset != 0) {
		msb++;
		bitset /= 2;
	}

	return 1ULL << msb;
}

/****************************************************************
*		printBB prints a bitboard to the console for a			*
*	chessboard like	visual representation of the bits.			*
*																*
*	@param bb64 bitboard -- the 64 bit bitboard to be printed.	*
****************************************************************/
void printBB(bb64 bitboard);

/****************************************************************
*		popCount64 returns the cardinality (number of 1 bits)	*
*	of a 64 bit integer.										*													*
*																*
*	@param bb64 bitset	-- the 64 bit integer to count.			*
*																*
*	@return int			-- the cardinality of the integer		*
****************************************************************/
int popCount64(bb64 bitset);

/****************************************************************
*		bitScanForward finds the index of the LS1B of a 64 bit 	*
*	unsigned integer and returns the index as an int.			*
*																*
*	@param  bitset			-- the number to be scanned.		*
*																*
*	@return int				-- the index of the LS1B			*
****************************************************************/
int bitScanForward(unsigned long long bitset);

/****************************************************************
*		bitScanReverse finds the index of the MS1B of a 64 bit 	*
*	unsigned integer and returns the index as an int.			*
*																*
*	@param  bitset			-- the number to be scanned.		*
*																*
*	@return int				-- the index of the MS1B			*
****************************************************************/
int bitScanReverse(unsigned long long bitset);

/****************************************************************
*		northOne alters a bitboard such that the set bits are  	*
*	one square north of their original square.					*
*																*
*	@param  bb				-- the bitboard to modify.			*
*																*
*	@return bb64			-- the modified bitboard.			*
****************************************************************/
bb64 northOne(bb64 bb);

/****************************************************************
*		northOne alters a bitboard such that the set bits are  	*
*	one square west of their original square. It does not allow	*
*	squares to wrap around the chess board.						*
*																*
*	@param  bb				-- the bitboard to modify.			*
*																*
*	@return bb64			-- the modified bitboard.			*
****************************************************************/
bb64 westOne(bb64 bb);

/****************************************************************
*		norWestOne alters a bitboard such that the set bits are	*
*	one square north west of their original square.	It does not	*
*	allow squares to wrap around the chess board.				*
*																*
*	@param  bb				-- the bitboard to modify.			*
*																*
*	@return bb64			-- the modified bitboard.			*
****************************************************************/
bb64 norWestOne(bb64 bb);

/****************************************************************
*		southOne alters a bitboard such that the set bits are  	*
*	one square south of their original square.					*
*																*
*	@param  bb				-- the bitboard to modify.			*
*																*
*	@return bb64			-- the modified bitboard.			*
****************************************************************/
bb64 southOne(bb64 bb);

/****************************************************************
*		souWestOne alters a bitboard such that the set bits are	*
*	one square south west of their original square.	It does not	*
*	allow squares to wrap around the chess board.				*
*																*
*	@param  bb				-- the bitboard to modify.			*
*																*
*	@return bb64			-- the modified bitboard.			*
****************************************************************/
bb64 souWestOne(bb64 bb);

/****************************************************************
*		eastOne alters a bitboard such that the set bits are	*
*	one square east of their original square. It does not allow	*
*	squares to wrap around the chess board.						*
*																*
*	@param  bb				-- the bitboard to modify.			*
*																*
*	@return bb64			-- the modified bitboard.			*
****************************************************************/
bb64 eastOne(bb64 bb);

/****************************************************************
*		norEastOne alters a bitboard such that the set bits are	*
*	one square north east of their original square.	It does not	*
*	allow squares to wrap around the chess board.				*
*																*
*	@param  bb				-- the bitboard to modify.			*
*																*
*	@return bb64			-- the modified bitboard.			*
****************************************************************/
bb64 norEastOne(bb64 bb);

/****************************************************************
*		souEastOne alters a bitboard such that the set bits are	*
*	one square south east of their original square.	It does not	*
*	allow squares to wrap around the chess board.				*
*																*
*	@param  bb				-- the bitboard to modify.			*
*																*
*	@return bb64			-- the modified bitboard.			*
****************************************************************/
bb64 souEastOne(bb64 bb);

/****************************************************************
*		printBits prints the bits of a number to the console 	*
*	int byte sized lines.										*
*																*
*	@T num				-- the number to be printed.			*
****************************************************************/
template <typename T>
inline void printBits(T num)
{
	for (int i = 0; i < sizeof(num) * 8; i++) {
		if (num & (1 << (8 * sizeof(num) - 1 - i)))
			std::cout << 1 << " ";
		else
			std::cout << ". ";
		if (i % 8 == 7) {
			std::cout << std::endl;
		}
	}
}

template <typename T>
inline std::string bitString(T num)
{
	std::string res;
	for (int i = 0; i < sizeof(num) * 8; i++) {
		if (num & (1 << (8 * sizeof(num) - 1 - i)))
			res += "1 ";
		else res += ". ";

		if (i % 8 == 7) {
			res += "\n";
		}
	}
	return res;
}

/****************************************************************
*		indexOf returns the index of the MSB in a bitboard	 	*
*	int byte sized lines.										*
*																*
*	@param bb				-- the bitboard to be used.			*
****************************************************************/
static inline int indexOf(const bb64 bb)
{
	bb64 tmp = bb;
	int index = 0;
	while (tmp >>= 1) index++;
	return index;
}

}
#endif		// Inclusion Guard