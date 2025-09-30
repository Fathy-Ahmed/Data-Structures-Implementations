#include "Stack04.h"
#include <cassert>
#include <iostream>

using std::cout;

Stack04::~Stack04()
{
    while (!is_empty()) pop();
}

bool Stack04::is_empty() const
{
    return !head;
}

void Stack04::push(int data)
{
    Node* tmp = new Node(data);
    tmp->next = head;
    head = tmp;
}

int Stack04::pop()
{
    assert(!is_empty());

    int ret = head->data;

    Node* del = head;
    head = head->next;

    delete del;

    return ret;
}

int Stack04::peek() const
{
    assert(!is_empty());

    int element = head->data;
    return element;
}

void Stack04::display() const
{
    for (Node* cur = head; cur; cur = cur->next)
        cout << cur->data << " | ";
    cout << '\n';
}


