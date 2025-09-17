#include <iostream>
#include <string>
#include <vector>
using namespace std;
int N;
vector<string> v;
void init() {
    cin >> N;
    v.resize(N);
    for (auto &a : v) {
        cin >> a;
    }
}

void solve() {
    // kbs1과 kbs2의 위치만 찾으면 된다.
    // 가장먼저 kbs1채널로 가서 끝까지 올리고
    // kbs2 채널로 가서 끝까지 올린다. 예외 kbs2가 첫번째 채널이었다면 정렬완료
    // 만약 kbs1을 찾다가 kbs2를 찾으면 달라진다.
    //
    int kbs2 = 1;
    int i = 0, cnt = 0;
    for (i = 0; v[i] != "KBS1"; i++) {
        if (v[i] == "KBS2")
            kbs2 = 0;
    }
    cnt = i;
    for (int i = 0; i < cnt; i++) {
        cout << 1;
    }
    for (int i = 0; i < cnt; i++) {
        cout << 4;
    }

    if (v[i] == "KBS2")
        return;
    else
        cout << 1;
    // kbs1 abc1 abc02 kbs2
    // kbs1 mbc kbs1 kbs2
    for (i = 0; v[i] != "KBS2"; i++) {
    }
    cnt = i;
    for (int i = 0; i < cnt - kbs2; i++) {
        cout << 1;
    }
    for (int i = 0; i < cnt - kbs2; i++) {
        cout << 4;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}