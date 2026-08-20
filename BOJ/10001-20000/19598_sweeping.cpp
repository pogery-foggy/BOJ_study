// 스위핑으로 푼것 나중에 스케줄링으로도 풀어보자
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
pair<long long, long long> arr[200000];
long long answer = 0;
void init() {
    cin >> N;
    for(int i = 0; i < 2*N; i+=2){
        int s,e;
        cin >> s >> e;
        arr[i] = {s,1};
        arr[i+1] = {e,-1};
    }
    sort(arr, arr+N*2);
}

void solve() {
    long long cur = 0;
    for(int i = 0;i < N*2; i++){
        cur += arr[i].second;
        answer = max(answer,cur);
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}