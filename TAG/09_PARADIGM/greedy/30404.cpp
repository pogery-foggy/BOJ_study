#include <iostream>

using namespace std;
int N, K;
int arr[100001];
void init() {
    cin >> N >> K;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
}

void solve() {
    int cnt = 0;
    for(int i = 0; i < N;){
        cnt++;
        int j = i+1;
        while(j<N && arr[j] <= arr[i]+K) j++;
        i = j;
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