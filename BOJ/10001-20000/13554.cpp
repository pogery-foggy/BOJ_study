#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#define MAX_N 100001
using namespace std;
typedef long long ll;
int sqrtN;
ll answer[MAX_N];

struct Query{
    int idx, s, e, k;
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

    int query(int l, int r){
        if(l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

int N, Q;
vector<Query> query;
int a[MAX_N], b[MAX_N];
int ca[MAX_N], cb[MAX_N];
Fenwick fa, fb;

void init(){
    cin >> N;
    sqrtN = sqrt(N);

    for(int i = 0; i < N; i++){
        cin >> a[i];
    }
    for(int i = 0; i < N; i++){
        cin >> b[i];
    }
    cin >> Q;
    for(int i = 0; i < Q; i++){
        int s, e,k;
        cin >> s >> e >> k;
        s--, e--;
        query.push_back({i, s, e, k});
    }

    sort(query.begin(), query.end());
}

void remove_pos(int idx){
    ca[a[idx]]--;
    cb[b[idx]]--;
    fa.update(a[idx], -1);
    fb.update(b[idx], -1);
}

void add(int idx){
    ca[a[idx]]++;
    cb[b[idx]]++;
    fa.update(a[idx], 1);
    fb.update(b[idx], 1);
}

ll cnt(int k){
    int sqrtK = sqrt(k);
    ll ret = 0;
    // i*b, a*i
    for(int i = 1; i <= sqrtK; i++){
        if(ca[i] == 0) continue;
        ret += 1LL *  ca[i] * fb.query(sqrtK + 1, k / i);
    }

    for(int i = 1; i <= sqrtK; i++){
        if(cb[i] == 0) continue;
        ret += 1LL * cb[i] * fa.query(1, k / i);
    }

    return ret;
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

        answer[query[i].idx] = cnt(query[i].k);
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