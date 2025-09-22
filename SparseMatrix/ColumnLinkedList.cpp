#include "ColumnLinkedList.h"
#include <iostream>
#include <cassert>
using std::cout;

void ColumnLinkedList::link(ColumnNode* first, ColumnNode* second) {
	if (first)
		first->next = second;

	if (second)
		second->prev = first;
}

ColumnNode* ColumnLinkedList::embed_after(ColumnNode* node_befor, int data, int col)
{
	ColumnNode* middle = new ColumnNode(data, col);
	++length;

	ColumnNode* node_after = node_befor->next;
	link(node_befor, middle);

	if (!node_after)
		tail = middle;
	else
		link(middle, node_after);

	return middle;
}

ColumnNode* ColumnLinkedList::get_col(int col, bool is_create_if_missing)
{
	ColumnNode* prev_col = head;
	while (prev_col->next && prev_col->next->column < col)
		prev_col = prev_col->next; // to get node with col-1

	bool found = prev_col->next && prev_col->next->column == col;

	if (found)
		return prev_col->next;

	if (!is_create_if_missing)
		return nullptr;

	return embed_after(prev_col, 0, col);
}

ColumnLinkedList::ColumnLinkedList(int cols) : cols(cols)
{
	// Sentinel_node
	tail = head = new ColumnNode(0, -1);
	++length;
}

void ColumnLinkedList::print_row()
{
	ColumnNode* cur = head->next;

	for (int c = 0; c < cols; ++c) {
		if (cur && cur->column == c) {
			cout << cur->data << " ";
			cur = cur->next;
		}
		else
			cout << "0 ";
	}
	cout << "\n";
}

void ColumnLinkedList::print_row_nonzero()
{
	for (ColumnNode* cur = head->next; cur; cur = cur->next)
		cout << cur->data << " ";
	cout << "\n";
}

void ColumnLinkedList::set_value(int data, int col) 
{
	get_col(col, true)->data = data;
}

int ColumnLinkedList::get_value(int col) 
{
	ColumnNode* node = get_col(col, false);
	if (!node)
		return 0;
	return node->data;
}

void ColumnLinkedList::add(ColumnLinkedList& other)
{
	assert(cols == other.cols);

	// Iterate on the other first, and add it to the current one
	for (ColumnNode* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
		ColumnNode* this_col = get_col(other_cur->column, true);  // **
		this_col->data += other_cur->data;
	}
	// ** We can make this function more efficient, but let's keep simple
}