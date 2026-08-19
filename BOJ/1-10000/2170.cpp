// 스위핑 정석 component를 분리한다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
pair<int, int> arr[2000000];
int N,answer,prv,cur;
void init() {
    // 선이 아닌 좌표를 기준으로 s와 e도 다르게 입력
    cin >> N;
    for(int i = 0; i < N*2; i+=2){  
        cin >> arr[i].first >> arr[i+1].first;
        arr[i].second = 1;
        arr[i+1].second = -1;
    }
    sort(arr, arr + N * 2);
}

void solve() {
    for(int i = 0; i < N * 2; i++){
        if(cur == 0) //탐색하고 있는 선의 시작점 설정
            prv = arr[i].first;
        cur += arr[i].second;  // 현재 탐색중인지 판단 마치 prefix_sum
        if(cur == 0) // cur+=-1 했을 때 0이면 탐색이 끝난 것이므로 더하기.
            answer += arr[i].first - prv;
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