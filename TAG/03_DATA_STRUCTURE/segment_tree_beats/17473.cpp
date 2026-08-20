#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 200001
#define INF -4000000000000000000LL
#define MASK (1LL << 20) - 1
typedef long long ll;
using namespace std;

struct Node{
    ll mx, aa, oo;
    ll lazy_a, lazy_o;
};

Node tree[MAX_N * 4];
ll arr[MAX_N];
int N, Q;
// and or
// mixed = aa ^ oo 구간에서 섞여 있는 비트
// or x는 x가 아무것도 못할때
// and는 0으로 내릴 비트가 mixed에 없을때만 lazy가능 


Node merge_node(Node l, Node r){
    Node ret;
    ret.mx = max(l.mx, r.mx);
    ret.aa = l.aa & r.aa;
    ret.oo = l.oo | r.oo;
    ret.lazy_a = MASK;
    ret.lazy_o = 0;
    return ret;
}

void apply(int node, ll a, ll o){
    tree[node].mx = (tree[node].mx & a) | o;
    tree[node].aa = (tree[node].aa & a) | o;
    tree[node].oo = (tree[node].oo & a) | o;

    tree[node].lazy_a &= a;
    tree[node].lazy_o = (tree[node].lazy_o & a) | o;
}

void push(int s, int e, int node){
    if(s == e)
        return;
    if(tree[node].lazy_a == MASK && !tree[node].lazy_o)
        return;

    apply(node << 1, tree[node].lazy_a, tree[node].lazy_o);
    apply(node << 1 | 1, tree[node].lazy_a, tree[node].lazy_o);

    tree[node].lazy_a = MASK;
    tree[node].lazy_o = 0;
}

void init_tree(int s, int e, int node){
    if(s == e){
        tree[node] = {arr[s], arr[s], arr[s], MASK, 0};
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_and(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || !(tree[node].oo & (MASK ^ x)))
        return;

    if(l <= s && e <= r && !((tree[node].oo ^ tree[node].aa) & (MASK ^ x))){
        apply(node, x, 0);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_and(s, mid, node << 1, l, r, x);
    update_and(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_or(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || !((MASK ^ tree[node].aa) & x))
        return;

    if(l <= s && e <= r && !((tree[node].oo ^ tree[node].aa) & x)){
        apply(node, MASK, x);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_or(s, mid, node << 1, l, r, x);
    update_or(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

ll query_max(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return INF;
    if(l <= s && e <= r)
        return tree[node].mx;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return max(query_max(s, mid, node << 1, l, r), query_max(mid + 1, e, node << 1 | 1, l, r));
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
        int type, l, r;
        cin >> type >> l >> r;
        l--;
        r--;

        if(type == 1){
            ll x;
            cin >> x;
            update_and(0, N - 1, 1, l, r, x);
        }
        else if(type == 2){
            ll x;
            cin >> x;
            update_or(0, N - 1, 1, l, r, x);
        }
        else{
            cout << query_max(0, N - 1, 1, l, r) << "\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}