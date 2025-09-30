#pragma once

typedef int type;

/// <summary>
/// This is the basic array base stack
/// </summary>
class Stack {
private:
	type* arr{};
	int arr_size{};
	int top{}; // index at the last postion or -1 if empty
public:
	Stack(int arr_size);

	~Stack();

	bool is_empty() const;

	bool is_full() const;

	void push(type item);

	type pop();

	type peek() const;

	void insert_bottom(type x);
	void reverse();

	void display() const;

};