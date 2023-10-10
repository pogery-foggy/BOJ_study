#include <deque>
#include <iostream>
using namespace std;

int D[5000000];
int A[5000000];
int N, L;
deque<pair<int, int>> maxi;

void init() {
    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    maxi.push_back(make_pair(A[0], 0));
    D[0] = A[0];
}

void solve() {
    for (int i = 1; i < N; i++) {
        if (!maxi.empty()) {
            if (maxi.front().second < i - L + 1)
                maxi.pop_front();
        }
        while (!maxi.empty() && A[i] < maxi.back().first)
            maxi.pop_back();
        maxi.push_back(make_pair(A[i], i));
        D[i] = maxi.front().first;
    }

    for(int i = 0 ; i < N; i ++){
        cout << D[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}