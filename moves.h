#pragma once
class Moves
{
public:
	enum Flags {
		NONE = 0,
		DOUBLE_PAWN_PUSH = 1, // MAY NOT BE NEEDED
		KING_CASTLE = 2,
		QUEEN_CASTLE = 3,
		CAPTURES = 4, //MAY NOT BE NEEDED
		EN_PASSANT = 5,
		KNIGHT_PROMOTION = 8,
		BISHOP_PROMOTION = 9,
		ROOK_PROMOTION = 10,
		QUEEN_PROMOTION = 11,
		KNIGHT_PROMOTION_CAPTURE = 12,
		BISHOP_PROMOTION_CAPTURE = 13,
		ROOK_PROMOTION_CAPTURE = 14,
		QUEEN_PROMOTION_CAPTURE = 15
	};

	enum Pieces {
		EMPTY = 0,
		KING = 1,
		PAWN = 2,
		KNIGHT = 3,
		BISHOP = 4,
		ROOK = 5,
		QUEEN = 6,
		WHITE = 8,
		BLACK = 16
	};

	static int encodeMove(int endSqr, int stSqr, int flag, int pieceMoved, int pieceCaptured);
};
 
