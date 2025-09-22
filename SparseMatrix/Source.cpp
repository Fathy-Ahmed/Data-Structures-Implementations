#include "SparseMatrix.h"
#include <iostream>
using namespace std;

void test_col() {
	ColumnLinkedList collst(12);
	collst.set_value(10, 10);
	collst.set_value(5, 5);
	collst.set_value(2, 2);
	collst.set_value(7, 7);
	collst.set_value(4, 4);
	//collst.print_row();
	collst.print_row_nonzero();
	collst.add(collst);
	collst.print_row_nonzero();
}

void test_sparse() {
	SparseMatrix mat(10, 10);
	mat.set_value(5, 3, 5);
	mat.set_value(7, 3, 7);
	mat.set_value(2, 3, 2);
	mat.set_value(0, 3, 2);
	mat.set_value(6, 5, 6);
	mat.set_value(4, 5, 4);
	mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	//mat.set_value(1, 70, 1);
	mat.print_matrix();
	mat.print_matrix_nonzero();

	SparseMatrix mat2(10, 10);
	mat2.set_value(5, 1, 9);
	mat2.set_value(6, 3, 8);
	mat2.set_value(9, 9, 9);
	mat.add(mat2);
	mat.print_matrix_nonzero();
}


int main() {
	cout << "*** Starting test cases *** \n\n\n";
	
	cout << "*** Start testing Column Linked List ***\n\n";
	test_col();

	cout << "\n*** Start testing Sparse Matrix ***\n\n";
	test_sparse();

	cout << "\n\n*** End of test cases ***\n\n";
	cout << "No RTA\n";
	return 0;
}