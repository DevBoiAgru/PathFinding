#include "Node.h"

Node::Node(int x, int y) {
	coords[0] = x;
	coords[1] = y;
}
void Node::display() {
	std::cout << "(" << coords[0] << ", " << coords[1] << ") ";
}
void Node::displayState() {
	switch (state) {
	case Discovered:
		std::cout << "Discovered";
		break;
	case Undiscovered:
		std::cout << "Undiscovered";
		break;
	case Goal:
		std::cout << "Goal";
		break;
	case Start:
		std::cout << "Start";
		break;
	case Blocking:
		std::cout << "Blocking";
		break;
	}
}