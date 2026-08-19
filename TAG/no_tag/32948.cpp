#include <iostream>

using namespace std;
typedef long long ll;
ll arr[1502][1502];
ll topdown_ps[1502][1502], downtop_ps[1502][1502], square_ps[1503][1503];
int N, Q;
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> arr[i][j];
        }
    }
    // [i][j] = [i][j-1] + [i-1][j-1] - [i-1][j-2]
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            topdown_ps[i][j] = arr[i][j] + topdown_ps[i][j - 1] + topdown_ps[i - 1][j - 1] - topdown_ps[i - 1][j - 2];
        }
    }

    // downtop
    for (int i = N; i > 0; i--) {
        for (int j = i; j > 0; j--) {
            downtop_ps[i][j] = arr[i][j] + downtop_ps[i + 1][j] + downtop_ps[i + 1][j + 1] - downtop_ps[i + 2][j + 1];
        }
    }

    // square
    for (int i = N; i > 0; i--) {
        for (int j = 1; j <= i; j++) {
            square_ps[i][j] += arr[i][j] + square_ps[i][j - 1] + square_ps[i + 1][j] - square_ps[i + 1][j - 1];
        }
    }
}

void solve() {
    int Q;
    cin >> Q;
    while (Q--) {
        ll y, x, h;
        cin >> y >> x >> h;
        // y-x+1 이 start i
        ll total = downtop_ps[y - x + 1][1];
        // 꼭대기
        ll top = downtop_ps[y][x];
        // 오른쪽바닥
        ll down = topdown_ps[y + h - 1][x + h - 1];
        // 왼쪽 바닥의 왼쪽 아래
        ll left_down = square_ps[y + h][x - 1];
        //((y + h - 1) < N ? arr[y + h][x] : 0);
        cout << top + down + left_down - total << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}