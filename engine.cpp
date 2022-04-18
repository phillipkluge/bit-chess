#include "engine.h"
#include "moves.h"
#include <iostream>

Engine::Engine()
{
	whiteToMove = true;
	precalculateSlidingAttacks();
}

long long Engine::moveGenerationTest(int depth)
{
	if (depth == 0) return 1;

	std::vector<int> moves = generateAllMoves();
	long long numPositions = 0;

	for (const int& m : moves)
	{
		makeMove(m);
		numPositions += moveGenerationTest(depth - 1);
		unmakeMove();
	}

	return numPositions;
}

std::vector<int> Engine::generateAllMoves()
{
	std::vector<int> allMoves;
	allMoves.reserve(128);

	generateSlidingMoves(allMoves);
	generatePawnMoves(allMoves);
	generateKnightMoves(allMoves);
	generateKingMoves(allMoves);

	return allMoves;
}

void Engine::generateSlidingMoves(std::vector<int>& allMoves)
{
	UINT64 bishops, rooks, queens, friendly, enemy;
	Moves::Pieces frCol, enCol;

	if (whiteToMove)
	{
		bishops = board.whiteBishops;
		rooks = board.whiteRooks;
		queens = board.whiteQueens;
		friendly = board.whitePieces;
		frCol = Moves::WHITE;
		enemy = board.blackPieces;
		enCol = Moves::BLACK;
	}
	else
	{
		bishops = board.blackBishops;
		rooks = board.whiteRooks;
		queens = board.blackQueens;
		friendly = board.blackPieces;
		frCol = Moves::BLACK;
		enemy = board.whitePieces;
		enCol = Moves::WHITE;
	}

	// for the bishops
	// goes through each of the bishops positions and finds valid moves
	while (bishops)
	{
		int bitOffSet = __builtin_ffsll(bishops) - 1; // gets the position of the next set bit
		bishops &= bishops-1; // sets that bit to 0

		UINT64 rayAttack = getRayAttacks(Moves::BISHOP, bitOffSet);
		UINT64 friendlyInVision = rayAttack & friendly;
		UINT64 enemyInVision = rayAttack & enemy;

		for (int i = 4; i < 8; ++i)
		{
			int numSquares = board.numSqrToEdge[bitOffSet][i];
			for (int j = 0; j < numSquares; ++j)
			{
				int currMove = 0;
				int currLoc = bitOffSet + (j * board.dirOffsets[i]);
				if (friendlyInVision & (board.ONE << currLoc))
				{
					break;
				}
				else if (enemyInVision & (board.ONE << currLoc))
				{
					// encode the move
					int currMove = Moves::encodeMove(currLoc, bitOffSet, Moves::NONE, frCol, enCol);
				}
				else
				{
					// encode the move
					int currMove = Moves::encodeMove(currLoc, bitOffSet, Moves::NONE, frCol, Moves::NONE);

				}
				allMoves.push_back(currMove);
			}
		}
	}

	// for the rooks
	// goes through each of the rooks positions and finds valid moves
	while (rooks)
	{
		int bitOffSet = __builtin_ffsll(rooks) - 1; // gets the position of the next set bit
		rooks &= rooks-1; // sets that bit to 0

		UINT64 rayAttack = getRayAttacks(Moves::ROOK, bitOffSet);
		UINT64 friendlyInVision = rayAttack & friendly;
		UINT64 enemyInVision = rayAttack & enemy;

		for (int i = 0; i < 4; ++i)
		{
			int numSquares = board.numSqrToEdge[bitOffSet][i];
			for (int j = 0; j < numSquares; ++j)
			{
				int currMove = 0;
				int currLoc = bitOffSet + (j * board.dirOffsets[i]);
				if (friendlyInVision & (board.ONE << currLoc))
				{
					break;
				}
				else if (enemyInVision & (board.ONE << currLoc))
				{
					// encode the move
					int currMove = Moves::encodeMove(currLoc, bitOffSet, Moves::NONE, frCol, enCol);
				}
				else
				{
					// encode the move
					int currMove = Moves::encodeMove(currLoc, bitOffSet, Moves::NONE, frCol, Moves::NONE);

				}
				allMoves.push_back(currMove);
			}
		}
	}

	// for the queens
	while (queens)
	{
		int bitOffSet = __builtin_ffsll(queens) - 1; // gets the position of the next set bit
		queens &= queens-1; // sets that bit to 0

		UINT64 rayAttack = getRayAttacks(Moves::QUEEN, bitOffSet);
		UINT64 friendlyInVision = rayAttack & friendly;
		UINT64 enemyInVision = rayAttack & enemy;

		for (int i = 0; i < 8; ++i)
		{
			int numSquares = board.numSqrToEdge[bitOffSet][i];
			for (int j = 0; j < numSquares; ++j)
			{
				int currMove = 0;
				int currLoc = bitOffSet + (j * board.dirOffsets[i]);
				if (friendlyInVision & (board.ONE << currLoc))
				{
					break;
				}
				else if (enemyInVision & (board.ONE << currLoc))
				{
					// encode the move
					int currMove = Moves::encodeMove(currLoc, bitOffSet, Moves::NONE, frCol, enCol);
				}
				else
				{
					// encode the move
					int currMove = Moves::encodeMove(currLoc, bitOffSet, Moves::NONE, frCol, Moves::NONE);

				}
				allMoves.push_back(currMove);
			}
		}
	}
}

void Engine::generatePawnMoves(std::vector<int>& moves)
{
}

void Engine::generateKnightMoves(std::vector<int>& moves)
{
}

void Engine::generateKingMoves(std::vector<int>& moves)
{
}

void Engine::makeMove(int move)
{
	// TODO: finish makeMove method
}

void Engine::unmakeMove()
{
	// TODO: finish unmakeMove method
}

UINT64 Engine::getRayAttacks(Moves::Pieces p, size_t idx)
{
	switch (p)
	{
	case Moves::BISHOP:
		return slidingRayAttacks[0][idx];
	case Moves::ROOK:
		return slidingRayAttacks[1][idx];
	case Moves::QUEEN:
		return slidingRayAttacks[2][idx];
	case Moves::KING:
		return slidingRayAttacks[3][idx];
	default:
		return board.ZERO;
	}
}

void Engine::precalculateSlidingAttacks()
{
	// for the bishop
	std::vector<UINT64> tempbish(board.ZERO);
	for (int sqr = 0; sqr < 64; ++sqr)
	{
		UINT64 temp = 0;
		for (int dir = 4; dir < 8; ++dir)
		{
			for (int iter = 0; iter < board.numSqrToEdge[sqr][dir]; ++iter)
			{
				temp |= (board.ONE << ((board.dirOffsets[dir] * (iter + 1)) + sqr));
			}
		}
		tempbish.push_back(temp);
	}
	slidingRayAttacks.push_back(tempbish);

	// for the rook
	std::vector<UINT64> temprook(board.ZERO);
	for (int sqr = 0; sqr < 64; ++sqr)
	{
		UINT64 temp = 0;
		for (int dir = 0; dir < 4; ++dir)
		{
			for (int iter = 0; iter < board.numSqrToEdge[sqr][dir]; ++iter)
			{
				temp |= (board.ONE << ((board.dirOffsets[dir] * (iter + 1)) + sqr));
			}
		}
		temprook.push_back(temp);
	}
	slidingRayAttacks.push_back(temprook);

	// for the queen
	std::vector<UINT64> tempqueen(board.ZERO);
	for (int sqr = 0; sqr < 64; ++sqr)
	{
		UINT64 temp = 0;
		for (int dir = 0; dir < 8; ++dir)
		{
			for (int iter = 0; iter < board.numSqrToEdge[sqr][dir]; ++iter)
			{
				temp |= (board.ONE << ((board.dirOffsets[dir] * (iter + 1)) + sqr));
			}
		}
		tempqueen.push_back(temp);
	}
	slidingRayAttacks.push_back(tempqueen);

	// for the king
	std::vector<UINT64> tempking(board.ZERO);
	for (int sqr = 0; sqr < 64; ++sqr)
	{
		UINT64 temp = 0;
		for (int dir = 0; dir < 8; ++dir)
		{
			if (board.numSqrToEdge[sqr][dir] != 0)
			{
				temp |= (board.ONE << ((board.dirOffsets[dir] + sqr)));
			}
		}
		tempking.push_back(temp);
	}
	slidingRayAttacks.push_back(tempking);
}