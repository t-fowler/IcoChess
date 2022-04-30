#pragma once
#include<iostream>

class IcoChessUCI {
public:
	enum class State
	{
		thinking,
		ok,
		error
	} state;

	IcoChessUCI() = default;
	void send_id();
	void send_uci();
	void send_ready();
	void send_move();
	void send_copyProtection();
};