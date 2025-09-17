#pragma once

#include <iostream>
using std::cout;

/**
 * @brief Node structure for the linked list
 * @details Each node contains integer data and a pointer to the next node
 */
struct Node
{
    int data{};   ///< Integer data stored in the node
    Node* next{}; //< Pointer to the next node in the list

    /**
     * @brief Constructor for Node
     * @param val The integer value to store in the node
     */
    Node(int data) : data(data) {}

    /**
     * @brief Deconstructor for Node
     */
    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};
