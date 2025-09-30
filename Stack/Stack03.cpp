#include "Stack03.h"
#include <iostream>
#include <cassert>
#define el '\n'
using std::cout;

Stack03::Stack03(int arr_size) :
	arr_size(arr_size), top1(-1), top2(arr_size) {
	arr = new int[arr_size];
}

Stack03::~Stack03() {
	delete[] arr;
}

bool Stack03::is_empty(int id) {
	if (id == 1)
		return top1 == -1;

	return top2 == arr_size;
}

bool Stack03::is_full() {
	return top1 + 1 >= top2;
}

int Stack03::peek(int id) {
	assert(!is_empty(id));

	if (id == 1)
		return arr[top1];

	return arr[top2];
}

void Stack03::push(int id, int item) {
	assert(!is_full());

	if (id == 1)
		arr[++top1] = item;
	else
		arr[--top2] = item;
}

int Stack03::pop(int id) {
	assert(!is_empty(id));

	if (id == 1)
		return arr[top1--];
	return arr[top2++];
}

void Stack03::display() {
	for (int i = top1; i >= 0; i--)
		cout << arr[i] << ' ';
	cout << el;

	for (int i = top2; i < arr_size; i++)
		cout << arr[i] << ' ';
	cout << el;
}