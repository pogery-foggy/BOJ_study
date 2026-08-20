#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cmath>
#include <cstring>
#define MAX_N 100001
#define MAX_B 400
using namespace std;
typedef long long ll;
// [l, r] 에서 합이 0인 가장 긴 부분배열
// <=> prefix 구간 [l-1, r] 안에서 같은 값의 최대 거리
int sqrtN;
int bucket_cnt[MAX_B];
int dist_cnt[MAX_N];

struct Query{
    int s, e;
    bool operator <(const Query &x) const {
        if (s/sqrtN != x.s/sqrtN)
            return s/sqrtN < x.s/sqrtN;
        return e < x.e;
    }
};

int N, Q;
vector<Query> query;
vector<int> v;
vector<deque<int>> pos;

void init(){
    cin >> N;
    sqrtN = sqrt(N + 1);

    query.clear();
    v.clear();
    v.resize(N+1);
    pos.clear();
    pos.resize(2*N + 1);

    memset(dist_cnt, 0, sizeof(dist_cnt));
    memset(bucket_cnt, 0, sizeof(bucket_cnt));

    int prefix = 0;
    v[0] = N; // -N,N을 0,2N으로 밀기

    for(int i = 1; i <= N; i++){
        int x;
        cin >> x;
        prefix += x;
        v[i] = prefix + N;
    }

    cin >> Q;
    query.reserve(Q);

    for(int i = 0; i < Q; i++){
        int s, e;
        cin >> s >> e;
        s--; // e는 하면 안됨 prefixsum만 1-index라서
        query.push_back({s, e});
    }

    sort(query.begin(), query.end());
}


int get_answer(){
    for(int b = N/sqrtN; b >= 0; b--){
        if(bucket_cnt[b] == 0) continue;

        int s = min(N, (b+1) * sqrtN - 1);
        int e = b * sqrtN;

        for(int i = s; i >= e; i--){
            if(dist_cnt[i] > 0) return i;
        }
    }
    return 0;
}

void erase_dist(int d){
    dist_cnt[d]--;
    if(dist_cnt[d] == 0)
        bucket_cnt[d / sqrtN]--;
}

void add_dist(int d){
    if(dist_cnt[d] == 0)
        bucket_cnt[d / sqrtN]++;
    dist_cnt[d]++;
}

int now(int x){
    if(pos[x].empty()) return 0;
    return pos[x].back() - pos[x].front();
}

void add_left(int idx){
    int x = v[idx];
    erase_dist(now(x));
    pos[x].push_front(idx);
    add_dist(now(x));
}

void add_right(int idx){
    int x = v[idx];
    erase_dist(now(x));
    pos[x].push_back(idx);
    add_dist(now(x));
}

void remove_left(int idx){
    int x = v[idx];
    erase_dist(now(x));
    pos[x].pop_front();
    add_dist(now(x));
}

void remove_right(int idx){
    int x = v[idx];
    erase_dist(now(x));
    pos[x].pop_back();
    add_dist(now(x));
}


void solve(){
    int s = 0, e = -1;
    ll ret = 0;

    for(int i = 0; i < Q; i++){
        int qs = query[i].s;
        int qe = query[i].e;

        while (e < qe) add_right(++e);
        while (e > qe) remove_right(e--);
        while (s < qs) remove_left(s++);
        while (s > qs) add_left(--s);

        ret += get_answer();
    }

    cout << ret << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        init();
        solve();
    }
    return 0;
}