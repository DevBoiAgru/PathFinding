#include "Pathfinding.h"

bool DISPLAY_COORDS{ true };

int main(){

	Maze maze(25, 25);
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Path finding");
	sf::Font font;
	if (!font.loadFromFile("Roboto-Medium.ttf"))
		std::cerr << "Failed to load font";

	Node* startNode = nullptr;
	Node* goalNode = nullptr;
	std::array<int, 2> start{ 17,20 }, goal{ 7, 2 };

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
				case Discovered:	// Blue
					squareColour = sf::Color(0, 0, 255, 255);
					break;
				case Blocking:		// Black
					squareColour = sf::Color(0, 0, 0, 255);
					break;
				case Goal:			// Red
					squareColour = sf::Color(255, 0, 0, 255);
					break;
				case Start:			// Yellow
					squareColour = sf::Color(255, 255, 0, 255);
					break;
				default:
					squareColour = sf::Color(255, 255, 255, 255);
					break;
				};
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

	int counter{ 0 };
	while (true) {
		if (frontier.empty()) {
			std::cerr << "No solution\n";
			return false;
		}
		Node* currentNode = frontier.front();
		frontier.pop_front();

		if (currentNode->state == Goal) {
			std::cout << "Solved!\n";
			return true;
		}

		std::array<Node*, 4> neighbors = maze.getNeighbours(currentNode);
		for (auto neighbor : neighbors) {
			if (neighbor != NULL && (neighbor->state == Undiscovered || neighbor->state == Goal)) {
				frontier.push_back(neighbor);
				if (neighbor->state == Undiscovered)
					neighbor->state = Discovered;
			}
		}
	}
}