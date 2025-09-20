#include "Node.h"
#define el '\n';
/**
 * Constructor implementation
 * Initializes the node with the given data value.
 * The next and prev pointers are automatically initialized to nullptr
 * by the member initializer list in the header.
 */
Node::Node(int data) : data(data) {}

/**
 * Helper function to set both directional pointers at once.
 * Useful when inserting a node between two existing nodes
 * or when restructuring the list.
 */
void Node::set(Node* next, Node* prev) {
	this->next = next;
	this->prev = prev;
}

/**
 * Destructor implementation with debug output.
 * Prints the data value and memory address of the node being destroyed.
 * This is helpful for:
 * - Debugging memory leaks
 * - Verifying proper cleanup
 * - Tracking node lifecycle during development
 */
Node::~Node() {
	std::cout << "Destroy value: " << data << " at address " << this << el;
}