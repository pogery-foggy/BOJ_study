#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 200001
#define INF 4000000000000000000LL
#define FULL (1LL << 51) - 1LL
typedef long long ll;
using namespace std;

// 실제로 중요한 건 각 집합지의 "존재하는 실력들의 집합"뿐이라서, 상태를 51비트 마스크 하나로 압축할 수 있다.
// 우수/저조한 집합지는 그 마스크의 사전식 최대/최소인데, 이건 그대로 정수 최대/최소와 같다.
// 따라서 1번은 range OR, 2번은 range AND, 3번은 point assign, 4번은 point swap 이고,
// 1/2번은 aa(구간 AND), oo(구간 OR)로 갱신하는 비트가 mixed가 아닐 때만 노드에서 끝내는 bitwise beats로 처리한다.
// 7번은 low mask L, high mask H만 알면 된다. L의 H에 없는 가장 높은 비트보다 위쪽에서 H에만 있는 비트들만 추가하면 최소 명수로 H 이상이 된다.

struct Node{
    ll mx, mn, aa, oo;
    ll lazy_a, lazy_o;
};

Node tree[MAX_N * 4];
ll arr[MAX_N];
int N, Q;

Node merge_node(Node l, Node r){
    Node ret;
    ret.mx = max(l.mx, r.mx);
    ret.mn = min(l.mn, r.mn);
    ret.aa = l.aa & r.aa;
    ret.oo = l.oo | r.oo;
    ret.lazy_a = FULL;
    ret.lazy_o = 0;
    return ret;
}

void apply(int node, ll a, ll o){
    tree[node].mx = (tree[node].mx & a) | o;
    tree[node].mn = (tree[node].mn & a) | o;
    tree[node].aa = (tree[node].aa & a) | o;
    tree[node].oo = (tree[node].oo & a) | o;

    tree[node].lazy_a &= a;
    tree[node].lazy_o = (tree[node].lazy_o & a) | o;
}

void push(int s, int e, int node){
    if(s == e)
        return;
    if(tree[node].lazy_a == FULL && !tree[node].lazy_o)
        return;

    apply(node << 1, tree[node].lazy_a, tree[node].lazy_o);
    apply(node << 1 | 1, tree[node].lazy_a, tree[node].lazy_o);

    tree[node].lazy_a = FULL;
    tree[node].lazy_o = 0;
}

void init_tree(int s, int e, int node){
    if(s == e){
        tree[node] = {arr[s], arr[s], arr[s], arr[s], FULL, 0};
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_or(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || !((FULL ^ tree[node].aa) & x))
        return;

    if(l <= s && e <= r && !((tree[node].oo ^ tree[node].aa) & x)){
        apply(node, FULL, x);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_or(s, mid, node << 1, l, r, x);
    update_or(mid + 1, e, node << 1 | 1, l, r, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

void update_and(int s, int e, int node, int l, int r, ll x){
    if(r < s || e < l || !(tree[node].oo & (FULL ^ x)))
        return;

    if(l <= s && e <= r && !((tree[node].oo ^ tree[node].aa) & (FULL ^ x))){
        apply(node, x, 0);
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    update_and(s, mid, node << 1, l, r, x);
    update_and(mid + 1, e, node << 1 | 1, l, r, x);
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

ll query_max(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return -1;
    if(l <= s && e <= r)
        return tree[node].mx;

    push(s, e, node);
    int mid = (s + e) >> 1;
    return max(query_max(s, mid, node << 1, l, r), query_max(mid + 1, e, node << 1 | 1, l, r));
}

ll get_val(int s, int e, int node, int idx){
    if(s == e)
        return tree[node].mx;

    push(s, e, node);
    int mid = (s + e) >> 1;
    if(idx <= mid)
        return get_val(s, mid, node << 1, idx);
    return get_val(mid + 1, e, node << 1 | 1, idx);
}

void set_val(int s, int e, int node, int idx, ll x){
    if(s == e){
        tree[node] = {x, x, x, x, FULL, 0};
        return;
    }

    push(s, e, node);
    int mid = (s + e) >> 1;
    if(idx <= mid)
        set_val(s, mid, node << 1, idx, x);
    else
        set_val(mid + 1, e, node << 1 | 1, idx, x);
    tree[node] = merge_node(tree[node << 1], tree[node << 1 | 1]);
}

ll get_add_mask(ll mn, ll mx){
    if(mn == mx)
        return 0;

    int top = -1;
    for (int i = 50; i >= 0; i--){
        if((mn & (1LL << i)) && !(mx & (1LL << i))){
            top = i;
            break;
        }
    }

    ll ret = 0;
    for (int i = top + 1; i <= 50; i++){
        if((mx & (1LL << i)) && !(mn & (1LL << i)))
            ret |= 1LL << i;
    }
    return ret;
}

void print_mask(ll x){
    if(!x){
        cout << "-1\n";
        return;
    }

    bool first = true;
    for (int i = 0; i <= 50; i++){
        if(x & (1LL << i)){
            if(!first)
                cout << ' ';
            cout << i;
            first = false;
        }
    }
    cout << '\n';
}

ll make_mask(int m){
    ll ret = 0;
    for (int i = 0; i < m; i++){
        int x;
        cin >> x;
        ret |= 1LL << x;
    }
    return ret;
}

void init(){
    cin >> N;
    for (int i = 0; i < N; i++){
        int m;
        cin >> m;
        arr[i] = make_mask(m);
    }
    init_tree(0, N - 1, 1);
    cin >> Q;
}

void solve(){
    while (Q--){
        int type;
        cin >> type;

        if(type == 1){
            int l, r, m;
            cin >> l >> r >> m;
            ll x = make_mask(m);
            update_or(0, N - 1, 1, l - 1, r - 1, x);
        }
        else if(type == 2){
            int l, r, m;
            cin >> l >> r >> m;
            ll x = make_mask(m);
            update_and(0, N - 1, 1, l - 1, r - 1, x);
        }
        else if(type == 3){
            int idx, m;
            cin >> idx >> m;
            ll x = make_mask(m);
            set_val(0, N - 1, 1, idx - 1, x);
        }
        else if(type == 4){
            int a, b;
            cin >> a >> b;
            a--, b--;
            if(a != b){
                ll x = get_val(0, N - 1, 1, a);
                ll y = get_val(0, N - 1, 1, b);
                set_val(0, N - 1, 1, a, y);
                set_val(0, N - 1, 1, b, x);
            }
        }
        else if(type == 5){
            int l, r;
            cin >> l >> r;
            ll x = query_min(0, N - 1, 1, l - 1, r - 1);
            print_mask(x);
        }
        else if(type == 6){
            int l, r;
            cin >> l >> r;
            ll x = query_max(0, N - 1, 1, l - 1, r - 1);
            print_mask(x);
        }
        else{
            int l, r;
            cin >> l >> r;
            ll mn = query_min(0, N - 1, 1, l - 1, r - 1);
            ll mx = query_max(0, N - 1, 1, l - 1, r - 1);
            ll x = get_add_mask(mn, mx);
            print_mask(x);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}