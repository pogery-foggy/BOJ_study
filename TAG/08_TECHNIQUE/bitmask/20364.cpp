#include <iostream>
using namespace std;

int N, Q,answer;
bool tree[1200000];

void init() { cin >> N >> Q; }
int check(int a) {
    int answer = 0;
    int tmp = a;
    while(a>0){
        if(tree[a]) answer = a;
        a>>=1;
    }
    tree[tmp] = true;
    return answer;
}

void solve() {
    for (int i = 0; i < Q; i++) {
        int x;
        cin >> x;
        cout << check(x) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}