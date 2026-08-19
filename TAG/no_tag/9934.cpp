#include <iostream>
#include <vector>
using namespace std;

int K;
vector<vector<int>> level;
struct Node {
    int data;
    Node *left;
    Node *right;
    Node() : data(0), left(nullptr), right(nullptr) {}
};
Node *root;

void init_tree(Node *cur, int depth) {
    if (depth == K) {
        cin >> cur->data; // 이해하기 쉽도록 아예 입력을 따로 뺄까
        return;
    }
    cur->left = new Node();
    cur->right = new Node();
    init_tree(cur->left, depth + 1);
    cin >> cur->data; // in-order 이것도 바깥으로 빼버릴까.
    init_tree(cur->right, depth + 1);
}

void init() {
    cin >> K;
    level.resize(K + 1);
    root = new Node();
    init_tree(root, 1);
    // dfs(root);
}
/* 혹시 모르니 만들어 놓자.
void dfs(Node *cur){
    if(cur->left){
        dfs(cur->left);
    }
    cin >> cur->data; // in-order라서.
    if(cur->right){
        dfs(cur->right);
    }
}*/

void fnd(Node *cur, int depth) {
    level[depth].push_back(cur->data);
    if (cur->left)
        fnd(cur->left, depth + 1);
    if (cur->right)
        fnd(cur->right, depth + 1);
}

void solve() {
    fnd(root, 1);
    for (int i = 1; i <= K; i++) {
        for (auto data : level[i]) {
            cout << data << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}