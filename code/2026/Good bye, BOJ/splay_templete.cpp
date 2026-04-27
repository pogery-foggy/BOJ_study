#include <iostream>
#define MAX_N 300000
#define MAX_NODE MAX_N
typedef long long ll;
using namespace std;

const int INF = 1000000000;

int N, Q;

struct Splay{
    struct Node{
        Node *l, *r, *p;
        int cnt;
        int d, mn, mx;
        ll sum;
        bool flip, dummy;

        Node() : l(nullptr), r(nullptr), p(nullptr), cnt(0), d(0),
                 mn(INF), mx(-INF), sum(0), flip(false), dummy(true) {}

        Node(int _d, bool _dummy = false) : l(nullptr), r(nullptr), p(nullptr),
                                            cnt(1), d(_d), flip(false), dummy(_dummy) {
            if(dummy){
                mn = INF;
                mx = -INF;
                sum = 0;
            }
            else{
                mn = mx = d;
                sum = d;
            }
        }
    };

    Node pool[MAX_NODE];
    Node *tree;
    Node *node[MAX_N + 5]; // node[x] = 값 x를 가진 노드
    Node *stk[MAX_NODE];
    int pool_cnt;

    int my_min(int a, int b){
        return a < b ? a : b;
    }

    int my_max(int a, int b){
        return a > b ? a : b;
    }

    void swap_node(Node *&a, Node *&b){
        Node *temp = a;
        a = b;
        b = temp;
    }

    Node *new_node(int d, bool dummy = false){
        pool[pool_cnt] = Node(d, dummy);
        return &pool[pool_cnt++];
    }

    void update(Node *x){
        if(!x)
            return;

        x->cnt = 1;

        if(x->dummy){
            x->sum = 0;
            x->mn = INF;
            x->mx = -INF;
        }
        else{
            x->sum = x->d;
            x->mn = x->d;
            x->mx = x->d;
        }

        if(x->l){
            x->cnt += x->l->cnt;
            x->sum += x->l->sum;
            x->mn = my_min(x->mn, x->l->mn);
            x->mx = my_max(x->mx, x->l->mx);
        }

        if(x->r){
            x->cnt += x->r->cnt;
            x->sum += x->r->sum;
            x->mn = my_min(x->mn, x->r->mn);
            x->mx = my_max(x->mx, x->r->mx);
        }
    }

    void push(Node *x){
        if(!x || !x->flip)
            return;

        swap_node(x->l, x->r);

        if(x->l)
            x->l->flip = !x->l->flip;
        if(x->r)
            x->r->flip = !x->r->flip;

        x->flip = false;
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

    // k는 dummy를 포함한 0-based rank
    // 왼쪽 dummy가 rank 0이므로 실제 1번째 원소는 kth(1)
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

    // s, e는 실제 배열 기준 1-based 구간
    // 결과 구간은 tree->r->l에 고립됨
    Node *gather(int s, int e){
        Node *rnode = kth(e + 1);
        Node *lnode = kth(s - 1);

        splay(rnode, lnode);
        return rnode->l;
    }

    void reverse_range(int s, int e){
        if(s > e)
            return;

        Node *x = gather(s, e);
        if(x)
            x->flip = !x->flip;
    }

    // k > 0: 오른쪽으로 k칸 shift
    // k < 0: 왼쪽으로 -k칸 shift
    void shift_range(int s, int e, int k){
        int len = e - s + 1;

        if(len <= 1)
            return;

        k %= len;
        if(k < 0)
            k += len;

        if(!k)
            return;

        reverse_range(s, e);
        reverse_range(s, s + k - 1);
        reverse_range(s + k, e);
    }

    int get_value(int pos){
        Node *x = kth(pos);
        return x->d;
    }

    // node[x]가 값 x를 가진 노드라고 가정
    // 현재 위치는 왼쪽 dummy까지 포함한 left cnt라서 그대로 1-based 위치가 됨
    int get_pos(int x){
        splay(node[x]);
        return tree->l ? tree->l->cnt : 0;
    }

    // [s, e] 구간을 잘라서 subtree pointer로 반환
    Node *cut_range(int s, int e){
        Node *x = gather(s, e);

        tree->r->l = nullptr;
        if(x)
            x->p = nullptr;

        update(tree->r);
        update(tree);

        return x;
    }

    // 현재 배열의 pos번째 원소 뒤에 subtree x 삽입
    // pos = 0이면 맨 앞, pos = 현재 길이면 맨 뒤
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

    void del_range(int s, int e){
        cut_range(s, e);
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
            x = new_node(mid, false);
            node[mid] = x;
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

    void print_tree(){
        int top = 0;
        Node *cur = tree;

        while(cur || top){
            while(cur){
                push(cur);
                stk[top++] = cur;
                cur = cur->l;
            }

            cur = stk[--top];

            if(!cur->dummy)
                cout << cur->d << ' ';

            cur = cur->r;
        }
        cout << "\n";
    }
};

Splay sp;

void init(){
    cin >> N >> Q;
    sp.init_tree();
}

void solve(){
    int op, l, r, x;

    while(Q--){
        cin >> op;

        if(op == 1){
            cin >> l >> r;

            Splay::Node *cur = sp.gather(l, r);
            cout << cur->mn << ' ' << cur->mx << ' ' << cur->sum << "\n";

            cur->flip = !cur->flip;
        }
        else if(op == 2){
            cin >> l >> r >> x;

            Splay::Node *cur = sp.gather(l, r);
            cout << cur->mn << ' ' << cur->mx << ' ' << cur->sum << "\n";

            sp.shift_range(l, r, x);
        }
        else if(op == 3){
            cin >> x;
            cout << sp.get_value(x) << "\n";
        }
        else if(op == 4){
            cin >> x;
            cout << sp.get_pos(x) << "\n";
        }
    }

    sp.print_tree();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}