#include <algorithm>
#include <iostream>
#define MAX_N 10001
#define MAX_X 100002
#define MAX_Y 100000
#define MAX_NODE 250000
using namespace std;

// x좌표끼리 묶고 (r+1)-(l)에서의 b~t 더하면 됨

struct Point{
    int x, y;
    bool operator <(const Point &t) const{
        if(x != t.x)
            return x < t.x;
        return y < t.y;
    }
};

int N, M;
Point point[MAX_N];
int root[MAX_X];
int L[MAX_NODE];
int R[MAX_NODE];
int tree[MAX_NODE];
int node_cnt;

int update(int prev, int s, int e, int idx){
    int node = ++node_cnt;
    L[node] = L[prev];
    R[node] = R[prev];
    tree[node] = tree[prev] + 1;
    if(s == e)
        return node;
    int mid = (s + e) >> 1;
    if(idx <= mid)
        L[node] = update(L[prev], s, mid, idx);
    else
        R[node] = update(R[prev], mid + 1, e, idx);
    return node;
}

int query(int node, int s, int e, int l, int r){
    if(!node||r < s || e < l)
        return 0;
    if(l <= s && e <= r)
        return tree[node];
    int mid = (s + e) >> 1;
    return query(L[node], s, mid, l, r) + query(R[node], mid + 1, e, l, r);
}

void init(){
    node_cnt = 0;
    root[0] = 0;
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        cin >> point[i].x >> point[i].y;
    sort(point, point + N);
    
    int idx = 0;
    for(int x = 0; x <= MAX_Y; x++){
        root[x + 1] = root[x];
        while(idx < N && point[idx].x == x){ // x좌표끼리묶음
            root[x + 1] = update(root[x + 1], 0, MAX_Y, point[idx].y);
            idx++;
        }
    }
}

void solve(){
    int answer = 0;
    while(M--){
        int l, r, b, t;
        cin >> l >> r >> b >> t;
        answer += query(root[r + 1], 0, MAX_Y, b, t) - query(root[l], 0, MAX_Y, b, t);
    }
    cout << answer << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}