#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#define MAX_N 30001
using namespace std;
// 그냥 구간을 정렳해두자
int sqrtN;
int answer[MAX_N];

struct Query{
    int idx, s, e;
    bool operator <(const Query &x) const {
        if (s/sqrtN != x.s/sqrtN)
            return s/sqrtN < x.s/sqrtN;
        return e < x.e;
    }
};

struct Fenwick{
    int tree[MAX_N];

    void update(int idx, int diff){
        while(idx < MAX_N){
            tree[idx] += diff;
            idx += idx & -idx;
        }
    }

    int sum(int idx){
        int ret = 0;
        while(idx > 0){
            ret += tree[idx];
            idx -= idx & -idx;
        }
        return ret;
    }

    int query(int k){
        int idx = 0;
        int bit = 1;

        while((bit << 1) < MAX_N)
            bit <<= 1;

        while(bit > 0){
            int next_idx = idx + bit;
            if(next_idx < MAX_N && tree[next_idx] < k){
                idx = next_idx;
                k -= tree[next_idx];
            }
            bit >>= 1;
        }
        return idx + 1;
    }
};

int N, Q;
vector<Query> query;
vector<int> v;
Fenwick num, gap;

void init(){
    cin >> N >> Q;
    sqrtN = sqrt(N);

    v.resize(N);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }

    for(int i = 0; i < Q; i++){
        int s, e;
        cin >> s >> e;
        s--, e--;
        query.push_back({i, s, e});
    }

    sort(query.begin(), query.end());
}

void add_gap(int x){
    gap.update(x, 1);
}

void remove_gap(int x){
    gap.update(x, -1);
}

int prev(int x){
    int cnt = num.sum(x-1);
    if(cnt == 0) return 0;
    return num.query(cnt);
}

int nxt(int x){
    int cnt = num.sum(x);
    if(cnt == num.sum(N)) return 0;
    return num.query(cnt+1);
}

void remove_pos(int idx){
    int x = v[idx];
    int l = prev(x);
    int r = nxt(x);

    if(l)
        remove_gap(x - l);
    if(r)
        remove_gap(r - x);
    if(l && r)
        add_gap(r - l); // r-l

    num.update(x, -1);
}

void add(int idx){
    int x = v[idx];
    int l = prev(x);
    int r = nxt(x);

    if(l && r)
        remove_gap(r - l);
    if(l)
        add_gap(x - l);
    if(r)
        add_gap(r - x);

    num.update(x,1);
}

void solve(){
    int s = 0, e = -1;

    for(int i = 0; i < Q; i++){
        int qs = query[i].s;
        int qe = query[i].e;

        while(e < qe) add(++e);
        while(e > qe) remove_pos(e--);
        while(s < qs) remove_pos(s++);
        while(s > qs) add(--s);

        answer[query[i].idx] = gap.query(1);
    }

    for(int i = 0; i < Q; i++){
        cout << answer[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}