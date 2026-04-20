#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#define MAX_N 1000000
#define INF -4000000000000000000LL
typedef long long ll;
using namespace std;

// 문제마다 MAX_N만 바꿔서 쓰면 됨.
// 기본 지원:
// 1) range add
// 2) range chmin
// 3) range chmax
// 4) range min / max / sum
// 5) floor_div, floor_sqrt 류는 update_func로 확장 가능
// https://github.com/infossm/infossm.github.io/blob/7571d3d0ac66f7dd60f35cc4e826d20995ca1875/_posts/2019-10-19-Segment-Tree-Beats.md


struct Node{
    ll sum;
    ll mx, sub_mx;
    int mx_cnt;
    ll mn, sub_mn;
    int mn_cnt;
    ll lazy;
};

Node tree[MAX_N * 4 + 5];
ll arr[MAX_N + 5];
int N, Q;

Node new_node(ll x){
    Node temp;
    temp.sum = x;
    temp.mx = x;
    temp.sub_mx = -INF;
    temp.mx_cnt = 1;
    temp.mn = x;
    temp.sub_mn = INF;
    temp.mn_cnt = 1;
    temp.lazy = 0;
    return temp;
}

Node merge_node(Node l, Node r){
    Node temp;
    temp.sum = l.sum + r.sum;
    temp.lazy = 0;

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
    else {
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
    else {
        temp.mn = r.mn;
        temp.sub_mn = min(l.mn, r.sub_mn);
        temp.mn_cnt = r.mn_cnt;
    }
    return temp;
}

void pull(int node){
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void init_tree(int s, int e, int node){
    if(s == e){
        tree[node] = new_node(arr[s]);
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    pull(node);
}

void apply_add(int s, int e, int node, ll dx){
    tree[node].sum += (e - s + 1) * dx;
    tree[node].mx += dx;
    if(tree[node].sub_mx != -INF)
        tree[node].sub_mx += dx;
    tree[node].mn += dx;
    if(tree[node].sub_mn != INF)
        tree[node].sub_mn += dx;
    tree[node].lazy += dx;
}

void apply_chmin(int node, ll x){
    if(tree[node].mx <= x)
        return;

    tree[node].sum -= (tree[node].mx - x) * tree[node].mx_cnt;

    if(tree[node].mn == tree[node].mx)
        tree[node].mn = x;
    else if(tree[node].sub_mn == tree[node].mx)
        tree[node].sub_mn = x;

    tree[node].mx = x;
}

void apply_chmax(int node, ll x){
    if(tree[node].mn >= x)
        return;

    tree[node].sum += (x - tree[node].mn) * tree[node].mn_cnt;

    if(tree[node].mx == tree[node].mn)
        tree[node].mx = x;
    else if(tree[node].sub_mx == tree[node].mn)
        tree[node].sub_mx = x;

    tree[node].mn = x;
}

void push(int s, int e, int node){
    if(s == e)
        return;

    int mid = (s + e) >> 1;
    if(tree[node].lazy){
        apply_add(s, mid, node << 1, tree[node].lazy);
        apply_add(mid + 1, e, node << 1 | 1, tree[node].lazy);
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
}

void update_add(int s, int e, int node, int l, int r, ll dx){
    if(r < s || e < l)
        return;
    if(l <= s && e <= r){
        apply_add(s, e, node, dx);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_add(s, mid, node << 1, l, r, dx);
    update_add(mid + 1, e, node << 1 | 1, l, r, dx);
    pull(node);
}

void update_chmin(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || tree[node].mx <= x)
        return;
    if(l <= s && e <= r && tree[node].sub_mx < x){
        apply_chmin(node, x);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_chmin(s, mid, node << 1, l, r, x);
    update_chmin(mid + 1, e, node << 1 | 1, l, r, x);
    pull(node);
}

void update_chmax(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || tree[node].mn >= x)
        return;
    if(l <= s && e <= r && x < tree[node].sub_mn){
        apply_chmax(node, x);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_chmax(s, mid, node << 1, l, r, x);
    update_chmax(mid + 1, e, node << 1 | 1, l, r, x);
    pull(node);
}

// delta(x)가 단조이고,
// delta(min) == delta(max)이면 그 구간 전체가 같은 값만큼 이동하는 경우에만 바로 처리 가능.
// floor(x / d) - x
// floor(sqrt(x)) - x
//
// auto get_delta = [&](ll x){ return floor_div(x, d) - x; };
// update_func(0, N - 1, 1, l, r, get_delta);
template <class F>
void update_func(int s, int e, int node, int l, int r, F &get_delta){
    if(r < s || e < l)
        return;

    if(l <= s && e <= r){
        ll left_delta = get_delta(tree[node].mn);
        ll right_delta = get_delta(tree[node].mx);

        if(!left_delta && !right_delta)
            return;
        if(left_delta == right_delta){
            apply_add(s, e, node, left_delta);
            return;
        }
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_func(s, mid, node << 1, l, r, get_delta);
    update_func(mid + 1, e, node << 1 | 1, l, r, get_delta);
    pull(node);
}

ll get_min(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return INF;
    if(l <= s && e <= r)
        return tree[node].mn;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return min(get_min(s, mid, node << 1, l, r), get_min(mid + 1, e, node << 1 | 1, l, r));
}

ll get_max(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return -INF;
    if(l <= s && e <= r)
        return tree[node].mx;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return max(get_max(s, mid, node << 1, l, r), get_max(mid + 1, e, node << 1 | 1, l, r));
}

ll get_sum(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return 0;
    if(l <= s && e <= r)
        return tree[node].sum;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return get_sum(s, mid, node << 1, l, r) + get_sum(mid + 1, e, node << 1 | 1, l, r);
}

ll floor_div(ll x, ll d){
    ll q = x / d;
    ll r = x % d;
    if(r < 0)
        q--;
    return q;
}

ll floor_sqrt(ll x){
    ll ret = sqrtl((long double)x);
    while ((__int128)(ret + 1) * (ret + 1) <= x)
        ret++;
    while ((__int128)ret * ret > x)
        ret--;
    return ret;
}

void init(){
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    init_tree(0, N - 1, 1);
}

void solve(){
    // range add      : update_add(0, N - 1, 1, l, r, x);
    // range chmin    : update_chmin(0, N - 1, 1, l, r, x);
    // range chmax    : update_chmax(0, N - 1, 1, l, r, x);
    // range min      : get_min(0, N - 1, 1, l, r);
    // range max      : get_max(0, N - 1, 1, l, r);
    // range sum      : get_sum(0, N - 1, 1, l, r);
    // floor_div/sqrt : update_func(0, N - 1, 1, l, r, get_delta);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}