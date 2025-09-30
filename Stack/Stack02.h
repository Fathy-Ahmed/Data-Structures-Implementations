#pragma once

/// <summary>
/// Another Stack desgin where the array[0] is the top
/// </summary>
class Stack02 {
private:
	int* arr{};
	int arr_size{};
	int added_elements{};
public:
	Stack02(int arr_size);

	~Stack02();

	bool is_empty() const;

	bool is_full() const;

	bool push(int item);

	bool pop();

	int peek() const;

	void display()const;
};
