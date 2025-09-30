#include "Stack.h"
#include <iostream>
#include <cassert>
#define el '\n'

using std::cout;


Stack::Stack(int arr_size) :arr_size(arr_size), top(-1) {
	arr = new type[arr_size];
}

Stack::~Stack() {
	delete[] arr;
}

bool Stack::is_empty() const {
	return top == -1;
}

bool Stack::is_full() const {
	return top == arr_size - 1;
}

void Stack::push(type item) {
	assert(!is_full());

	arr[++top] = item;
}

type Stack::pop() {
	assert(!is_empty());
	return arr[top--];
}

type Stack::peek() const {
	assert(!is_empty());
	return arr[top];
}

void Stack::insert_bottom(type x) {
	assert(!is_full());

	if (is_empty())
		push(x);
	else {
		type cur = pop();
		insert_bottom(x);
		push(cur);
	}
}
void Stack::reverse() {
	if (is_empty())
		return;
	type cur = pop();
	reverse();
	insert_bottom(cur);
}

void Stack::display() const {
	for (int i = top; i >= 0; --i)
		cout << arr[i] << ' ';
	cout << el;
}