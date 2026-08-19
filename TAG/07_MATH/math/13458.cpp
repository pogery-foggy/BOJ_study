#include <iostream>

using namespace std;
int N, A[1000000], B, C, answer[1000000];

void init() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    cin >> B >> C;
}

void solve() {
    for (int i = 0; i < N; i++) {
        if (A[i] - B <= 0) {
            answer[i] = 1;
        } else {
            A[i] -= B;
            answer[i]++;
            if (A[i] % C == 0)
                answer[i] += A[i] / C;
            else
                answer[i] += A[i] / C + 1;
        }
    }

    long long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += answer[i];
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}