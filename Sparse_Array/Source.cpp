#include "SparseArray.h"
#include <iostream>
#define el '\n';
using namespace std;

void test_index() {
	ArrayLinkedList array(10);	// length 10
	array.set_value(50, 5);
	array.set_value(20, 2);
	array.set_value(70, 7);
	array.set_value(40, 4);
	array.print_array();
	// 0 0 20 0 40 50 0 70 0 0
	array.print_array_nonzero();
	// 20 40 50 70
	cout << array.get_value(7) << "\n";	// 70

	ArrayLinkedList array2(10);
	array2.set_value(1, 4);
	array2.set_value(3, 7);
	array2.set_value(4, 6);

	array.add(array2);
	array.print_array();
	// 0 0 20 0 41 50 4 73 0 0
}

int main() {

	cout << "\n*** Tests Start ***\n\n";

	test_index();

	cout << "\n*** Tests Passed ***\n\n";

	cout << "\n\nNo RTA" << el;
	return 0;
}