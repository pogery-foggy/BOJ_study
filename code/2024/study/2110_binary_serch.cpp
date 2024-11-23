#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,C;
vector<long long> arr;
long long answer = 0;
void init() {
    cin >> N >> C;
    arr.resize(N);
    for(auto &a : arr){
        cin >> a;
    }
    sort(arr.begin(),arr.end());
}

bool can_insert(int x) {
	int cnt = 1;
	int prev = arr[0];
	for (int i = 1; i < N; i++) {
		if (arr[i] - prev >= x) {
			cnt++;
			prev = arr[i];
		}
	}
	return cnt >= C;
}

void solve() {
    long long mini = 1, maxi = arr[N-1] - arr[0];
    
    while(mini<=maxi){
        long long mid = (mini + maxi) >> 1;
        if(can_insert(mid)){
            answer = max(mid,answer);
            mini = mid + 1;
        }
        else maxi = mid - 1;
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