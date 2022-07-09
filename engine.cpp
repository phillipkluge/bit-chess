#include "engine.h"
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
		bishops = board.pieceBoards[0][4];
		rooks = board.pieceBoards[0][5];
		queens = board.pieceBoards[0][6];
        
		friendly = board.pieceBoards[0][0];
		frCol = Moves::WHITE;
		enemy = board.pieceBoards[1][0];
		enCol = Moves::BLACK;
	}
	else
	{
		bishops = board.pieceBoards[1][4];
		rooks = board.pieceBoards[1][5];
		queens = board.pieceBoards[1][6];
        
		friendly = board.pieceBoards[1][0];
		frCol = Moves::BLACK;
		enemy = board.pieceBoards[0][0];
		enCol = Moves::WHITE;
	}
    
	// goes through each of the sliding piece positions and finds valid moves
    slidingPieceMoves(allMoves, Moves::BISHOP, bishops, friendly, enemy, frCol, enCol);
    // slidingPieceMoves(allMoves, Moves::ROOK, rooks, friendly, enemy, frCol, enCol);
    // slidingPieceMoves(allMoves, Moves::QUEEN, queens, friendly, enemy, frCol, enCol);
}

void Engine::slidingPieceMoves(std::vector<int>& allMoves, Moves::Pieces pieceType, UINT64 pieceBoard, UINT64 friendly, UINT64 enemy, Moves::Pieces frCol, Moves::Pieces enCol)
{
    while (pieceBoard)
    {
        int bitOffSet = __builtin_ffsll(pieceBoard) - 1; // gets the position of the next set bit
        pieceBoard &= pieceBoard-1; // sets that bit to 0

        UINT64 rayAttack = getRayAttacks(pieceType, bitOffSet);
        UINT64 friendlyInVision = rayAttack & friendly;
        UINT64 enemyInVision = rayAttack & enemy;
        
        int startDirIndex = (pieceType == Moves::BISHOP) ? 4 : 0;
        int endDirIndex = (pieceType == Moves::ROOK) ? 4 : 8;

        for (int i = startDirIndex; i < endDirIndex; ++i)
        {
            int numSquares = board.numSqrToEdge[bitOffSet][i];
            for (int j = 0; j < numSquares; ++j)
            {
                int currMove = 0;
                int currLoc = bitOffSet + ((j + 1) * board.dirOffsets[i]);
                if (friendlyInVision & (board.ONE << currLoc))
                {
                    break;
                }
                else if (enemyInVision & (board.ONE << currLoc))
                {
                	Moves::Pieces enPieceType = getEnPieceType(currLoc, enCol);

                    // encode the move
                    currMove = Moves::encodeMove(currLoc, bitOffSet, Moves::CAPTURES, frCol + pieceType, enCol + enPieceType);
                    allMoves.push_back(currMove);
                    break;
                }
                else
                {
                    // encode the move
                    currMove = Moves::encodeMove(currLoc, bitOffSet, Moves::NONE, frCol + pieceType, Moves::NONE);
                    allMoves.push_back(currMove);
                }
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
	Moves::outputMove m = Moves::decodeMove(move);
	UINT64 fromBB = board.ONE << m.stSqr;
	UINT64 toBB = board.ONE << m.endSqr;
	UINT64 fromtoBB = fromBB ^ toBB;
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

Moves::Pieces Engine::getEnPieceType(int currLoc, Moves::Pieces enCol)
{
	UINT64 mask = board.ONE << currLoc;
	UINT64 pawns, bishops, knights, rooks, queens, kings;
	UINT64 boards[7];

	size_t idx = (enCol == Moves::WHITE) ? 0 : 1;

	for (int i = 1; i < 7; ++i)
	{
		if (((board.pieceBoards[idx][i] & mask) >> currLoc) == 1)
		{
			return static_cast<Moves::Pieces>(i);
		}
	}
	return Moves::EMPTY;
}
