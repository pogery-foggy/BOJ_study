#include <iostream>
#include <vector>
#define MAX_N 10001
using namespace std;

int p[MAX_N], depth[MAX_N], N, a, b;
vector<vector<int>> childs;

void dfs(int cur){  // 깊이 구하기
    for(auto child : childs[cur]){
        depth[child] = depth[cur] + 1;
        dfs(child);
    }
}

void init() {
    cin >> N;
    childs.resize(N+1);
    for(int i = 1; i <=N; i++){
        p[i] = i;
        depth[i] = 0;
        childs[i].clear();
    }
    for(int i = 0; i < N-1; i++){
        int parent, child;
        cin >> parent >> child;
        childs[parent].push_back(child);
        p[child] = parent;
    }
    //root구하고 depth 구하기
    for(int i = 1; i <= N; i++){
        if(p[i] == i) dfs(i);
    }

}

void solve() {
    // 높이 맞추기
    int a, b;
    cin >> a >>b;
    if(depth[a] < depth[b]){    // 더 낮은 위치에 a넣기
        int temp = a;
        a = b;
        b = temp;
    }
    while(depth[a] != depth[b]){
        a = p[a];
    }
    while(a!=b){
        a = p[a];
        b = p[b];
    }
    cout << a << "\n";
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