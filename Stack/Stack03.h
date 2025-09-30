#pragma once

/// <summary>
/// This act like two stack in one stack
/// if we have stack of 100 but i used 20 only i can use the other 80 as anthor stack
/// it's new design
/// 
/// Stack 1: add normally
/// Stack 2: add from the back
/// 
/// this way:
/// 		same time for the old code at Stack01
/// 		Both of them can utilize amap
/// 
/// </summary>
class Stack03 {
private:

	int* arr;
	int arr_size{};
	int top1{};
	int top2{};

public:
	Stack03(int arr_size);

	~Stack03();

	bool is_empty(int id);

	bool is_full();

	int peek(int id);

	void push(int id, int item);

	int pop(int id);

	void display();

};