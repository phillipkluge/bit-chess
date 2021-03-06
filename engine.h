#pragma once
#include "board.h"
#include "moves.h"
#include <vector>
class Engine
{
private:
	Board board;
	std::vector<std::vector<UINT64> > slidingRayAttacks;
	bool whiteToMove;
private:
	//std::vector<int> generateAllMoves();
	void generateSlidingMoves(std::vector<int>& moves);
    void slidingPieceMoves(std::vector<int>& allMoves, Moves::Pieces pieceType, UINT64 pieceBoard, UINT64 friendly, UINT64 enemy, Moves::Pieces frCol, Moves::Pieces enCol);
	void generatePawnMoves(std::vector<int> &moves);
	void generateKnightMoves(std::vector<int> &moves);
	void generateKingMoves(std::vector<int> &moves);
	void makeMove(int move);
	void unmakeMove();
	void precalculateSlidingAttacks();
	Moves::Pieces getEnPieceType(int currLoc, Moves::Pieces enCol);
public:
	Engine();
	std::vector<int> generateAllMoves();
	UINT64 getRayAttacks(Moves::Pieces p, size_t idx);
	long long moveGenerationTest(int depth);
};
