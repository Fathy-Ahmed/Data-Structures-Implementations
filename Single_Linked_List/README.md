# Single Linked List Implementation

A comprehensive C++ implementation of a singly linked list data structure with advanced operations and debugging utilities.

## Overview

This project provides a robust and feature-rich implementation of a singly linked list with over 30 operations including insertion, deletion, searching, manipulation algorithms, and specialized functions for duplicate handling, list reversal, and rotation.

## Features

### Core Operations
- **Insertion**: Insert at front, end, or specific position with sorted insertion support
- **Deletion**: Remove from front, end, specific position, or by value
- **Search**: Linear search with position tracking and optimized search variants
- **Traversal**: Forward iteration with position-based access

### Advanced Algorithms
- **Duplicate Handling**: Multiple algorithms for removing duplicates in sorted and unsorted lists
- **List Manipulation**: Reverse, rotate, swap operations
- **Rearrangement**: Group odd/even positioned elements, move specific values
- **Comparison**: Deep equality checking between lists

### Specialized Features
- **Memory Management**: Automatic cleanup with destructor
- **Debug Utilities**: Comprehensive debugging and integrity verification
- **Error Handling**: Boundary checking and assertion-based validation

## File Structure

```
Single_Linked_List/
├── Node.h                    # Node structure definition
├── Single_linked_list.h      # Class declaration and documentation  
├── Single_Linked_List.cpp    # Implementation of all methods
└── main.cpp                  # Test cases and examples
```

## Class Interface

### Constructor/Destructor
```cpp
LinkedList();                 // Default constructor
~LinkedList();               // Automatic memory cleanup
```

### Basic Operations
```cpp
// Insertion
void insert_end(int val);
void insert_front(int val);
void insert_sorted(int val);

// Deletion  
void delete_front();
void delete_back();
void delete_node_with_key(int val);

// Search & Access
int search(int val);
Node* get_nth(int n);
Node* get_nth_back(int n);
```

### Advanced Operations
```cpp
// List Manipulation
void reverse();
void rotate_left(int k);
void swap_pairs();
void swap_head_and_tail();

// Duplicate Removal
void remove_duplicates();              // O(n²) approach
void remove_duplicates2();             // O(n) with hash set
void remove_all_repeated();            // Remove all duplicated values
void remove_all_repeated_from_sorted(); // Optimized for sorted lists

// Specialized Operations
void move_key_occurence_back(int key);
void delete_even_positions();
void odd_pos_even_pos();
```

## Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Insert Front/End | O(1) | O(1) |
| Delete Front | O(1) | O(1) |
| Delete Back | O(n) | O(1) |
| Search | O(n) | O(1) |
| Remove Duplicates | O(n²) | O(1) |
| Remove Duplicates (Hash) | O(n) | O(n) |
| Reverse | O(n) | O(1) |
| Rotate Left | O(n) | O(1) |

## Usage Examples

### Basic Usage
```cpp
#include "Single_linked_list.h"

int main() {
    LinkedList list;
    
    // Insert elements
    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    
    // Display list
    list.print(); // Output: 1 2 3
    
    // Search for element
    int pos = list.search(2); // Returns position (1-indexed)
    
    return 0;
}
```

### Advanced Operations
```cpp
LinkedList list;
// Add: 1 1 2 2 3 3 4 5
for (int val : {1,1,2,2,3,3,4,5}) {
    list.insert_end(val);
}

// Remove all duplicated values (keeps only unique elements)
list.remove_all_repeated_from_sorted();
list.print(); // Output: 4 5

// Rotate list left by 2 positions  
list.rotate_left(2);

// Reverse the entire list
list.reverse();
```

## Compilation

### Single Command
```bash
g++ main.cpp Single_Linked_List.cpp -o linkedlist_demo
```

### Separate Compilation
```bash
g++ -c main.cpp
g++ -c Single_Linked_List.cpp  
g++ main.o Single_Linked_List.o -o linkedlist_demo
```

## Testing

The implementation includes comprehensive test cases covering:

- Basic operations (insert, delete, search)
- Edge cases (empty list, single element)
- Advanced algorithms (duplicate removal, rotation)
- Error conditions and boundary testing

Run tests:
```bash
./linkedlist_demo
```

## Memory Management

- **Automatic Cleanup**: Destructor handles all memory deallocation
- **No Memory Leaks**: Each `new` operation is paired with corresponding `delete`
- **Debug Tracking**: Optional debug mode tracks all node allocations

## Debug Features

### Integrity Verification
```cpp
list.debug_verify_data_integrity(); // Validates internal consistency
```

### Debug Output
```cpp
list.debug_print_list("Current State"); // Shows detailed node information
list.debug_print_address();             // Memory address tracking
```

## Design Decisions

### Architecture
- **Single Header/Implementation**: Clean separation of interface and implementation
- **Template-Free**: Uses `int` data type for simplicity and educational purposes
- **Const Correctness**: Proper use of const methods for read-only operations

### Performance Optimizations
- **Tail Pointer**: O(1) insertion at end
- **Early Termination**: Search operations stop when target found  
- **In-Place Algorithms**: Memory-efficient manipulation where possible

## Limitations

- **Data Type**: Currently supports only integer values
- **Thread Safety**: Not thread-safe (single-threaded use only)
- **Iterator Interface**: No STL-style iterator support

## Future Enhancements

- Generic template implementation for any data type
- Thread-safe operations with mutex protection
- STL-compatible iterator interface
- Circular linked list variant
- Doubly linked list implementation

## Contributing

1. Follow existing code style and naming conventions
2. Add comprehensive test cases for new features
3. Update documentation for any interface changes
4. Ensure all debug verification passes

## License

This implementation is provided for educational purposes. Feel free to use and modify according to your needs.

## Author

**Fathy Ahmed Fathy**  
Version 1.0 - September 2025

---

*This implementation serves as a comprehensive reference for understanding linked list operations and can be used for educational purposes, algorithm practice, or as a foundation for more complex data structures.*
