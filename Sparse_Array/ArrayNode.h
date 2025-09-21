#pragma once

struct ArrayNode
{
	int data{};
	int index{};	// element index in the array (non-zero)
	ArrayNode* next{};
	ArrayNode* prev{};

	ArrayNode(int data, int index) :data(data), index(index) {}
};
