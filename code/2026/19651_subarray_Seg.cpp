#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 100010
using namespace std;
typedef long long ll;
struct Node{
    ll lmx, rmx, mx, sum, value;
    bool all_zero;   
};
ll arr[MAX_N], brr[MAX_N], crr[MAX_N];
ll crr_index[MAX_N];
Node tree[MAX_N * 4];
int N, M ;

Node set_node(ll x){
    Node temp;
    if(x){
        temp.value = x;
        temp.lmx = 0;
        temp.rmx = 0;
        temp.mx = 0;
        temp.sum = 0;
        temp.all_zero = false;
    }
    else{
        temp.value = 0;
        temp.lmx = 1;
        temp.rmx = 1;
        temp.mx = 1;
        temp.sum = 1;
        temp.all_zero = true;
    }
    return temp;
}

Node merge_node(Node l, Node r){
    Node temp;
    temp.lmx = l.lmx;
    if(l.all_zero) temp.lmx = l.sum+r.lmx;
    temp.rmx = r.rmx;
    if(r.all_zero) temp.rmx = r.sum + l.rmx;
    temp.sum = l.sum + r.sum;
    temp.mx = max({l.mx, r.mx, l.rmx+r.lmx});
    temp.all_zero = l.all_zero & r.all_zero;
    return temp;
}


Node init_tree(int s, int e,int node){
    if(s==e){
        tree[node] = set_node(crr[s]);
        crr_index[s] = node;
        return tree[node];
    }
    int mid = (s+e) >> 1;
    Node l = init_tree(s,mid,node<<1);
    Node r = init_tree(mid+1,e,node<<1|1);
    return tree[node] = merge_node(l,r);
}

void init(){
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> arr[i];

    brr[0] = arr[0];
    for(int i = 1; i <= N; i++)
        brr[i] = arr[i] - arr[i-1];

    crr[0] = brr[0];
    for(int i = 1; i <= N+1; i++)
        crr[i] = brr[i] - brr[i-1];
    cin >> M;

    // 차이 계산해주려고 두칸 더 필요함 (s-1, e+1)만큼
    N+=2;
    init_tree(0,N-1,1);
    //for(int i = 0; i < N; i++){
    //   cout << arr[i] <<" "<< brr[i] << " "<< crr[i] << "\n";
    //}
    //cout <<"\n";
}

void update(int node, int diff){
    tree[node] = set_node(tree[node].value + diff);
    node >>= 1;
    while(node > 0){
        Node l = tree[node<<1];
        Node r = tree[node<<1|1];
        tree[node] = merge_node(l,r);
        node >>= 1;
    }
}

Node query(int s, int e, int l, int r, int node){
    if(r < s || e < l)
        return set_node(1);
    if(l<=s && e<=r)
        return tree[node];

    int mid = (s+e)>>1;
    Node le = query(s,mid,l,r,node<<1);
    Node ri = query(mid+1,e,l,r,node<<1|1);
    return merge_node(le,ri);
}

void solve(){
    // s : s x
    // s : s+1 d-x
    // e : e+1 -x-(e-s+1)d
    // e : e+2 x+(e-s)d
    while(M--){
        int type;
        cin >> type;
        if(type == 1){
            int s,e,x,d;
            cin >> s >> e >> x >> d;
            s -= 1;
            e -= 1;
            update(crr_index[s], x);
            update(crr_index[s+1], d-x);
            update(crr_index[e+1], -x-(e-s+1)*d);
            update(crr_index[e+2], x+(e-s)*d);
        }else{
            int s, e;
            cin >> s >> e;
            s -= 1;
            e -= 1;
            // 사이를 봐야함
            Node answer = query(0,N-1,s+2,e,1);
            cout << answer.mx+2 << "\n";
        }
        //cout << "debug";
        //for(int i = 0; i < N; i++){
        //    cout << tree[crr_index[i]].value << " ";
        //}cout << "\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}