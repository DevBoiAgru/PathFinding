#include "Node.h"

Node::Node(int x, int y) {
	coords[0] = x;
	coords[1] = y;
}
void Node::display() {
	std::cout << "(" << coords[0] << ", " << coords[1] << ") ";
}