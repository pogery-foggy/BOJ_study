#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 1000000
#define INF -4000000000000000000LL
typedef long long ll;
using namespace std;

// 비츠에서 lazy는 부모랑 자식을 일치하는 정규화?동기화? 일반 lazy보다 더 딥하다.
// 자식의 최대/최소가 부모 범위를 벗어나지 못하게.
// 그냥 완전포함이었으면 바꾸기 + 더 들어가도 갱신되는 게 없는거 찾기

struct Node{
    ll sum, mx1, mx2;
    int mx_cnt;
};

Node tree[MAX_N * 4 + 5];
ll arr[MAX_N];
int N, Q;

Node merge_node(Node l, Node r){
    Node ret;
    ret.sum = l.sum + r.sum;

    if(l.mx1 == r.mx1){
        ret.mx1 = l.mx1;
        ret.mx2 = max(l.mx2, r.mx2);
        ret.mx_cnt = l.mx_cnt + r.mx_cnt;
    }
    else if(l.mx1 > r.mx1){
        ret.mx1 = l.mx1;
        ret.mx2 = max(l.mx2, r.mx1);
        ret.mx_cnt = l.mx_cnt;
    }
    else{
        ret.mx1 = r.mx1;
        ret.mx2 = max(l.mx1, r.mx2);
        ret.mx_cnt = r.mx_cnt;
    }
    return ret;
}

void init_tree(int s, int e, int node){
    if(s == e){
        tree[node] = {arr[s], arr[s], INF, 1};
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void apply_chmin(int node, ll x){
    if(tree[node].mx1 <= x)
        return;
    tree[node].sum -= (tree[node].mx1 - x) * tree[node].mx_cnt;
    tree[node].mx1 = x;
}

void push(int s, int e, int node){
    if(s == e)
        return;

    if(tree[node << 1].mx1 > tree[node].mx1)
        apply_chmin(node << 1, tree[node].mx1);
    if(tree[node << 1 | 1].mx1 > tree[node].mx1)
        apply_chmin(node << 1 | 1, tree[node].mx1);
}

void update_chmin(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || tree[node].mx1 <= x)
        return;

    if(l <= s && e <= r && tree[node].mx2 < x){
        apply_chmin(node, x);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_chmin(s, mid, node << 1, l, r, x);
    update_chmin(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

ll query_max(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return INF;
    if(l <= s && e <= r)
        return tree[node].mx1;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return max(query_max(s, mid, node << 1, l, r), query_max(mid + 1, e, node << 1 | 1, l, r));
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
            update_chmin(0, N - 1, 1, l, r, x);
        }
        else if(type == 2){
            cout << query_max(0, N - 1, 1, l, r) << "\n";
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