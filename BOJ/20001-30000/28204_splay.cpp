#include <iostream>
#define MAX_N 1000010
#define DIV (1 << 30)
#define MASK ((1 << 30) - 1)
using namespace std;

// 늘 먹던 연산 순서대로 처리하기
int n, m, M;

struct Splay{
    struct Node{
        Node *l, *r, *p;
        int len, cnt;
        int d, sum, lazy;

        Node() : l(nullptr), r(nullptr), p(nullptr), len(0), cnt(0), d(0), sum(0), lazy(0) {}

        Node(int _len, int _d) : l(nullptr), r(nullptr), p(nullptr),
                                 len(_len), cnt(_len), d(_d), lazy(0) {
            sum = (int)((1LL * len * d) & MASK);
        }
    };

    Node pool[MAX_N];
    Node *tree, *left_dummy, *right_dummy;
    Node *stk[MAX_N];
    int pool_cnt;

    int get_cnt(Node *x){
        return x ? x->cnt : 0;
    }

    int get_sum(Node *x){
        return x ? x->sum : 0;
    }

    Node *new_node(int len, int d){
        pool[pool_cnt] = Node(len, d);
        return &pool[pool_cnt++];
    }

    void update(Node *x){
        if(!x)
            return;

        x->cnt = x->len;
        x->sum = (int)((1LL * x->len * x->d) & MASK);

        if(x->l){
            x->cnt += x->l->cnt;
            x->sum = (x->sum + x->l->sum) & MASK;
        }

        if(x->r){
            x->cnt += x->r->cnt;
            x->sum = (x->sum + x->r->sum) & MASK;
        }
    }

    void apply_add(Node *x, int dx){
        if(!x || !dx)
            return;

        x->d = (x->d + dx) & MASK;
        x->sum = (int)((x->sum + 1LL * x->cnt * dx) & MASK);
        x->lazy = (x->lazy + dx) & MASK;
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

    Node *find_by_pos(int pos){
        Node *x = tree;

        while(true){
            push(x);

            int left_cnt = get_cnt(x->l);

            if(pos < left_cnt){
                x = x->l;
            }
            else if(pos < left_cnt + x->len){
                splay(x);
                return x;
            }
            else{
                pos -= left_cnt + x->len;
                x = x->r;
            }
        }
    }

    void split_pos(int pos){
        if(pos <= 0 || pos >= M)
            return;

        Node *x = find_by_pos(pos);
        int left_cnt = get_cnt(x->l);
        int offset = pos - left_cnt;

        if(offset == 0)
            return;

        Node *y = new_node(x->len - offset, x->d);

        y->r = x->r;
        if(y->r)
            y->r->p = y;

        x->r = y;
        y->p = x;
        x->len = offset;

        update(y);
        update(x);
    }

    Node *get_prev_boundary(int pos){
        if(pos == 0){
            splay(left_dummy);
            return left_dummy;
        }

        return find_by_pos(pos - 1);
    }

    Node *get_next_boundary(int pos){
        if(pos == M){
            splay(right_dummy);
            return right_dummy;
        }

        return find_by_pos(pos);
    }

    int add_range(int l, int r, int dx){
        split_pos(l);
        split_pos(r + 1);

        Node *rnode = get_next_boundary(r + 1);
        Node *lnode = get_prev_boundary(l);

        splay(rnode, lnode);

        Node *cur = rnode->l;
        apply_add(cur, dx);

        int ret = get_sum(cur);
        update(rnode);
        update(lnode);
        return ret;
    }

    void init_tree(){
        pool_cnt = 0;

        left_dummy = new_node(0, 0);
        Node *body = new_node(M, 0);
        right_dummy = new_node(0, 0);

        tree = body;

        body->l = left_dummy;
        body->r = right_dummy;
        left_dummy->p = body;
        right_dummy->p = body;

        update(left_dummy);
        update(right_dummy);
        update(body);
    }
} sp;

void init(){
    cin >> n >> m;
    M = 1 << m;
    sp.init_tree();
}

void solve(){
    int x = 0;

    for(int i = 1; i <= n; i++){
        int p, q;
        cin >> p >> q;

        int cur_mask = M - 1;
        int pp = (p + (x & cur_mask)) & cur_mask;
        int qq = (q + (x & cur_mask)) & cur_mask;
        
        int l = pp < qq ? pp : qq;
        int r = pp < qq ? qq : pp;
        int added_sum = sp.add_range(l, r, i & MASK);
        x = (x + added_sum) & MASK;
    }

    cout << x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}