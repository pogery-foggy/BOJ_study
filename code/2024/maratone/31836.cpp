#include <iostream>
#include <vector>
using namespace std;
int N, acnt, bcnt;
vector<int> A, B;

void init() { cin >> N; }

void solve() {
    int i = 0;
    bool flag = true;

    if (N % 3 == 2) {
        A.push_back(1);
        B.push_back(2);
        acnt++;
        bcnt++;
        i = 2;
    }
    while (i + 3 <= N) {
        if (flag) {
            A.push_back(++i);
            A.push_back(++i);
            B.push_back(++i);
            acnt += 2;
            bcnt++;
            flag = !flag;
        } else {
            B.push_back(++i);
            B.push_back(++i);
            A.push_back(++i);
            acnt++;
            bcnt += 2;
            flag = !flag;
        }
    }

    cout << acnt << "\n";
    for (int i = 0; i < acnt; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";
    cout << bcnt << "\n";
    for (int i = 0; i < bcnt; i++) {
        cout << B[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}