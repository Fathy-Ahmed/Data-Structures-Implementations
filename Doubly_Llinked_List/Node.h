#pragma once

#include <iostream>

/**
 * @brief Node structure for doubly linked list
 *
 * A simple node structure that contains:
 * - Integer data value
 * - Pointer to next node in forward direction
 * - Pointer to previous node in backward direction
 *
 * The destructor provides debug output to track node destruction.
 */
struct Node
{
	int data{};		///< The integer value stored in this node
	Node* next{};	///< Pointer to the next node in the list (nullptr if last)
	Node* prev{};	///< Pointer to the previous node in the list (nullptr if first)

	/**
	 * @brief Constructor that initializes the node with a data value
	 * @param data The integer value to store in this node
	 */
	Node(int data);

	/**
	 * @brief Helper function to set both next and previous pointers
	 * @param next Pointer to the next node
	 * @param prev Pointer to the previous node
	 */
	void set(Node* next, Node* prev);

	/**
	 * @brief Destructor that prints debug information when node is destroyed
	 *
	 * Outputs the data value and memory address being destroyed.
	 * Useful for debugging memory management and detecting leaks.
	 */
	~Node();
};