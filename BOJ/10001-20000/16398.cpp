#include <iostream>
#include <queue>
using namespace std;

priority_queue<pair<int, pair<int, int>>> pq;

int N, u, c, v, p[1001];
void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        p[i] = i;
    }
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++){
            cin >> c;
            if(i < j)
                pq.push({ -c,{i,j} });
        }
    }
}

int find_root(int x) {
    if (x == p[x]) return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    p[a] = b;
}

void solve() {
    int cnt = 0;
    int answer = 0;
    while (cnt < N - 1) {
        c = -pq.top().first;
        u = pq.top().second.first;
        v = pq.top().second.second;
        pq.pop();
        if (find_root(u) == find_root(v)) continue;
        answer += c;
        cnt++;
        union_root(u, v);
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