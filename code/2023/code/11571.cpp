#include <iostream>

using namespace std;
int a, b, cnt, s, e, user_in_a, user_in_b;
void init() {
    cin >> user_in_a >> user_in_b;
    a = user_in_a;
    b = user_in_b;
    cnt = 0;
}

void solve() {
    int is_visit[10250] = {
        0,
    };
    while (1) {
        a = (a % b * 10);
        if (is_visit[a]) {
            s = is_visit[a];
            e = cnt;
            break;
        }
        is_visit[a] = ++cnt;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        init();
        solve();
        a = user_in_a;
        b = user_in_b;
        cout << a / b << ".";
        int temp = a % b * 10;
        for (int i = 0; i < s - 1; i++) {
            cout << temp / b;
            temp = (temp % b * 10);
        }
        cout << "(";
        for (int j = s - 1; j < e; j++) {
            cout << temp / b;
            temp = temp % b * 10;
        }
        cout << ")\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}