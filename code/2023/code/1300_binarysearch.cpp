#include <iostream>

using namespace std;

long long N, K;
long long answer;
long long s, e, mid;

void init() {
    cin >> N >> K;
    s = 1;
    e = N * N;
}

long long p(long long fnd) {
    long long sum = 0;
    for (int i = 1; i < N + 1; i++) {
        //6보다 작은건 6/1 + 6/2 + 6/3... +6/N;
        // 그래봤자 한줄에 N개를 넘을 순 없다.
        sum += min(N, fnd / i);
    }
    return sum;
}

void solve() {
    while (s <= e) {
        long long mid = (s + e) >> 1;

        // K개보다 작아야 일단 답이 성립하니까. while문을 벗어날 때까지 반복하면 특정하게 된다.
        if (p(mid) < K) {
            s = mid + 1;
        } else { // else가 나왔다는건 일단 성립할 조건을 갖췄다는 것.
            answer = mid;
            e = mid - 1;
        }
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}