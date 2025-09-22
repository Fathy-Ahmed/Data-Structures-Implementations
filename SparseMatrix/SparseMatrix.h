#pragma once
#include "RowNode.h"


class SparseMatrix {
private:
	RowNode* head{};
	RowNode* tail{};
	int length = 0;
	int rows{};
	int cols{};

	void link(RowNode* first, RowNode* second);

	RowNode* embed_after(RowNode* node_before, int row);

	RowNode* get_row(int row, bool is_create_if_missing);

public:
	SparseMatrix(int rows, int cols);

	void set_value(int data, int row, int col);

	int get_value(int row, int col);

	void print_matrix();

	void print_matrix_nonzero();

	void add(SparseMatrix& other);
};