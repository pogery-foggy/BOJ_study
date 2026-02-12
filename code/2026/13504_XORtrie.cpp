#include <iostream>
#include <algorithm>
#define MAX_N 3501000
using namespace std;

struct Node {
	int child[2]; // XOR이니까 그냥 0 1로 하자
	int cnt;
	Node() : cnt(0) { child[0] = child[1] = -1; }
}; 

struct Trie {
	Node node[MAX_N];
	int root, idx;

    //Trie(){
	void reset() {
		idx = 1;
		root = 0;
		node[0] = Node();
	}

	int new_node() {
		int ret = idx++;
		node[ret] = Node();
		return ret;
	}

	void insert(int x) {
		int cur = root;
		node[cur].cnt++;
		for (int i = 31; i >= 0; i--) {
			int b = (x >> i) & 1;
			if (node[cur].child[b] == -1) node[cur].child[b] = new_node();
			cur = node[cur].child[b];
			node[cur].cnt++;
		}
	}

	int query(int x) {
		int cur = root;
		int ret = 0;
		for (int i = 31; i >= 0; i--) {
			int b = (x >> i) & 1;
			int want = b ^ 1;

			int next = node[cur].child[want];
			if (next != -1 && node[next].cnt > 0) {
				ret |= (1 << i);
				cur = next;
			} else {
				cur = node[cur].child[b];
			}
		}
		return ret;
	}
};

int N;
Trie tr;

void init() {
	cin >> N;
	tr.reset();
}

void solve() {
	int prev = 0;
	int ans = 0;

	tr.insert(0);

	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		prev ^= a;
		ans = max(ans, tr.query(prev));
		tr.insert(prev);
	}
	cout << ans << "\n";
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