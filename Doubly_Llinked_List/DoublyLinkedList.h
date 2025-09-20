#pragma once

#include "Node.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

/**
 * @brief A doubly linked list implementation with comprehensive debugging capabilities
 *
 * This class provides a complete doubly linked list with nodes that have both
 * forward and backward pointers. It includes extensive debugging functionality
 * to help verify data integrity and visualize the list structure.
 *
 * Features:
 * - Standard insertion/deletion operations
 * - Sorted insertion
 * - Pattern-based deletions (even/odd positions)
 * - List manipulation (reverse, merge, swap operations)
 * - Palindrome checking
 * - Multiple middle-finding algorithms
 * - Comprehensive debugging tools
 */
class LinkedList {
private:
	Node* head{};		///< Pointer to the first node in the list
	Node* tail{};		///< Pointer to the last node in the list
	int length = 0;		///< Current number of nodes in the list
	
	// Debug support - tracks all nodes for integrity verification	
	vector<Node*> debug_data;		///< Vector storing pointers to all nodes for debugging

	/**
	 * @brief Adds a node to the debug tracking vector
	 * @param node Pointer to the node to track
	 */
	void debug_add_node(Node* node);
	/**
	 * @brief Removes a node from the debug tracking vector
	 * @param node Pointer to the node to stop tracking
	 */
	void debug_remove_node(Node* node);

public:
	/**
	 * @brief Default constructor - creates an empty linked list
	 */
	LinkedList();

	/**
	 * @brief Destructor - cleans up all nodes and memory
	 */
	~LinkedList();

	// Disable copy operations to prevent shallow copying issues
	LinkedList(const LinkedList&) = delete;
	LinkedList& operator=(const LinkedList& another) = delete;

	//====================================================================================
	// DEBUG FUNCTIONS - For development and testing purposes
	//====================================================================================

	/**
	 * @brief Prints memory addresses of all nodes in forward order
	 */
	void   debuge_print_address();

	/**
	 * @brief Prints detailed information about a specific node
	 * @param node Pointer to the node to print
	 * @param is_seperate Whether to add "Sep:" prefix to output
	 */
	void   debug_print_node(Node* node, bool is_seperate = false);


	/**
	 * @brief Prints the entire list structure with node relationships
	 * @param msg Optional message to print before the list
	 */
	void   debug_print_list(string msg = "");

	/**
	 * @brief Converts the list to a space-separated string representation
	 * @return String containing all node values separated by spaces
	 */
	string debug_to_string();

	/**
	 * @brief Verifies the internal consistency of the list structure
	 *
	 * Checks:
	 * - Head/tail pointer correctness
	 * - Length consistency
	 * - Forward and backward traversal integrity
	 * - Debug vector synchronization
	 *
	 * @throws Assertion error if inconsistency is found
	 */
	void   debug_verfiy_data_integrity();


	//====================================================================================
	// HELPER FUNCTIONS - Internal utility functions
	//====================================================================================


	// These 2 simple functions just to not forget changing the vector and length

	/**
	 * @brief Helper function to safely delete a node and update tracking
	 * @param node Pointer to the node to delete
	 */
	void delete_node(Node* node);

	/**
	 * @brief Helper function to add a node and update tracking
	 * @param node Pointer to the node to add to tracking
	 */
	void add_node(Node* node);


	//====================================================================================
	// DISPLAY FUNCTIONS
	//====================================================================================


	/**
	 * @brief Prints all values in the list from head to tail
	 */
	void print();

	/**
	 * @brief Prints all values in the list from tail to head
	 */
	void print_reverse();

	//====================================================================================
	// INSERTION FUNCTIONS
	//====================================================================================


	/**
	 * @brief Helper function to link two nodes bidirectionally
	 * @param first Pointer to the first node (or nullptr)
	 * @param second Pointer to the second node (or nullptr)
	 */
	void link(Node* first, Node* second);

	/**
	 * @brief Helper function to insert a new node after a given node
	 * @param node_before Pointer to the node after which to insert
	 * @param val Value to insert
	 */
	void embed_after(Node* node_before, int val);

	/**
	 * @brief Inserts a new node at the end of the list
	 * @param val Value to insert
	 */
	void insert_end(int val);

	/**
	 * @brief Inserts a new node at the beginning of the list
	 * @param val Value to insert
	 */
	void insert_front(int val);

	/**
	 * @brief Inserts a value in sorted order (assumes list is already sorted)
	 * @param val Value to insert in correct sorted position
	 */
	void insert_sorted(int val);

	//====================================================================================
	// DELETION FUNCTIONS
	//====================================================================================

	/**
	 * @brief Helper function to delete a node and link its neighbors
	 * @param cur Pointer to the node to delete
	 * @return Pointer to the previous node (for iteration purposes)
	 */
	Node* delete_and_link(Node* cur);

	/**
	 * @brief Deletes the first node in the list
	 */
	void delete_front();

	/**
	 * @brief Deletes the last node in the list
	 */
	void delete_end();

	/**
	 * @brief Deletes the first node found with the specified value
	 * @param val Value to search for and delete
	 */
	void delete_node_with_key(int val);

	/**
	 * @brief Deletes all nodes with the specified value
	 * @param val Value to search for and delete all occurrences
	 */
	void delete_all_nodes_with_key(int val);

	/**
	 * @brief Deletes all nodes at even positions (2nd, 4th, 6th, etc.) - Version 1
	 */
	void delete_even_positions1();

	/**
	 * @brief Deletes all nodes at even positions (2nd, 4th, 6th, etc.) - Version 2
	 */
	void delete_even_positions2();

	/**
	 * @brief Deletes all nodes at odd positions (1st, 3rd, 5th, etc.) - Version 1
	 */
	void delete_odd_positions1();

	/**
	 * @brief Deletes all nodes at odd positions (1st, 3rd, 5th, etc.) - Version 2
	 */
	void delete_odd_positions2();

	//====================================================================================
	// ANALYSIS FUNCTIONS
	//====================================================================================

	/**
	 * @brief Checks if the list forms a palindrome
	 * @return true if the list reads the same forwards and backwards, false otherwise
	 */
	bool is_palindrome();

	/**
	 * @brief Finds the middle element using two-pointer approach from ends
	 * @return Value of the middle node
	 * @throws Assertion error if list is empty
	 */
	int find_the_middle1();

	/**
	 * @brief Finds the middle element using tortoise and hare algorithm
	 * @return Value of the middle node
	 * @throws Assertion error if list is empty
	 */
	int find_the_middle2();

	//====================================================================================
	// ACCESS FUNCTIONS
	//====================================================================================

	/**
	 * @brief Gets the nth node from the beginning (1-indexed)
	 * @param n Position from the start (1 = first node)
	 * @return Pointer to the nth node, or nullptr if n > length
	 */
	Node* get_nth_node(int n);

	/**
	 * @brief Gets the nth node from the end (1-indexed)
	 * @param n Position from the end (1 = last node)
	 * @return Pointer to the nth node from end, or nullptr if n > length
	 */
	Node* get_nth_node_back(int n);

	//====================================================================================
	// ADVANCED MANIPULATION FUNCTIONS
	//====================================================================================

	/**
	 * @brief Swaps the kth node from start with kth node from end
	 * @param k Position from start/end to swap (1-indexed)
	 */
	void swap_forward_with_backword(int k);

	/**
	 * @brief Swaps the kth node from start with kth node from end
	 * @param k Position to swap (1-indexed)
	 */
	void swap_kth(int k);

	/**
	 * @brief Reverses the entire list in-place
	 */
	void reverse();

	/**
	 * @brief Merges another sorted list with this sorted list
	 *
	 * Both lists must be sorted in ascending order. After merging,
	 * the other list becomes empty and this list contains all elements
	 * in sorted order.
	 *
	 * @param other Reference to the other sorted LinkedList to merge
	 */
	void merge_2sorted_lists(LinkedList& other);

};