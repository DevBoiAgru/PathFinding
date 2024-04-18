#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include "Node.h"
#include "Maze.h"


static bool solve(Maze& maze, Node*& start, Node* &goal);