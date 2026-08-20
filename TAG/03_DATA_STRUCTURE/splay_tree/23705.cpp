#include <iostream>
#define MAX_N 100010
#define INF 4000000000000000000LL
typedef long long ll;
using namespace std;

// 자른 subtree insert_after(r-k)
// 정답은 각 원소 weight = n-1-2*value의 prefix sum 최솟값 위치고 update에서 mn/mn_pos로 유지
// cyclic shift는 subtree prefix-min 집계로 구현

int N, Q;

struct Splay{
    struct Info{
        int len, mn_pos;
        ll sum, mn;
    };

    struct Node{
        Node *l, *r, *p;
        int cnt, len;
        int d;
        ll sum, mn;
        int mn_pos;
        bool dummy;

        Node() : l(nullptr), r(nullptr), p(nullptr), cnt(0), len(0), d(0),
                 sum(0), mn(INF), mn_pos(0), dummy(true) {}

        Node(int _d, bool _dummy = false) : l(nullptr), r(nullptr), p(nullptr),
                                            cnt(1), d(_d), dummy(_dummy) {
            if(dummy){
                len = 0;
                sum = 0;
                mn = INF;
                mn_pos = 0;
            }
            else{
                len = 1;
                sum = d;
                mn = d;
                mn_pos = 1;
            }
        }
    };

    Node pool[MAX_N + 5];
    Node *tree;
    Node *stk[MAX_N + 5];
    int pool_cnt;

    Node *new_node(int d, bool dummy = false){
        pool[pool_cnt] = Node(d, dummy);
        return &pool[pool_cnt++];
    }

    Info get_info(Node *x){
        if(!x)
            return {0, 0, 0, INF};
        return {x->len, x->mn_pos, x->sum, x->mn};
    }

    Info merge_info(Info a, Info b){
        Info ret;
        ret.len = a.len + b.len;
        ret.sum = a.sum + b.sum;
        ret.mn = a.mn;
        ret.mn_pos = a.mn_pos;

        ll bm = b.mn == INF ? INF : a.sum + b.mn;
        if(bm < ret.mn){
            ret.mn = bm;
            ret.mn_pos = a.len + b.mn_pos;
        }

        return ret;
    }

    void update(Node *x){
        if(!x)
            return;

        x->cnt = 1;
        if(x->l)
            x->cnt += x->l->cnt;
        if(x->r)
            x->cnt += x->r->cnt;

        Info cur;
        if(x->dummy)
            cur = {0, 0, 0, INF};
        else
            cur = {1, 1, x->d, x->d};

        Info ret = merge_info(get_info(x->l), cur);
        ret = merge_info(ret, get_info(x->r));

        x->len = ret.len;
        x->sum = ret.sum;
        x->mn = ret.mn;
        x->mn_pos = ret.mn_pos;
    }

    void push(Node *x){
        return;
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

    Node *gather(int s, int e){
        Node *rnode = kth(e + 1);
        Node *lnode = kth(s - 1);

        splay(rnode, lnode);
        return rnode->l;
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

    void insert_after(int pos, Node *x){
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

    void shift_left(int l, int r, int k){
        int s = l + 1;
        Node *x = cut_range(s, s + k - 1);
        insert_after(r - k, x);
    }

    int get_answer(){
        if(tree->mn < 0)
            return tree->mn_pos;
        return 0;
    }

    Node *build(int s, int e, Node *p){
        if(s > e)
            return nullptr;

        int mid = (s + e) >> 1;
        Node *x;

        if(mid == 0 || mid == N + 1){
            x = new_node(0, true);
        }
        else{
            int val = mid - 1;
            int w = N - 1 - 2 * val;
            x = new_node(w, false);
        }

        x->p = p;
        x->l = build(s, mid - 1, x);
        x->r = build(mid + 1, e, x);

        update(x);
        return x;
    }

    void init_tree(){
        pool_cnt = 0;
        tree = build(0, N + 1, nullptr);
    }
};

Splay sp;

void init(){
    cin >> N >> Q;
    sp.init_tree();
}

void solve(){
    while(Q--){
        int l, r, k;
        cin >> l >> r >> k;

        sp.shift_left(l, r, k);
        cout << sp.get_answer() << '\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}