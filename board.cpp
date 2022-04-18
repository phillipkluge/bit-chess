#include "board.h"
#include <iostream>

Board::Board()
{
	// initializing the bitboards
	whitePieces = 0;
	blackPieces = 0;
	occupied = 0;

	whitePawns = 0;
	whiteBishops = 0;
	whiteKnights = 0;
	whiteRooks = 0;
	whiteQueens = 0;
	whiteKings = 0;
	blackPawns = 0;
	blackBishops = 0;
	blackKnights = 0;
	blackRooks = 0;
	blackQueens = 0;
	blackKings = 0;

	// for now, set the board up in a standard way
	std::string boardArray[8][8] = {
    /*  {"r", "n", "b", "q", "k", "b", "n", "r"},
		{"p", "p", "p", "p", "p", "p", "p", "p"},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{"P", "P", "P", "P", "P", "P", "P", "P"},
		{"R", "N", "B", "Q", "K", "B", "N", "R"} */

		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", "B", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "}
	};
	initializeBoardFromArray(boardArray);
	precalculateData();
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
				whitePieces |= ONE << position;
				occupied |= ONE << position;
				switch (s)
				{
					case 'P':
						whitePawns |= ONE << position;
						break;
					case 'B':
						whiteBishops |= ONE << position;
						break;
					case 'N':
						whiteKnights |= ONE << position;
						break;
					case 'R':
						whiteRooks |= ONE << position;
						break;
					case 'Q':
						whiteQueens |= ONE << position;
						break;
					case 'K':
						whiteKings |= ONE << position;
						break;
				}
			}
			else // black pieces
			{
				blackPieces |= ONE << position;
				occupied |= ONE << position;
				switch (s)
				{
					case 'p':
						blackPawns |= ONE << position;
						break;
					case 'b':
						blackBishops |= ONE << position;
						break;
					case 'n':
						blackKnights |= ONE << position;
						break;
					case 'r':
						blackRooks |= ONE << position;
						break;
					case 'q':
						blackQueens |= ONE << position;
						break;
					case 'k':
						blackKings |= ONE << position;
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
