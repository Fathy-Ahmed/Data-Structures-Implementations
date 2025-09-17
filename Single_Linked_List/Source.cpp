#include <iostream>
#include "SingleLinkedList.h"
#define el '\n'
using namespace std;

void test1()
{
    cout << "\n\ntest1\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    // some actions
    list.print();

    string expected = "1 2 3";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");

    cout << "✓ Test 1 passed\n";

}

void test2()
{
    cout << "\n\ntest2\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    // some actions
    list.print();

    string expected = "1 2 3 4";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");

    cout << "✓ Test 2 passed\n";
}

void test_basic_operations()
{
    cout << "\n=== Test Basic Operations ===\n";
    LinkedList list;

    // Test empty list
    cout << "Empty list: ";
    list.print();
    assert(list.debug_to_string() == "");

    // Test single element
    list.insert_end(42);
    cout << "Single element: ";
    list.print();
    assert(list.debug_to_string() == "42");

    // Test multiple elements
    list.insert_end(10);
    list.insert_end(20);
    cout << "Multiple elements: ";
    list.print();
    assert(list.debug_to_string() == "42 10 20");

    cout << "✓ Basic operations passed\n";
}

void test_insert_operations()
{
    cout << "\n=== Test Insert Operations ===\n";
    LinkedList list;

    // Test insert_front
    list.insert_front(1);
    list.insert_front(2);
    list.insert_front(3);
    cout << "Insert front (3,2,1): ";
    list.print();
    assert(list.debug_to_string() == "3 2 1");

    // Test insert_end
    list.insert_end(4);
    list.insert_end(5);
    cout << "Insert end (4,5): ";
    list.print();
    assert(list.debug_to_string() == "3 2 1 4 5");

    cout << "✓ Insert operations passed\n";
}

void test_delete_operations()
{
    cout << "\n=== Test Delete Operations ===\n";
    LinkedList list;

    // Setup list: 1 2 3 4 5
    for (int i = 1; i <= 5; i++) {
        list.insert_end(i);
    }
    cout << "Initial: ";
    list.print();

    // Test delete_front
    list.delete_front();
    cout << "After delete_front: ";
    list.print();
    assert(list.debug_to_string() == "2 3 4 5");

    // Test delete_back
    list.delete_back();
    cout << "After delete_back: ";
    list.print();
    assert(list.debug_to_string() == "2 3 4");

    // Test delete_node_with_key
    list.delete_node_with_key(3);
    cout << "After delete key 3: ";
    list.print();
    assert(list.debug_to_string() == "2 4");

    cout << "✓ Delete operations passed\n";
}

void test_search_operations()
{
    cout << "\n=== Test Search Operations ===\n";
    LinkedList list;

    // Setup: 10 20 30 40 50
    for (int i = 1; i <= 5; i++) {
        list.insert_end(i * 10);
    }
    cout << "List: ";
    list.print();

    // Test search
    assert(list.search(30) == 3);
    assert(list.search(99) == -1);
    cout << "Search 30: position " << list.search(30) << "\n";
    cout << "Search 99: position " << list.search(99) << "\n";

    // Test get_nth
    Node* node = list.get_nth(2);
    assert(node && node->data == 20);
    cout << "get_nth(2): " << (node ? node->data : -1) << "\n";

    // Test get_nth_back
    node = list.get_nth_back(2);
    assert(node && node->data == 40);
    cout << "get_nth_back(2): " << (node ? node->data : -1) << "\n";

    cout << "✓ Search operations passed\n";
}

void test_duplicate_removal() 
{
    cout << "\n=== Test Duplicate Removal ===\n";

    // Test remove_duplicates (unsorted)
    LinkedList list1;
    int arr1[] = { 1, 2, 1, 3, 2, 4 };
    for (int x : arr1) list1.insert_end(x);
    cout << "Before remove_duplicates: ";
    list1.print();
    list1.remove_duplicates();
    cout << "After remove_duplicates: ";
    list1.print();
    assert(list1.debug_to_string() == "1 2 3 4");

    // Test remove_all_repeated (removes all duplicates)
    LinkedList list2;
    int arr2[] = { 1, 1, 2, 3, 3, 4, 5 };
    for (int x : arr2) list2.insert_end(x);
    cout << "Before remove_all_repeated: ";
    list2.print();
    list2.remove_all_repeated();
    cout << "After remove_all_repeated: ";
    list2.print();
    assert(list2.debug_to_string() == "2 4 5");

    // Test remove_all_repeated_from_sorted
    LinkedList list3;
    int arr3[] = { 1, 1, 2, 3, 3, 4, 5, 5 };
    for (int x : arr3) list3.insert_end(x);
    cout << "Before remove_all_repeated_from_sorted: ";
    list3.print();
    list3.remove_all_repeated_from_sorted();
    cout << "After remove_all_repeated_from_sorted: ";
    list3.print();
    assert(list3.debug_to_string() == "2 4");

    cout << "✓ Duplicate removal passed\n";
}

void test_list_manipulation()
{
    cout << "\n=== Test List Manipulation ===\n";

    // Test reverse
    LinkedList list1;
    for (int i = 1; i <= 4; i++) list1.insert_end(i);
    cout << "Before reverse: ";
    list1.print();
    list1.reverse();
    cout << "After reverse: ";
    list1.print();
    assert(list1.debug_to_string() == "4 3 2 1");

    // Test swap_pairs
    LinkedList list2;
    for (int i = 1; i <= 5; i++) list2.insert_end(i);
    cout << "Before swap_pairs: ";
    list2.print();
    list2.swap_pairs();
    cout << "After swap_pairs: ";
    list2.print();
    assert(list2.debug_to_string() == "2 1 4 3 5");

    // Test rotate_left
    LinkedList list3;
    for (int i = 1; i <= 5; i++) list3.insert_end(i);
    cout << "Before rotate_left(2): ";
    list3.print();
    list3.rotate_left(2);
    cout << "After rotate_left(2): ";
    list3.print();
    assert(list3.debug_to_string() == "3 4 5 1 2");

    cout << "✓ List manipulation passed\n";
}

void test_advanced_operations()
{
    cout << "\n=== Test Advanced Operations ===\n";

    // Test move_key_occurence_back
    LinkedList list1;
    int arr1[] = { 1, 2, 1, 3, 1, 4 };
    for (int x : arr1) list1.insert_end(x);
    cout << "Before move key 1 to back: ";
    list1.print();
    list1.move_key_occurence_back(1);
    cout << "After move key 1 to back: ";
    list1.print();
    assert(list1.debug_to_string() == "2 3 4 1 1 1");

    // Test delete_even_positions
    LinkedList list2;
    for (int i = 1; i <= 6; i++) list2.insert_end(i);
    cout << "Before delete_even_positions: ";
    list2.print();
    list2.delete_even_positions();
    cout << "After delete_even_positions: ";
    list2.print();
    assert(list2.debug_to_string() == "1 3 5");

    // Test odd_pos_even_pos
    LinkedList list3;
    for (int i = 1; i <= 6; i++) list3.insert_end(i);
    cout << "Before odd_pos_even_pos: ";
    list3.print();
    list3.odd_pos_even_pos();
    cout << "After odd_pos_even_pos: ";
    list3.print();
    assert(list3.debug_to_string() == "1 3 5 2 4 6");

    cout << "✓ Advanced operations passed\n";
}

void test_edge_cases()
{
    cout << "\n=== Test Edge Cases ===\n";

    // Test single element operations
    LinkedList single;
    single.insert_end(42);
    cout << "Single element list: ";
    single.print();

    single.reverse();
    assert(single.debug_to_string() == "42");
    cout << "After reverse (single): ";
    single.print();

    single.swap_pairs();
    assert(single.debug_to_string() == "42");
    cout << "After swap_pairs (single): ";
    single.print();

    // Test two element operations
    LinkedList two;
    two.insert_end(1);
    two.insert_end(2);
    cout << "Two element list: ";
    two.print();

    two.swap_head_and_tail();
    cout << "After swap_head_and_tail: ";
    two.print();
    assert(two.debug_to_string() == "2 1");

    cout << "✓ Edge cases passed\n";
}

void test_comparison_operations()
{
    cout << "\n=== Test Comparison Operations ===\n";

    LinkedList list1, list2, list3;

    // Setup identical lists
    for (int i = 1; i <= 3; i++) {
        list1.insert_end(i);
        list2.insert_end(i);
    }

    // Setup different list
    for (int i = 1; i <= 2; i++) {
        list3.insert_end(i);
    }

    cout << "List1: ";
    list1.print();
    cout << "List2: ";
    list2.print();
    cout << "List3: ";
    list3.print();

    assert(list1.is_same1(list2) == true);
    assert(list1.is_same1(list3) == false);
    assert(list1.is_same2(list2) == true);
    assert(list1.is_same2(list3) == false);

    cout << "list1 == list2: " << (list1.is_same1(list2) ? "true" : "false") << "\n";
    cout << "list1 == list3: " << (list1.is_same1(list3) ? "true" : "false") << "\n";

    cout << "✓ Comparison operations passed\n";
}

void test_sorted_operations()
{
    cout << "\n=== Test Sorted Operations ===\n";

    LinkedList list;

    // Test insert_sorted
    int arr[] = { 3, 1, 4, 1, 5, 9, 2, 6 };
    for (int x : arr) {
        list.insert_sorted(x);
    }
    cout << "After inserting {3,1,4,1,5,9,2,6} in sorted order: ";
    list.print();
    assert(list.debug_to_string() == "1 1 2 3 4 5 6 9");

    cout << "✓ Sorted operations passed\n";
}

void run_all_tests()
{
    cout << "\n" << string(50, '=') << "\n";
    cout << "RUNNING COMPREHENSIVE LINKEDLIST TESTS\n";
    cout << string(50, '=') << "\n";

    try {
		test1();
		test2();
        test_basic_operations();
        test_insert_operations();
        test_delete_operations();
        test_search_operations();
        test_duplicate_removal();
        test_list_manipulation();
        test_advanced_operations();
        test_edge_cases();
        test_comparison_operations();
        test_sorted_operations();

        cout << "\n" << string(50, '=') << "\n";
        cout << "🎉 ALL TESTS PASSED SUCCESSFULLY! 🎉\n";
        cout << string(50, '=') << "\n";

    }
    catch (const exception& e) {
        cout << "\n❌ TEST FAILED: " << e.what() << "\n";
    }
}

int main()
{
    run_all_tests();


    cout << "\n\nNo RTE\n\n";

    return 0;
}