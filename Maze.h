#pragma once
#include <vector>
#include <array>
#include "Node.h"

class Maze {
private:
	int gridHeight, gridWidth;
public:
	Maze(int width, int height);

	std::vector<std::vector<Node*>> grid;
	// 0: left  1: top  2: right  3: down
	std::array<Node*, 4> getNeighbours(Node* target);
	void display();
};

double distanceToPoint(std::array<int, 2> coords1, std::array<int, 2> coords2);