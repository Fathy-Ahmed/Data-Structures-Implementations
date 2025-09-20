#include "DoublyLinkedList.h"
#define FAST ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0)
#define el '\n'
using namespace std;



//====================================================================================
// SIMPLE TEST FRAMEWORK
//====================================================================================

class TestFramework {
public:
    static int total_tests;
    static int passed_tests;
    static int failed_tests;
    static void assert_test(bool condition, const std::string& test_name) {
        total_tests++;
        if (condition) {
            passed_tests++;
            cout << "[PASS] " << test_name << el;
        }
        else {
            failed_tests++;
            cout << "[FAIL] " << test_name << el;
        }
    }

    static void print_summary() {
        cout << "\n" << std::string(60, '=') << el;
        cout << "TEST SUMMARY:" << el;
        cout << "Total Tests: " << total_tests << el;
        cout << "Passed: " << passed_tests << el;
        cout << "Failed: " << failed_tests << el;
        cout << "Success Rate: " << (total_tests > 0 ? (passed_tests * 100 / total_tests) : 0) << "%" << el;
        cout << std::string(60, '=') << el;
    }

    static void reset_counters() {
        total_tests = passed_tests = failed_tests = 0;
    }
};

// Static member definitions
int TestFramework::total_tests = 0;
int TestFramework::passed_tests = 0;
int TestFramework::failed_tests = 0;

//====================================================================================
// TEST HELPER FUNCTIONS
//====================================================================================

class TestHelper {
public:
    // Helper to create a list with given values
    static void populate_list(LinkedList& list, const std::vector<int>& values) {
        for (int val : values) {
            list.insert_end(val);
        }
    }

    // Helper to verify list contents match expected values
    static bool verify_list_contents(LinkedList& list, const std::vector<int>& expected) {
        std::string actual = list.debug_to_string();
        std::string expected_str = "";
        for (size_t i = 0; i < expected.size(); ++i) {
            expected_str += std::to_string(expected[i]);
            if (i < expected.size() - 1) expected_str += " ";
        }
        return actual == expected_str;
    }

    // Helper to verify empty list
    static bool verify_empty_list(LinkedList& list) {
        return list.debug_to_string().empty();
    }
};

//====================================================================================
// CONSTRUCTOR AND DESTRUCTOR TESTS
//====================================================================================

void test_constructor_destructor() {
    cout << "\n=== CONSTRUCTOR & DESTRUCTOR TESTS ===" << el;

    // Test 1: Default constructor creates empty list
    {
        LinkedList list;
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list),
            "Default constructor creates empty list"
        );
    }
    // Destructor is automatically called here - should not crash

    // Test 2: Destructor properly cleans up non-empty list
    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 4, 5 });
        // List goes out of scope here - destructor should clean up properly
    }
    TestFramework::assert_test(true, "Destructor handles non-empty list without crashes");
}

//====================================================================================
// INSERTION TESTS
//====================================================================================

void test_insertion_functions() {
    cout << "\n=== INSERTION TESTS ===" << el;

    // Test insert_end
    {
        LinkedList list;
        list.insert_end(10);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 10 }),
            "insert_end on empty list"
        );

        list.insert_end(20);
        list.insert_end(30);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 10, 20, 30 }),
            "insert_end multiple elements"
        );
    }

    // Test insert_front
    {
        LinkedList list;
        list.insert_front(10);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 10 }),
            "insert_front on empty list"
        );

        list.insert_front(20);
        list.insert_front(30);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 30, 20, 10 }),
            "insert_front multiple elements"
        );
    }

    // Test insert_sorted on empty list
    {
        LinkedList list;
        list.insert_sorted(15);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 15 }),
            "insert_sorted on empty list"
        );
    }

    // Test insert_sorted maintaining order
    {
        LinkedList list;
        list.insert_sorted(20);
        list.insert_sorted(10);
        list.insert_sorted(30);
        list.insert_sorted(25);
        list.insert_sorted(5);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 5, 10, 20, 25, 30 }),
            "insert_sorted maintains ascending order"
        );
    }

    // Test insert_sorted with duplicates
    {
        LinkedList list;
        list.insert_sorted(20);
        list.insert_sorted(20);
        list.insert_sorted(10);
        list.insert_sorted(20);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 10, 20, 20, 20 }),
            "insert_sorted handles duplicates correctly"
        );
    }
}

//====================================================================================
// DELETION TESTS
//====================================================================================

void test_deletion_functions() {
    cout << "\n=== DELETION TESTS ===" << el;

    // Test delete_front
    {
        LinkedList list;
        list.delete_front(); // Should not crash on empty list
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list),
            "delete_front on empty list"
        );

        TestHelper::populate_list(list, { 10, 20, 30 });
        list.delete_front();
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 20, 30 }),
            "delete_front removes first element"
        );

        list.delete_front();
        list.delete_front();
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list),
            "delete_front until list is empty"
        );
    }

    // Test delete_end
    {
        LinkedList list;
        list.delete_end(); // Should not crash on empty list
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list),
            "delete_end on empty list"
        );

        TestHelper::populate_list(list, { 10, 20, 30 });
        list.delete_end();
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 10, 20 }),
            "delete_end removes last element"
        );

        list.delete_end();
        list.delete_end();
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list),
            "delete_end until list is empty"
        );
    }

    // Test delete_node_with_key
    {
        LinkedList list;
        list.delete_node_with_key(10); // Should not crash on empty list

        TestHelper::populate_list(list, { 10, 20, 30, 20, 40 });
        list.delete_node_with_key(20); // Remove first occurrence
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 10, 30, 20, 40 }),
            "delete_node_with_key removes first occurrence"
        );

        list.delete_node_with_key(10); // Remove head
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 30, 20, 40 }),
            "delete_node_with_key removes head"
        );

        list.delete_node_with_key(40); // Remove tail
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 30, 20 }),
            "delete_node_with_key removes tail"
        );

        list.delete_node_with_key(999); // Non-existent key
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 30, 20 }),
            "delete_node_with_key with non-existent key"
        );
    }

    // Test delete_all_nodes_with_key
    {
        LinkedList list;
        TestHelper::populate_list(list, { 10, 20, 10, 30, 10, 40, 10 });
        list.delete_all_nodes_with_key(10);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 20, 30, 40 }),
            "delete_all_nodes_with_key removes all occurrences"
        );

        list.delete_all_nodes_with_key(20);
        list.delete_all_nodes_with_key(30);
        list.delete_all_nodes_with_key(40);
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list),
            "delete_all_nodes_with_key can empty the list"
        );
    }

    // Test delete_even_positions
    {
        LinkedList list1, list2;
        TestHelper::populate_list(list1, { 1, 2, 3, 4, 5, 6 });
        TestHelper::populate_list(list2, { 1, 2, 3, 4, 5, 6 });

        list1.delete_even_positions1();
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list1, { 1, 3, 5 }),
            "delete_even_positions1 removes positions 2,4,6"
        );

        list2.delete_even_positions2();
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list2, { 1, 3, 5 }),
            "delete_even_positions2 removes positions 2,4,6"
        );
    }

    // Test delete_odd_positions
    {
        LinkedList list1, list2;
        TestHelper::populate_list(list1, { 1, 2, 3, 4, 5, 6 });
        TestHelper::populate_list(list2, { 1, 2, 3, 4, 5, 6 });

        list1.delete_odd_positions1();
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list1, { 2, 4, 6 }),
            "delete_odd_positions1 removes positions 1,3,5"
        );

        list2.delete_odd_positions2();
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list2, { 2, 4, 6 }),
            "delete_odd_positions2 removes positions 1,3,5"
        );
    }
}

//====================================================================================
// ANALYSIS TESTS
//====================================================================================

void test_analysis_functions() {
    cout << "\n=== ANALYSIS TESTS ===" << el;

    // Test is_palindrome
    {
        LinkedList list;
        TestFramework::assert_test(
            !list.is_palindrome(),
            "is_palindrome returns false for empty list"
        );

        list.insert_end(1);
        TestFramework::assert_test(
            list.is_palindrome(),
            "is_palindrome returns true for single element"
        );
    }

    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 2, 1 });
        TestFramework::assert_test(
            list.is_palindrome(),
            "is_palindrome returns true for odd-length palindrome"
        );
    }

    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 2, 1 });
        TestFramework::assert_test(
            list.is_palindrome(),
            "is_palindrome returns true for even-length palindrome"
        );
    }

    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 4, 5 });
        TestFramework::assert_test(
            !list.is_palindrome(),
            "is_palindrome returns false for non-palindrome"
        );
    }

    // Test find_the_middle functions
    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 4, 5 });
        TestFramework::assert_test(
            list.find_the_middle1() == 3,
            "find_the_middle1 finds correct middle in odd-length list"
        );
        TestFramework::assert_test(
            list.find_the_middle2() == 3,
            "find_the_middle2 finds correct middle in odd-length list"
        );
    }

    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 4 });
        TestFramework::assert_test(
            list.find_the_middle1() == 3,
            "find_the_middle1 finds correct middle in even-length list"
        );
        TestFramework::assert_test(
            list.find_the_middle2() == 3,
            "find_the_middle2 finds correct middle in even-length list"
        );
    }
}

//====================================================================================
// ACCESS TESTS
//====================================================================================

void test_access_functions() {
    cout << "\n=== ACCESS TESTS ===" << el;

    LinkedList list;
    TestHelper::populate_list(list, { 10, 20, 30, 40, 50 });

    // Test get_nth_node
    TestFramework::assert_test(
        list.get_nth_node(1) && list.get_nth_node(1)->data == 10,
        "get_nth_node(1) returns first node"
    );
    TestFramework::assert_test(
        list.get_nth_node(3) && list.get_nth_node(3)->data == 30,
        "get_nth_node(3) returns third node"
    );
    TestFramework::assert_test(
        list.get_nth_node(5) && list.get_nth_node(5)->data == 50,
        "get_nth_node(5) returns last node"
    );
    TestFramework::assert_test(
        list.get_nth_node(6) == nullptr,
        "get_nth_node(6) returns nullptr for out-of-bounds"
    );

    // Test get_nth_node_back
    TestFramework::assert_test(
        list.get_nth_node_back(1) && list.get_nth_node_back(1)->data == 50,
        "get_nth_node_back(1) returns last node"
    );
    TestFramework::assert_test(
        list.get_nth_node_back(3) && list.get_nth_node_back(3)->data == 30,
        "get_nth_node_back(3) returns third from end"
    );
    TestFramework::assert_test(
        list.get_nth_node_back(5) && list.get_nth_node_back(5)->data == 10,
        "get_nth_node_back(5) returns first node"
    );
    TestFramework::assert_test(
        list.get_nth_node_back(6) == nullptr,
        "get_nth_node_back(6) returns nullptr for out-of-bounds"
    );
}

//====================================================================================
// MANIPULATION TESTS
//====================================================================================

void test_manipulation_functions() {
    cout << "\n=== MANIPULATION TESTS ===" << el;

    // Test reverse
    {
        LinkedList list;
        list.reverse(); // Should not crash on empty list
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list),
            "reverse on empty list"
        );

        list.insert_end(42);
        list.reverse();
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 42 }),
            "reverse on single-element list"
        );
    }

    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 4, 5 });
        list.reverse();
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 5, 4, 3, 2, 1 }),
            "reverse on multiple-element list"
        );
    }

    // Test swap_kth
    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 4, 5 });
        list.swap_kth(1); // Swap 1st and 5th
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 5, 2, 3, 4, 1 }),
            "swap_kth swaps 1st and 5th elements"
        );
    }

    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 4, 5 });
        list.swap_kth(2); // Swap 2nd and 4th
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 1, 4, 3, 2, 5 }),
            "swap_kth swaps 2nd and 4th elements"
        );
    }

    {
        LinkedList list;
        TestHelper::populate_list(list, { 1, 2, 3, 4 });
        list.swap_kth(2); // Swap 2nd and 3rd (adjacent)
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, { 1, 3, 2, 4 }),
            "swap_kth handles adjacent elements"
        );
    }

    // Test merge_2sorted_lists
    {
        LinkedList list1, list2;
        TestHelper::populate_list(list1, { 1, 3, 5 });
        TestHelper::populate_list(list2, { 2, 4, 6 });

        list1.merge_2sorted_lists(list2);
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list1, { 1, 2, 3, 4, 5, 6 }),
            "merge_2sorted_lists merges two sorted lists"
        );
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list2),
            "merge_2sorted_lists empties the source list"
        );
    }

    {
        LinkedList list1, list2;
        TestHelper::populate_list(list2, { 1, 2, 3 });

        list1.merge_2sorted_lists(list2); // Merge into empty list
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list1, { 1, 2, 3 }),
            "merge_2sorted_lists handles empty target list"
        );
    }

    {
        LinkedList list1, list2;
        TestHelper::populate_list(list1, { 1, 2, 3 });

        list1.merge_2sorted_lists(list2); // Merge empty list
        TestFramework::assert_test(
            TestHelper::verify_list_contents(list1, { 1, 2, 3 }),
            "merge_2sorted_lists handles empty source list"
        );
    }
}

//====================================================================================
// EDGE CASE TESTS
//====================================================================================

void test_edge_cases() {
    cout << "\n=== EDGE CASE TESTS ===" << el;

    // Test operations on single-element list
    {
        LinkedList list;
        list.insert_end(42);

        TestFramework::assert_test(
            list.is_palindrome(),
            "Single element is palindrome"
        );
        TestFramework::assert_test(
            list.find_the_middle1() == 42,
            "Middle of single element list"
        );

        list.delete_front();
        TestFramework::assert_test(
            TestHelper::verify_empty_list(list),
            "Delete single element results in empty list"
        );
    }

    // Test large list operations
    {
        LinkedList list;
        std::vector<int> large_data;
        for (int i = 1; i <= 1000; ++i) {
            large_data.push_back(i);
            list.insert_end(i);
        }

        TestFramework::assert_test(
            TestHelper::verify_list_contents(list, large_data),
            "Large list insertion (1000 elements)"
        );

        TestFramework::assert_test(
            list.find_the_middle1() == 501,
            "Find middle in large list (method 1)"
        );
        TestFramework::assert_test(
            list.find_the_middle2() == 501,
            "Find middle in large list (method 2)"
        );
    }

    // Test with negative numbers
    {
        LinkedList list;
        TestHelper::populate_list(list, { -5, -3, -1, 0, 1, 3, 5 });

        TestFramework::assert_test(
            list.find_the_middle1() == 0,
            "Middle element with negative numbers"
        );

        list.delete_node_with_key(-5);
        list.delete_node_with_key(5);
        TestFramework::assert_test(
            list.is_palindrome(),
            "Palindrome with negative numbers"
        );
    }
}

//====================================================================================
// MAIN TEST RUNNER
//====================================================================================

int main() {FAST;
    cout << "DOUBLY LINKED LIST - COMPREHENSIVE TEST SUITE" << el;
    cout << "=" << std::string(60, '=') << el;

    TestFramework::reset_counters();

    // Run all test categories
    test_constructor_destructor();
    test_insertion_functions();
    test_deletion_functions();
    test_analysis_functions();
    test_access_functions();
    test_manipulation_functions();
    test_edge_cases();

    // Print final summary
    TestFramework::print_summary();

    return TestFramework::failed_tests > 0 ? 1 : 0;
}