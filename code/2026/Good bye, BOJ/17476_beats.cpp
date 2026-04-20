#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 100001
#define INF 4000000000000000000LL
typedef long long ll;
using namespace std;
// 19랑 거의똑같음
struct Node{
    ll sum, mx, mn, lazy, same;
};

Node tree[MAX_N * 4];
ll arr[MAX_N];
int N, Q;

Node merge_node(Node l, Node r){
    Node ret;
    ret.sum = l.sum + r.sum;
    ret.mx = max(l.mx, r.mx);
    ret.mn = min(l.mn, r.mn);
    ret.lazy = 0;
    ret.same = INF;
    return ret;
}

ll floor_sqrt(ll x){
    ll ret = sqrtl((long double)x);
    while((ret + 1) * (ret + 1) <= x)
        ret++;
    while(ret * ret > x)
        ret--;
    return ret;
}

void apply_add(int s, int e, int node, ll x){
    tree[node].sum += (e - s + 1) * x;
    tree[node].mx += x;
    tree[node].mn += x;
    if(tree[node].same != INF)
        tree[node].same += x;
    else
        tree[node].lazy += x;
}

void apply_same(int s, int e, int node, ll x){
    tree[node].sum = (e - s + 1) * x;
    tree[node].mx = x;
    tree[node].mn = x;
    tree[node].lazy = 0;
    tree[node].same = x;
}

void push(int s, int e, int node){
    if(s == e)
        return;

    int mid = (s + e) >> 1;
    if(tree[node].same != INF){
        apply_same(s, mid, node << 1, tree[node].same);
        apply_same(mid + 1, e, node << 1 | 1, tree[node].same);
        tree[node].same = INF;
    }
    if(tree[node].lazy){
        apply_add(s, mid, node << 1, tree[node].lazy);
        apply_add(mid + 1, e, node << 1 | 1, tree[node].lazy);
        tree[node].lazy = 0;
    }
}

void init_tree(int s, int e, int node){
    if(s == e){
        tree[node] = {arr[s], arr[s], arr[s], 0, INF};
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_add(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l)
        return;
    if(l <= s && e <= r){
        apply_add(s, e, node, x);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_add(s, mid, node << 1, l, r, x);
    update_add(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_sqrt(int s, int e, int node, int l, int r){
    if(r < s || e < l || tree[node].mx <= 1)
        return;

    if(l <= s && e <= r){
        ll mn_sqrt = floor_sqrt(tree[node].mn);
        ll mx_sqrt = floor_sqrt(tree[node].mx);

        if(mn_sqrt == mx_sqrt){
            apply_same(s, e, node, mn_sqrt);
            return;
        }
        if(tree[node].mn + 1 == tree[node].mx){
            apply_add(s, e, node, mn_sqrt - tree[node].mn);
            return;
        }
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_sqrt(s, mid, node << 1, l, r);
    update_sqrt(mid + 1, e, node << 1 | 1, l, r);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

ll query_sum(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return 0;
    if(l <= s && e <= r)
        return tree[node].sum;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return query_sum(s, mid, node << 1, l, r) + query_sum(mid + 1, e, node << 1 | 1, l, r);
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
            update_add(0, N - 1, 1, l, r, x);
        }
        else if(type == 2){
            update_sqrt(0, N - 1, 1, l, r);
        }
        else{
            cout << query_sum(0, N - 1, 1, l, r) << "\n";
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