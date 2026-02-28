// 리스트복사
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#define MAX_B 5500
#define MAX_N 10000000
using namespace std;

// N 200000 * 4 + log200000 * 100000 최소 990만
struct Node {
    int l, r; 
    int val;
};
struct Branch {
    int n; // 문자열 길이 
    int root;
};

Node tree[MAX_N];
int tree_cnt;
Branch branch[MAX_B];
int branch_cnt;
unordered_map<string, int> m; 

void init() {
    m.clear();
    m.reserve(MAX_B);
    tree_cnt = 0;
    branch_cnt = 0;
}

int new_node(int l, int r, int val) {
    int node = tree_cnt++;
    tree[node].l = l;
    tree[node].r = r;
    tree[node].val = val;
    return node;
}

int init_tree(int s, int e, int arr[]) {
    if (s == e) {
        return new_node(-1, -1, arr[s]);
    }
    int mid = (s + e) >> 1;
    int L = init_tree(s, mid, arr);
    int R = init_tree(mid + 1, e, arr);
    return new_node(L, R, 0);
}

void makeList(char mName[], int mLength, int mListValue[]) {
    string name(mName);

    int root = init_tree(0, mLength - 1, mListValue);

    int bid = branch_cnt++;
    m[name] = bid;
    branch[bid].n = mLength;
    branch[bid].root = root;
}

void copyList(char mDest[], char mSrc[], bool mCopy) {
    string dest(mDest), src(mSrc);

    if (!mCopy) { // 주소만 복사
        m[dest] = m[src];
    } else { // 전체복사인데 git 트리처럼
        int bid = branch_cnt++;
        m[dest] = bid;
        branch[bid].n = branch[m[src]].n;
        branch[bid].root = branch[m[src]].root;
    }
}

int update_tree(int s, int e, int node, int idx, int v) {
    int next = new_node(tree[node].l, tree[node].r, tree[node].val);

    if (s == e) {
        tree[next].val = v;
        return next;
    }

    int mid = (s + e) >> 1;
    if (idx <= mid)
        tree[next].l = update_tree(s, mid, tree[node].l, idx, v);
    else
        tree[next].r = update_tree(mid + 1, e, tree[node].r, idx, v);

    return next;
}

void updateElement(char mName[], int mIndex, int mValue) {
    string name(mName);
    int bid = m[name];

    branch[bid].root = update_tree(0, branch[bid].n - 1, branch[bid].root, mIndex, mValue);
}

int query_tree(int s, int e, int node, int idx) {
    if (s == e)
        return tree[node].val;

    int mid = (s + e) >> 1;
    if (idx <= mid)
        return query_tree(s, mid, tree[node].l, idx);
    else
        return query_tree(mid + 1, e, tree[node].r, idx);
}

int element(char mName[], int mIndex) {
    string name(mName);
    int bid = m[name];

    return query_tree(0, branch[bid].n - 1, branch[bid].root, mIndex);
}