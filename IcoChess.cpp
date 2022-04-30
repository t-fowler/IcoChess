#pragma once
#include <iostream>
#include <stack>
#include <string>
#include "stdlib.h"

#include "IcoChess.h"
#include "Move.h"
#include "IcoUtil.h"
#include "BitManipulation.h"
#include "Position.h"

void IcoChessUCI::send_id() 
{
	std::cout << "id name IcoChess 0.1\n";
	std::cout << "id author Tyler Fowler\n";
}
void IcoChessUCI::send_uci() 
{
	std::cout << "uciok\n";
}
void IcoChessUCI::send_ready()
{
	std::cout << "readyok\n";
}
void IcoChessUCI::send_move()
{
	std::cout << "Unimplemented.\n";
}
void IcoChessUCI::send_copyProtection() 
{
	std::cout << "Unimplemented.\n";
}


void wait(std::string waitFor)
{
	std::string cmd;
	std::cin >> cmd;
	while (!(cmd == waitFor)) {
		std::cin >> cmd;
	}
}

/*int main()
{
	IcoChessUCI uci;

	wait("uci");
	uci.send_id();
	uci.send_uci();

	wait("isready");
	uci.send_ready();

	std::string cmd;
	while (true)
	{
		std::cin >> cmd;
		if (cmd == "debug on") {

		}
		else if (cmd == "debug off") {

		}
		else if (cmd == "isready") {
			uci.send_ready();
		}
		else if (cmd == "position ...") {

		}
		else if (cmd == "go ...") {

		}
		else if (cmd == "stop") {

		}
		else if (cmd == "ponderhit") {

		}
		else if (cmd == "quit") {
			break;
		}
	}
}*/