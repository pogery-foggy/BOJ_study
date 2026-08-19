#include <iostream>
#include <vector>
using namespace std;

int cogwheel[4], K, turn[4], d[4];
vector<pair<int, int>> rotates;

void init() {
    for (int i = 0; i < 4; i++) {
        char a;
        cin >> a;
        cogwheel[i] = a - '0';
        for (int j = 0; j < 7; j++) {
            cin >> a;
            cogwheel[i] <<= 1;
            cogwheel[i] |= a - '0';
        }
    }
    for(int j = 0; j<4;j++){
    for(int i = 0 ;i < 8; i++){
        cout << (cogwheel[j] & (1<<i));
    }
    cout <<"\n";
    }
    cin >> K;
    rotates.resize(K);
    for (auto &a : rotates) {
        cin >> a.first >> a.second;
    }
}
// L == 1, R == 2;
void dfs(int cur, int direction, int LorR) {
    turn[cur] =true;
    int find_d= -1;
    if (cur == -1 || cur == 4)
        return;
    if (LorR == 0) {
        d[cur] = direction;
        dfs(cur - 1, direction, 1);
        dfs(cur + 1, direction, 2);
    } else if (LorR == 1) {
        int l = (cogwheel[cur] >> 6);
        int r = cogwheel[cur + 1] >> 2;
        find_d = (l^r) & 1;
        if (find_d) {
            d[cur] = -direction;
            dfs(cur - 1, -direction, 1);
        } else
            turn[cur] = false;
    } else if (LorR == 2) {
        int l = (cogwheel[cur - 1] >> 6);
        int r = cogwheel[cur] >> 2;
        find_d = (l^r) & 1;
        if (find_d) {
            d[cur] = -direction;
            dfs(cur + 1, -direction, 2);
        } else
            turn[cur] = false;
    }
    cout << "cur : " << find_d << "dir : " << direction << "\n";
}

void solve() {
    for (auto a : rotates) {
        for (int i = 0; i < 4; i++)
            turn[i] = false;
        int num = a.first;
        int dire = a.second;
        dfs(num - 1, dire, 0);
        for (int i = 0; i < 4; i++) {
            int change = 255;
            if (turn[i]) {
                if (d[i] == 1) {
                    change &= ((cogwheel[i] >> 1) | ((cogwheel[i] & 1) << 7));
                } else {
                    change &= ((cogwheel[i] << 1) | ((cogwheel[i] >> 7) & 1));
                }
                cogwheel[i] = change;
            }
        }
        cout << "--------------\n";
    }
    int answer = 0;
    for (int i = 0; i < 4; i++) {
        answer += ((cogwheel[i] >> 7) << i);
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