#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 100001
#define INF 4000000000000000000LL
typedef long long ll;
using namespace std;

// floor_div(mn,d) == floor_div(mx,d)면 구간을 same으로 처리가능
// 아니면 mn+1==mx면 값이 두개뿐이고 이때 lazy 가능
// 둘 다 안되면 자식으로 내려가야함

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

ll floor_div(ll x, ll d){
    ll q = x / d;
    ll r = x % d;
    if(r < 0)
        q--;
    return q;
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

void update_div(int s, int e, int node, int l, int r, ll d){
    if(r < s || e < l)
        return;

    if(l <= s && e <= r){
        ll mn_div = floor_div(tree[node].mn, d);
        ll mx_div = floor_div(tree[node].mx, d);

        if(mn_div == mx_div){
            apply_same(s, e, node, mn_div);
            return;
        }
        if(tree[node].mn + 1 == tree[node].mx){
            apply_add(s, e, node, mn_div - tree[node].mn);
            return;
        }
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_div(s, mid, node << 1, l, r, d);
    update_div(mid + 1, e, node << 1 | 1, l, r, d);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

ll query_min(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return INF;
    if(l <= s && e <= r)
        return tree[node].mn;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return min(query_min(s, mid, node << 1, l, r), query_min(mid + 1, e, node << 1 | 1, l, r));
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
    cin >> N >> Q;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    init_tree(0, N - 1, 1);
}

void solve(){
    while (Q--){
        int type, l, r;
        cin >> type >> l >> r;

        if(type == 1){
            ll x;
            cin >> x;
            update_add(0, N - 1, 1, l, r, x);
        }
        else if(type == 2){
            ll d;
            cin >> d;
            update_div(0, N - 1, 1, l, r, d);
        }
        else if(type == 3){
            cout << query_min(0, N - 1, 1, l, r) << "\n";
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