#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> arr;
string s;
int N, answer;
bool flag;
bool cmp(string a, string b) { return a.size() < b.size(); }
void init() {
    cin >> N;
    answer = N;
    arr.resize(N);
    for (auto &a : arr) {
        cin >> a;
    }
    sort(arr.begin(), arr.end(), cmp);
}

void solve() {
    for (int i = 0; i < arr.size() - 1; i++) {
        flag = true;
        for (int j = i + 1; j < arr.size(); j++) {
            for (int k = 0; k < arr[i].size(); k++) {
                if (arr[i][k] != arr[j][k]) {
                    flag = false;
                }
            }
            if (flag) {
                answer--;
                break;
            }
            flag = true;
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