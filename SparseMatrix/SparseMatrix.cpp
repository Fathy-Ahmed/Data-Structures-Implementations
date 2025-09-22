#include "SparseMatrix.h"
#include <cassert>
#include <iostream>

void SparseMatrix::link(RowNode* first, RowNode* second)
{
	if (first)
		first->next = second;
	if (second)
		second->prev = first;
}

RowNode* SparseMatrix::embed_after(RowNode* node_before, int row)
{
	RowNode* middle = new RowNode(row, cols);
	++length;

	RowNode* node_after = node_before->next;
	link(node_before, middle);

	if (!node_after)
		tail = middle;
	else
		link(middle, node_after);

	return middle;
}

RowNode* SparseMatrix::get_row(int row, bool is_create_if_missing)
{
	// Similar logic to insert_sorted
	RowNode* prev_row = head;
	// Find the node with row-1
	while (prev_row->next && prev_row->next->row < row)
		prev_row = prev_row->next;

	bool found = prev_row->next && prev_row->next->row == row;

	if (found)
		return prev_row->next;

	if (!is_create_if_missing)	// not found and no create
		return nullptr;

	return embed_after(prev_row, row);
}

SparseMatrix::SparseMatrix(int rows, int cols) : rows(rows), cols(cols)
{
	tail = head = new RowNode(-1, cols);
	++length;
}

void SparseMatrix::set_value(int data, int row, int col)
{
	assert(0 <= row && row < rows);
	assert(0 <= col && col < cols);

	RowNode* node = get_row(row, true);
	node->col_list.set_value(data, col);
}

int SparseMatrix::get_value(int row, int col)
{
	assert(0 <= row && row < rows);
	assert(0 <= col && col < cols);

	RowNode* node = get_row(row, false);
	if (!node)		// no such row
		return 0;
	return node->col_list.get_value(col);
}

void SparseMatrix::print_matrix()
{
	std::cout << "\nPrint Matrix: " << rows << " x " << cols << "\n";

	RowNode* cur = head->next;

	for (int r = 0; r < rows; ++r) {
		if (cur && cur->row == r) {
			cur->col_list.print_row();
			cur = cur->next;
		}
		else {
			for (int j = 0; j < cols; ++j)
				std::cout << "0 ";
			std::cout << "\n";
		}
	}
}

void SparseMatrix::print_matrix_nonzero()
{
	std::cout << "\nPrint Matrix: " << rows << " x " << cols << "\n";
	for (RowNode* cur = head->next; cur; cur = cur->next)
		cur->col_list.print_row_nonzero();
}

void SparseMatrix::add(SparseMatrix& other)
{
	assert(rows == other.rows && cols == other.cols);
	// Iterate on the other first, and add it to the current one
	for (RowNode* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
		RowNode* this_row = get_row(other_cur->row, true);  // **
		this_row->col_list.add(other_cur->col_list);
	}
	// ** We can make this function more efficient, but let's keep simple
}
