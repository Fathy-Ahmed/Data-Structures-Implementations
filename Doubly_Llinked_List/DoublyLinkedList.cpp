#include "DoublyLinkedList.h"
#include <cassert>
#include <vector>
#include <sstream>
//#define ll long long
#define el '\n'

using std::cout;

//====================================================================================
// CONSTRUCTORS AND DESTRUCTOR
//====================================================================================

LinkedList::LinkedList() {}

// Destructor implementation provided by ChatGPT
LinkedList::~LinkedList() {
	Node* cur = head;
	// Traverse the list and delete each node
	while (cur) {
		Node* next = cur->next;
		delete cur;
		cur = next;
	}
	// Reset all member variables to clean state
	head = tail = nullptr;
	length = 0;
	debug_data.clear();
}

//====================================================================================
// DEBUG SUPPORT FUNCTIONS
//====================================================================================

void LinkedList::debug_add_node(Node* node) {
	// Add node pointer to debug tracking vector
	debug_data.push_back(node);
}

void LinkedList::debug_remove_node(Node* node) {
	// Find and remove node pointer from debug tracking vector
	auto it = find(debug_data.begin(), debug_data.end(), node);
	if (it == debug_data.end())
		cout << "Node does not exist\n";
	else debug_data.erase(it);
}

void LinkedList::debuge_print_address() {
	// Print memory address and data for each node in forward order
	for (Node* cur = head; cur; cur = cur->next)
		cout << cur << ", " << cur->data << el;
	cout << el;
}

void LinkedList::debug_print_node(Node* node, bool is_seperate) {
	// Print detailed node information showing prev/current/next relationships
	if (is_seperate)
		cout << "Sep: ";
	if (!node) {
		cout << "nullptr" << el;
		return;
	}

	// Show previous node's data or 'X' if none
	if (!node->prev)
		cout << "X\t";
	else
		cout << node->prev->data << "\t";

	cout << " <= [" << node->data << "]\t => \t";

	// Show next node's data or 'X' if none
	if (!node->next)
		cout << "X\t";
	else
		cout << node->next->data << "\t";

	// Indicate if this node is head or tail
	if (node == head)
		cout << "head\n";
	else if (node == tail)
		cout << "tail\n";
	else
		cout << "\n";
}

void LinkedList::debug_print_list(string msg) {
	// Print the entire list structure using debug_print_node for each node
	if (msg != "")
		cout << msg << el;
	for (int i = 0; i < (int)debug_data.size(); ++i)
		debug_print_node(debug_data[i]);
	cout << "************\n" << std::flush;
}

string LinkedList::debug_to_string() {
	// Convert list to space-separated string representation
	if (length == 0)
		return "";

	std::ostringstream oss;
	for (Node* cur = head; cur; cur = cur->next) {
		oss << cur->data;
		if (cur->next)
			oss << " ";
	}
	return oss.str();
}

void LinkedList::debug_verfiy_data_integrity() {
	// Comprehensive integrity check of the list structure
	if (length == 0) {
		// Empty list checks
		assert(head == nullptr);
		assert(tail == nullptr);
	}
	else {
		// Non-empty list basic checks
		assert(head != nullptr);
		assert(tail != nullptr);
		if (length == 1)
			assert(head == tail);
		else
			assert(head != tail);
		// Head should have no previous, tail should have no next
		assert(!head->prev);
		assert(!tail->next);
	}

	// Forward traversal length verification
	int len = 0;
	for (Node* cur = head; cur; cur = cur->next, len++) {
		if (len == length - 1)	// make sure we end at tail
			assert(cur == tail);
	}

	assert(length == len);
	assert(length == (int)debug_data.size());

	// Backward traversal length verification
	len = 0;
	for (Node* cur = tail; cur; cur = cur->prev, len++) {
		if (len == length - 1)	// make sure we end at head
			assert(cur == head);
	}
}

//====================================================================================
// HELPER FUNCTIONS FOR NODE MANAGEMENT
//====================================================================================

// These 2 simple functions just to not forget changing the vector and length
void LinkedList::delete_node(Node* node) {
	// Remove from debug tracking and decrement length before deletion
	debug_remove_node(node);
	--length;
	delete node;
}

void LinkedList::add_node(Node* node) {
	// Add to debug tracking and increment length
	debug_add_node(node);
	++length;
}

//====================================================================================
// DISPLAY FUNCTIONS
//====================================================================================

void LinkedList::print() {
	// Simple forward traversal printing
	for (Node* cur = head; cur; cur = cur->next)
		cout << cur->data << " ";
	cout << el;
}

void LinkedList::print_reverse() {
	// Simple backward traversal printing
	for (Node* cur = tail; cur; cur = cur->prev) {
		cout << cur->data << ' ';
	}cout << el;
}

//====================================================================================
// LINKING AND INSERTION FUNCTIONS
//====================================================================================

void LinkedList::link(Node* first, Node* second)
{
	// Bidirectionally link two nodes, handling nullptr cases
	if (first)
		first->next = second;
	if (second)
		second->prev = first;
}

void LinkedList::insert_end(int val) {
	// Create new node and add to end of list
	Node* item = new Node(val);
	add_node(item);

	if (!head)
		// Empty list: new node becomes both head and tail
		head = tail = item;
	else {
		// Non-empty list: link to current tail and update tail
		link(tail, item);
		tail = item;
	}

	debug_verfiy_data_integrity();
}

void LinkedList::insert_front(int val) {
	// Create new node and add to beginning of list
	Node* item = new Node(val);
	add_node(item);

	if (!head)
		// Empty list: new node becomes both head and tail
		head = tail = item;
	else {
		// Non-empty list: link to current head and update head
		link(item, head);
		head = item;
	}
	debug_verfiy_data_integrity();
}

void LinkedList::embed_after(Node* node_before, int val) {
	// Insert new node between node_before and its current next node
	Node* item = new Node(val);
	add_node(item);

	Node* node_after = node_before->next;
	link(node_before, item);
	link(item, node_after);
}

void LinkedList::insert_sorted(int val) {
	// Insert value in correct position to maintain sorted order
	if (!length || head->data >= val)
		// Empty list or value should be first
		insert_front(val);
	else if (tail->data <= val)
		// Value should be last
		insert_end(val);
	else {
		// Find correct position and insert
		for (auto cur = head; cur; cur = cur->next) {
			if (val <= cur->data) {
				embed_after(cur->prev, val);
				break;
			}
		}
	}

	debug_verfiy_data_integrity();
}

//====================================================================================
// DELETION FUNCTIONS
//====================================================================================

Node* LinkedList::delete_and_link(Node* cur)
{
	// Delete current node and link its neighbors together
	Node* ret = cur->prev;
	link(cur->prev, cur->next);
	delete_node(cur);

	return ret; // Return previous node for iteration purposes
}

void LinkedList::delete_front() {
	// Delete the first node in the list
	if (length == 0)
		return;

	Node* cur = head->next;
	delete_node(head);
	head = cur;

	if (head)
		head->prev = nullptr;
	else
		// List became empty
		tail = nullptr;

	debug_verfiy_data_integrity();
}

void LinkedList::delete_end()
{
	// Delete the last node in the list
	if (length <= 1)
		// Single node or empty list: use delete_front
		delete_front();
	else {
		// Multiple nodes: update tail and delete old tail
		auto temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete_node(temp);
	}
	debug_verfiy_data_integrity();
}

void LinkedList::delete_node_with_key(int val) {
	// Delete first occurrence of value
	if (!length)
		return;
	if (head->data == val)
		delete_front();
	else {
		// Search for value and delete when found
		for (Node* cur = head; cur; cur = cur->next)
		{
			if (cur->data == val) {
				cur = delete_and_link(cur);
				if (!cur->next) // tail
					tail = cur;
				break;
			}
		}
	}
	debug_verfiy_data_integrity();
}

void LinkedList::delete_all_nodes_with_key(int val)
{
	// Delete all occurrences of the specified value
	for (Node* cur = head; cur; )
	{
		if (cur->data == val) {
			if (!cur->prev) {
				// Deleting head node
				delete_front();
				cur = head;
			}
			else {
				// Deleting non-head node
				cur = delete_and_link(cur);
				if (!cur->next) {
					tail = cur;
					break;
				}
			}
		}
		else {
			cur = cur->next;
		}
	}

	debug_verfiy_data_integrity();
}

void LinkedList::delete_even_positions1()
{
	// Delete nodes at even positions (2nd, 4th, 6th, etc.) - Version 1
	if (!length)
		return;
	int i = 1;
	for (Node* cur = head; cur; ++i, cur = cur->next)
	{
		if (i % 2 == 0) {
			// Even position: delete this node
			cur = delete_and_link(cur);
			if (cur->next) {
				// Continue from next node
				cur = cur->next;
				++i;
			}
			else {
				// Reached end
				tail = cur;
				break;
			}
		}
	}
	debug_verfiy_data_integrity();
}

void LinkedList::delete_even_positions2()
{
	// Delete nodes at even positions (2nd, 4th, 6th, etc.) - Version 2
	if (length <= 1)
		return;
	// Iterate through odd positions and delete the next (even) node
	for (Node* cur = head; cur && cur->next; cur = cur->next) {
		delete_and_link(cur->next);
		if (!cur->next) // even lenght
			tail = cur;
	}
	debug_verfiy_data_integrity();
}

void LinkedList::delete_odd_positions1()
{
	// Delete nodes at odd positions (1st, 3rd, 5th, etc.) - Version 1
	if (!length)
		return;
	// Delete first node, then delete even positions from remaining list
	delete_front();
	delete_even_positions1();
}

void LinkedList::delete_odd_positions2()
{
	// Delete nodes at odd positions (1st, 3rd, 5th, etc.) - Version 2
	if (!length)
		return;
	// Delete first node, then delete even positions from remaining list
	delete_front();
	delete_even_positions2();
}

//====================================================================================
// ANALYSIS FUNCTIONS
//====================================================================================

bool LinkedList::is_palindrome()
{
	// Check if list reads same forwards and backwards
	if (!length)
		return false;

	// Compare nodes from both ends moving inward
	int len = length / 2;
	Node* h = head, * t = tail;
	while (len--)
	{
		if (abs(h->data) != abs(t->data))
			return false;
		h = h->next;
		t = t->prev;
	}
	return true;
}

int LinkedList::find_the_middle1()
{
	// Find middle using two pointers moving from both ends
	assert(head);

	Node* h = head, * t = tail;
	// Move pointers toward each other until they meet or cross
	while (t != h && t->prev != h) {
		h = h->next;
		t = t->prev;
	}
	return t->data;
}

int LinkedList::find_the_middle2()
{
	// Find middle using tortoise and hare algorithm
	assert(head);
	Node* slow = head, * fast = head;
	// Fast moves 2 steps, slow moves 1 step
	// When fast reaches end, slow is at middle
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow->data;
}

//====================================================================================
// ACCESS FUNCTIONS
//====================================================================================

Node* LinkedList::get_nth_node(int n)
{
	// Get nth node from beginning (1-indexed)
	if (n > length)
		return nullptr;
	Node* ret = head;
	while (--n) ret = ret->next;
	return ret;
}

Node* LinkedList::get_nth_node_back(int n)
{
	// Get nth node from end (1-indexed)
	if (n > length)
		return nullptr;
	Node* ret = tail;
	while (--n) ret = ret->prev;
	return ret;
}

//====================================================================================
// ADVANCED MANIPULATION FUNCTIONS
//====================================================================================

void LinkedList::swap_forward_with_backword(int k)
{
	// Swap kth node from start with kth node from end
	int kth_back = length - k + 1;
	if (k > length || k == kth_back)
		return;

	// Ensure k is the smaller position for consistent handling
	if (k > kth_back)
		std::swap(k, kth_back);

	Node* first = get_nth_node(k);
	Node* last = get_nth_node(kth_back);

	// Store neighbor pointers before swapping
	Node* first_prev = first->prev;
	Node* first_next = first->next;

	Node* last_prev = last->prev;
	Node* last_next = last->next;

	if (k + 1 == kth_back) {	// neighbours
		// Special case: nodes are adjacent
		link(first_prev, last);
		link(last, first);
		link(first, last_next);
	}
	else {
		// General case: nodes are not adjacent
		link(first_prev, last);
		link(last, first_next);

		link(last_prev, first);
		link(first, last_next);
	}
	if (k == 1)
		// Swapping head and tail
		std::swap(head, tail);
	debug_verfiy_data_integrity();
}

void LinkedList::swap_kth(int k)
{
	// Swap kth node from start with kth node from end
	auto first = get_nth_node(k);
	auto last = get_nth_node_back(k);
	if (first == last)
		return;

	// Ensure consistent ordering for adjacent node handling
	if (first->prev == last)
		std::swap(first, last);

	// Store neighbor pointers before swapping
	Node* first_prev = first->prev;
	Node* first_next = first->next;

	Node* last_prev = last->prev;
	Node* last_next = last->next;

	if (first->next == last) {	// neighbours
		// Special case: nodes are adjacent
		link(first_prev, last);
		link(last, first);
		link(first, last_next);
	}
	else {
		// General case: nodes are not adjacent
		link(first_prev, last);
		link(last, first_next);

		link(last_prev, first);
		link(first, last_next);
	}
	if (k == 1)
		// Swapping involves head/tail
		std::swap(head, tail);
	debug_verfiy_data_integrity();
}

void LinkedList::reverse()
{
	// Reverse the entire list by changing link directions
	if (length <= 1)
		return;

	// Reverse all the links by traversing and swapping directions
	Node* first = head, * second = head->next;
	while (second) {
		Node* f = second, * s = second->next;
		// Reverse the link direction
		link(second, first);

		first = f;
		second = s;
	}
	// Swap head and tail pointers
	std::swap(head, tail);
	// Clear the boundary conditions
	head->prev = tail->next = nullptr;

	debug_verfiy_data_integrity();
}

void LinkedList::merge_2sorted_lists(LinkedList& other)
{
	// Merge two sorted lists into one sorted list
	if (!other.head)
		return;
	if (head) {
		// Both lists have elements: merge them
		Node* cur1 = head;
		Node* cur2 = other.head;
		Node* last{};
		head = nullptr;

		// Compare elements and build new sorted list
		while (cur1 && cur2) {
			Node* next{};
			if (cur1->data <= cur2->data) {
				next = cur1;
				cur1 = cur1->next;
			}
			else {
				next = cur2;
				cur2 = cur2->next;
			}
			link(last, next);
			last = next;
			if (!head) // first element
				head = last;
		}

		// Append remaining elements
		if (cur2) {
			tail = other.tail;
			link(last, cur2);
		}
		else if (cur1) {
			link(last, cur1);
		}
	}
	else {
		// This list is empty: take the other list
		head = other.head;
		tail = other.tail;
	}

	// Update length and debug data
	length += other.length;

	debug_data.insert(debug_data.end(), other.debug_data.begin(), other.debug_data.end());

	// Clear the other list (transfer ownership)
	other.length = 0;
	other.head = other.tail = nullptr;
	other.debug_data.clear();

	debug_verfiy_data_integrity();
}