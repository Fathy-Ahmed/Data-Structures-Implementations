#include "Stack02.h"
#include <iostream>
#include <cassert>
#define el '\n'

using std::cout;

Stack02::Stack02(int arr_size) : arr_size(arr_size), added_elements(0) {
	arr = new int[arr_size];
}

Stack02::~Stack02() {
	delete[] arr;
}

bool Stack02::is_empty() const {
	return added_elements == 0;
}

bool Stack02::is_full() const {
	return added_elements == arr_size;
}

bool Stack02::push(int item) {
	if (is_full())
		return false;

	for (int i = added_elements - 1; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}

	arr[0] = item;
	++added_elements;
	return true;
}

bool Stack02::pop() {
	if (is_empty())
		return false;

	for (int i = 0; i < added_elements - 1; i++)
	{
		arr[i] = arr[i + 1];
	}

	--added_elements;
	return true;
}

int Stack02::peek() const {
	if (is_empty())
		return -1;

	return arr[0];
}


void Stack02::display()const {
	for (int i = 0; i < added_elements; i++)
		cout << arr[i] << ' ';
	cout << el;
}