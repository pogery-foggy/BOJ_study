#include <iostream>
#include <queue>
#include <vector>
#define MAX_N 2001
using namespace std;
typedef pair<long long, pair<long long, long long>> plll;
priority_queue<plll, vector<plll>, greater<plll>> pq, pq_past;
long long N, M, p[MAX_N], answer;

void init() {
    while (!pq.empty())
        pq.pop();
    while (!pq_past.empty())
        pq_past.pop();
    answer = 0;
    cin >> N >> M;
    for (long long i = 0; i < N; i++)
        p[i] = i;
    for (long long i = 1; i < N; i++) {
        long long u, c;
        cin >> u >> c;
        pq.push({c, {i, u}});
    }
}

long long find_root(long long x) {
    if (p[x] == x)
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(long long a, long long b) {
    a = find_root(a);
    b = find_root(b);
    p[a] = b;
}

long long mst() {
    long long cost = 0;
    long long cnt = 0;
    while (cnt < N - 1 && !pq.empty()) {
        long long c = pq.top().first;
        long long u = pq.top().second.first;
        long long v = pq.top().second.second;
        pq_past.push(pq.top());
        pq.pop();
        u = find_root(u);
        v = find_root(v);
        if (u == v)
            continue;
        cnt++;
        cost += c;
        union_root(u, v);
    }
    return cost;
}

void solve() {
    for (long long i = 0; i < M; i++) {
        while (!pq_past.empty()) {
            pq.push(pq_past.top());
            pq_past.pop();
        }
        for (long long i = 0; i < N; i++)
            p[i] = i;
        long long u, v, c;
        cin >> u >> v >> c;
        pq.push({c, {u, v}});
        answer ^= mst();
    }
    cout << answer << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}