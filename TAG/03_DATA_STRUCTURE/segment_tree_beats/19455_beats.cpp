#include <algorithm>
#include <iostream>
#define MAX_N 500001
#define FULL (1 << 30) - 1
#define INF 1 << 30
using namespace std;

// or는 켜려는 1비트 
// and는 끄려는 0비트가 노드에서 섞여있지 않을 때 lazy

struct Node{
    int mn, va, vo;
    int la, lo;
};

Node tree[MAX_N * 4];
int arr[MAX_N];
int N, Q;

Node new_node(int x){
    Node temp;
    temp.mn = x;
    temp.va = x;
    temp.vo = x;
    temp.la = FULL;
    temp.lo = 0;
    return temp;
}

Node merge_node(Node l, Node r){
    Node temp;
    temp.mn = min(l.mn, r.mn);
    temp.va = l.va & r.va;
    temp.vo = l.vo | r.vo;
    temp.la = FULL;
    temp.lo = 0;
    return temp;
}

void init_tree(int s, int e, int node){
    if(s == e){
        tree[node] = new_node(arr[s]);
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void apply(int node, int a, int o){
    tree[node].mn = (tree[node].mn & a) | o;
    tree[node].va = (tree[node].va & a) | o;
    tree[node].vo = (tree[node].vo & a) | o;
    tree[node].la &= a;
    tree[node].lo = (tree[node].lo & a) | o;
}

void push(int s, int e, int node){
    if(s == e)
        return;
    if(tree[node].la == FULL && !tree[node].lo)
        return;

    apply(node << 1, tree[node].la, tree[node].lo);
    apply(node << 1 | 1, tree[node].la, tree[node].lo);
    tree[node].la = FULL;
    tree[node].lo = 0;
}

void update_and(int s, int e, int node, int l, int r, int x){
    int cut = FULL ^ x;
    if(r < s || e < l || !(tree[node].vo & cut))
        return;
    if(l <= s && e <= r && !((tree[node].va ^ tree[node].vo) & cut)){
        apply(node, x, 0);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_and(s, mid, node << 1, l, r, x);
    update_and(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_or(int s, int e, int node, int l, int r, int x){
    if(r < s || e < l || (tree[node].va & x) == x)
        return;
    if(l <= s && e <= r && !((tree[node].va ^ tree[node].vo) & x)){
        apply(node, FULL, x);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_or(s, mid, node << 1, l, r, x);
    update_or(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

int get_min(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return INF;
    if(l <= s && e <= r)
        return tree[node].mn;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return min(get_min(s, mid, node << 1, l, r), get_min(mid + 1, e, node << 1 | 1, l, r));
}

void init(){
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    init_tree(0, N - 1, 1);
    cin >> Q;
}

void solve(){
    while (Q--){
        char op;
        int l, r;
        cin >> op >> l >> r;
        l--;
        r--;

        if(op == '&'){
            int x;
            cin >> x;
            update_and(0, N - 1, 1, l, r, x);
        }
        else if(op == '|'){
            int x;
            cin >> x;
            update_or(0, N - 1, 1, l, r, x);
        }
        else
            cout << get_min(0, N - 1, 1, l, r) << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}