#pragma once

#include <iostream>
#include <cassert>

using std::cout;

/// <summary>
/// LinkedList based Stack
/// </summary>
template <typename T>
class Stack04 {
private:
	struct Node
	{
		T data{};
		Node* next{};
		Node(T data) :data(data) {}
	};

	Node* head;

public:

	~Stack04()
	{
		while (!is_empty()) pop();
	}

	bool is_empty()const
	{
		return !head;
	}

	void push(T data)
	{
		Node* tmp = new Node(data);
		tmp->next = head;
		head = tmp;
	}

	T pop()
	{
		assert(!is_empty());

		T ret = head->data;

		Node* del = head;
		head = head->next;

		delete del;

		return ret;
	}

	T peek()const
	{
		assert(!is_empty());

		T element = head->data;
		return element;
	}

	void display()const
	{
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " | ";
		cout << '\n';
	}
};