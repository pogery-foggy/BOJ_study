#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_N 100001
#define INF 2147480000

using namespace std;
typedef pair<int, int> pii;

pii arr[MAX_N];
int arr_index[MAX_N + 1], N, M;
pii tree[MAX_N * 4];

pii init_tree(int s, int e, int node) {
	if (s == e) {
		arr_index[s] = node;
		return tree[node] = arr[s];
	}
	int mid = (s + e) >> 1;
	pii l = init_tree(s, mid, node << 1);
	pii r = init_tree(mid + 1, e, node << 1 | 1);
	return tree[node] = min(l, r);
}

void update(int idx, int change) {
	int fnd = arr_index[idx];
	tree[fnd] = { change, idx + 1 };
	while (fnd > 0) {
		fnd /= 2;
		tree[fnd] = min(tree[fnd << 1], tree[fnd << 1 | 1]);
	}
};

pii query(int s, int e, int l, int r, int node) {
	if (e < l || r < s)
		return make_pair(INF, INF);
	if (l <= s && e <= r) {
		return tree[node];
	}
	int mid = (s + e) >> 1;
	pii le = query(s, mid, l, r, node << 1);
	pii ri = query(mid + 1, e, l, r, node << 1 | 1);
	return min(le, ri);
}


void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		arr[i] = { a,i + 1 };
	}
	cin >> M;

	init_tree(0, N - 1, 1);
}

void solve() {
	for (int i = 0; i < M; i++) {
		int mode;
		cin >> mode;
		if (mode == 1) {
			int idx, cng;
			cin >> idx >> cng;
			update(idx - 1, cng);
		}
		else {
			int l, r;
			cin >> l >> r;
			pii answer = query(0, N - 1, l - 1, r - 1, 1);
			cout << answer.second << "\n";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	init();
	solve();
	return 0;
}

