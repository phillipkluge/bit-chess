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
		std::cout << allMoves.at(i) << " ";
	}
	std::cout << std::endl;

	return 0;
}
