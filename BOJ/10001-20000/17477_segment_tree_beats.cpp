#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 500001
#define INF 4000000000000000000LL
typedef long long ll;
using namespace std;


// A구현정신나갔나
// B는 구간 전체 현재 max그룹 현재 min그룹 lazy를 따로둠
// add는 전부 바뀌니까 B 전체에 +1, chmin/chmax는 성공한 노드에서 +1

struct Node{
    ll mx, sub_mx;
    int mx_cnt;
    ll mn, sub_mn;
    int mn_cnt;
    ll add;
    ll sum;
    ll lazy, mx_lazy, mn_lazy;
};

Node tree[MAX_N * 4];
ll arr[MAX_N];
int N, Q;

Node new_node(ll x){
    Node temp;
    temp.mx = x;
    temp.sub_mx = -INF;
    temp.mx_cnt = 1;
    temp.mn = x;
    temp.sub_mn = INF;
    temp.mn_cnt = 1;
    temp.add = 0;
    temp.sum = 0;
    temp.lazy = 0;
    temp.mx_lazy = 0;
    temp.mn_lazy = 0;
    return temp;
}

Node merge_node(Node l, Node r){
    Node temp;
    temp.add = 0;
    temp.sum = l.sum + r.sum;
    temp.lazy = 0;
    temp.mx_lazy = 0;
    temp.mn_lazy = 0;

    if(l.mx == r.mx){
        temp.mx = l.mx;
        temp.sub_mx = max(l.sub_mx, r.sub_mx);
        temp.mx_cnt = l.mx_cnt + r.mx_cnt;
    }
    else if(l.mx > r.mx){
        temp.mx = l.mx;
        temp.sub_mx = max(l.sub_mx, r.mx);
        temp.mx_cnt = l.mx_cnt;
    }
    else{
        temp.mx = r.mx;
        temp.sub_mx = max(l.mx, r.sub_mx);
        temp.mx_cnt = r.mx_cnt;
    }

    if(l.mn == r.mn){
        temp.mn = l.mn;
        temp.sub_mn = min(l.sub_mn, r.sub_mn);
        temp.mn_cnt = l.mn_cnt + r.mn_cnt;
    }
    else if(l.mn < r.mn){
        temp.mn = l.mn;
        temp.sub_mn = min(l.sub_mn, r.mn);
        temp.mn_cnt = l.mn_cnt;
    }
    else{
        temp.mn = r.mn;
        temp.sub_mn = min(l.mn, r.sub_mn);
        temp.mn_cnt = r.mn_cnt;
    }
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

void apply_add(int node, ll dx){
    tree[node].mx += dx;
    if(tree[node].sub_mx != -INF)
        tree[node].sub_mx += dx;
    tree[node].mn += dx;
    if(tree[node].sub_mn != INF)
        tree[node].sub_mn += dx;
    tree[node].add += dx;
}

void apply_chmin(int node, ll x){
    if(tree[node].mx <= x)
        return;

    if(tree[node].mn == tree[node].mx)
        tree[node].mn = x;
    else if(tree[node].sub_mn == tree[node].mx)
        tree[node].sub_mn = x;

    tree[node].mx = x;
}

void apply_chmax(int node, ll x){
    if(tree[node].mn >= x)
        return;

    if(tree[node].mx == tree[node].mn)
        tree[node].mx = x;
    else if(tree[node].sub_mx == tree[node].mn)
        tree[node].sub_mx = x;

    tree[node].mn = x;
}

void apply_sum(int s, int e, int node, ll x){
    tree[node].sum += (e - s + 1) * x;
    tree[node].lazy += x;
}

void apply_mx(int node, ll x){
    tree[node].sum += tree[node].mx_cnt * x;
    tree[node].mx_lazy += x;
}

void apply_mn(int node, ll x){
    tree[node].sum += tree[node].mn_cnt * x;
    tree[node].mn_lazy += x;
}

void push(int s, int e, int node){
    if(s == e)
        return;

    int mid = (s + e) >> 1;

    if(tree[node].add){
        apply_add(node << 1, tree[node].add);
        apply_add(node << 1 | 1, tree[node].add);
        tree[node].add = 0;
    }

    if(tree[node].lazy){
        apply_sum(s, mid, node << 1, tree[node].lazy);
        apply_sum(mid + 1, e, node << 1 | 1, tree[node].lazy);
        tree[node].lazy = 0;
    }

    if(tree[node << 1].mx > tree[node].mx)
        apply_chmin(node << 1, tree[node].mx);
    if(tree[node << 1 | 1].mx > tree[node].mx)
        apply_chmin(node << 1 | 1, tree[node].mx);

    if(tree[node << 1].mn < tree[node].mn)
        apply_chmax(node << 1, tree[node].mn);
    if(tree[node << 1 | 1].mn < tree[node].mn)
        apply_chmax(node << 1 | 1, tree[node].mn);

    if(tree[node].mx_lazy){
        if(tree[node << 1].mx == tree[node].mx)
            apply_mx(node << 1, tree[node].mx_lazy);
        if(tree[node << 1 | 1].mx == tree[node].mx)
            apply_mx(node << 1 | 1, tree[node].mx_lazy);
        tree[node].mx_lazy = 0;
    }

    if(tree[node].mn_lazy){
        if(tree[node << 1].mn == tree[node].mn)
            apply_mn(node << 1, tree[node].mn_lazy);
        if(tree[node << 1 | 1].mn == tree[node].mn)
            apply_mn(node << 1 | 1, tree[node].mn_lazy);
        tree[node].mn_lazy = 0;
    }
}

void update_add(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || !x)
        return;
    if(l <= s && e <= r){
        apply_add(node, x);
        apply_sum(s, e, node, 1);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_add(s, mid, node << 1, l, r, x);
    update_add(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_chmax(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || tree[node].mn >= x)
        return;
    if(l <= s && e <= r && x < tree[node].sub_mn){
        apply_chmax(node, x);
        apply_mn(node, 1);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_chmax(s, mid, node << 1, l, r, x);
    update_chmax(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_chmin(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || tree[node].mx <= x)
        return;
    if(l <= s && e <= r && tree[node].sub_mx < x){
        apply_chmin(node, x);
        apply_mx(node, 1);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_chmin(s, mid, node << 1, l, r, x);
    update_chmin(mid + 1, e, node << 1 | 1, l, r, x);
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
        l--, r--;

        if(type == 1){
            ll x;
            cin >> x;
            update_add(0, N - 1, 1, l, r, x);
        }
        else if(type == 2){
            ll x;
            cin >> x;
            update_chmax(0, N - 1, 1, l, r, x);
        }
        else if(type == 3){
            ll x;
            cin >> x;
            update_chmin(0, N - 1, 1, l, r, x);
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