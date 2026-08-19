
#include <algorithm>
#include <iostream>
#define MAX_N 200010
#define INF 4000000000000000000LL
typedef long long ll;
using namespace std;

int N, answer;
ll low[MAX_N], high[MAX_N];

// LIS인데 이걸 어떻게 스플레이에 접목하지 좀 그리디하게 가야하나
// LIS의 최소를 splay에 inorder로 두고
// 일단 해야할거부터
// 1.L보다 작은 LIS 끝 위치 찾고 : kth
// 2.이번에는 R보다 작은거 : kth
// 3. 삽입 & 구간+1 :insert + range add
// 4. 삭제 : del

struct Splay{
    struct Node{
        Node *l, *r, *p;
        int cnt;
        ll d, mx, lazy;
        bool dummy;

        Node() : l(nullptr), r(nullptr), p(nullptr), cnt(0), d(0), mx(-INF), lazy(0), dummy(true) {}

        Node(ll _d, bool _dummy = false) : l(nullptr), r(nullptr), p(nullptr), cnt(1),
                                           d(_d), mx(_d), lazy(0), dummy(_dummy) {}
    };

    Node pool[MAX_N];
    Node *tree;
    Node *stk[MAX_N];
    int pool_cnt;

    Node *new_node(ll d, bool dummy = false){
        pool[pool_cnt] = Node(d, dummy);
        return &pool[pool_cnt++];
    }

    ll maxll(ll a, ll b){
        return a > b ? a : b;
    }

    void update(Node *x){
        if(!x)
            return;

        x->cnt = 1;
        x->mx = x->d;

        if(x->l){
            x->cnt += x->l->cnt;
            x->mx = maxll(x->mx, x->l->mx);
        }
        if(x->r){
            x->cnt += x->r->cnt;
            x->mx = maxll(x->mx, x->r->mx);
        }
    }

    void apply_add(Node *x, ll dx){
        if(!x)
            return;

        x->d += dx;
        x->mx += dx;
        x->lazy += dx;
    }

    void push(Node *x){
        if(!x || !x->lazy)
            return;

        apply_add(x->l, x->lazy);
        apply_add(x->r, x->lazy);
        x->lazy = 0;
    }

    void push_path(Node *x, Node *g = nullptr){
        int top = 0;

        for(Node *cur = x; cur; cur = cur->p){
            stk[top++] = cur;
            if(cur == g)
                break;
        }

        while(top)
            push(stk[--top]);
    }

    void rotate(Node *x){
        Node *p = x->p;
        Node *g = p->p;
        Node *b = nullptr;

        push(p);
        push(x);

        if(x == p->l){
            b = x->r;
            x->r = p;
            p->l = b;
        }
        else{
            b = x->l;
            x->l = p;
            p->r = b;
        }

        x->p = g;
        p->p = x;

        if(b)
            b->p = p;

        if(g){
            if(p == g->l)
                g->l = x;
            else
                g->r = x;
        }
        else{
            tree = x;
        }

        update(p);
        update(x);
    }

    void splay(Node *x, Node *g = nullptr){
        if(!x)
            return;

        push_path(x, g);

        while(x->p != g){
            Node *p = x->p;
            Node *pp = p->p;

            if(pp == g){
                rotate(x);
            }
            else if((x == p->l) == (p == pp->l)){
                rotate(p);
                rotate(x);
            }
            else{
                rotate(x);
                rotate(x);
            }
        }

        if(!g)
            tree = x;
        else
            update(g);
    }

    Node *kth(int k){
        Node *x = tree;

        while(true){
            push(x);

            int left_cnt = x->l ? x->l->cnt : 0;

            if(k < left_cnt){
                x = x->l;
            }
            else if(k == left_cnt){
                splay(x);
                return x;
            }
            else{
                k -= left_cnt + 1;
                x = x->r;
            }
        }
    }

    // mx로 lower_bound를 흉내낼 수 있음
    int lower_bound(ll x){
        Node *cur = tree;
        int ret = 0;

        while(true){
            push(cur);

            if(cur->l && cur->l->mx >= x){
                cur = cur->l;
                continue;
            }

            int left_cnt = cur->l ? cur->l->cnt : 0;

            if(cur->d >= x){
                ret += left_cnt;
                splay(cur);
                return ret;
            }

            ret += left_cnt + 1;
            cur = cur->r;
        }
    }

    Node *gather(int s, int e){
        Node *rnode = kth(e + 1);
        Node *lnode = kth(s - 1);

        splay(rnode, lnode);
        return rnode->l;
    }

    void range_add(int s, int e, ll dx){
        if(s > e)
            return;

        Node *x = gather(s, e);
        apply_add(x, dx);
        update(tree->r);
        update(tree);
    }

    Node *cut_range(int s, int e){
        Node *x = gather(s, e);

        tree->r->l = nullptr;
        if(x)
            x->p = nullptr;

        update(tree->r);
        update(tree);

        return x;
    }

    void insert_back(int pos, Node *x){
        if(!x)
            return;

        Node *rnode = kth(pos + 1);
        Node *lnode = kth(pos);

        splay(rnode, lnode);

        rnode->l = x;
        x->p = rnode;

        update(rnode);
        update(lnode);
    }

    void insert(int pos, ll d){
        Node *x = new_node(d, false);
        insert_back(pos, x);
    }

    void del_pos(int pos){
        cut_range(pos, pos);
    }

    void init_tree(){
        pool_cnt = 0;

        Node *ldummy = new_node(-INF, true);
        Node *first = new_node(-1, false);
        Node *rdummy = new_node(INF, true);

        ldummy->r = first;
        first->p = ldummy;
        first->r = rdummy;
        rdummy->p = first;

        update(rdummy);
        update(first);
        update(ldummy);
        tree = ldummy;
    }
};

Splay sp;

void init(){
    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> low[i];
        high[i] = low[i];
    }

    for(int i = 0; i < N; i++){
        ll x;
        cin >> x;
        low[i] = min(low[i], x);
        high[i] = max(high[i], x);
    }

    for(int i = 0; i < N; i++){
        ll x;
        cin >> x;
        low[i] = min(low[i], x);
        high[i] = max(high[i], x);
    }

    answer = 0;
    sp.init_tree();
}

void solve(){
    for(int i = 0; i < N; i++){
        ll l = low[i];
        ll r = high[i];

        int pos_a = sp.lower_bound(l) - 1;
        int pos_b = sp.lower_bound(r) - 1;

        sp.insert(pos_a, l);
        sp.range_add(pos_a + 2, pos_b + 1, 1);

        if(pos_b < answer + 1)
            sp.del_pos(pos_b + 2);
        else
            answer++;
    }

    cout << answer << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}