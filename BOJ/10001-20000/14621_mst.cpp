#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 1001
using namespace std;
typedef pair<int,pair<int,int>> piii;
int N,M;
int p[MAX_N];
char sex[MAX_N];
priority_queue<piii, vector<piii>, greater<piii>> pq;

void init() {
    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        p[i] = i;
        cin >> sex[i];
    }
    for(int i = 0; i < M; i++){
        int u,v,d;
        cin >> u >> v >> d;
        if(sex[u] == sex[v]) continue;
        pq.push({d,{u,v}});
    }
}
int find_root(int x){
    if(p[x] == x) return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b){
    a = find_root(a);
    b = find_root(b);
    p[b] = a;
    /*
    a = find_root(a);
    p[a] = find_root(b);    // 경로압축하면서 묶기
    return p[a] != a;
    */
}

void solve() {
    int cost = 0; 
    int cnt = 0;
    while(cnt < N-1 && !pq.empty()){
        int c = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        u = find_root(u);
        v = find_root(v);
        if(u == v) continue;
        cost += c;
        cnt ++;
        union_root(u,v);
    }
    if(cnt < N-1) cout << -1;
    else cout << cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}