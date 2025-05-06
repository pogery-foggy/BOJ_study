#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> a, b;
vector<int> answer;
vector<int> sa, sb;
int N;

void init() {
    cin >> N;
    a.resize(N);
    b.resize(N);
    for (auto &x : a) {
        cin >> x;
    }
    for (auto &x : b) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
}

void solve() {
    int x = 0, y = 0;
    while (x < a.size() && y < b.size()) {
        int na = a[x];
        int nb = b[y];
        if (na == nb) {
            answer.push_back(na);
            x++;
            y++;
        } else if (na < nb) {
            sa.push_back(na);
            x++;
        } else {
            sb.push_back(nb);
            y++;
        }
    }

    while (x < a.size()) {
        sa.push_back(a[x]);
        x++;
    }
    while (y < b.size()) {
        sb.push_back(b[y]);
        y++;
    }

    
    cout << answer.size() << "\n";
    for (auto c : answer) {
        cout << c << " ";
    }
    for (auto c : sa) {
        cout << c << " ";
    }
    cout << "\n";
    for (auto c : answer) {
        cout << c << " ";
    }
    for (auto c : sb) {
        cout << c << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}