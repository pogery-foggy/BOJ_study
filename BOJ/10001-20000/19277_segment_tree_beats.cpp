#include <algorithm>
#include <iostream>
#define MAX_N 200001
typedef long long ll;
using namespace std;

struct Node{
    ll mx, mn;
    ll lazy;
    ll st;
};

// mx / x == mn / x면 구간 전체가 같은 값 ,+ mn == mn + 1이면 똑같이 값이 둘 중 하나니까 add로 바꿀 수 있음
// 그게 아니면 자식으로 보내자

Node tree[MAX_N * 4];
ll arr[MAX_N];
int N, Q;

Node merge_node(Node l, Node r){
    Node temp;
    temp.mx = max(l.mx, r.mx);
    temp.mn = min(l.mn, r.mn);
    temp.lazy = 0;
    temp.st = -1;
    return temp;
}


void init_tree(int s, int e, int node){
    if(s == e){
        tree[node] = {arr[s], arr[s], 0, -1};
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void apply_set(int node, ll x){
    tree[node].mx = x;
    tree[node].mn = x;
    tree[node].lazy = 0;
    tree[node].st = x;
}

void apply_add(int node, ll dx){
    tree[node].mx += dx;
    tree[node].mn += dx;
    if(tree[node].st != -1)
        tree[node].st += dx;
    else
        tree[node].lazy += dx;
}

void push(int s, int e, int node){
    if(s == e)
        return;

    if(tree[node].st != -1){
        apply_set(node << 1, tree[node].st);
        apply_set(node << 1 | 1, tree[node].st);
        tree[node].st = -1;
    }
    if(tree[node].lazy){
        apply_add(node << 1, tree[node].lazy);
        apply_add(node << 1 | 1, tree[node].lazy);
        tree[node].lazy = 0;
    }
}

void update_add(int s, int e, int node, int l, int r, ll dx){
    if(r < s || e < l)
        return;
    if(l <= s && e <= r){
        apply_add(node, dx);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_add(s, mid, node << 1, l, r, dx);
    update_add(mid + 1, e, node << 1 | 1, l, r, dx);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_div(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || x == 1 || tree[node].mx == 0)
        return;

    if(l <= s && e <= r){
        ll mx2 = tree[node].mx / x;
        ll mn2 = tree[node].mn / x;

        if(mx2 == mn2){
            apply_set(node, mx2);
            return;
        }
        if(tree[node].mx == tree[node].mn + 1){
            apply_add(node, mn2 - tree[node].mn);
            return;
        }
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_div(s, mid, node << 1, l, r, x);
    update_div(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

ll get_max(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return -1;
    if(l <= s && e <= r)
        return tree[node].mx;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return max(get_max(s, mid, node << 1, l, r), get_max(mid + 1, e, node << 1 | 1, l, r));
}

void init(){
    cin >> N >> Q;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    init_tree(0, N - 1, 1);
}

void solve(){
    while (Q--){
        int t, l, r;
        ll x;
        cin >> t >> l >> r >> x;

        if(t == 0)
            update_add(0, N - 1, 1, l, r, x);
        else if(t == 1)
            update_div(0, N - 1, 1, l, r, x);
        else
            cout << get_max(0, N - 1, 1, l, r) << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}