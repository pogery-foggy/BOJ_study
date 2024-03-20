#include <iostream>
#include <string>

using namespace std;

int N;
int arr[200001];
int mini = 1, follow = 1, ago, num_cnt;
bool num[200001], is_change[200001];
void init() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        num[arr[i]] = true;
    }
    follow = arr[1];
}

string solve() {
    ago = arr[1];
    num_cnt = 1;
    if (arr[N] != N + 1)
        return "No";
    for (int i = 2; i <= N; i++) {

        if (arr[i] < ago) {
            return "No";
        }
        if (arr[i] > i + 1) {
            return "No";
        }
        if (arr[i] != ago) {
            is_change[i] = true;
            num_cnt++;
        }
        ago = arr[i];
    }
    return "Yes";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    string a = solve();
    cout << a << "\n";
    if (a == "Yes") {
        for (int i = 1; i <= N; i++) {
            if (!is_change[i]) {
                while (num[mini]) {
                    mini++;
                }
                cout << mini << " ";
                mini++;
            } else {
                cout << follow << " ";
                follow = arr[i];
            }
        }
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}