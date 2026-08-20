#include <algorithm>
#include <iostream>
#define MAX_N 500001
#define INF 1000000007
using namespace std;

// r를 기준으로 추가하면서 x에 대해 r<=현재 e 인 커튼들 중 x를 덮는 커튼의 최대 l 유지
// 커튼l,r은 구간l,r에 대한 chmax(l)고, 쿼리는 구간 최솟값이 s 이상인지만 보면됨

struct Node{
    int mx, sub_mx;
    int mx_cnt;
    int mn, sub_mn;
    int mn_cnt;
};

struct Curtain{
    int l, r;
    bool operator <(const Curtain &x) const{
        return r < x.r;
    }
};

struct Query{
    int s, e, idx;
    bool operator <(const Query &x) const{
        return e < x.e;
    }
};

int N, M, Q;
Node tree[MAX_N * 4];
Curtain curtain[MAX_N];
Query query[MAX_N];
bool answer[MAX_N];

Node new_node(int x){
    Node temp;
    temp.mx = x;
    temp.sub_mx = -INF;
    temp.mx_cnt = 1;
    temp.mn = x;
    temp.sub_mn = INF;
    temp.mn_cnt = 1;
    return temp;
}

Node merge_node(Node l, Node r){
    Node temp;

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
        tree[node] = new_node(0);
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void apply_chmax(int node, int x){
    if(tree[node].mn >= x)
        return;

    if(tree[node].mx == tree[node].mn)
        tree[node].mx = x;
    else if(tree[node].sub_mx == tree[node].mn)
        tree[node].sub_mx = x;

    tree[node].mn = x;
}

void push(int s, int e, int node){
    if(s == e)
        return;

    if(tree[node << 1].mn < tree[node].mn)
        apply_chmax(node << 1, tree[node].mn);
    if(tree[node << 1 | 1].mn < tree[node].mn)
        apply_chmax(node << 1 | 1, tree[node].mn);
}

void update_chmax(int s, int e, int node, int l, int r, int x){
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
    cin >> N >> M >> Q;
    for (int i = 1; i <= M; i++)
        cin >> curtain[i].l >> curtain[i].r;
    for (int i = 1; i <= Q; i++){
        cin >> query[i].s >> query[i].e;
        query[i].idx = i;
    }

    sort(curtain + 1, curtain + M + 1);
    sort(query + 1, query + Q + 1);
    init_tree(1, N, 1);
}

void solve(){
    int idx = 1;

    for (int i = 1; i <= Q; i++){
        while (idx <= M && curtain[idx].r <= query[i].e){
            update_chmax(1, N, 1, curtain[idx].l, curtain[idx].r, curtain[idx].l);
            idx++;
        }
        answer[query[i].idx] = (get_min(1, N, 1, query[i].s, query[i].e) >= query[i].s);
    }

    for (int i = 1; i <= Q; i++){
        cout << (answer[i]?"YES":"NO") << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}