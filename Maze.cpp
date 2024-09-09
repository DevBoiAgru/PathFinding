#include "Maze.h"
#include <iostream>

Maze::Maze(int width, int height) {
	// Make a 2d array for the grid
	gridHeight = height;
	gridWidth = width;
	for (int y = 0; y < height; y++) {
		std::vector<Node*> row;
		for (int x = 0; x < width; x++) {
			Node* node = new Node(x, y);
			row.push_back(node);
		}
		grid.push_back(row);
	}
}

std::array<Node*, 4> Maze::getNeighbours(Node* target) {
	int x = target->coords[0];
	int y = target->coords[1];
	Node* top = grid[x][y];
	Node* bottom = grid[x][y];
	Node* right = grid[x][y];
	Node* left = grid[x][y];

	// Check if there is a node around the target
	if (y <= 0)
		top = nullptr;
	else
		top = grid[y - 1][x];

	if (y >= gridHeight - 1)				// -1 is accounting for zero based indexing
		bottom = nullptr;
	else
		bottom = grid[y + 1][x];

	if (x <= 0)
		left = nullptr;
	else
		left = grid[y][x - 1];

	if (x >= gridWidth - 1)					// -1 is accounting for zero based indexing
		right = nullptr;
	else
		right = grid[y][x + 1];
	std::array<Node*, 4> result{ left, top, right, bottom };
	return result;
}

int ManhattanDistance(Node* point1, Node* point2) {
	int x1 = point1->coords[0];
	int y1 = point1->coords[1];
	int x2 = point1->coords[0];
	int y2 = point1->coords[1];
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}