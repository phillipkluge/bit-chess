#pragma once
#include <string>
#include <vector>

typedef unsigned long long UINT64;
class Board
{
private:
	void precalculateData();
public:
	UINT64 whitePieces;
	UINT64 blackPieces;
	UINT64 occupied;

	UINT64 whitePawns;
	UINT64 whiteBishops;
	UINT64 whiteKnights;
	UINT64 whiteRooks;
	UINT64 whiteQueens;
	UINT64 whiteKings;

	UINT64 blackPawns;
	UINT64 blackBishops;
	UINT64 blackKnights;
	UINT64 blackRooks;
	UINT64 blackQueens;
	UINT64 blackKings;

	static const UINT64 ONE = 1;
	static const UINT64 ZERO = 0;

	std::vector<std::vector<int> > numSqrToEdge;
	std::vector<int> dirOffsets;
public:
	Board();
	void initializeBoardFromArray(std::string boardArray[8][8]);
};
