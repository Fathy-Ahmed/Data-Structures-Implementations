/**
 * @file LinkedList.h
 * @brief Comprehensive singly linked list implementation with advanced operations
 * @author Fathy Ahmed Fathy
 * @date 9/16/2025 finshed
 * @version 1.0
 */

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <utility>
#include <algorithm>

#include "Node.h"

using std::vector;
using std::string;
using std::pair;

//using namespace std;


/**
 * @class LinkedList
 * @brief A comprehensive singly linked list implementation with advanced operations
 * @details This class provides a complete set of operations for managing a singly linked list,
 *          including insertion, deletion, searching, manipulation, and debugging utilities.
 *          Features include duplicate removal, rotation, reversal, and various specialized operations.
 */
class LinkedList
{
private:
    Node* head{};   ///< Pointer to the first node in the list
    Node* tail{};   ///< Pointer to the last node in the list
    int length = 0; ///< Number of nodes in the list

    // Debug utilities for development and testing
    vector<Node*> debug_data; ///< Vector to track all nodes for debugging purposes

    // Helper debug functions

    /**
     * @brief Adds a node to the debug tracking system
     * @param node Pointer to the node to be tracked
     */
    void debug_add_node(Node* node);

    /**
     * @brief Removes a node from the debug tracking system
     * @param node Pointer to the node to be removed from tracking
     */
    void debug_remove_node(Node* node);

public:
    /**
     * @brief Default constructor
     * @details Initializes an empty linked list
     */
    LinkedList();

    /**
     * @brief Copy constructor (deleted)
     * @details Prevents accidental copying of the linked list
     */
    LinkedList(const LinkedList&) = delete;

    /**
     * @brief Assignment operator (deleted)
     * @details Prevents accidental assignment of linked lists
     */
    LinkedList& operator=(const LinkedList& another) = delete;

    /**
     * @brief Destructor - deallocates all nodes
     * @details Safely deletes all nodes to prevent memory leaks
     * @complexity O(n) time - O(1) memory
     */
    ~LinkedList();

    /**
     * @brief Prints memory addresses of all nodes (debugging)
     * @details Outputs the memory address and data of each node for debugging purposes
     */
    void debug_print_address();

    /**
     * @brief Prints information about a specific node (debugging)
     * @param node Pointer to the node to print
     * @param is_seperate Flag to indicate if this is a separate debug output
     */
    void debug_print_node(Node* node, bool is_seperate = false);

    /**
     * @brief Prints all nodes in the debug tracking system
     * @param msg Optional message to display before the list
     */
    void debug_print_list(string msg = "");

    /**
     * @brief Converts the list to a string representation (debugging)
     * @return String representation of the list
     */
    string debug_to_string();

    /**
     * @brief Verifies the integrity of the data structure (debugging)
     * @details Checks if head, tail, length, and node connections are consistent
     */
    void debug_verify_data_integrity();

    /**
     * @brief Safely deletes a node and updates tracking
     * @param node Pointer to the node to be deleted
     */
    void delete_node(Node* node);

    /**
     * @brief Deletes the node immediately after the given node
     * @param node Pointer to the node whose next node will be deleted
     * @complexity O(1) time - O(1) memory
     */
    void delete_next_node(Node* node);

    /**
     * @brief Inserts a new node after the specified node
     * @param node Pointer to the node after which to insert
     * @param val Value to insert in the new node
     */
    void embed_after(Node* node, int val);

    ////////////////////////////////////////////////////////////

    /**
     * @brief Prints all elements in the list
     * @details Outputs all node values separated by spaces, followed by a newline
     */
    void print();

    /**
     * @brief Swaps the head and tail nodes of the list
     * @details Rearranges the list so that the first and last elements exchange positions
     */
    void swap_head_and_tail();

    /**
     * @brief Rotates the list to the left by k positions
     * @param k Number of positions to rotate left
     * @complexity O(n) time - O(1) memory
     */
    void rotate_left(int k);

    /**
     * @brief Removes duplicate values using nested loop approach
     * @details Removes all duplicate occurrences, keeping only the first occurrence
     * @complexity O(n²) time - O(1) memory
     */
    void remove_duplicates();

    /**
     * @brief Removes duplicate values using hash set approach
     * @details More efficient duplicate removal using additional memory
     * @complexity O(n) time - O(n) memory
     */
    void remove_duplicates2();

    /**
     * @brief Removes the last occurrence of a specific key
     * @param key The value to remove (last occurrence only)
     * @complexity O(n) time - O(1) memory
     */
    void remove_last_occurence(int key);

    /**
     * @brief Finds the maximum value in the list using recursion
     * @param head Starting node for recursion (default: nullptr)
     * @param is_first_call Flag for initial call (default: true)
     * @return The maximum integer value in the list
     * @complexity O(n) time - O(n) memory
     */
    int max(Node* head = nullptr, bool is_first_call = true);

    /**
     * @brief Moves a node to the end of the list
     * @param cur Pointer to the current node to move
     * @param prv Pointer to the previous node
     * @return Pointer to the next node in the original position
     */
    Node* move_to_end(Node* cur, Node* prv);

    /**
     * @brief Moves all occurrences of a key to the back of the list
     * @param key The value to move to the end
     * @complexity O(n) time - O(1) memory
     */
    void move_key_occurence_back(int key);

    /**
     * @brief Rearranges list to group odd and even positioned elements
     * @details Groups all odd-positioned nodes first, then even-positioned nodes
     */
    void odd_pos_even_pos();

    /**
     * @brief Inserts a target node after a source node
     * @param src Source node after which to insert
     * @param target Target node to be inserted
     */
    void insert_after(Node* src, Node* target);

    /**
     * @brief Alternately merges another list into this list
     * @param anthor Reference to the other linked list
     * @complexity O(n) time - O(1) memory
     */
    void insert_alternate(LinkedList& anthor);

    /**
     * @brief Adds another list to this list as if they were numbers
     * @param anthor Reference to the other linked list representing a number
     * @details Treats lists as digits and performs addition with carry
     */
    void add_num(LinkedList& anthor);

    /////////////my/////////////////////

    /**
     * @brief Alternative implementation for moving key occurrences to back
     * @param key The value to move to the end
     * @complexity O(n) time - O(1) memory
     * @details Uses removal and re-insertion approach
     */
    void move_key_occurence_back2(int key);

    /**
     * @brief Removes all occurrences of a specific key
     * @param k The value to remove completely from the list
     * @complexity O(n) time - O(1) memory
     */
    void remove_all_repeated_of_k(int k);

    ////////////////////////////////////////////////////////////

    /**
     * @brief Adds a node to the list and updates tracking
     * @param node Pointer to the node to be added
     */
    void add_node(Node* node);

    /**
     * @brief Inserts a new node at the end of the list
     * @param val Value to insert at the end
     */
    void insert_end(int val);

    /**
     * @brief Inserts a new node at the beginning of the list
     * @param val Value to insert at the front
     * @complexity O(1) time - O(1) memory
     */
    void insert_front(int val);

    /**
     * @brief Inserts a value in sorted order (assumes list is sorted)
     * @param val Value to insert in the correct sorted position
     * @complexity O(n) time - O(1) memory
     */
    void insert_sorted(int val);

    ////////////////////////////////////////////////////////////

    /**
     * @brief Removes the first node from the list
     * @complexity O(1) time - O(1) memory
     */
    void delete_front();

    /**
     * @brief Removes the last node from the list
     * @complexity O(n) time - O(1) memory
     */
    void delete_back();

    /**
     * @brief Removes the node at the specified index (1-based)
     * @param index Position of the node to remove (1-based indexing)
     * @complexity O(n) time - O(1) memory
     */
    void delete_nth_node(int index);

    /**
     * @brief Removes the first node containing the specified value
     * @param val Value to search for and remove
     * @complexity O(n) time - O(1) memory
     */
    void delete_node_with_key(int val);

    /**
     * @brief Removes all nodes at even positions (2nd, 4th, 6th, ...)
     * @complexity O(n) time - O(1) memory
     */
    void delete_even_positions();

    /**
     * @brief Removes all nodes that have duplicate values (unsorted list)
     * @details Removes all occurrences of values that appear more than once
     * @complexity O(n) time - O(n) memory
     */
    void remove_all_repeated();

    /**
     * @brief Helper function for sorted list duplicate removal
     * @param cur Pointer to the node to move and delete
     * @return Pointer to the next node after deletion
     */
    Node* move_and_delete(Node* cur);

    /**
     * @brief Removes all nodes that have duplicate values (sorted list)
     * @details Optimized for sorted lists - removes all occurrences of duplicated values
     * @complexity O(n) time - O(1) memory
     */
    void remove_all_repeated_from_sorted();

    ////////////////////////////////////////////////////////////

    /**
     * @brief Retrieves the node at the nth position (1-based)
     * @param n Position of the node to retrieve (1-based indexing)
     * @return Pointer to the nth node, or nullptr if not found
     * @complexity O(n) time - O(1) memory
     */
    Node* get_nth(int n);

    /**
     * @brief Retrieves the nth node from the end (1-based)
     * @param n Position from the end (1-based indexing)
     * @return Pointer to the nth node from end, or nullptr if not found
     * @complexity O(n) time - O(1) memory
     */
    Node* get_nth_back(int n);

    /**
     * @brief Searches for a value and returns its position
     * @param val Value to search for
     * @return 1-based position of the value, or -1 if not found
     * @complexity O(n) time - O(1) memory
     */
    int search(int val);

    /**
     * @brief Searches for a value and moves it one position forward if found
     * @param val Value to search for and potentially move
     * @return New 1-based position after moving, or -1 if not found
     * @details Implements self-organizing search with move-to-front heuristic
     */
    int search_improved(int val);

    ////////////////////////////////////////////////////////////

    /**
     * @brief Compares this list with another list using length optimization
     * @param another Reference to another LinkedList to compare
     * @return true if lists contain the same elements in the same order
     * @complexity O(n) time - O(1) memory
     */
    bool is_same1(const LinkedList& another);

    /**
     * @brief Compares this list with another list without using length
     * @param another Reference to another LinkedList to compare
     * @return true if lists contain the same elements in the same order
     * @complexity O(n) time - O(1) memory
     */
    bool is_same2(const LinkedList& another);

    ////////////////////////////////////////////////////////////

    /**
     * @brief Swaps data of each pair of consecutive nodes
     * @details Swaps (1st,2nd), (3rd,4th), (5th,6th), etc.
     * @complexity O(n) time - O(1) memory
     */
    void swap_pairs();

    /**
     * @brief Reverses the entire linked list
     * @details Changes the direction of all links, swaps head and tail
     * @complexity O(n) time - O(1) memory
     */
    void reverse();

    /**
     * @brief Reverses a subchain of k nodes starting from cur_head
     * @param cur_head Starting node of the subchain to reverse
     * @param k Number of nodes to reverse in the subchain
     * @return Pair containing the new head and tail of reversed subchain, plus next chain head
     * @complexity O(k) time - O(1) memory
     */
    pair<Node*, pair<Node*, Node*>> reverse_subchain(Node* cur_head, int k);

    /**
     * @brief Reverses the list in groups of k nodes
     * @param k Size of each group to reverse
     * @details Reverses every k consecutive nodes while maintaining overall list structure
     * @example For k=3: [1,2,3,4,5,6] becomes [3,2,1,6,5,4]
     * @complexity O(n) time - O(1) memory
     */
    void reverse_chains(int k);
};
