#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_N 200000
using namespace std;

vector<int> tree[MAX_N * 4];
int arr[MAX_N];
int A[MAX_N], B[MAX_N];
int N, M;

// 전체 명령을 관리하고, 
// query < min          변화없음
// min <= query < max   y
// max <= query         toggle
// y고정하는 마지막 위치 찾고, toggle몇번나왔는지

void init_tree(int s, int e, int node){
    if(s==e){
        tree[node].push_back(arr[s]);
        return;
    }
    int mid = (s+e) >> 1;
    init_tree(s,mid,node<<1);
    init_tree(mid+1,e,node<<1|1);
    auto &l =  tree[node<<1];
    auto &r = tree[node<<1|1];
    tree[node].resize(int(l.size()+r.size()));
    merge(l.begin(), l.end(), r.begin(), r.end(), tree[node].begin());
}

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> A[i] >> B[i];
    for (int i = 0; i < M; i++)
        cin >> arr[i];
    init_tree(0, M - 1, 1);
}

bool is_exist(int l, int r, int node) {
    auto &cur = tree[node];
    auto it = lower_bound(cur.begin(), cur.end(), l);
    return it != cur.end() && *it <= r;
}

int query_last(int s, int e, int l, int r, int node) {
    if (!is_exist(l, r, node))
        return -1;
    if (s == e)
        return s;

    int mid = (s + e) >> 1;
    // 마지막이라 오른쪽먼저
    int ret = query_last(mid + 1, e, l, r, node << 1 | 1);
    if (ret != -1)
        return ret;
    return query_last(s, mid, l, r, node << 1);
}

int query(int s,int e,int l,int r, int y, int node){
    if(r<s || e<l) return 0;
    if(l<=s && e<=r) {
        auto &cur = tree[node];
        return cur.end() - lower_bound(cur.begin(), cur.end(), y);
    }
    int mid = (s+e)>>1;
    return query(s,mid,l,r,y,node<<1) + query(mid+1,e,l,r,y,node<<1|1);
}

void solve() {
    long long answer = 0;
    for(int i = 0; i < N ; i++){
        int x = min(A[i], B[i]);
        int y = max(A[i], B[i]);
        if(x==y){
            answer += x;
            continue;
        }
        // 전체 명령중  min <= query < max가 마지막으로 등장한 곳
        int last = query_last(0 , M-1, x, y-1, 1);

        if (last == -1) {
            int cnt = query(0, M - 1, 0, M - 1, y, 1);
            if (cnt & 1) {
                if (A[i] == x)
                    answer += y;
                else
                    answer += x;
            } else {
                answer += A[i];
            }
        }
        else { // 있다면 last 이후
            int cnt = 0;
            if (last + 1 <= M - 1)
                cnt = query(0, M - 1, last + 1, M - 1, y, 1);

            if (cnt & 1)
                answer += x;
            else
                answer += y;
        }
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