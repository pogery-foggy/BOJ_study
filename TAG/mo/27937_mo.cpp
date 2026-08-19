#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define MAX_N 200005
#define MAX_B 1000
using namespace std;
typedef long long ll;
// 현재 구간 [l, r]의 답을
// 오른쪽으로 p를 붙일 때 + (F(p, p) - F(l-1, p))
// 왼쪽으로 p를 붙일 때 + (F(r, p) - F(p, p))
// 로 본다.
//
// 여기서
// F(x, p) = sum_{i = 1..x} |a[i] - a[p]|
//
// dry Mo로 이동을 전부 분해하면
// F(p, p) 들의 구간합 + 고정된 x에 대한 F(x, p) 구간합 형태만 남는다.
// F(x, p)는 x를 0 -> N으로 sweep 하면서 값축 sqrt 분할로 처리한다.

int sqrtN;
int sqrtA, block_cnt;
int N, Q;
int a[MAX_N];
ll answer[MAX_N];

struct Query{
    int idx, s, e;
    bool operator <(const Query &x) const {
        if (s / sqrtN != x.s / sqrtN)
            return s / sqrtN < x.s / sqrtN;
        if ((s / sqrtN) & 1)
            return e > x.e;
        return e < x.e;
    }
};

struct Event{
    int l, r, idx, sign;
};

vector<Query> query;
vector<vector<Event>> event;

ll val[MAX_N];
ll lazy_x[MAX_B], lazy_c[MAX_B];
int block_num[MAX_N], block_l[MAX_B], block_r[MAX_B];

ll self_cost[MAX_N];
ll prefix_self[MAX_N];
ll base_answer[MAX_N];
ll delta_answer[MAX_N];

void init_bucket(){
    sqrtA = sqrt(N);
    if(sqrtA == 0) sqrtA = 1;

    block_cnt = (N + sqrtA - 1) / sqrtA;

    for(int b = 0; b < block_cnt; b++){
        block_l[b] = b * sqrtA + 1;
        block_r[b] = min(N, (b + 1) * sqrtA);
        for(int i = block_l[b]; i <= block_r[b]; i++){
            block_num[i] = b;
        }
    }
}

void clear_bucket(){
    for(int i = 1; i <= N; i++){
        val[i] = 0;
    }
    for(int b = 0; b < block_cnt; b++){
        lazy_x[b] = 0;
        lazy_c[b] = 0;
    }
}

void update_range(int l, int r, ll dx, ll dc){
    if(l > r) return;

    int lb = block_num[l];
    int rb = block_num[r];

    if(lb == rb){
        for(int i = l; i <= r; i++){
            val[i] += dx * i + dc;
        }
        return;
    }

    for(int i = l; i <= block_r[lb]; i++){
        val[i] += dx * i + dc;
    }

    for(int b = lb + 1; b < rb; b++){
        lazy_x[b] += dx;
        lazy_c[b] += dc;
    }

    for(int i = block_l[rb]; i <= r; i++){
        val[i] += dx * i + dc;
    }
}

void add_value(int x){
    // |i - x| 가 아니라 |value - x|를 값축에서 더하는 것
    // [1, x]   에는 x - v = -v + x
    // [x+1, N] 에는 v - x = +v - x
    update_range(1, x, -1, x);
    update_range(x + 1, N, 1, -x);
}

ll get_value(int x){
    int b = block_num[x];
    return val[x] + lazy_x[b] * x + lazy_c[b];
}

void build_self_cost(){
    clear_bucket();
    prefix_self[0] = 0;

    for(int i = 1; i <= N; i++){
        add_value(a[i]);
        self_cost[i] = get_value(a[i]); // F(i, i)
        prefix_self[i] = prefix_self[i - 1] + self_cost[i];
    }
}

void build_event(){
    event.assign(N + 1, vector<Event>());

    int s = 1, e = 0;
    ll cur_base = 0;

    for(int i = 0; i < Q; i++){
        int qs = query[i].s;
        int qe = query[i].e;

        // while(e < qe) add(++e);
        if(e < qe){
            cur_base += prefix_self[qe] - prefix_self[e];
            event[s - 1].push_back({e + 1, qe, i, -1});
            e = qe;
        }

        // while(e > qe) remove_pos(e--);
        if(qe < e){
            cur_base -= prefix_self[e] - prefix_self[qe];
            event[s - 1].push_back({qe + 1, e, i, 1});
            e = qe;
        }

        // while(s < qs) remove_pos(s++);
        if(s < qs){
            cur_base += prefix_self[qs - 1] - prefix_self[s - 1];
            event[e].push_back({s, qs - 1, i, -1});
            s = qs;
        }

        // while(s > qs) add(--s);
        if(qs < s){
            cur_base -= prefix_self[s - 1] - prefix_self[qs - 1];
            event[e].push_back({qs, s - 1, i, 1});
            s = qs;
        }

        base_answer[i] = cur_base;
    }
}

void sweep_event(){
    clear_bucket();

    for(int x = 0; x <= N; x++){
        if(x > 0)
            add_value(a[x]); // 이제 get_value(a[p]) = F(x, p)

        for(int i = 0; i < event[x].size(); i++){
            int l = event[x][i].l;
            int r = event[x][i].r;
            int idx = event[x][i].idx;
            int sign = event[x][i].sign;

            ll ret = 0;
            for(int p = l; p <= r; p++){
                ret += get_value(a[p]);
            }

            delta_answer[idx] += 1LL * sign * ret;
        }
    }
}

void init(){
    cin >> N >> Q;

    sqrtN = (N / sqrt((double)Q));
    if(sqrtN == 0) sqrtN = 1;

    init_bucket();

    for(int i = 1; i <= N; i++){
        cin >> a[i];
    }

    query.reserve(Q);
    for(int i = 0; i < Q; i++){
        int s, e;
        cin >> s >> e;
        query.push_back({i, s, e});
    }

    sort(query.begin(), query.end());

    for(int i = 0; i < Q; i++){
        base_answer[i] = 0;
        delta_answer[i] = 0;
    }
}

void solve(){
    build_self_cost();
    build_event();
    sweep_event();

    ll cur_delta = 0;
    for(int i = 0; i < Q; i++){
        cur_delta += delta_answer[i];
        answer[query[i].idx] = base_answer[i] + cur_delta;
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