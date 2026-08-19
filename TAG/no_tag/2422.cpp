#include <iostream>

using namespace std;

int N, M, dont[201][201], cnt, choose[3];

void init() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        dont[a][b] = 1;
        dont[b][a] = 1;
    }
}

void solve(int idx, int stacks) {
    if (stacks == 3) {
        cnt++;
        return;
    }
    for (int i = idx + 1; i <= N; i++) {
        if (dont[idx][i])
            continue;
        if (stacks == 2 && dont[choose[0]][i])
            continue;
        choose[stacks] = i;
        solve(i, stacks + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve(0, 0); // 1부터, 쌓은개수
    cout << cnt;
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}