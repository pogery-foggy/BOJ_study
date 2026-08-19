#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> negative, positive, zero, one;
int N;

bool compare(int x, int y) { return x > y; }

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        if (a < 0) {
            negative.push_back(a);
        } else if (a == 0) {
            zero.push_back(a);
        } else if (a == 1) {
            one.push_back(a);
        } else {
            positive.push_back(a);
        }
    }
    sort(negative.begin(), negative.end());
    sort(positive.begin(), positive.end(), compare);
}

void solve() {
    long long answer = 0;
    if (!negative.empty())
        for (int i = 0; i < negative.size() - 1; i += 2) {
            long long a = negative[i];
            long long b = negative[i + 1];
            answer += a * b;
        }
    if (!positive.empty())
        for (int i = 0; i < positive.size() - 1; i += 2) {
            long long a = positive[i];
            long long b = positive[i + 1];
            answer += a * b;
        }

    int remain_negative = 0;
    if (!negative.empty() && negative.size() % 2)
        remain_negative = negative[negative.size() - 1];
    if (zero.empty())
        answer += remain_negative;
    if (!positive.empty() && positive.size() % 2)
        answer += positive[positive.size() - 1];
    answer += one.size();

    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}