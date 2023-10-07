#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int M, t, N, time;
string s;
vector<pair<int, string>> user_in;
queue<int> q[2]; // left, right
bool isleft, flag;
int answer[10001];

void init() {
    cin >> M >> t >> N;
    for (int i = 0; i < N; i++) {
        int a;
        string b;
        cin >> a >> b;
        user_in.push_back(make_pair(a, b));
        if (b == "left")
            q[0].push(i);
        else
            q[1].push(i);
    }
}

void solve() {
    while (1) {
        if (q[0].empty() && q[1].empty())
            break;
        flag = false;
        if (!q[isleft].empty()) {
            for (int i = M; i > 0; i--) {
                if (!q[isleft].empty() && user_in[q[isleft].front()].first <= time) {
                    answer[q[isleft].front()] = time + t;
                    q[isleft].pop();
                    flag = true;
                }
                else{
                    break;
                }
            }
            if (flag) {
                time += t;
                isleft = !isleft;
            } else {
                if (!q[!isleft].empty()) {
                    if (user_in[q[isleft].front()].first <= user_in[q[!isleft].front()].first) {
                        time += max(0, user_in[q[isleft].front()].first - time);
                    } else {
                        time += t + max(0, user_in[q[!isleft].front()].first - time);
                        isleft = !isleft;
                    }
                } else {
                    time += max(0, user_in[q[isleft].front()].first - time);
                }
            }
        } else if (!q[!isleft].empty()) {
            time += t + max(0, user_in[q[!isleft].front()].first - time);
            isleft = !isleft;
        }
    }

    for(int i = 0; i <N; i++){
        cout << answer[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}