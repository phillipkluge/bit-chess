#include <iostream>
#include <bitset>
#include <vector>
#include "board.h"
#include "engine.h"
#include "moves.h"

int main()
{
	Engine BitEngine;
	std::vector<int> allMoves = BitEngine.generateAllMoves();

	for (int i = 0; i < allMoves.size(); i++)
	{
		int move = allMoves.at(i);
		std::cout << move << std::endl;

		int endSqr, stSqr, flag, pieceMoved, pieceCaptured;
		Moves::outputMove m = Moves::decodeMove(move);
		endSqr = m.endSqr;
		stSqr = m.stSqr;
		flag = m.flag;
		pieceMoved = m.pieceMoved;
		pieceCaptured = m.pieceCaptured;
		std::cout << endSqr << " " << stSqr << " " << flag << " " << pieceMoved << " " << pieceCaptured << std::endl;
	}
	std::cout << std::endl;

	return 0;
}
