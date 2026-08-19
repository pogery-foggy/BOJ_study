#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

pair<int, int> arr[20000];
int N, L;

void init() {
    cin >> N >> L;
    for (int i = 0; i < N * 2; i += 2) {
        cin >> arr[i].first >> arr[i + 1].first;
        arr[i].second = 1;
        arr[i + 1].second = -1;
    }
    sort(arr, arr + N * 2);
}

void solve() {
    int cur = 0;
    int covered = 0;
    int s = 0, e = 0;
    int answer = 0;
    for (int i = 0; i < N * 2; i++) {
        if (cur == 0) {
            s = arr[i].first;
        }
        cur += arr[i].second;
        if (cur == 0) {
            e = arr[i].first;
            if(covered < s) covered = s;    // 널빤지가 s까지 안닿으면 다시 s로 계산하기
            if(covered < e)                 // 마찬가지로 널빤지가 이번 웅덩이를 다 덮지 못하면
            {
                int l = e - covered; // 웅덩이 길이
                int cnt = (l+L-1)/L; // 널빤지 개수
                answer += cnt;
                covered += cnt * L; // 덮힌위치 갱신
            }
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