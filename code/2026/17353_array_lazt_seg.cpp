#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#define MAX_N 100000
typedef long long ll;
using namespace std;

ll cnt_tree[MAX_N * 4], cut_tree[MAX_N * 4];
ll arr[MAX_N * 4];
int N;
// 차분 배열 트릭
/*
0 0 0 0 0이 있어.
그럼 여기서 3~5를 증가하려고 한다.
그러면 일단은 쿼리에 상관없이 1 2 3 4 5를 증가 시킨다. 근데 3~5만 증가니까 0 0 3 4 5가 된다..
근데 이게 1부터 센거다 보니까 두칸만큼의 거품이 생겼어. 그래서 minus_tree가 그 칸수(1-L)만큼 빼서 거품을 뺀다
// */
// int init_tree(int s,int e,int node){
//     if(s==e) return tree[node] = 0;
//     int mid = (s+e) >> 1;
//     return tree[node] = init_tree(s,mid, node<<1) + init_tree(mid+1, e, node<<1|1);
// }

void init() {
    cin >> N;
    // init_tree(0,N-1,1);
    for (int i = 0; i < N; i++)
        cin >> arr[i];
}

void push(ll lazy[], int node) {
    if (!lazy[node])
        return;
    lazy[node << 1] += lazy[node];
    lazy[node << 1 | 1] += lazy[node];
    lazy[node] = 0;
}

void update(ll lazy[], int s, int e, int node, int l, int r, int dx) {
    if (e < l || r < s)
        return;
    if (l <= s && e <= r) {
        lazy[node] += dx;
        return;
    }
    push(lazy, node);
    int mid = (s + e) >> 1;
    update(lazy, s, mid, node << 1, l, r, dx);
    update(lazy, mid + 1, e, node << 1 | 1, l, r, dx);
}

int sum(ll lazy[], int s, int e, int node, int l, int r) {
    if (e < l || r < s)
        return 0;
    if (l <= s && e <= r) {
        return lazy[node];
    }
    push(lazy, node);
    int mid = (s + e) >> 1;
    return sum(lazy, s, mid, node << 1, l, r) + sum(lazy, mid + 1, e, node << 1 | 1, l, r);
}

void solve() {
    int Q;
    cin >> Q;
    while (Q--) {
        int type;
        cin >> type;
        if (type == 1) {
            ll l, r;
            cin >> l >> r;
            l -= 1;
            r -= 1;
            update(cnt_tree, 0, N - 1, 1, l, r, 1);           // dx = 1
            update(cut_tree, 0, N - 1, 1, l, r, 1 - (l + 1)); // dx = 1 - L(왼쪽 칸의 수)
        } else {
            ll x;
            cin >> x;
            int cnt = sum(cnt_tree, 0, N - 1, 1, x - 1, x - 1);
            int cut = sum(cut_tree, 0, N - 1, 1, x - 1, x - 1);
            cout << arr[x - 1] + x * cnt + cut << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}