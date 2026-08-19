#include <iostream>
#include <string>
#define MAX_N 1000010
using namespace std;

int N, Q;
string S;
// 이것도 in-order를 봄.
// 나머지는 다 괜찮은데 4번 명령이 어려움
// 각 노드가 ( ) 매칭갯수 들고.. 그냥 네가지 다 들고있자
// normal,nonflip normal,flip reverse,nonflip reverse,flip

struct Info{
    int open, close, pair_cnt;
};

Info merge_info(Info l, Info r){
    int match = l.open < r.close ? l.open : r.close;
    return {l.open + r.open - match, l.close + r.close - match, l.pair_cnt + r.pair_cnt + match};
}

struct Splay{
    struct Node{
        Node *l, *r, *p;
        int cnt, d;
        bool rev, inv, dummy;
        Info info[2][2];

        Node() : l(nullptr), r(nullptr), p(nullptr), cnt(0), d(0),
                 rev(false), inv(false), dummy(true) {}

        Node(int _d, bool _dummy = false) : l(nullptr), r(nullptr), p(nullptr),
                                            cnt(1), d(_d), rev(false), inv(false), dummy(_dummy) {}
    };

    Node pool[MAX_N];
    Node *tree;
    Node *stk[MAX_N];
    int pool_cnt;

    Info empty_info(){
        return {0, 0, 0};
    }

    void swap_node(Node *&a, Node *&b){
        Node *temp = a;
        a = b;
        b = temp;
    }

    void swap_info(Info &a, Info &b){
        Info temp = a;
        a = b;
        b = temp;
    }

    Node *new_node(int d, bool dummy = false){
        pool[pool_cnt] = Node(d, dummy);
        return &pool[pool_cnt++];
    }

    Info get_mid(Node *x, int add_inv){
        if(x->dummy)
            return empty_info();

        if((x->d ^ add_inv) == 0)
            return {1, 0, 0};
        return {0, 1, 0};
    }

    void update(Node *x){
        if(!x)
            return;

        x->cnt = 1;
        if(x->l)
            x->cnt += x->l->cnt;
        if(x->r)
            x->cnt += x->r->cnt;

        for(int add_inv = 0; add_inv < 2; add_inv++){
            Info mid = get_mid(x, add_inv);
            Info left_forward = x->l ? x->l->info[0][add_inv] : empty_info();
            Info right_forward = x->r ? x->r->info[0][add_inv] : empty_info();
            Info left_reverse = x->l ? x->l->info[1][add_inv] : empty_info();
            Info right_reverse = x->r ? x->r->info[1][add_inv] : empty_info();

            x->info[0][add_inv] = merge_info(merge_info(left_forward, mid), right_forward);
            x->info[1][add_inv] = merge_info(merge_info(right_reverse, mid), left_reverse);
        }
    }

    void apply_reverse(Node *x){
        if(!x)
            return;

        swap_node(x->l, x->r);
        swap_info(x->info[0][0], x->info[1][0]);
        swap_info(x->info[0][1], x->info[1][1]);
        x->rev = !x->rev;
    }

    void apply_inverse(Node *x){
        if(!x)
            return;

        if(!x->dummy)
            x->d ^= 1;
        swap_info(x->info[0][0], x->info[0][1]);
        swap_info(x->info[1][0], x->info[1][1]);
        x->inv = !x->inv;
    }

    void push(Node *x){
        if(!x)
            return;

        if(x->rev){
            apply_reverse(x->l);
            apply_reverse(x->r);
            x->rev = false;
        }

        if(x->inv){
            apply_inverse(x->l);
            apply_inverse(x->r);
            x->inv = false;
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

    void fix_gather_parent(){
        update(tree->r);
        update(tree);
    }

    void inverse(int s, int e){
        Node *x = gather(s, e);
        apply_inverse(x);
        fix_gather_parent();
    }

    void reverse(int s, int e){
        Node *x = gather(s, e);
        apply_reverse(x);
        fix_gather_parent();
    }

    void rotate(int s, int e){
        Node *x = gather(s, e);
        apply_reverse(x);
        apply_inverse(x);
        fix_gather_parent();
    }

    int query(int s, int e){
        Node *x = gather(s, e);
        return x ? x->info[0][0].pair_cnt : 0;
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
            x = new_node(S[mid - 1] == '(' ? 0 : 1, false);
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
    cin >> S;
    sp.init_tree();
}

void solve(){
    while(Q--){
        int cmd, l, r;
        cin >> cmd >> l >> r;

        if(cmd == 1){
            sp.inverse(l, r);
        }
        else if(cmd == 2){
            sp.reverse(l, r);
        }
        else if(cmd == 3){
            sp.rotate(l, r);
        }
        else{
            cout << sp.query(l, r) << "\n";
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