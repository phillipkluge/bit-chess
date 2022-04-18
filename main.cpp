#include <iostream>
#include <bitset>
#include <vector>
#include "board.h"
#include "engine.h"
#include "moves.h"

int main()
{
	Engine BitEngine;

	// TESTING RAY ATTACKS ON E4
/* 	UINT64 a = BitEngine.getRayAttacks(Moves::BISHOP, 28);
	UINT64 b = BitEngine.getRayAttacks(Moves::ROOK, 28);
	UINT64 c = BitEngine.getRayAttacks(Moves::QUEEN, 28);
	UINT64 d = BitEngine.getRayAttacks(Moves::KING, 28);
	std::bitset<64> x(a);
	std::bitset<64> y(b);
	std::bitset<64> z(c);
	std::bitset<64> aa(d);

	std::cout << x << std::endl;
	std::cout << y << std::endl;
	std::cout << z << std::endl;
	std::cout << aa << std::endl; */

	std::vector<int> allMoves = BitEngine.generateAllMoves();

	for (int i = 0; i < allMoves.size(); i++)
	{
		std::cout << allMoves.at(i) << " ";
	}
	std::cout << std::endl;

	return 0;
}
