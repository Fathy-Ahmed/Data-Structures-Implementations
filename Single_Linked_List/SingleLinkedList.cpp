/**
 * @file LinkedList.cpp
 * @brief Implementation of the comprehensive LinkedList class
 * @author Fathy Ahmed Fathy
 * @date 9/16/2025 finshed
 * @version 1.0
 */

#include <iostream>
#include "SingleLinkedList.h"


#define el '\n'
#define ll long long
using namespace std;

// ===== Private Debug Helpers =====
void LinkedList::debug_add_node(Node* node)
{
    debug_data.push_back(node);
}

void LinkedList::debug_remove_node(Node* node)
{
    auto it = find(debug_data.begin(), debug_data.end(), node);
    if (it == debug_data.end())
        cout << "Node does not exist\n";
    else
        debug_data.erase(it);
}

// ===== Constructor / Destructor =====
LinkedList::LinkedList() {}
LinkedList::~LinkedList()
{
    while (head)
    {
        Node* cur = head->next;
        delete head;
        head = cur;
    }
    cout << "\nDestructor called\n"
        << el;
}

// ===== Debug functions =====
void LinkedList::debug_print_address()
{
    for (Node* cur = head; cur; cur = cur->next)
        cout << cur << "," << cur->data << "\t";
    cout << "\n";
}
void LinkedList::debug_print_node(Node* node, bool is_seperate)
{
    if (is_seperate)
        cout << "Sep: ";
    if (node == nullptr)
    {
        cout << "nullptr\n";
        return;
    }
    cout << node->data << " ";
    if (node->next == nullptr)
        cout << "X ";
    else
        cout << node->next->data << " ";

    if (node == head)
        cout << "head\n";
    else if (node == tail)
        cout << "tail\n";
    else
        cout << "\n";
}
void LinkedList::debug_print_list(string msg)
{
    if (msg != "")
        cout << msg << "\n";
    for (int i = 0; i < (int)debug_data.size(); ++i)
        debug_print_node(debug_data[i]);
    cout << "************\n"
        << flush;
}
string LinkedList::debug_to_string()
{
    if (length == 0)
        return "";
    ostringstream oss;
    for (Node* cur = head; cur != nullptr; cur = cur->next)
    {
        oss << cur->data;
        if (cur->next)
            oss << " ";
    }
    return oss.str();
}
void LinkedList::debug_verify_data_integrity()
{
    if (length == 0)
    {
        assert(head == nullptr);
        assert(tail == nullptr);
    }
    else
    {
        assert(head != nullptr);
        assert(tail != nullptr);

        if (length == 1)
            assert(head == tail);
        else
            assert(head != tail);

        assert(!tail->next);
    }

    int len = 0;
    for (Node* cur = head; cur != nullptr; cur = cur->next, len++)
        assert(len < 10000);

    assert(length == len);
    assert(length == (int)debug_data.size());
}

// ===== Operations =====
void LinkedList::delete_node(Node* node)
{
    debug_remove_node(node); // for debug
    --length;
    delete node;
}
void LinkedList::delete_next_node(Node* node)
{
    assert(node);

    Node* to_delete = node->next;

    bool is_tail = to_delete == tail;

    node->next = to_delete->next;

    delete_node(to_delete);

    if (is_tail)
        tail = node;
}
void LinkedList::embed_after(Node* node, int val)
{
    Node* item = new Node(val);
    ++length;
    debug_add_node(item);
    item->next = node->next;
    node->next = item;
}

void LinkedList::print()
{
    for (Node* cur = head; cur != nullptr; cur = cur->next)
        cout << cur->data << " ";
    cout << el;
}

void LinkedList::swap_head_and_tail()
{
    if (length <= 1)
        return;

    if (length == 2)
    {
        tail->next = head;
        head->next = nullptr;
        swap(head, tail);
    }
    else
    {
        auto prv = get_nth(length - 1);
        tail->next = head->next;

        prv->next = head;
        head->next = nullptr;

        swap(head, tail);

        debug_verify_data_integrity();
    }
}
void LinkedList::rotate_left(int k)
{ // O(n) time - O(1) memory
    if (length <= 1 || k % length == 0)
        return;

    k %= length;

    auto nth = get_nth(k);
    tail->next = head; // create cycle

    tail = nth;
    head = nth->next;

    tail->next = nullptr;
    debug_verify_data_integrity();
}
void LinkedList::remove_duplicates()
{ // O(n^2) time - O(1) memory
    if (length <= 1)
        return;

    for (Node* cur1 = head; cur1; cur1 = cur1->next)
    {
        for (Node* cur2 = cur1->next, *prv = cur1; cur2;)
        {
            if (cur1->data == cur2->data)
            {
                delete_next_node(prv);
                cur2 = prv->next;
            }
            else
                prv = cur2, cur2 = cur2->next;
        }
    }

    debug_verify_data_integrity();
}
void LinkedList::remove_duplicates2()
{ // O(n) time - O(n) memory
    if (length <= 1)
        return;

    unordered_set<int> seen;

    Node* cur = head;
    Node* prv = nullptr;

    while (cur)
    {
        if (seen.count(cur->data))
        {
            delete_next_node(prv);
            cur = prv->next;
        }
        else
        {
            seen.insert(cur->data);
            prv = cur;
            cur = cur->next;
        }
    }

    debug_verify_data_integrity();
}
void LinkedList::remove_last_occurence(int key)
{ // O(n) time - O(1) memory
    if (!length)
        return;

    Node* prv_deleted_node = nullptr;
    bool is_found = false;
    for (Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
    {
        if (cur->data == key)
        {
            prv_deleted_node = prv;
            is_found = true;
        }
    }

    if (is_found)
    {
        if (prv_deleted_node)
            delete_next_node(prv_deleted_node);
        else
            delete_front();
    }

    debug_verify_data_integrity();
}
int LinkedList::max(Node* head, bool is_first_call)
{ // O(n) time - O(n) memory
    if (is_first_call)
        return this->max(this->head, false);

    if (head == nullptr)
        return INT_MIN;

    return std::max(head->data, this->max(head->next, false));
}
Node* LinkedList::move_to_end(Node* cur, Node* prv)
{
    Node* next = cur->next;
    tail->next = cur;

    if (prv)
        prv->next = next;
    else
        head = next;

    tail = cur;
    tail->next = nullptr;

    return next;
}
void LinkedList::move_key_occurence_back(int key)
{ // O(n) time - O(1) memory
    if (length <= 1)
        return;

    int len = length;

    for (Node* cur = head, *prv = nullptr; len--;)
    {
        if (cur->data == key)
            cur = move_to_end(cur, prv);
        else
            prv = cur, cur = cur->next;
    }

    debug_verify_data_integrity();
}
void LinkedList::odd_pos_even_pos()
{
    if (length <= 2)
        return;

    Node* first_even = head->next;
    Node* cur_odd = head;

    while (cur_odd->next && cur_odd->next->next)
    {
        Node* next_even = cur_odd->next;

        cur_odd->next = cur_odd->next->next;
        next_even->next = next_even->next->next;

        cur_odd = cur_odd->next;
        if (length % 2 == 1)
            tail = next_even;
    }

    cur_odd->next = first_even;

    debug_verify_data_integrity();
}

void LinkedList::insert_after(Node* src, Node* target)
{
    assert(src && target);
    target->next = src->next;
    src->next = target;
    debug_add_node(target);
    ++length;
}
void LinkedList::insert_alternate(LinkedList& anthor)
{ // O(n) time - O(1) memory
    if (!anthor.length)
        return;

    if (!length)
    {
        head = anthor.head;
        tail = anthor.tail;
        length = anthor.length;
        debug_data = anthor.debug_data;
    }
    else
    {
        Node* cur2 = anthor.head;
        for (Node* cur1 = head; cur1 && cur2;)
        {
            Node* cur2_next_temp = cur2->next;
            insert_after(cur1, cur2);
            anthor.length--;
            cur2 = cur2_next_temp;

            if (cur1 == tail)
            {
                tail = anthor.tail;
                cur1->next->next = cur2;
                length += anthor.length;
                break;
            }

            cur1 = cur1->next->next;
        }
    }
}

void LinkedList::add_num(LinkedList& anthor)
{
    // let X = max(len, anthor.len)
    // let Y = max(len, anthor.len) - min(len, anthor.len)
    // O(X) time - O(Y) memory

    if (!anthor.length)
        return;

    Node* my_cur = head;
    Node* his_cur = anthor.head;
    int carry = 0, my_value, his_value;

    while (my_cur || his_cur)
    {
        my_value = his_value = 0;

        if (my_cur)
            my_value = my_cur->data;
        if (his_cur)
        {
            his_value = his_cur->data;
            his_cur = his_cur->next;
        }

        my_value += his_value + carry;
        carry = my_value / 10;
        my_value = my_value % 10;

        if (my_cur)
        {
            my_cur->data = my_value;
            my_cur = my_cur->next;
        }
        else
            insert_end(my_value);
    }

    if (carry)
        insert_end(carry);

    debug_verify_data_integrity();
}

/////////////my/////////////////////
void LinkedList::move_key_occurence_back2(int key)
{ // O(n) time - O(1) memory
    if (length <= 1)
        return;

    int c = 0;

    for (Node* cur = head, *prv = nullptr; cur;)
    {
        if (cur->data == key)
        {
            cur = cur->next;
            c++;

            if (!prv)
                delete_front();
            else
                delete_next_node(prv);
        }
        else
        {
            prv = cur, cur = cur->next;
        }
    }
    while (c--)
    {
        insert_end(key);
    }

    debug_verify_data_integrity();
}
void LinkedList::remove_all_repeated_of_k(int k)
{ // O(n) time - O(1) memory
    if (!length)
        return;

    for (Node* cur = head, *prv = nullptr; cur;)
    {
        if (cur->data == k)
        {
            if (prv)
            {
                delete_next_node(prv);
                cur = prv->next;
            }
            else
            {
                cur = cur->next;
                delete_front();
            }
        }
        else
        {
            prv = cur;
            cur = cur->next;
        }
    }

    debug_verify_data_integrity();
}

////////////////////////////////////////////////////////////
void LinkedList::add_node(Node* node)
{
    debug_add_node(node);
    ++length;
}
void LinkedList::insert_end(int val)
{
    Node* item = new Node(val);

    add_node(item); // for debug

    if (!head)
        head = tail = item;
    else
        tail->next = item, tail = item;
}
void LinkedList::insert_front(int val)
{ // time o(1) - memory o(1)
    Node* item = new Node(val);
    add_node(item);

    item->next = head;
    head = item;

    if (length == 1)
        tail = head;

    debug_verify_data_integrity();
}
void LinkedList::insert_sorted(int val)
{ // O(N) time - O(1) memory
    if (!length || val <= head->data)
        insert_front(val);
    else if (val >= tail->data)
        insert_end(val);
    else
    {
        for (Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
        {
            if (cur->data >= val)
            {
                embed_after(prv, val);
                break;
            }
        }
    }
    debug_verify_data_integrity();
}
void LinkedList::delete_front()
{ // time o(1) - memory o(1)
    Node* cur = head->next;
    delete_node(head);
    head = cur;

    debug_verify_data_integrity();
}
void LinkedList::delete_back()
{ // time o(n) - memory o(1)
    if (length <= 1)
    {
        delete_front();
        return;
    }

    Node* prev = get_nth(length - 1);
    delete_node(tail);
    tail = prev;
    tail->next = nullptr;

    debug_verify_data_integrity();
}
void LinkedList::delete_nth_node(int index)
{ // time o(n) - memory o(1)
    if (index < 0 || index > length)
        cout << "Error: index out of bounds\n";
    else if (index == 1)
        delete_front();
    else if (index == length)
        delete_back();
    else
    {
        Node* prev = get_nth(index - 1);
        Node* nth = prev->next;

        prev->next = nth->next;

        delete_node(nth);
        debug_verify_data_integrity();
    }
}
// Delete the first node with the given key value
void LinkedList::delete_node_with_key(int val)
{ // time o(n) - memory o(1)
    if (!length)
        cout << "Error: Empty List\n";
    else if (head->data == val)
        delete_front();
    else
    {
        for (Node* cur = head, *prev = nullptr; cur; prev = cur, cur = cur->next)
        {
            if (cur->data == val)
            {
                delete_next_node(prev); // connect prv with after
                return;
            }
        }

        cout << "Value not found!\n";
        debug_verify_data_integrity();
    }
}
void LinkedList::delete_even_positions()
{ // O(N) time - O(1) memory
    if (length <= 1)
        return;

    for (Node* cur = head->next, *prv = head; cur;)
    {
        delete_next_node(prv);

        if (!prv->next)
            break; // tail

        prv = prv->next;
        cur = prv->next;
    }

    debug_verify_data_integrity();
}
Node* LinkedList::get_nth(int n)
{
    // time o(n) - memory o(1)
    int i = 1;

    for (Node* cur = head; cur != nullptr && i <= n; cur = cur->next)
        if (i++ == n)
            return cur;

    return nullptr; // not found
}
Node* LinkedList::get_nth_back(int n)
{ // time o(n) - memory o(1)
    if (length < n)
        return nullptr;
    return get_nth(length - n + 1);
}
int LinkedList::search(int val)
{ // time o(n) - memory o(1)
    // One-index
    int i = 1;
    for (Node* cur = head; cur != nullptr; cur = cur->next, i++)
        if (cur->data == val)
            return i;

    return -1; // not found
}
int LinkedList::search_improved(int val)
{
    // // One-index and shift the element by one to left if found return the new position
    if (head->data == val)
        return 1;

    int i = 1;
    for (Node* cur = head; cur->next != nullptr; cur = cur->next, i++)
        if (cur->next->data == val)
        {
            swap(cur->next->data, cur->data);
            return i;
        }

    return -1;
}
bool LinkedList::is_same1(const LinkedList& another)
{ // time o(n) - memory o(1)
    // using length
    if (length != another.length)
        return false;

    Node* another_h = another.head;

    for (Node* cur_h = head; cur_h; cur_h = cur_h->next)
    {
        if (cur_h->data != another_h->data)
            return false;
        another_h = another_h->next;
    }

    return true;
}
bool LinkedList::is_same2(const LinkedList& another)
{ // time o(n) - memory o(1)
    // without using length
    Node* t1 = head;
    Node* t2 = another.head;

    while (t1 && t2)
    {
        if (t1->data != t2->data)
            return false;

        t1 = t1->next, t2 = t2->next;
    }

    return !t1 && !t2; // to check that both ends together
}
// swap each 2 consecutive values
void LinkedList::swap_pairs()
{ // time o(1) - memory o(1)
    for (Node* cur = head; cur; cur = cur->next)
    {
        if (cur->next)
        {
            swap(cur->data, cur->next->data);
            cur = cur->next;
        }
    }
}
void LinkedList::reverse()
{ // O(N) time - O(1) memory
    if (length <= 1)
        return;

    tail = head;
    Node* prv = head;
    head = head->next;

    while (head)
    {
        // store and reverse
        Node* next = head->next;
        head->next = prv;

        // move step
        prv = head;
        head = next;
    }

    head = prv;
    tail->next = nullptr;

    debug_verify_data_integrity();
}

////////////////////////////////////////////////////////////

// elements not sorted
void LinkedList::remove_all_repeated()
{
    if (length <= 1)
        return;

    unordered_map<int, int> seen;

    for (Node* cur = head; cur; cur = cur->next)
        seen[cur->data]++;

    for (Node* cur = head, *prv = nullptr; cur;)
    {
        if (seen[cur->data] > 1)
        {
            if (prv)
            {
                delete_next_node(prv);
                cur = prv->next;
            }
            else
            {
                cur = cur->next;
                delete_front();
            }
        }
        else
        {
            prv = cur;
            cur = cur->next;
        }
    }

    debug_verify_data_integrity();
}

// elements  sorted
Node* LinkedList::move_and_delete(Node* cur)
{
    auto temp = cur->next;
    delete_node(cur);
    return temp;
}
void LinkedList::remove_all_repeated_from_sorted()
{
    if (length <= 1)
        return;


    //tail = head; /////////////////

    Node* prv = nullptr;
    Node* cur = head; 

    while (cur)
    {
        bool removed = false;
        while (cur && cur->next && cur->data == cur->next->data)
        {
            int val = cur->data;
            removed = true;
            while (cur && cur->data == val)
                cur = move_and_delete(cur);
        }

        if (removed)
        {
            if (prv)
                prv->next = cur;
            else
				head = cur;

            if (!cur)
                tail = prv;
        }
        else
        {
            prv = cur;
            cur = cur->next;
            tail = prv;
        }
    }


    if (!head) // list became empty
        tail = head;

    debug_verify_data_integrity();
}

pair<Node*, pair<Node*, Node*>> LinkedList::reverse_subchain(Node* cur_head, int k)
{                              // O(N) time - O(1) memory
    Node* cur_tail = cur_head; // head is tail once reversed
    Node* prv = cur_head;
    cur_head = cur_head->next;
    for (int i = 1; i < k - 1 && cur_head; i++)
    {
        Node* next = cur_head->next;
        cur_head->next = prv;

        prv = cur_head;
        cur_head = next;
    }
    return make_pair(prv, make_pair(cur_tail, cur_head));
}
void LinkedList::reverse_chains(int k)
{
    if (length <= 1 || k <= 1)
        return;

    Node* last_tail = nullptr;
    Node* next_chain_head = head;
    head = nullptr;
    while (next_chain_head)
    {
        auto p = reverse_subchain(next_chain_head, k);
        Node* chain_head = p.first;
        Node* chain_tail = p.second.first;
        next_chain_head = p.second.second;
        tail = chain_tail;

        if (!head) // first chain
            head = chain_head;
        else
            last_tail->next = chain_head;
        last_tail = chain_tail;
    }
    tail->next = nullptr;
    debug_verify_data_integrity();
}
