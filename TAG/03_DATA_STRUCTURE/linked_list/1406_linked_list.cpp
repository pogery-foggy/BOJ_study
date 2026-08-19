#include <iostream>
#include <string>

using namespace std;

struct Node {
    char data;
    Node *next;
    Node *prev;
};

Node *head = new Node, *tail = new Node, *current;
int N;

void get_node(char user_in, Node *cur) {
    Node *p_new = new Node;
    p_new->data = user_in;

    p_new->next = cur->next;
    p_new->prev = cur;
    cur->next->prev = p_new;
    cur->next = p_new;
}

void del_node(Node *cur) {
    cur->next->prev = cur->prev;
    cur->prev->next = cur->next;
}

void init() {
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;
    string arr;
    cin >> arr;
    current = head;
    for (auto a : arr) {
        get_node(a, current);
        current = current->next;
    }
}

void print_list() {
    Node * target = head;
    target = head->next;
    while (1) {
        cout << target->data;
        if (target->next == tail)
            break;
        target = target->next;
    }
}

void solve() {
    cin >> N;
    char mode, addc;
    for (int i = 0; i < N; i++) {
        cin >> mode;
        if (mode == 'P') {
            cin >> addc;
            get_node(addc, current);
            current = current->next;
        } else if (mode == 'L') {
            if (current->prev != nullptr)
                current = current->prev;
        } else if (mode == 'D') {
            if (current->next != tail)
                current = current->next;
        } else if(mode == 'B'){
            if (current != head){
                del_node(current);
                current = current -> prev;
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    print_list();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}