#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define MAX_N 1001

using namespace std;
typedef pair<int,pair<int,int>> piii;
priority_queue<piii, vector<piii>, greater<piii>> pq;
int N,M, p[MAX_N], Q;
int is_visit[MAX_N];
vector<vector<pair<int,int>>> edge;
long long total;

int find_root(int x){
    if(p[x] == x) return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b){
    a = find_root(a);
    b = find_root(b);
    p[b] = a;
}

long long mst(){
    long long cost = 0;
    int cnt = 0;
    while(cnt < N - 1 && !pq.empty()){
        int c = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        u = find_root(u);
        v = find_root(v);
        if(u == v) continue;
        edge[u].push_back({v,c});
        edge[v].push_back({u,c});
        union_root(u,v);
        cnt++;
        cost += c;
    }
    return cost;
}

void init() {
    cin >> N >> M;
    edge.resize(N+1);
    for(int i = 1; i <= N; i++) p[i] = i;
    for(int i = 0; i < M; i++){
        int u,v,c;
        cin >> u >> v >> c;
        pq.push({c,{u,v}});
    }
    cin >> Q;
    total = mst();
}

int bfs(int s,int e){
    queue<pair<int,int>> q; // cur_node, max_cost
    q.push({s,0});
    is_visit[s] = true;
    while(!q.empty()){
        int cur = q.front().first;
        int cost = q.front().second;
        q.pop();
        if(cur == e) return cost;
        for(auto a: edge[cur]){
            if(is_visit[a.first]) continue;
            is_visit[a.first] = true;
            q.push({a.first, max(cost,a.second)});
        }
    }
    return 0;
}

void solve() {
    for(int i = 0;i < Q; i++){
        int x, y;
        cin >> x >> y;
        for(int i = 1; i <= N; i++){
            is_visit[i] = false;
        }
        cout << total - bfs(x,y) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}