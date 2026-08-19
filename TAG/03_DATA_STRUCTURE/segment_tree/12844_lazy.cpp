#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_N 500001
using namespace std;

int N,M;
int tree[MAX_N * 4];
int lazy[MAX_N * 4];

int init_tree(int s,int e,int node){
    if(s==e){
        cin >> tree[node];
        return tree[node];
    }
    int mid = (s+e) >> 1;
    return tree[node] = init_tree(s,mid,node<<1) ^ init_tree(mid+1,e,node<<1|1);
}

void init() {
    cin >> N;
    init_tree(0, N-1, 1);
}

void push(int node,int s, int e){
    if(lazy[node]){
        if(s!=e){
            lazy[node<<1] ^=  lazy[node];
            lazy[node<<1|1] ^= lazy[node];
        }
        tree[node] ^= (((e-s+1)%2)?lazy[node]:0);
        lazy[node] = 0;
    }
}

void update(int s,int e,int l, int r, int node, int k){
    push(node,s,e);
    if(e<l || r<s) return;
    if(l <= s && e <= r){
        lazy[node] ^= k;
        push(node,s,e);
        return;
    }
    int mid = (s+e) >> 1;
    update(s,mid,l,r,node<<1,k);
    update(mid+1,e,l,r,node<<1|1,k);
    tree[node] = tree[node<<1] ^ tree[node<<1|1];
}

int query(int s, int e, int l, int r, int node){
    push(node, s, e);
    if(e<l || r<s) return 0;
    if(l <= s && e <= r)
        return tree[node];
    int mid = (s+e) >> 1;
    return query(s,mid,l,r,node<<1) ^ query(mid+1,e,l,r,node<<1|1); 
}

void solve() {
    cin >> M;
    while(M--){
        int type;
        cin >> type;
        if(type == 1){
            int l, r, k;
            cin >> l >> r >> k;
            update(0,N-1,l,r,1,k);
        }else{
            int l, r;
            cin >> l >> r;
            cout << query(0,N-1,l,r,1) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}