#include <iostream>
#define MAX_N 100001
#define MAX_M 100001
#define MAX_NODE 2200000
using namespace std;
typedef long long ll;

struct Node{
    int l, r;
    ll val;
    Node(): l(-1), r(-1), val(0){}
};

// 100000(N) * 4 + log100000 (16.6) * 100000(Q) 
// 400000 + 1700000 = 2100000
// tree, node개수, root개수(쿼리수만큼)이 필요함
Node tree[MAX_NODE];
int node_cnt, root_cnt;
int N, M;
ll arr[MAX_N];
int root[MAX_M + 1];

int new_node(int l,int r,ll val){
    int node = node_cnt++;
    tree[node].l = l;
    tree[node].r = r;
    tree[node].val = val;
    return node;
}

int init_tree(int s,int e){
    if(s==e){
        return new_node(-1,-1,arr[s]);
    }
    int mid = (s+e) >> 1;
    int l = init_tree(s,mid);
    int r = init_tree(mid+1,e);
    return new_node(l,r,tree[l].val + tree[r].val);
}

void init() {
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    cin >> M;

    node_cnt = 0;
    root_cnt = 0;
    root[root_cnt++] = init_tree(0,N-1);
}

// 노드의 번호가 리턴된다고 보면됨. 그거로 모든게 이루어지니까
int update(int s, int e, int node, int idx, ll v){
    // 여기서 부터 노드 공간을 만들어줘야함. 일단 기존걸 복사
    int next = new_node(tree[node].l, tree[node].r, tree[node].val);

    if(s==e){
        tree[next].val = v;
        return next;
    }
    int mid = (s+e) >> 1;
    // next의 왼쪽 또는 오른쪽으로 파고들기 
    // node도 왼쪽이나 오른쪽으로 가면 됨.
    if(idx <= mid){
        tree[next].l = update(s,mid,tree[node].l, idx, v);
    }else{
        tree[next].r = update(mid+1,e,tree[node].r, idx, v);
    }
    int L = tree[next].l;
    int R = tree[next].r;
    tree[next].val = tree[L].val + tree[R].val;
    return next;
}

ll query(int s, int e, int l, int r, int node){
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return tree[node].val;
    int mid = (s+e) >> 1;
    long long L = query(s,mid,l,r,tree[node].l);
    long long R = query(mid+1,e,l,r,tree[node].r);
    return L+R;
}

void solve() {
    // root_cnt : 쿼리 idx번째
    while(M--){
        int type;
        cin >> type;
        if(type == 1){
            ll idx, v;
            cin >> idx >> v;
            root[root_cnt] = update(0, N-1, root[root_cnt-1], idx-1, v);
            root_cnt++;
        }else{
            ll k, i, j;
            cin >> k >> i >> j;
            ll answer = query(0,N-1,i-1,j-1,root[k]);
            cout << answer << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}