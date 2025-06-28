#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, K, D[1001], W;
vector<vector<int>> edge;
int indegree[1001], sum_time[1001];
queue<int> q;

void init() {
    cin >> N >> K;
    edge.resize(N+1);
    for(int i = 1; i <= N; i++){
        cin >> D[i];
        edge[i].clear();
        indegree[i] = 0;
        sum_time[i] = D[i];
    }
    for(int i = 0 ; i < K; i++){
        int x, y;
        cin >> x >> y;
        edge[x].push_back(y);
        indegree[y]++;
    }
    cin >> W;
    for(int i = 1; i <= N; i++){
        if(!indegree[i]) q.push(i);
    }
}

void solve() {
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(auto next : edge[cur]){
            if(sum_time[cur]+D[next] > sum_time[next])
                sum_time[next] = sum_time[cur] + D[next];
            indegree[next]--;
            if(!indegree[next]) q.push(next);
        }
    }
    cout << sum_time[W] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}