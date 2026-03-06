#include <iostream>
#include <algorithm>
#define MAX_NODE 11000000
#define MAX_M 500001
#define MAX_BIT 19
using namespace std;

/* pst 첫번째 응용 이건 트라이긴한데 */
// l,r에서 k번째 수를 찾으려면 각 수가 들어올때마다 pst업데이트 하고 root[r] - root[l-1]에서 k번째 수를 찾으면 됨.

struct Node{
    int l,r;
    int cnt;
    Node() : l(0), r(0), cnt(0){}
};

Node tree[MAX_NODE];
int node_cnt, version;
int root[MAX_M];
int M;

int new_node(int from){
    int node = ++node_cnt;
    tree[node] = tree[from];
    return node;
}

int get_cnt(int node){
    return tree[node].cnt;
}

void init(){
    cin >> M;
    node_cnt = 0;
    root[node_cnt] = 0;
    version = 0;
}

int insert_x(int prev, int x){
    int cur = new_node(prev);
    tree[cur].cnt++;
    int t_cur= cur;
    int t_prev = prev;

    for(int i = MAX_BIT; i>=0; i--){
        int bit = (x >> i) & 1;
        if(!bit){
            int next_prev = tree[t_prev].l;
            int next_cur = new_node(next_prev);
            tree[next_cur].cnt++;
            tree[t_cur].l = next_cur;
            
            t_cur = next_cur;
            t_prev = next_prev;
        }
        else{
            int next_prev = tree[t_prev].r;
            int next_cur = new_node(next_prev);
            tree[next_cur].cnt++;
            tree[t_cur].r = next_cur;
            
            t_cur = next_cur;
            t_prev = next_prev;
        }
    }
    return cur;
}

int query_max_xor(int L, int R, int x){
    int ret = 0;
    for(int i = MAX_BIT; i>=0 ; i--){
        int bit = (x>>i) & 1;
        int want = bit^1;
        if(want == 0){
            if(get_cnt(tree[R].l) - get_cnt(tree[L].l) > 0){
                L = tree[L].l;
                R = tree[R].l;
            }else{
                ret |= (1<<i);
                L = tree[L].r;
                R = tree[R].r;
            }
        }else{
            if(get_cnt(tree[R].r) - get_cnt(tree[L].r) > 0){
                ret |= (1<<i);
                L = tree[L].r;
                R = tree[R].r;
            }else{
                L = tree[L].l;
                R = tree[R].l;
            }
        }
    }
    return ret;
}

int query_leq(int L, int R, int x){
    int ret = 0;
    for(int i = MAX_BIT; i>=0 ; i--){
        int bit = (x>>i) & 1;
        if(bit){
            // 1이면 0은 무조건 포함
            ret += get_cnt(tree[R].l) - get_cnt(tree[L].l);
            // next = 1
            L = tree[L].r;
            R = tree[R].r;
        }else{
            // next = 0
            L = tree[L].l;
            R = tree[R].l;
        }
    }
    // same
    ret += get_cnt(R) - get_cnt(L); 
    return ret;
}

int query_kth(int L, int R, int k){
    int ret = 0;
    for(int i = MAX_BIT; i>=0 ; i--){
        int cnt = get_cnt(tree[R].l) - get_cnt(tree[L].l);
        if(k <= cnt){
            L = tree[L].l;
            R = tree[R].l;
        }else{
            k -= cnt;
            ret |= (1<<i);
            L = tree[L].r;
            R = tree[R].r;
        }
    }
    return ret;
}

void solve(){
    while(M--){
        int type;
        cin >> type;
        if(type == 1){
            int x;
            cin >> x;
            root[version+1] = insert_x(root[version], x);
            version++;
        }
        else if(type == 2){
            int l,r,x;
            cin >> l >> r >> x;
            int answer = query_max_xor(root[l-1],root[r],x);
            cout << answer << "\n";
        }else if(type == 3){
            int k;
            cin >> k;
            version -= k;
        }else if(type == 4){
            int l,r,x;
            cin >> l >> r >> x;
            int answer = query_leq(root[l-1],root[r],x);
            cout << answer << "\n";
        }else{
            int l,r,k;
            cin >> l >> r >> k;
            int answer = query_kth(root[l-1],root[r],k);
            cout << answer << "\n";
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