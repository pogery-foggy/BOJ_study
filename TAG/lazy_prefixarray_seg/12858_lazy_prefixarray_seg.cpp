#include <iostream>
#define MAX_N 100001
typedef long long ll;
using namespace std;

// gcd의 성질중에 gcd(a,b,c,d,....)는 gcd(a,b-a,c-b,d-c,....)와 동일하다는 걸 처음알았다
// 차분배열 써서 diff[a]+=T, diff[b]-=T 두 점만하면 끝
// a 복구할 때 차분배열이라 합 구해야함

int N, Q;
ll arr[MAX_N], diff[MAX_N];
ll tree_sum[MAX_N * 4];
ll tree_gcd[MAX_N * 4];

ll absll(ll x){
    if(x < 0)
        return -x;
    return x;
}

ll gcd(ll a, ll b){
    a = absll(a);
    b = absll(b);
    while(b){
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void init_tree(int s, int e, int node){
    if(s == e){
        tree_sum[node] = diff[s];
        tree_gcd[node] = absll(diff[s]);
        return;
    }

    int mid = (s + e) >> 1;
    init_tree(s, mid, node << 1);
    init_tree(mid + 1, e, node << 1 | 1);
    tree_sum[node] = tree_sum[node << 1] + tree_sum[node << 1 | 1];
    tree_gcd[node] = gcd(tree_gcd[node << 1], tree_gcd[node << 1 | 1]);
}

void update(int s, int e, int node, int idx, ll v){
    if(idx < s || e < idx)
        return;

    if(s == e){
        tree_sum[node] += v;
        tree_gcd[node] = absll(tree_sum[node]);
        return;
    }

    int mid = (s + e) >> 1;
    update(s, mid, node << 1, idx, v);
    update(mid + 1, e, node << 1 | 1, idx, v);
    tree_sum[node] = tree_sum[node << 1] + tree_sum[node << 1 | 1];
    tree_gcd[node] = gcd(tree_gcd[node << 1], tree_gcd[node << 1 | 1]);
}

ll query_sum(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return 0;
    if(l <= s && e <= r)
        return tree_sum[node];

    int mid = (s + e) >> 1;
    return query_sum(s, mid, node << 1, l, r) + query_sum(mid + 1, e, node << 1 | 1, l, r);
}

ll query_gcd(int s, int e, int node, int l, int r){
    if(r < s || e < l)
        return 0;
    if(l <= s && e <= r)
        return tree_gcd[node];

    int mid = (s + e) >> 1;
    return gcd(query_gcd(s, mid, node << 1, l, r), query_gcd(mid + 1, e, node << 1 | 1, l, r));
}

void init(){
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> arr[i];

    diff[0] = arr[0];
    for(int i = 1; i < N; i++)
        diff[i] = arr[i] - arr[i - 1];
    init_tree(0, N-1, 1);
    
    cin >> Q;
}

void solve(){
    while(Q--){
        ll T;
        int A, B;
        cin >> T >> A >> B;

        if(T == 0){
            ll a = query_sum(0, N-1, 1, 0, A-1);
            ll b = 0;

            if(A < B)
                b = query_gcd(0, N-1, 1, A, B-1); // A+1, B

            cout << gcd(a, b) << "\n";
        }
        else{
            update(0, N-1, 1, A-1, T);
            update(0, N-1, 1, B, -T);
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