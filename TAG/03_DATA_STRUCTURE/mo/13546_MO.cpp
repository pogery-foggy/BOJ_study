#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cmath>
#define MAX_N 100001
#define MAX_K 100001
#define MAX_B 400
using namespace std;
// 덱을 모노톤하게 유지하고 
int sqrtN;
int bucket_cnt[MAX_B];
int dist_cnt[MAX_N];
int answer[MAX_N];

struct Query{
    int idx, s, e;
    bool operator <(const Query &x) const {
        if (s/sqrtN != x.s/sqrtN)
            return s/sqrtN < x.s/sqrtN;
        return e < x.e;
    }
};

int N, K, Q;
vector<Query> query;
vector<int> v;
deque<int> pos[MAX_K];

void init(){
    cin >> N >> K;
    sqrtN = sqrt(N);

    v.resize(N);

    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    cin >> Q;
    for(int i = 0; i < Q; i++){
        int s, e;
        cin >> s >> e;
        s--, e--;
        query.push_back({i, s, e});
    }

    sort(query.begin(), query.end());
}

int get_answer(){
    for(int b = N / sqrtN; b >= 0; b--){
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
    if (dist_cnt[d] == 0)
        bucket_cnt[d / sqrtN]--;
}

void add_dist(int d){
    if (dist_cnt[d] == 0)
        bucket_cnt[d / sqrtN]++;
    dist_cnt[d]++;
}

int now(int x){
    if (pos[x].empty()) return 0;
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

    for(int i = 0; i < Q; i++){
        int qs = query[i].s;
        int qe = query[i].e;

        while(e < qe) add_right(++e);
        while(e > qe) remove_right(e--);
        while(s < qs) remove_left(s++);
        while(s > qs) add_left(--s);

        answer[query[i].idx] = get_answer();
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