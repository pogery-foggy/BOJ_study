#include <iostream>

using namespace std;
int N, M;
int arr[101];

void init() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        arr[i] = i;
    }
}

void swap(int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void solve() {
    for (int i = 0; i < M; i++) {
        int l, r;
        cin >> l >> r;
        swap(l, r);
    }

    for (int i = 1; i <= N; i++) {
        cout << arr[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}