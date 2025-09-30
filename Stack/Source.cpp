#include "Stack.h"
#include "Stack02.h"
#include "Stack03.h"
#include "Stack04.h"
#include <stack>
#include <vector>
#define el '\n'
using namespace std;
//typedef int type;

// Test Cases & Applications


string reverse_subwords(string line) {
	line += ' ';
	int n = line.size();
	Stack02 st(n);
	string ret = "";
	for (int i = 0; i < n; ++i) {
		if (line[i] != ' ') st.push(i);
		else {
			while (st.peek() != -1) {
				ret += line[st.peek()];
				st.pop();
			}
			ret += ' ';
		}
	}
	return ret;
}

int reverse_num(int num) {
	if (num == 0)
		return 0;
	
	Stack s(32);

	while (num)
		s.push(num % 10), num /= 10;

	int tens = 1;
	while (!s.is_empty())
		num = s.pop() * tens + num, tens *= 10;

	return num;
}

bool is_valid_parentheses(string s){
	int n = s.length();
	Stack02 st(n);
	for (int i = 0; i < n; ++i) {
		char ch = s[i];

		if (ch == '[' || ch == '{' || ch == '(') 
			st.push(i);

		else {
			if (st.is_empty()
				|| ch == ']' && s[st.peek()] != '['
				|| ch == '}' && s[st.peek()] != '{'
				|| ch == ')' && s[st.peek()] != '(')
				return false;

			st.pop();
		}
	}
	return st.is_empty();
}

string remove_all_adjacent_dublicates(string s) {
	int n = s.length();
	Stack st(n);
	for (int i = 0; i < n; ++i) {
		if (st.is_empty() || s[st.peek()] != s[i]) 
			st.push(i);
		else {
			st.pop();
		}
	}
	string ret = "";
	while (!st.is_empty()) 
		ret = s[st.pop()] + ret;

	return ret;
}

vector<int> asteroid_collision(vector<int>& asteroids) {
	vector<int> ret;
	int n = asteroids.size();
	Stack result(n);
	for (int asteroid : asteroids)
	{
		bool is_exploded = false;
		while (!result.is_empty() && asteroid < 0 && result.peek() > 0) {
			if (result.peek() < -asteroid) {
				result.pop();
				continue;
			}
			else if (result.peek() == -asteroid)
				result.pop();

			is_exploded = true;
			break;
		}
		if (!is_exploded)
			result.push(asteroid);
	}

	while (!result.is_empty()) ret.push_back(result.peek()), result.pop();

	reverse(ret.begin(), ret.end());
	return ret;
}

struct StackElement
{
	int n;
	int result{ -1 };

	StackElement(int n = 1, int result = -1) :
		n(n), result(result) {}

	bool is_computed() {
		return result >= 0;
	}
};
class ManualStack {
private:
	StackElement* arr;
	int arr_size{};
	int top{};
public:
	ManualStack(int arr_size) :arr_size(arr_size), top(-1) {
		arr = new StackElement(arr_size);
	}
	
	bool is_empty() const {
		return top == -1;
	}

	bool is_full() const {
		return top == arr_size - 1;
	}

	void push(StackElement item) {
		assert(!is_full());

		arr[++top] = item;
	}

	StackElement pop() {
		assert(!is_empty());
		return arr[top--];
	}

	StackElement peek() const {
		assert(!is_empty());
		return arr[top];
	}
};
int factorial(int n) {
	if (n <= 1)
		return n;
	int sub_result = n * factorial(n - 1);
	return n * sub_result;
}
int factorial_with_manual_stack(int n) {
	if (n <= 1)
		return n;
	ManualStack st(n);
	st.push(StackElement(n));
	StackElement cur(1);

	while (!st.is_empty()) {
		cur = st.peek();

		if (!cur.is_computed()) {
			if (cur.n <= 1) {
				cur.result = 1;
				st.pop();
				st.push(cur);
			}
			else
				st.push(StackElement(cur.n - 1));
		}
		else {
			cur = st.pop();
			if (!st.is_empty()) {
				StackElement parent = st.pop();
				parent.result = parent.n * cur.result; // n * factorial(n - 1);
				st.push(parent);
			}
		}
	}

	return cur.result;
}

int score_of_valid_parentheses(string s) {
	Stack st(s.size());

	st.push(0); // temp value to help us

	for (char& c : s){
		if (c == '(')
			st.push(0);
		else {
			int last = st.peek();
			st.pop();

			if (last == 0)
				last = 1;
			else
				last *= 2;

			int parent_par = st.peek() + last;
			st.pop();
			st.push(parent_par);
		}
	}
	return st.peek();
}

int score_of_valid_parentheses_V1(string s) {
	Stack st(s.size());

	st.push(0); // temp value to help us

	for (char& c : s){
		if (c == '(')
			st.push(0);
		else {
			int last = st.peek();
			st.pop();

			if (last == 0)
				last = 1;
			else
				last *= 2;

			int parent_par = st.peek() + last;
			st.pop();
			st.push(parent_par);
		}
	}
	return st.peek();
}
int score_of_valid_parentheses_V2(string s) {
	Stack st(s.size());

	int ind = 0;
	for (char& c : s)
	{
		if (c == '(') {
			st.push(ind);
			ind = 0;
		}
		else {
			ind = st.pop() + max(ind * 2, 1);
		}
	}
	return ind;
}

vector<int> next_greater_element(vector<int> nums) {
	int n = nums.size();
	Stack st(n);
	vector<int> ans(n);

	for (int i = n-1; i >= 0; i--)
	{
		if (st.is_empty()) 
			ans[i] = -1, st.push(nums[i]);
		else {
			while (!st.is_empty() && nums[i] >= st.peek()) st.pop();
			if (st.is_empty())
				ans[i] = -1;
			else
				ans[i] = st.peek();
			st.push(nums[i]);
		}
	}
	return ans;
}

int precedence(char s) {
	if (s == '+' || s == '-')
		return 1;
	if (s == '*' || s == '/')
		return 2;
	if (s == '^')
		return 3;
	return 0;
}
bool is_operator(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}
string infix_to_postfix(string infix) {
	Stack04<char> operators;
	string postfix;
	for (char& ch : infix) {
		if (isdigit(ch) || isalpha(ch)) postfix += ch;
		else {
			if (ch == '(') operators.push(ch);
			else if (ch == ')') {
				while (operators.peek() != '(') 
					postfix += operators.pop();
				operators.pop();
			}
			else if(is_operator(ch)) {
				while (is_operator(ch)
					&& !operators.is_empty()
					&& is_operator(operators.peek())
					&& precedence(ch) <= precedence(operators.peek()) 
					&& (precedence(ch) != 3 || precedence(operators.peek()) != 3))
				{
					postfix += operators.pop();
				}
				operators.push(ch);
			}
		}
	}

	while(!operators.is_empty()) 
		postfix += operators.pop();

	return postfix;
}
float operation(float a, float b, char operand) {
	if (operand == '+')
		return a + b;
	if (operand == '-')
		return a - b;
	if (operand == '*')
		return a * b;
	if (operand == '/')
		return a / b;
	if (operand == '^')
		return powf(a, b);
	return 0.0;
}
float postfix_evaluation(string postfix) {
	Stack04<float>st;
	for (char& ch : postfix) {
		if (isdigit(ch)) st.push(ch-'0');
		else {
			float num2 = st.pop();
			float num1 = st.pop();
			st.push(operation(num1, num2, ch));
		}
	}
	return st.peek();
}

char sign(char a, char b) {
	if (a == b)
		return '+';		// ++ or --
	return '-';			// +- or -+
}
string remove_brackets(string str) {
	Stack04<char> st;
	st.push('+');
	string res = "";

	for (int i = 0; i < (int)str.size(); i++)
	{
		char c = str[i];

		if (isdigit(c))
			res += c;
		else if (c == '+' || c == '-')
			res += sign(st.peek(), c);
		else if (c == '(' && i) {
			if (str[i - 1] != '(')
				st.push(sign(st.peek(), str[i - 1]));
			else
				st.push(st.peek());
		}
		else 
			st.pop();
	}

	return res;
}




void remove_brackets_tests() {
	string test;

	test = "1+2-3-4+5-6-7+8";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "9-(2+3)";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "9-(2-3)";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "9+(2-3)";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "1-(2-3-(4+5))-6-(7-8)";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "1-(2-3-(4+5)+6-7)";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "1-(2-3-(4+5-(6-7)))";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "1-((4+5)-(6-7)))";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "1-(((4-5)-(6-7))))";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "1-(2-3-((4+5)-(6-7)))";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "1-(2-3-((4-5)-(6-7)))";
	cout << test << " => " << remove_brackets(test) << "\n";

	test = "1-(2-3+((4-5)-(6-7)))";
	cout << test << " => " << remove_brackets(test) << "\n";

	/* Output
		1+2-3-4+5-6-7+8 => 1+2-3-4+5-6-7+8
		9-(2+3) => 9-2-3
		9-(2-3) => 9-2+3
		9+(2-3) => 9+2-3
		1-(2-3-(4+5))-6-(7-8) => 1-2+3+4+5-6-7+8
		1-(2-3-(4+5)+6-7) => 1-2+3+4+5-6+7
		1-(2-3-(4+5-(6-7))) => 1-2+3+4+5-6+7
		1-((4+5)-(6-7))) => 1-4-5+6-7
		1-(((4-5)-(6-7)))) => 1-4+5+6-7
		1-(2-3-((4+5)-(6-7))) => 1-2+3+4+5-6+7
		1-(2-3-((4-5)-(6-7))) => 1-2+3+4-5-6+7
		1-(2-3+((4-5)-(6-7))) => 1-2+3-4+5+6-7
	 */
}
void infix_to_postfix_tests() {
	cout << (infix_to_postfix("1+2*3") == "123*+" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("1+2*3-4") == "123*+4-" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("(1+2)*(6-4)") == "12+64-*" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("5-9/(3*4/2)") == "5934*2//-" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("((2+3)*4-(7-5))*(6+3)") == "23+4*75--63+*" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("2+3-((5+2)*3)") == "23+52+3*-" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("3+4^5*3") == "345^3*+" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("4^3^2") == "432^^" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("5+4^3^2-9") == "5432^^+9-" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("a+b*(c^d-e)^(f+G*h)-i") == "abcd^e-fGh*+^*+i-" ? "Passed" : "Not Passed") << el;
	cout << (infix_to_postfix("1+2^3^4*5-6") == "1234^^5*+6-" ? "Passed" : "Not Passed") << el;
}
void test_based_array_stack() {
	cout << "\n\n***\ttest based array stack\t***\n\n";

	Stack stk(3);
	stk.push(10);
	stk.push(20);
	stk.push(30);

	if (!stk.is_full())
		stk.push(50);
	else
		cout << "Full Stack\n";
	stk.display();	// 30 20 10
	cout << stk.peek() << "\n";	// 30

	while (!stk.is_empty()) {
		cout << stk.peek() << " ";
		stk.pop();
	} // 30 20 10
}

int main() {
	//cout << factorial_with_manual_stack(5); // 120

	/* score_of_valid_parentheses Tests
	cout << score_of_valid_parentheses_V1("()()()()((()(((()))((())(((((()))()()())))))))") << el;	// 968
	cout << score_of_valid_parentheses_V2("()()()()((()(((()))((())(((((()))()()())))))))") << el;	// 968
	*/

	//for(int &num : next_greater_element({10, 5, 7, 15, 11})) cout<<num<<' ';cout<<el;

	//infix_to_postfix_tests();
	
	/* Postfix Evaluation Tests
	cout << (postfix_evaluation("52/") == 2.5 ? "Passed" : "Not Passed") << el;
	cout << (postfix_evaluation("12+3+") == 6 ? "Passed" : "Not Passed") << el;
	cout << (postfix_evaluation("123*+") == 7 ? "Passed" : "Not Passed") << el;
	cout << (postfix_evaluation("23*4+") == 10 ? "Passed" : "Not Passed") << el;
	cout << (postfix_evaluation("135*+72/-") == 12.5 ? "Passed" : "Not Passed") << el;
	cout << (postfix_evaluation("432^^") == 262144 ? "Passed" : "Not Passed") << el;
	cout << (postfix_evaluation("21-2+") == 3 ? "Passed" : "Not Passed") << el; 
	*/

	//remove_brackets_tests();

	return 0;
}