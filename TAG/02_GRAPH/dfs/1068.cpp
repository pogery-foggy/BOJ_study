#include <iostream>
#include <vector>
using namespace std;
const int MAX_N = 51;
vector<int> edge[MAX_N], s;
bool no[MAX_N];
int N, _, cnt;
void init() {
    cin >> N;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        if(a == -1)
            s.push_back(i);
        else 
            edge[a].push_back(i);
    }


    int a;
    cin >> a;
    no[a] = true;
}

void dfs(int cur){
    if(edge[cur].size() == 0){
        cnt++;
        return;
    }
    for(auto nxt : edge[cur]){
        if(no[nxt]){
            if(edge[cur].size() == 1) cnt++;
            continue;
        }
        dfs(nxt);
    }
}

void solve() {
    for(auto a : s)
        if(!no[a])
            dfs(a);
        
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}