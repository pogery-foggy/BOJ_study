#include <iostream>
#include <queue>
using namespace std;

priority_queue<pair<int,pair<int,int>>> pq;
int N, M, p[1001];
void init() {
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        int u, v, c;
        cin >> u >> v >> c;
        pq.push({-c,{u,v}});
    }
    for(int i = 1 ; i <= N; i++){
        p[i] = i;
    }
}

int find_parent(int x){
    if(p[x] == x) return x;
    return p[x] = find_parent(p[x]);
}

void union_find(int a, int b){
    a = find_parent(a);
    b = find_parent(b);
    if(a == b) return;
    p[a] = b;
}

void solve() {
    int cnt = 0;
    int total_cost = 0;
    while(cnt < N-1){
        int c = -pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        if(find_parent(u) == find_parent(v)) continue;
        total_cost+=c;
        union_find(u,v);
        cnt++;
    }
    cout << total_cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}