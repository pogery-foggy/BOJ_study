#include <iostream>
#define MAX_NODE 400005 // 초기 N + 삽입 횟수 + 5 정도로 잡기
using namespace std;
typedef long long ll;

struct Node {
    int l, r, p;
    int sz;
    ll val, sum;
    bool rev;
    Node() : l(0), r(0), p(0), sz(0), val(0), sum(0), rev(false) {}
};

struct Splay {
    Node node[MAX_NODE];
    ll seq[MAX_NODE];
    int stk[MAX_NODE];
    int root, ptr;

    Splay() : root(0), ptr(0) {}

    int new_node(ll val) {
        ++ptr;
        node[ptr] = Node();
        node[ptr].sz = 1;
        node[ptr].val = node[ptr].sum = val;
        return ptr;
    }

    int get_size(int x) { return x ? node[x].sz : 0; }
    ll get_sum(int x) { return x ? node[x].sum : 0; }

    void pull(int x) {
        if (!x)
            return;
        node[x].sz = get_size(node[x].l) + get_size(node[x].r) + 1;
        node[x].sum = get_sum(node[x].l) + get_sum(node[x].r) + node[x].val;
    }

    void apply_rev(int x) {
        if (!x)
            return;
        swap(node[x].l, node[x].r);
        node[x].rev = !node[x].rev;
    }

    void push(int x) {
        if (!x || !node[x].rev)
            return;
        apply_rev(node[x].l);
        apply_rev(node[x].r);
        node[x].rev = false;
    }

    void rotate(int x) {
        int p = node[x].p;
        int g = node[p].p;
        push(p);
        push(x);

        bool is_right = (x == node[p].r);
        int b = (is_right ? node[x].l : node[x].r);

        if (g) {
            if (node[g].l == p)
                node[g].l = x;
            else if (node[g].r == p)
                node[g].r = x;
        }
        node[x].p = g;

        if (is_right) {
            node[x].l = p;
            node[p].p = x;
            node[p].r = b;
            if (b)
                node[b].p = p;
        } else {
            node[x].r = p;
            node[p].p = x;
            node[p].l = b;
            if (b)
                node[b].p = p;
        }
        pull(p);
        pull(x);

        if (!node[x].p)
            root = x;
    }

    void push_all(int x) {
        int top = 0;
        while (x) {
            stk[top++] = x;
            x = node[x].p;
        }
        while (top)
            push(stk[--top]);
    }

    void splay(int x, int goal = 0) {
        push_all(x);
        while (node[x].p != goal) {
            int p = node[x].p;
            int g = node[p].p;
            if (g != goal) {
                if ((node[p].l == x) == (node[g].l == p))
                    rotate(p);
                else
                    rotate(x);
            }
            rotate(x);
        }
        if (goal == 0)
            root = x;
    }

    int build(int s, int e) {
        if (s > e)
            return 0;
        int mid = (s + e) >> 1;
        int x = new_node(seq[mid]);

        node[x].l = build(s, mid - 1);
        if (node[x].l)
            node[node[x].l].p = x;

        node[x].r = build(mid + 1, e);
        if (node[x].r)
            node[node[x].r].p = x;

        pull(x);
        return x;
    }

    // arr[1..n] 사용, 양 끝 더미는 자동으로 넣음
    void init(int n, ll arr[]) {
        ptr = 0;
        seq[0] = 0; // left dummy
        for (int i = 1; i <= n; i++)
            seq[i] = arr[i];
        seq[n + 1] = 0; // right dummy
        root = build(0, n + 1);
    }

    // 전체 inorder 에서 0-indexed k번째 노드(더미 포함)
    int kth(int k, int goal = 0) {
        int cur = root;
        while (1) {
            push(cur);
            int left_sz = get_size(node[cur].l);
            if (k < left_sz) {
                cur = node[cur].l;
            } else if (k == left_sz) {
                break;
            } else {
                k -= left_sz + 1;
                cur = node[cur].r;
            }
        }
        splay(cur, goal);
        return cur;
    }

    // 실제 수열 기준 [l, r] (1-indexed)
    int gather(int l, int r) {
        int x = kth(l - 1);
        int y = kth(r + 1, x);
        return node[y].l;
    }

    ll query_sum(int l, int r) {
        int x = gather(l, r);
        return node[x].sum;
    }

    void reverse_range(int l, int r) {
        int x = gather(l, r);
        apply_rev(x);
        pull(node[root].r);
        pull(root);
    }

    void set_value(int k, ll val) {
        int x = gather(k, k);
        node[x].val = val;
        pull(x);
        pull(node[root].r);
        pull(root);
    }

    // 앞에 pos개가 오도록 두고 그 뒤에 삽입. 새 원소 위치는 pos+1
    void insert_at(int pos, ll val) {
        int x = kth(pos);
        int y = kth(pos + 1, x);
        int z = new_node(val);
        node[y].l = z;
        node[z].p = y;
        pull(y);
        pull(x);
    }

    void erase_at(int pos) {
        gather(pos, pos);
        int y = node[root].r;
        node[y].l = 0;
        pull(y);
        pull(root);
    }

    int size() { return get_size(root) - 2; }
};

Splay sp;