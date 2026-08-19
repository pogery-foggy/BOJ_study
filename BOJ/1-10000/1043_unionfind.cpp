#include <iostream>
#include <vector>

using namespace std;
int N, M, K, answer;
int p[51];
vector<int> known;
vector<int> party[51];
void init() {
    cin >> N >> M;

    cin >> K;
    known.resize(K);
    for (auto &a : known) {
        cin >> a;
    }

    for (int i = 0; i < M; i++) {
        int a;
        cin >> a;
        party[i].resize(a);
        for (auto &b : party[i]) {
            cin >> b;
        }
    }

    for (int i = 1; i <= N; i++) {
        p[i] = i;
    }

    answer = M;
}

int find_parent(int a) {
    if (a == p[a])
        return a;
    return p[a] = find_parent(p[a]);
}

void Union(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    p[b] = a;
}

bool p_check(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    return a == b;
}

void solve() {
    for (int i = 0; i < M; i++) {
        int u1 = party[i][0];
        for (int j = 1; j < party[i].size(); j++) {
            int u2 = party[i][j];
            Union(u1, u2);
        }
    }

    for (int i = 0; i < M; i++) {
        bool lie = true;
        for (int j = 0; j < party[i].size(); j++) {
            int u1 = party[i][j];
            for (int k = 0; k < K; k++) {
                int u2 = known[k];
                if (p_check(u1, u2)) {
                    lie = false;
                    goto lier;
                }
            }
        }
    lier:
        if (!lie)
            answer--;
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