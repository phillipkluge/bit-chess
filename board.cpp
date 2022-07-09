#include "board.h"
#include <iostream>

Board::Board()
{
	pieceBoards = new UINT64*[2];

	// initializing the bitboards
	occupied = 0;
	unoccupied = 0;

	UINT64 whitePieces = 0;
	UINT64 whiteKings = 0;
	UINT64 whitePawns = 0;
	UINT64 whiteKnights = 0;
	UINT64 whiteBishops = 0;
	UINT64 whiteRooks = 0;
	UINT64 whiteQueens = 0;

	UINT64 blackPieces = 0;
	UINT64 blackKings = 0;
	UINT64 blackPawns = 0;
	UINT64 blackKnights = 0;
	UINT64 blackBishops = 0;
	UINT64 blackRooks = 0;
	UINT64 blackQueens = 0;

	// managing the location of the bitboards
	UINT64 tempWhite[7] = {whitePieces, whiteKings, whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens};
	UINT64 tempBlack[7]= {blackPieces, blackKings, blackPawns, blackKnights, blackBishops, blackRooks, blackQueens};
	pieceBoards[0] = tempWhite;
	pieceBoards[1] = tempBlack;

	// for now, set the board up in a standard way
	std::string boardArray[8][8] = {
		// {"r", "n", "b", "q", "k", "b", "n", "r"},
		// {"p", "p", "p", "p", "p", "p", "p", "p"},
		// {" ", " ", " ", " ", " ", " ", " ", " "},
		// {" ", " ", " ", " ", " ", " ", " ", " "},
		// {" ", " ", " ", " ", " ", " ", " ", " "},
		// {" ", " ", " ", " ", " ", " ", " ", " "},
		// {"P", "P", "P", "P", "P", "P", "P", "P"},
		// {"R", "N", "B", "Q", "K", "B", "N", "R"} 

		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", "p", " ", " ", " ", " "},
		{" ", " ", " ", " ", "B", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "}
	};
	initializeBoardFromArray(boardArray);
	precalculateData();

	unoccupied = ~occupied;
}

void Board::initializeBoardFromArray(std::string boardArray[8][8])
{
	for (int i = 7; i >= 0; --i)
	{
		for (int j = 0; j < 8; ++j)
		{
			std::string piece = boardArray[i][j];
			char& s = piece[0];

			int position = (((7 - i) * 8) + j);

			if (s == ' ') // empty pieces
			{
				continue;
			}
			else if ((isupper(s))) // white pieces
			{
				pieceBoards[0][0] |= ONE << position;
				occupied |= ONE << position;
				switch (s)
				{
					case 'K':
						pieceBoards[0][1] |= ONE << position;
						break;
					case 'P':
						pieceBoards[0][2] |= ONE << position;
						break;
					case 'N':
						pieceBoards[0][3] |= ONE << position;
						break;
					case 'B':
						pieceBoards[0][4] |= ONE << position;
						break;
					case 'R':
						pieceBoards[0][5] |= ONE << position;
						break;
					case 'Q':
						pieceBoards[0][6] |= ONE << position;
						break;
				}
			}
			else // black pieces
			{
				pieceBoards[1][0] |= ONE << position;
				occupied |= ONE << position;
				switch (s)
				{
					case 'K':
						pieceBoards[1][1] |= ONE << position;
						break;
					case 'P':
						pieceBoards[1][2] |= ONE << position;
						break;
					case 'N':
						pieceBoards[1][3] |= ONE << position;
						break;
					case 'B':
						pieceBoards[1][4] |= ONE << position;
						break;
					case 'R':
						pieceBoards[1][5] |= ONE << position;
						break;
					case 'Q':
						pieceBoards[1][6] |= ONE << position;
						break;
				}
			}
		}
	}
}

void Board::precalculateData()
{
	std::vector<std::vector<int> > temp(64, std::vector<int>(0));

	numSqrToEdge = temp;

	for (int file = 0; file < 8; ++file)
	{
		for (int rank = 0; rank < 8; ++rank)
		{
			int index = rank * 8 + file;

			int North = 7 - rank;
			int South = rank;
			int West = file;
			int East = 7 - file;

			numSqrToEdge[index].push_back(North);
			numSqrToEdge[index].push_back(South);
			numSqrToEdge[index].push_back(West);
			numSqrToEdge[index].push_back(East);
			numSqrToEdge[index].push_back(std::min(North, West));
			numSqrToEdge[index].push_back(std::min(South, East));
			numSqrToEdge[index].push_back(std::min(North, East));
			numSqrToEdge[index].push_back(std::min(South, West));
		}
	}

	dirOffsets.push_back(8);
	dirOffsets.push_back(-8);
	dirOffsets.push_back(-1);
	dirOffsets.push_back(1);
	dirOffsets.push_back(7);
	dirOffsets.push_back(-7);
	dirOffsets.push_back(9);
	dirOffsets.push_back(-9);
}
