#pragma once

#include "ColumnNode.h"

class ColumnLinkedList {
private:
	ColumnNode* head{};
	ColumnNode* tail{};
	int length = 0;
	int cols{};	// Total number of columns

	void link(ColumnNode* first, ColumnNode* second);

	ColumnNode* embed_after(ColumnNode* node_befor, int data, int col);

	ColumnNode* get_col(int col, bool is_create_if_missing);

public:

	ColumnLinkedList(int cols);

	void print_row();
	void print_row_nonzero();

	void set_value(int data, int col);

	int get_value(int col);

	void add(ColumnLinkedList& other);
};