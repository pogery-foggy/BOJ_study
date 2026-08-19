#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

pair<int,int> arr[200000];
int N;
void init() {
    cin >> N;
    for(int i = 0; i < N*2; i+=2){
        cin >> arr[i].first >> arr[i+1].first;
        arr[i].second = 1;
        arr[i+1].second = -1;
    }
    sort(arr, arr+N*2);
}

void solve() {
    int cur = 0, prev = 0, answer = 0;
    for(int i = 0; i < N*2; i++){
        if(cur == 0){
            prev = arr[i].first;
        }
        cur += arr[i].second;
        if(cur == 0){
            answer += arr[i].first - prev;
        }
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