#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// 배열기반 트라이, 공간 계산 잘해야함
struct Node {
    int l, r; // 0 1
    int cnt, terminate;
    Node() : l(-1), r(-1), cnt(0), terminate(-1) {}
};

// 배열 기반으로 하려면 큐에 노드를 넣어놓고 할당해줘야 함.
struct Trie {
    Node node[6006000];
    int root;
    queue<int> q; // node 할당하기 위한 queue
    int bits[30]; // 0에 가까울 수록 최상위 비트

    Trie() {
        for (int i = 0; i < 6006000; i++)
            q.push(i);
        root = new_node();
    }

    int new_node() {
        int ret = q.front();
        q.pop();
        return ret;
    }
    /*여기까지가 초기화랑 할당*/

    // 처음에 a개의 비트로 맞춰야 함(비트수가 달라지면 안됨)
    // 어차피 최상위 비트부터 봐야 하니까 거꾸로. 29~0 넣을때는 0~29
    // 없으면 new_node() 29면 terminate
    // 끝에 값을 저장해놓자.
    void insert(int x) {
        int cur = root, val = x;
        for (int i = 29; i >= 0; i--) {
            bits[i] = x & 1;
            x >>= 1;
        }
        for (int i = 0; i < 30; i++) {
            if (bits[i]) {
                if (node[cur].r == -1) {
                    node[cur].r = new_node();
                }
                cur = node[cur].r;
                node[cur].cnt++;
                if (i == 29)
                    node[cur].terminate = val;
            } else {
                if (node[cur].l == -1) {
                    node[cur].l = new_node();
                }
                cur = node[cur].l;
                node[cur].cnt++;
                if (i == 29)
                    node[cur].terminate = val;
            }
        }
    }
    void del(int x) {
        int cur = root;
        for (int i = 29; i >= 0; i--) {
            bits[i] = x & 1;
            x >>= 1;
        }
        for (int i = 0; i < 30; i++) {
            if (bits[i]) {
                int next = node[cur].r;
                if (--node[next].cnt == 0) {
                    node[cur].r = -1;
                    node[next].terminate = -1; // 어차피 -1이어도 반납할거라 초기화해야함
                    q.push(next);
                }
                cur = next;
            } else {
                int next = node[cur].l;
                if (--node[next].cnt == 0) {
                    node[cur].l = -1;
                    node[next].terminate = -1;
                    q.push(next);
                }
                cur = next;
            }
        }
    }
    int query(int x) {
        int cur = root, val = x;
        for (int i = 29; i >= 0; i--) {
            bits[i] = x & 1;
            x >>= 1;
        }
        for (int i = 0; i <= 30; i++) {
            int next;
            if (bits[i]) { // 1이면 0찾아야함
                if (node[cur].l != -1)
                    next = node[cur].l;
                else
                    next = node[cur].r;
            } else {
                if (node[cur].r != -1)
                    next = node[cur].r;
                else
                    next = node[cur].l;
            }
            cur = next;
            if (node[cur].terminate != -1) {
                return val ^ node[cur].terminate;
            }
        }
        return -1;
    }
};

Trie tr;
int M;

void init() { cin >> M; }

void solve() {
    tr.insert(0);
    while (M--) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            tr.insert(x);
        } else if (type == 2) {
            tr.del(x);
        } else {
            cout << tr.query(x) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}