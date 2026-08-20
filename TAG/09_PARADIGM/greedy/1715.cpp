#include <iostream>
#include <queue>
#include <vector>
using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;
int N;
vector<int> arr;
void init() {
    cin >> N;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        pq.push(a);
    }
}

void solve() {
    int cnt = 0;
    while(pq.size()>1){
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        cnt += a + b;
        pq.push(a+b);
    }
    cout << cnt;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}