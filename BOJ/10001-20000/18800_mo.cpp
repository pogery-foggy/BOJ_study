#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define MAX_N 100001
#define MAX_M 200001
using namespace std;
typedef long long ll;
// 누적합으로 생각했다면... 차분배열을 생각했어야 했다.
// d[i] = a[i]-a[i-1]라고 하면 d[s] +=x , d[s+K]-= x
// d l+1 ~ r == 0으로 만들기
// chain - chain에서 prefix_sum 값들의 최빈도

int sqrtN;
ll answer[MAX_N];

struct Query{
    int idx, s, e;
    bool operator <(const Query &x) const {
        if (s/sqrtN != x.s/sqrtN)
            return s/sqrtN < x.s/sqrtN;
        if ((s/sqrtN) & 1)
            return e > x.e;
        return e < x.e;
    }
};

int N, K, Q, M;
ll a[MAX_N];
vector<Query> query;
ll v[MAX_M];          // 변형한 prefix 배열
vector<int> modv;      // 각 위치의 mod K
vector<int> num;       // 압축값 번호
vector<int> len;
vector<int> mx;        // 최빈도
vector<vector<int>> cnt;
vector<vector<int>> freq_cnt;

ll total_mx = 0;

void init(){
    cin >> N >> K >> Q;
    M = N + K - 1;
    sqrtN = sqrt(M);
    //cout << 1;
    a[0] = 0;
    for(int i = 1; i <= N; i++){
        cin >> a[i];
    }

    modv.assign(M + 1, 0);
    num.assign(M + 1, 0);
    len.assign(K, 0);
    mx.assign(K, 0);

    for(int i = 1; i <= N; i++){
        ll diff = a[i] - a[i - 1];
        v[i + K - 1] = v[i - 1] + diff;
    }

    vector<vector<ll>> temp(K, vector<ll>());
    for(int i = 1; i <= M; i++){
        int idx = i - K + 1;
        int c = idx % K;
        if (c < 0) c += K;

        modv[i] = c;
        len[c]++;
        temp[c].push_back(v[i]);
    }
    //cout <<  1;
    cnt.resize(K);
    freq_cnt.resize(K);
    for(int c = 0; c < K; c++){
        sort(temp[c].begin(), temp[c].end());
        temp[c].erase(unique(temp[c].begin(), temp[c].end()), temp[c].end());
        cnt[c].assign(temp[c].size(), 0);
        freq_cnt[c].assign(len[c] + 1, 0);
    }
    //cout << 1;
    for(int i = 1; i <= M; i++){
        int c = modv[i];
        num[i] = lower_bound(temp[c].begin(), temp[c].end(), v[i]) - temp[c].begin();
    }
    //cout << 1;
    //query.clear();
    query.reserve(Q);
    //cout << 1;
    for(int i = 0; i < Q; i++){
        int l, r;
        cin >> l >> r;
        query.push_back({i, l, r + K - 1});
    }
    sort(query.begin(), query.end());
    //cout << 1;
    // ?????????? 왜 여기서 나가지
    total_mx = 0;
    //cout << 1;
}


void add(int idx){
    int c = modv[idx];
    int x = num[idx];

    total_mx -= mx[c];

    int old = cnt[c][x];
    if (old > 0)
        freq_cnt[c][old]--;
    cnt[c][x]++;
    freq_cnt[c][old + 1]++;

    if (mx[c] < old+1)
        mx[c] = old+1;

    total_mx += mx[c];
}

void remove_pos(int idx){
    int c = modv[idx];
    int x = num[idx];
    total_mx -= mx[c];

    int old = cnt[c][x];
    freq_cnt[c][old]--;
    cnt[c][x]--;

    if (old-1 > 0)
        freq_cnt[c][old - 1]++;

    if (mx[c] == old && freq_cnt[c][old] == 0)
        mx[c]--;

    total_mx += mx[c];
}

void solve(){
    int s = 1, e = 0;

    for(int i = 0; i < Q; i++){
        int qs = query[i].s;
        int qe = query[i].e;

        while(e < qe) add(++e);
        while(e > qe) remove_pos(e--);
        while(s < qs) remove_pos(s++);
        while(s > qs) add(--s);

        answer[query[i].idx] = 1LL * (qe - qs + 1) - total_mx;
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