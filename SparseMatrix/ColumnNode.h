#pragma once

struct	ColumnNode {
	int data{};
	int column{};

	ColumnNode* next{};
	ColumnNode* prev{};

	ColumnNode(int data, int column) :data(data), column(column) {}
};