#include <iostream>
#include <queue>

using namespace std;
priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
int N;
void init() { cin >> N; }

void solve() {
    long user_in;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        if (!user_in) {
            if (pq.empty()) {
                cout << "0"
                     << "\n";
            } else {
                cout << pq.top().first * pq.top().second << "\n";
                pq.pop();
            }
        } else {
            if (user_in < 0)
                pq.push({-user_in, -1});
            else
                pq.push({user_in, 1});
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