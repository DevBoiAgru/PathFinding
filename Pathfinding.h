#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "Node.h"
#include "Maze.h"


static bool solve(Maze& maze, Node*& start, Node* &goal);	// Returns true if we were able to solve the maze