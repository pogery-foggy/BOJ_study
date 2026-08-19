#include <iostream>
#include <algorithm>
#define MAX_N 100001
#define INF -2100000000LL
using namespace std;
typedef long long ll;
struct Node {
    ll lmx, rmx, mx, sum;   
};

Node set_node(int x){
    Node temp;
    temp.lmx = x;
    temp.rmx = x;
    temp.mx = x;
    temp.sum = x;
    return temp;
}

Node set_node(Node l, Node r){
    Node temp;
    temp.lmx = max(l.sum + r.lmx, l.lmx);
    temp.rmx = max(r.sum + l.rmx, r.rmx);
    temp.mx = max({l.mx, r.mx, l.rmx + r.lmx});
    temp.sum = l.sum + r.sum;
    return temp;
}

Node out_range(){
    Node temp;
    temp.lmx = INF;
    temp.rmx = INF;
    temp.mx = INF;
    temp.sum = 0;
    return temp;
}

int N,M, arr[MAX_N];
Node tree[MAX_N * 4];

Node init_tree(int s,int e, int node){
    if(s==e){
        return tree[node] = set_node(arr[s]);
    }
    int mid = (s + e) >> 1;
    Node l = init_tree(s, mid, node << 1);
    Node r = init_tree(mid + 1, e, node << 1 | 1);
    return tree[node] = set_node(l, r);
}

Node query(int s, int e, int l, int r, int node) {
    if (l > e || r < s) {
        return out_range();
    }
    if (l <= s && e <= r) {
        return tree[node];
    }
    int mid = (s + e) >> 1;
    Node le = query(s, mid, l, r, node << 1);
    Node ri = query(mid + 1, e, l, r, node << 1 | 1);
    return set_node(le, ri);
}

void init() {
    cin >> N;
    for(int i = 0; i< N; i++){
        cin >> arr[i];
    }
    init_tree(0,N-1,1);
    cin >> M;
}

void solve() {
    while(M--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;

        ll answer = INF;

        if(y1 < x2){ // 떨어져 있으면 l + sum + r
            Node A = query(0, N-1, x1, y1, 1);
            Node B = query(0, N-1, y1+1, x2-1, 1);
            Node C = query(0, N-1, x2, y2, 1);
            answer = A.rmx + B.sum + C.lmx;
        }
        else{ // 겹칠때
            // 왼쪽 + 오른쪽 짜투리
            // 겹친 부분
            // 왼쪽 짜투리 + 오른쪽
            Node L = query(0, N-1, x1, y1, 1);
            Node R = query(0, N-1, y1+1, y2, 1);
            answer = max(answer, L.rmx + R.lmx);

            Node M = query(0 ,N-1, x2, y1, 1);
            answer = max(answer, M.mx);

            L = query(0, N-1, x1, x2-1, 1);
            R = query(0, N-1, x2, y2, 1);
            answer = max(answer, L.rmx + R.lmx);
        }
        cout << answer << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}