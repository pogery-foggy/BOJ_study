#include <iostream>
#define MAX_N 200010
typedef long long ll;
using namespace std;

// 1 2번 lazy,lazy add 3번 1빼고 kth

int N, Q, len;
ll arr[MAX_N];

struct Splay{
    struct Node{
        Node *l, *r, *p;
        int cnt;
        ll d, sum;
        ll add_a, add_d, set_val;
        bool set_lazy, dummy;

        Node() : l(nullptr), r(nullptr), p(nullptr), cnt(0), d(0), sum(0),
                 add_a(0), add_d(0), set_val(0), set_lazy(false), dummy(true) {}

        Node(ll _d, bool _dummy = false) : l(nullptr), r(nullptr), p(nullptr),
                                           cnt(1), d(_d), add_a(0), add_d(0),
                                           set_val(0), set_lazy(false), dummy(_dummy) {
            sum = dummy ? 0 : d;
        }
    };

    Node pool[MAX_N];
    Node *tree;
    Node *stk[MAX_N];
    int pool_cnt;

    Node *new_node(ll d, bool dummy = false){
        pool[pool_cnt] = Node(d, dummy);
        return &pool[pool_cnt++];
    }

    void update(Node *x){
        if(!x)
            return;

        x->cnt = 1;
        x->sum = x->dummy ? 0 : x->d;

        if(x->l){
            x->cnt += x->l->cnt;
            x->sum += x->l->sum;
        }

        if(x->r){
            x->cnt += x->r->cnt;
            x->sum += x->r->sum;
        }
    }

    void apply_set(Node *x, ll v){
        if(!x)
            return;

        x->d = v;
        x->sum = 1LL * x->cnt * v;
        x->set_lazy = true;
        x->set_val = v;
        x->add_a = x->add_d = 0;
    }

    void apply_add(Node *x, ll a, ll d){
        if(!x)
            return;

        ll n = x->cnt;
        ll left_cnt = x->l ? x->l->cnt : 0;

        x->sum += a * n + d * n * (n - 1) / 2;
        x->d += a + d * left_cnt;
        x->add_a += a;
        x->add_d += d;
    }

    void push(Node *x){
        if(!x)
            return;

        if(x->set_lazy){
            apply_set(x->l, x->set_val);
            apply_set(x->r, x->set_val);
            x->set_lazy = false;
        }

        if(x->add_a || x->add_d){
            ll left_cnt = x->l ? x->l->cnt : 0;

            apply_add(x->l, x->add_a, x->add_d);
            apply_add(x->r, x->add_a + (left_cnt + 1) * x->add_d, x->add_d);

            x->add_a = x->add_d = 0;
        }
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

    void set_range(int s, int e, ll x){
        Node *cur = gather(s, e);
        apply_set(cur, x);

        update(tree->r);
        update(tree);
    }

    void add_range(int s, int e, ll x){
        Node *cur = gather(s, e);
        apply_add(cur, x, x);

        update(tree->r);
        update(tree);
    }

    ll get_sum(int s, int e){
        Node *cur = gather(s, e);
        return cur ? cur->sum : 0;
    }

    void insert_back(int pos, Node *x){
        Node *rnode = kth(pos + 1);
        Node *lnode = kth(pos);

        splay(rnode, lnode);

        rnode->l = x;
        x->p = rnode;

        update(rnode);
        update(lnode);
    }

    void insert_prev(int pos, ll x){
        insert_back(pos - 1, new_node(x, false));
    }

    Node *build(int s, int e, Node *p){
        if(s > e)
            return nullptr;

        int mid = (s + e) >> 1;
        Node *x;

        if(mid == 0 || mid == N + 1)
            x = new_node(0, true);
        else
            x = new_node(arr[mid], false);

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
} sp;

void init(){
    cin >> N >> Q;
    len = N;

    for(int i = 1; i <= N; i++)
        cin >> arr[i];

    sp.init_tree();
}

void solve(){
    while(Q--){
        int op, a, b;
        ll x;

        cin >> op;

        if(op == 1){
            cin >> a >> b >> x;
            sp.set_range(a, b, x);
        }
        else if(op == 2){
            cin >> a >> b >> x;
            sp.add_range(a, b, x);
        }
        else if(op == 3){
            cin >> a >> x;
            sp.insert_prev(a, x);
            len++;
        }
        else{
            cin >> a >> b;
            cout << sp.get_sum(a, b) << "\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}