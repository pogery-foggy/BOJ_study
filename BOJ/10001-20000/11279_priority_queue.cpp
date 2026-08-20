#include <iostream>
#include <queue>

using namespace std;
priority_queue<long long> pq;
int N;
void init() { cin >> N; }

void solve() {
    long long user_in;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        if (!user_in) {
            if (pq.empty()) {
                cout << "0"
                     << "\n";
            } else {
                cout << pq.top() << "\n";
                pq.pop();
            }
        } else {
            pq.push(user_in);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    solve();
    return 0;
}