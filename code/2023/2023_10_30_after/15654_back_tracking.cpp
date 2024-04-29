#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N, M, user_in;
bool is_visit[8];
vector<int> arr,answer;
void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        arr.push_back(user_in);
    }
    sort(arr.begin(),arr.end());
}

void bfs(int cnt){
    if(cnt == M){
        for(auto ans : answer){
            cout << ans << " ";
        }
        cout << "\n";
    }
    int last = -1;
    for(int i = 0; i < N; i++){
        if(!is_visit[i] && last != arr[i]){
            answer.push_back(arr[i]);
            last = arr[i];
            
            is_visit[i]=true;
            bfs(cnt+1);
            is_visit[i]=false;
            answer.pop_back();
        }
    }
}

void solve() {
    bfs(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}