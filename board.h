#pragma once
#include <string>
#include <vector>

typedef unsigned long long UINT64;
class Board
{
private:
	void precalculateData();
public:
	UINT64 **pieceBoards;
	/*
	           0            1           2           3             4             5           6
	0 -> {whitePieces, whiteKings, whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens}
	1 -> {blackPieces, blackKings, blackPawns, blackKnights, blackBishops, blackRooks, blackQueens}
	
	*/

	UINT64 occupied;
	UINT64 unoccupied;

	static const UINT64 ONE = 1;
	static const UINT64 ZERO = 0;

	std::vector<std::vector<int> > numSqrToEdge;
	std::vector<int> dirOffsets;
public:
	Board();
	void initializeBoardFromArray(std::string boardArray[8][8]);
};
