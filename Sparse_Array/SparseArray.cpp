#include "SparseArray.h"
#define el '\n';
#include<iostream>
#include <cassert>
using std::cout;

void ArrayLinkedList::link(ArrayNode* first, ArrayNode* second)
{
	if (first)
		first->next = second;
	if (second)
		second->prev = first;
}

ArrayNode* ArrayLinkedList::embed_after(ArrayNode* node_before, int data, int index)
{
	ArrayNode* md = new ArrayNode(data, index);
	++length;

	ArrayNode* node_after = node_before->next;
	link(node_before, md);

	if (!node_after)
		tail = md;
	else
		link(md, node_after);

	return md;
}

ArrayNode* ArrayLinkedList::get_index(int index, bool is_create_if_missing)
{
	ArrayNode* prev_index = head;

	while (prev_index->next && prev_index->next->index < index)
		prev_index = prev_index->next;

	bool found = prev_index->next && prev_index->next->index == index;

	if (found)
		return prev_index->next;

	if (!is_create_if_missing)
		return nullptr;

	return embed_after(prev_index, 0, index);
}

ArrayLinkedList::ArrayLinkedList(int array_length): array_length(array_length)
{
	//Sentinel_node
	tail = head = new ArrayNode(0, -1);
	++length;
}

void ArrayLinkedList::print_array()
{
	ArrayNode* cur = head->next;
	for (int i = 0; i < array_length; ++i)
	{
		if (cur && cur->index == i) {
			cout << cur->data << ' ';
			cur = cur->next;
		}
		else cout << 0 << ' ';
	}
	cout << el;
}

void ArrayLinkedList::print_array_nonzero()
{
	for (ArrayNode* cur = head->next; cur; cur = cur->next)
		cout << cur->data << ' ';
	cout << el;
}

void ArrayLinkedList::set_value(int data, int index)
{
	get_index(index, true)->data = data;
}

int ArrayLinkedList::get_value(int index)
{
	ArrayNode* node = get_index(index, false);

	if (!node)
		return 0;

	return node->data;
}

void ArrayLinkedList::add(ArrayLinkedList& other)
{
	assert(array_length == other.array_length);

	for (ArrayNode* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
		auto this_index = get_index(other_cur->index, true);
		this_index->data = other_cur->data;
	}

	// ** We can make this function more efficient, but let's keep simple

}

