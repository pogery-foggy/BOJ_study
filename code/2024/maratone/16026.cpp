#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
vector<int> tenarr;
int answer;
int N, cut;
void init() {
    cin >> N >> cut;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        if (a < 10)
            continue;
        else if (a == 10)
            answer++;
        else if (a % 10 == 0)
            tenarr.push_back(a);
        else
            arr.push_back(a);
    }

    if (!tenarr.empty()) {
        sort(tenarr.begin(), tenarr.end());
    }
    if (!arr.empty()) {
        sort(arr.begin(), arr.end());
    }
}

void solve() {
    if (arr.empty() && tenarr.empty()) {
        cout << answer;
        return;
    }

    int index = 0;
    while (!tenarr.empty() && cut > 0 && index < tenarr.size()) {
        int need = tenarr[index] / 10 - 1;
        if (need <= cut) {
            index++;
            answer += need + 1;
            cut -= need;
        } else {
            answer += cut;
            cut = 0;
        }
    }
    index = 0;
    while (!arr.empty() && cut > 0 && index < arr.size()) {
        int need = arr[index] / 10;
        if (need <= cut) {
            answer += need;
            cut -= need;
            index++;
        } else {
            answer += cut;
            cut = 0;
        }
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}