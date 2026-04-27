#include <iostream>
#define MAX_N 1000010
#define MAX_R 1005
using namespace std;

int N, Q;

// in-order를 카드 순서로 봄
// x,y 잘라서 첫번째나 맨 마지막에 붙이는게 1 2
// x,y자르고 순서대로 수집한다음 번갈아 넣고 제자리에 다시 넣음

struct Splay{
    struct Node{
        Node *l, *r, *p;
        int cnt, d;
        bool dummy;

        Node() : l(nullptr), r(nullptr), p(nullptr), cnt(0), d(0), dummy(true) {}

        Node(int _d, bool _dummy = false) : l(nullptr), r(nullptr), p(nullptr),
                                            cnt(1), d(_d), dummy(_dummy) {}
    };

    Node pool[MAX_N];
    Node *tree;
    Node *stk[MAX_N];
    Node *temp[MAX_R], *nxt[MAX_R];
    int pool_cnt, temp_cnt;

    Node *new_node(int d, bool dummy = false){
        pool[pool_cnt] = Node(d, dummy);
        return &pool[pool_cnt++];
    }

    void update(Node *x){
        if(!x)
            return;

        x->cnt = 1;
        if(x->l)
            x->cnt += x->l->cnt;
        if(x->r)
            x->cnt += x->r->cnt;
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
            stk[--top];
    }

    void rotate(Node *x){
        Node *p = x->p;
        Node *g = p->p;
        Node *b = nullptr;

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

    int get_len(){
        return tree->cnt - 2;
    }

    void topping(int s, int e){
        Node *x = cut_range(s, e);
        insert_after(0, x);
    }

    void botting(int s, int e){
        Node *x = cut_range(s, e);
        insert_after(get_len(), x);
    }

    void collect(Node *x){
        temp_cnt = 0;
        int top = 0;
        Node *cur = x;

        while(cur || top){
            while(cur){
                stk[top++] = cur;
                cur = cur->l;
            }

            cur = stk[--top];
            temp[temp_cnt++] = cur;
            cur = cur->r;
        }
    }

    Node *build_by_order(Node **arr, int s, int e, Node *p){
        if(s > e)
            return nullptr;

        int mid = (s + e) >> 1;
        Node *x = arr[mid];

        x->p = p;
        x->l = build_by_order(arr, s, mid - 1, x);
        x->r = build_by_order(arr, mid + 1, e, x);

        update(x);
        return x;
    }

    void shuffle(int s, int e){
        Node *x = cut_range(s, e);
        collect(x);

        int len = temp_cnt;
        int half = (len + 1) >> 1;
        int idx = 0;

        for(int i = 0; i < half; i++){
            nxt[idx++] = temp[i];
            if(i + half < len)
                nxt[idx++] = temp[i + half];
        }

        x = build_by_order(nxt, 0, len - 1, nullptr);
        insert_after(s - 1, x);
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
        bool first = true;

        while(cur || top){
            while(cur){
                stk[top++] = cur;
                cur = cur->l;
            }

            cur = stk[--top];

            if(!cur->dummy){
                if(!first)
                    cout << ' ';
                first = false;
                cout << cur->d;
            }

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
    while(Q--){
        int cmd, l, r;
        cin >> cmd >> l >> r;
        if(cmd == 1)
            sp.topping(l, r);
        else if(cmd == 2)
            sp.botting(l, r);
        else
            sp.shuffle(l, r);
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