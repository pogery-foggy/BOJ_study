#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_N 1000001

using namespace std;

long long arr[MAX_N];
int arr_index[MAX_N + 1], N, M;
long long tree[MAX_N * 4];

long long init_tree(int s, int e, int node) {
	if (s == e) {
		arr_index[s] = node;
		return tree[node] = arr[s];
	}
	int mid = (s + e) >> 1;
	long long l = init_tree(s, mid, node << 1);
	long long r = init_tree(mid + 1, e, node << 1 | 1);
	return tree[node] = l + r;
}

void update(int idx, long long change) {
	int fnd = arr_index[idx];
	tree[fnd] += change;
	while (fnd > 0) {
		fnd /= 2;
		tree[fnd] = tree[fnd << 1] + tree[fnd << 1 | 1];
	}
};

long long query(int s, int e, int l, int r, int node) {
	if (e < l || r < s)
		return 0;
	if (l <= s && e <= r) {
		return tree[node];
	}
	int mid = (s + e) >> 1;
	long long le = query(s, mid, l, r, node << 1);
	long long ri = query(mid + 1, e, l, r, node << 1 | 1);
	return le + ri;
}


void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		arr[i] = 0;
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
			long long answer = query(0, N - 1, l - 1, r - 1, 1);
			cout << answer << "\n";
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

