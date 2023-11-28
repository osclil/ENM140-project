/* piece.h */

#ifndef PIECE_H
#define PIECE_H

#include <cstdint>
#include <type_traits>

enum class piece : std::uint8_t
{
	/* Empty board */
	e_EMPTY,
	/* Black Pieces */
	e_BLACK_PAWN,
	e_BLACK_KNIGHT,
	e_BLACK_BISHOP,
	e_BLACK_ROOK,
	e_BLACK_QUEEN,
	e_BLACK_KING,
	/* White pieces */
	e_WHITE_PAWN,
	e_WHITE_KNIGHT,
	e_WHITE_BISHOP,
	e_WHITE_ROOK,
	e_WHITE_QUEEN,
	e_WHITE_KING,
	/* Off board*/
	e_VOID
};


inline std::uint8_t to_underlying(const piece &p)
{
	return static_cast<std::underlying_type<piece>::type>(p);
}

#endif /* PIECE_H */

