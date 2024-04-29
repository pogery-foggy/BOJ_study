#include <iostream>
#include <stack>
#include <string>
using namespace std;

string s;

int oper_compare(char oper) {
    if (oper == '*' || oper == '/')
        return 2;
    else if (oper == '+' || oper == '-')
        return 1;
    return -1;
}

void init() { cin >> s; }

bool is_alpha(char oper) { return oper >= 'A' && oper <= 'Z'; }

string infix_to_postfix(string infix) {
    string postfix;
    stack<char> oper_stack;
    for (int i = 0; i < infix.size(); i++) {
        if (is_alpha(infix[i])) {
            postfix.push_back(infix[i]);
        } else if (infix[i] == '(') {
            oper_stack.push(infix[i]);
        } else if (infix[i] == ')') {
            while (!oper_stack.empty() && oper_stack.top() != '(') {
                postfix.push_back(oper_stack.top());
                oper_stack.pop();
            }
            oper_stack.pop();
        } else if (infix[i] == '*' || infix[i] == '/' || infix[i] == '+' || infix[i] == '-') {
            while (!oper_stack.empty() && oper_compare(oper_stack.top()) >= oper_compare(infix[i])) {
                postfix.push_back(oper_stack.top());
                oper_stack.pop();
            }
            oper_stack.push(infix[i]);
        }
    }
    while (!oper_stack.empty()) {
        postfix.push_back(oper_stack.top());
        oper_stack.pop();
    }

    return postfix;
}

void solve() { cout << infix_to_postfix(s); }

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}