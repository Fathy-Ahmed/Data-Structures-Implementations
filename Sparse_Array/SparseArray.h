#pragma once

#include "ArrayNode.h"

class ArrayLinkedList {
private:
	ArrayNode* head{};
	ArrayNode* tail{};
	int length = 0;			// total number of nodes
	int array_length = 0;	// total number of array elements

	void link(ArrayNode* first, ArrayNode* second);

	ArrayNode* embed_after(ArrayNode* node_before, int data, int index);

	ArrayNode* get_index(int index, bool is_create_if_missing);

public:

	ArrayLinkedList(int array_length);

	void print_array();

	void print_array_nonzero();

	void set_value(int data, int index);

	int get_value(int index);

	void add(ArrayLinkedList& other);

};