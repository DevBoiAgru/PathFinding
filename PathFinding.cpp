#include "Pathfinding.h"


// Only need one size because everything is square
constexpr int MAZE_SIZE = 25;
constexpr int WINDOW_SIZE = 1000;

constexpr int START_X = 15, START_Y = 17, GOAL_X = 2, GOAL_Y = 2;

bool DISPLAY_COORDS{ false };

int main(int argc, char** argv){
	if (argc > 1) {
		if (strcmp("coords", argv[1]))
			DISPLAY_COORDS = true;
	}

	Maze maze(MAZE_SIZE, MAZE_SIZE);
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Path finding");
	sf::Font font;
	if (DISPLAY_COORDS) {
		if (!font.loadFromFile("Assets/Roboto-Medium.ttf"))
			std::cerr << "Failed to load font!";
	}

	Node* startNode = nullptr;
	Node* goalNode = nullptr;
	std::array<int, 2> start{ START_X,START_Y }, goal{ GOAL_X, GOAL_Y };

	for (auto& row : maze.grid) {
		for (auto& node : row) {
			// Set start / finish
			if (node->coords == start) {
				startNode = node;
				node->state = Start;
			}
			if (node->coords == goal) {
				goalNode = node;
				node->state = Goal;
			}
		}
	}

	solve(maze, startNode, goalNode);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				int cellX = sf::Mouse::getPosition(window).x / 39;
				int cellY = sf::Mouse::getPosition(window).y / 39;

				if (cellY < 25 && cellX < 25){		// Cells cannot exceed maze size
					if (event.mouseButton.button == sf::Mouse::Left) {
						maze.grid[cellY][cellX]->state = Blocking;
					}
					else if (event.mouseButton.button == sf::Mouse::Right) {
						maze.grid[cellY][cellX]->state = Undiscovered;
					}
				}

				for (auto& row : maze.grid) {
					for (auto& node : row) {
						if (node->coords == start) {
							startNode = node;
							node->state = Start;
						}
						else if (node->coords == goal) {
							goalNode = node;
							node->state = Goal;
						}
						else if (node->state == Discovered){
							node->state = Undiscovered;
						}
					}
				}

				solve(maze, startNode, goalNode);
			}
		}
		window.clear();

		for (auto& row : maze.grid) {
			for (auto& node : row) {

				// Draw squares for every node
				sf::RectangleShape square(sf::Vector2f(38.5, 38.5));

				// Colour the square
				sf::Color squareColour;
				switch (node->state) {
				case Undiscovered:	// White
					squareColour = sf::Color(255, 255, 255, 255);
					break;
				case Discovered:	// Gray
					squareColour = sf::Color(200, 200, 200, 255);
					break;
				case Blocking:		// Black
					squareColour = sf::Color(0, 0, 0, 255);
					break;
				case Goal:			// Blue
					squareColour = sf::Color(0, 0, 255, 255);
					break;
				case Start:			// Red
					squareColour = sf::Color(255, 0, 0, 255);
					break;
				case Path:			// Green
					squareColour = sf::Color(0, 255, 0, 255);
					break;
				default:			// White
					squareColour = sf::Color(255, 255, 255, 255);
					break;
				};

				// Force goal node be coloured red since we set it to discovered when we find it
				if (node->coords == goalNode->coords) {
					squareColour = sf::Color(0, 0, 255, 255);
				}

				square.setFillColor(squareColour);
				square.setPosition(sf::Vector2f(7 + node->coords[0] * 39.4, 7 + node->coords[1] * 39.4));
				window.draw(square);

				if (DISPLAY_COORDS){
					sf::Text nodeCoords;
					nodeCoords.setFont(font);
					nodeCoords.setFillColor(sf::Color::Black);
					nodeCoords.setCharacterSize(10);
					nodeCoords.setString("(" + std::to_string(node->coords[0]) + ", " + std::to_string(node->coords[1]) + ")");
					nodeCoords.setPosition(sf::Vector2f(7 + node->coords[0] * 39.4, 7 + node->coords[1] * 39.4));
					window.draw(nodeCoords);
				}
			}
		}


		window.display();
	}
}

static bool solve(Maze &maze, Node* &start, Node* &goal) {
	std::deque<Node*> frontier;
	frontier.push_back(start);

	while (true) {
		if (frontier.empty()) {
			std::cerr << "No solution\n";
			return false;
		}

		// BFS
		//Node* currentNode = frontier.front();
		//frontier.pop_front();

		// DFS
		//Node* currentNode = frontier.back();
		//frontier.pop_back();

		// idk what this is but it works better than BFS and DFS
		// Get node closest to the goal node in the frontier and use that
		int closestNodeIndex = -1;
		for (int i = 0; i < frontier.size(); i++) {
			if (closestNodeIndex == -1) {
				closestNodeIndex = i;
			}
			else {
				if (ManhattanDistance(frontier[i], goal) < ManhattanDistance(frontier[closestNodeIndex], goal)) {
					closestNodeIndex = i;
				}
			}
		}
		Node* currentNode = frontier[closestNodeIndex];
		frontier.erase(frontier.begin() + closestNodeIndex);

		if (currentNode->state == Goal) {

			while (currentNode->parent != nullptr) {
				currentNode->state = Path;
				currentNode = currentNode->parent;				// Backtracking
			}
			return true;
		}

		std::array<Node*, 4> neighbors = maze.getNeighbours(currentNode);

		for (auto neighbor : neighbors) {
			if (neighbor != NULL && (neighbor->state == Undiscovered || neighbor->state == Goal || neighbor->state == Path)) {
				neighbor->parent = currentNode;
				frontier.push_back(neighbor);
				if (neighbor->state == Undiscovered || neighbor->state == Path)
					neighbor->state = Discovered;
			}
		}
	}
}