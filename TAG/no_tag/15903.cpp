#include <iostream>
#include <queue>
using namespace std;

priority_queue<long long, vector<long long>, greater<long long>> pq;
int N, M;
void init() {
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        pq.push(a);
    }
}

void solve() {
    for(int i = 0; i < M; i++){
        long long a, b;
        a = pq.top();
        pq.pop();
        b = pq.top();
        pq.pop();
        pq.push(a+b);
        pq.push(a+b);
    }
    long long answer = 0;
    while(!pq.empty()){
        answer += pq.top();
        pq.pop();
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