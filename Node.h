#pragma once
#include <iostream>
#include <array>

enum NodeState {
	Discovered,
	Undiscovered,
	Goal,
	Start,
	Blocking
};

class Node {
public:
	Node(int x, int y);
	std::array<int, 2> coords;
	NodeState state{Undiscovered};
	Node* parent = nullptr;
	void display();
	void displayState();
};