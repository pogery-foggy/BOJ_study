#include <iostream>
#include <queue>

using namespace std;
long long N, M, answer, total;
int p[200001];
priority_queue<pair<long long, pair<long long, long long>>> pq;

void init() {
    cin >> N >> M;
	answer = 0;
	total = 0;
	while (!pq.empty()) pq.pop();
	for (int i = 0; i < N; i++)
		p[i] = i;
	for (int i = 0; i < M; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		total += c;
		pq.push({ -c,{u,v} });
	}
}

int find_parent(int x) {
	if (p[x] == x) return x;
	return p[x] = find_parent(p[x]);
}

void union_parent(int a, int b) {
	a = find_parent(a);
	b = find_parent(b);
	p[a] = b;
}

void solve() {
	int cnt = 0;
    bool flag = false;
	while (cnt < N - 1) {
        if(pq.empty()){
            flag = true;
            break;
        }
		int c = -pq.top().first;
		int u = pq.top().second.first;
		int v = pq.top().second.second;
		pq.pop();
		u = find_parent(u);
		v = find_parent(v);
		if (u == v) continue;
		cnt++;
		union_parent(u, v);
		total -= c;
	}
    if(!flag)
	cout << total << "\n";
    else cout << -1;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	init();
	solve();
	
	return 0;
}