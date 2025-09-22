#pragma once

#include "ColumnLinkedList.h"
struct RowNode
{
	int row{};
	ColumnLinkedList col_list;

	RowNode* next{};
	RowNode* prev{};

	RowNode(int row, int cols) : row(row), col_list(cols) {}
};