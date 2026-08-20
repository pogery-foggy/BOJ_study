#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 500001
#define MAX_T (1 << 20)
#define INF 4000000000000000000LL
typedef long long ll;
using namespace std;

// https://mzhang2021.github.io/cp-blog/historic-segtree/
// thanks to https://gist.github.com/tjkendev/ad154c067a02648f2c2d8194abe6022d
// 내가 이거로 나중에 블로그 글 써볼까
// C는 A의 과거 최댓값, B는 A의 과거 최솟값
// C는 historical beats로 바로 관리할 수 있음
// B는 D = -A 로 바꾸면 과거 최솟값이 D의 과거 최댓값으로 바뀌므로 같은 엔진을 하나 더 쓰면 됨.
// 한 트리 안에서는 현재값의 max/min/other 그룹별로 d = hist - cur 를 관리하고
// d가 음수가 되는 순간만 0으로 끌어올려서 historic max를 갱신

struct Hist{
    ll mn, sub_mn;
    ll mx, sub_mx;
};

struct Seg{
    ll mx[MAX_T], sub_mx[MAX_T];
    ll mn[MAX_T], sub_mn[MAX_T];
    ll lazy[MAX_T];
    Hist mx_d[MAX_T], oth_d[MAX_T], mn_d[MAX_T];
    int N, sz;

    Hist new_hist(ll x){
        return {0, INF, x, -INF};
    }
    Hist empty_hist(){
        return {INF, INF, -INF, -INF};
    }

    Hist merge_hist(Hist l, Hist r){
        if(l.mn == INF)
            return r;
        if(r.mn == INF)
            return l;

        Hist temp;
        temp.sub_mx = max(l.sub_mx, r.sub_mx);
        // 왼쪽 오른쪽 양쪽
        if(l.mn < r.mn){
            temp.mn = l.mn;
            temp.sub_mn = min(l.sub_mn, r.mn);
            temp.sub_mx = max(temp.sub_mx, r.mx);
            temp.mx = l.mx;
        }
        else if(l.mn > r.mn){
            temp.mn = r.mn;
            temp.sub_mn = min(l.mn, r.sub_mn);
            temp.sub_mx = max(temp.sub_mx, l.mx);
            temp.mx = r.mx;
        }
        else{
            temp.mn = l.mn;
            temp.sub_mn = min(l.sub_mn, r.sub_mn);
            temp.mx = max(l.mx, r.mx);
        }
        return temp;
    }

    void add_hist(Hist &x, ll v){
        if(x.mn != INF)
            x.mn += v;
        if(x.sub_mn != INF)
            x.sub_mn += v;
    }

    void chmax_hist(Hist &x, ll v){
        if(x.mn < v){
            x.mx += v - x.mn;
            x.mn = v;
        }
    }

    ll get_hist_max(Hist &x){
        return max(x.mx, x.sub_mx);
    }

    void init_empty(int node){
        mx[node] = sub_mx[node] = -INF;
        mn[node] = sub_mn[node] = INF;
        lazy[node] = 0;
        mx_d[node] = oth_d[node] = mn_d[node] = empty_hist();
    }

    void init_tree(int s, int e, int node, ll arr[]){
        lazy[node] = 0;
        if(s == e){
            if(s < N){
                mx[node] = mn[node] = arr[s];
                sub_mx[node] = -INF;
                sub_mn[node] = INF;
                mx_d[node] = new_hist(arr[s]);
                oth_d[node] = empty_hist();
                mn_d[node] = new_hist(arr[s]);
            }
            else{
                init_empty(node);
            }
            return;
        }

        int mid = (s + e) >> 1;
        init_tree(s, mid, node << 1, arr);
        init_tree(mid + 1, e, node << 1 | 1, arr);
        pull(node);
    }

    void init(int n, ll arr[]){
        N = n;
        sz = 1;
        while(sz < N) sz <<= 1;
        init_tree(0,sz-1,1,arr);
    }

    void apply_add(int node, ll x){
        mx[node] += x;
        if(sub_mx[node] != -INF)
            sub_mx[node] += x;
        mn[node] += x;
        if(sub_mn[node] != INF)
            sub_mn[node] += x;

        // cur += x 이므로 d = hist - cur 는 전부 x만큼 감소함
        add_hist(mx_d[node], -x);
        add_hist(oth_d[node], -x);
        add_hist(mn_d[node], -x);
        lazy[node] += x;
    }

    void apply_chmin(int node, ll x){
        if(mx[node] <= x)
            return;
        // 현재 최댓값 그룹만 내려가므로 그 그룹의 d는 old - x 만큼 증가함
        add_hist(mx_d[node], mx[node] - x);
        if(mx[node] == mn[node]){
            add_hist(mn_d[node], mn[node] - x);
            mx[node] = mn[node] = x;
        }
        else if(mx[node] == sub_mn[node]){
            mx[node] = sub_mn[node] = x;
        }
        else{
            mx[node] = x;
        }
    }

    void apply_chmax(int node, ll x){
        if(mn[node] >= x)
            return;

        add_hist(mn_d[node], mn[node] - x);
        if(mn[node] == mx[node]){
            add_hist(mx_d[node], mx[node] - x);
            mn[node] = mx[node] = x;
        }
        else if(mn[node] == sub_mx[node]){
            mn[node] = sub_mx[node] = x;
        }
        else{
            mn[node] = x;
        }
    }

    void push_hist(int child, int node){
        // 자식의 현재 최소값이 부모의 어느 그룹에 속하는지 보고
        // 걔 그룹이 들고 있던 d의 하한을 자식의 mn_d로 넘김
        if(mn[node] == mn[child])
            chmax_hist(mn_d[child], mn_d[node].mn);
        else if(mx[node] == mn[child])
            chmax_hist(mn_d[child], mx_d[node].mn);
        else
            chmax_hist(mn_d[child], oth_d[node].mn);

        if(mx[node] == mx[child])
            chmax_hist(mx_d[child], mx_d[node].mn);
        else if(mn[node] == mx[child])
            chmax_hist(mx_d[child], mn_d[node].mn);
        else
            chmax_hist(mx_d[child], oth_d[node].mn);

        // 자식내부의 중간값들은 부모에서도 안전하게 other 하한만 받을 수 있음
        chmax_hist(oth_d[child], oth_d[node].mn);
    }

    void push_cur(int s,int e, int node){
        if(s==e) return;
        int l = node << 1, r = node << 1 | 1;
        if(lazy[node]){
            apply_add(l, lazy[node]);
            apply_add(r, lazy[node]);
            lazy[node] = 0;
        }

        if(mx[node] < mx[l])
            apply_chmin(l, mx[node]);
        if(mx[node] < mx[r])
            apply_chmin(r, mx[node]);
        if(mn[l] < mn[node])
            apply_chmax(l, mn[node]);
        if(mn[r] < mn[node])
            apply_chmax(r, mn[node]);
    }
    void push(int s, int e, int node){
        if(s == e)
            return;
        push_cur(s,e,node);
        int l = node << 1, r = node << 1 | 1;
        // historic용 d 하한
        push_hist(l, node);
        push_hist(r, node);
    }

    void pull(int node){
        int l = node << 1, r = node << 1 | 1;

        // 자식 내부에서 중간값이었던 원소들을 우선 그대로 모음
        oth_d[node] = merge_hist(oth_d[l], oth_d[r]);

        if(mx[l] > mx[r]){
            mx[node] = mx[l];
            sub_mx[node] = max(sub_mx[l], mx[r]);
            mx_d[node] = mx_d[l];
        }
        else if(mx[l] < mx[r]){
            mx[node] = mx[r];
            sub_mx[node] = max(mx[l], sub_mx[r]);
            mx_d[node] = mx_d[r];
        }
        else{
            mx[node] = mx[l];
            sub_mx[node] = max(sub_mx[l], sub_mx[r]);
            mx_d[node] = merge_hist(mx_d[l], mx_d[r]);
        }

        if(mn[l] < mn[r]){
            mn[node] = mn[l];
            sub_mn[node] = min(sub_mn[l], mn[r]);
            mn_d[node] = mn_d[l];
        }
        else if(mn[l] > mn[r]){
            mn[node] = mn[r];
            sub_mn[node] = min(mn[l], sub_mn[r]);
            mn_d[node] = mn_d[r];
        }
        else{
            mn[node] = mn[l];
            sub_mn[node] = min(sub_mn[l], sub_mn[r]);
            mn_d[node] = merge_hist(mn_d[l], mn_d[r]);
        }

        // 자식의 min/max 그룹이 부모 기준으로는 더 이상 극값이 아닐 수 있으니까 그런 그룹을 other에 보냄
        if(mn[l] == mx[l]){
            // 왼쪽 자식이 한 값뿐이면 그 값이 부모의 내부값일 때만 전부 other
            if(mn[node] < mn[l] && mx[l] < mx[node])
                oth_d[node] = merge_hist(oth_d[node], mx_d[l]);
        }
        else{
            if(mx[l] < mx[node])
                oth_d[node] = merge_hist(oth_d[node], mx_d[l]);
            if(mn[node] < mn[l])
                oth_d[node] = merge_hist(oth_d[node], mn_d[l]);
        }

        if(mn[r] == mx[r]){
            if(mn[node] < mn[r] && mx[r] < mx[node])
                oth_d[node] = merge_hist(oth_d[node], mx_d[r]);
        }
        else{
            if(mx[r] < mx[node])
                oth_d[node] = merge_hist(oth_d[node], mx_d[r]);
            if(mn[node] < mn[r])
                oth_d[node] = merge_hist(oth_d[node], mn_d[r]);
        }

        lazy[node] = 0;
    }

    void fix_hist(int s, int e, int node){
        // d < 0 이면 hist < cur 인 원소가 있다는 뜻
        if(0 <= mx_d[node].mn && 0 <= oth_d[node].mn && 0 <= mn_d[node].mn)
            return;

        if(0 < mx_d[node].sub_mn && 0 < oth_d[node].sub_mn && 0 < mn_d[node].sub_mn){
            chmax_hist(mx_d[node], 0);
            chmax_hist(oth_d[node], 0);
            chmax_hist(mn_d[node], 0);
            return;
        }

        if(s==e){
            chmax_hist(mx_d[node], 0);
            chmax_hist(oth_d[node], 0);
            chmax_hist(mn_d[node], 0);
            return;
        }
        push(s, e, node);
        int mid = (s + e) >> 1;
        fix_hist(s, mid, node << 1);
        fix_hist(mid + 1, e, node << 1 | 1);
        pull(node);
    }

    void update_add(int s, int e, int node, int l, int r, ll x){
        if(r < s || e < l || !x)
            return;
        if(l <= s && e <= r){
            apply_add(node, x);
            if(x > 0) fix_hist(s, e, node);
            return;
        }

        push(s, e, node);
        int mid = (s + e) >> 1;
        update_add(s, mid, node << 1, l, r, x);
        update_add(mid + 1, e, node << 1 | 1, l, r, x);
        pull(node);
    }

    void update_chmax(int s, int e, int node, int l, int r, ll x){
        if(r < s || e < l || mn[node] >= x)
            return;
        if(l <= s && e <= r && x < sub_mn[node]){
            apply_chmax(node, x);
            fix_hist(s, e, node);
            return;
        }

        push(s, e, node);
        int mid = (s + e) >> 1;
        update_chmax(s, mid, node << 1, l, r, x);
        update_chmax(mid + 1, e, node << 1 | 1, l, r, x);
        pull(node);
    }

    void update_chmin(int s, int e, int node, int l, int r, ll x){
        if(r < s || e < l || mx[node] <= x)
            return;
        if(l <= s && e <= r && sub_mx[node] < x){
            apply_chmin(node, x);
            // fix_hist(s, e, node);
            return;
        }

        push(s, e, node);
        int mid = (s + e) >> 1;
        update_chmin(s, mid, node << 1, l, r, x);
        update_chmin(mid + 1, e, node << 1 | 1, l, r, x);
        pull(node);
    }

    ll query_min(int s, int e, int node, int l, int r){
        if(r < s || e < l)
            return INF;
        if(l <= s && e <= r)
            return mn[node];

        push_cur(s, e, node);
        int mid = (s + e) >> 1;
        return min(query_min(s, mid, node << 1, l, r), query_min(mid + 1, e, node << 1 | 1, l, r));
    }

    ll query_hist_max(int s, int e, int node, int l, int r){
        if(r < s || e < l)
            return -INF;
        if(l <= s && e <= r)
            return max(get_hist_max(mx_d[node]), max(get_hist_max(oth_d[node]), get_hist_max(mn_d[node])));
        push(s, e, node);
        int mid = (s + e) >> 1;
        return max(query_hist_max(s, mid, node << 1, l, r), query_hist_max(mid + 1, e, node << 1 | 1, l, r));
    }
};

Seg seg[2];
ll arr[2][MAX_N];
int N, Q;

void init(){
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> arr[0][i];
        arr[1][i] = -arr[0][i];
    }
    seg[0].init(N, arr[0]);
    seg[1].init(N, arr[1]);
    cin >> Q;
}

void solve(){
    while (Q--){
        int type, l, r;
        cin >> type >> l >> r;
        l--, r--;

        if(type == 1){
            ll x;
            cin >> x;
            seg[0].update_add(0, seg[0].sz-1, 1, l, r, x);
            seg[1].update_add(0, seg[1].sz-1, 1, l, r, -x);
        }
        else if(type == 2){
            ll x;
            cin >> x;
            seg[0].update_chmax(0, seg[0].sz-1, 1, l, r, x);
            seg[1].update_chmin(0, seg[1].sz-1, 1, l, r, -x);
        }
        else if(type == 3){
            ll x;
            cin >> x;
            seg[0].update_chmin(0, seg[0].sz-1, 1, l, r, x);
            seg[1].update_chmax(0, seg[1].sz-1, 1, l, r, -x);
        }
        else if(type == 4){
            cout << seg[0].query_min(0, seg[0].sz-1, 1, l, r) << "\n";
        }
        else if(type == 5){
            // A의 historical minimum에 음수 부호를 되돌리면 historical maximum이 나옴
            cout << -seg[1].query_hist_max(0, seg[1].sz-1, 1, l, r) << "\n";
        }
        else{
            cout << seg[0].query_hist_max(0, seg[0].sz-1, 1, l, r) << "\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}