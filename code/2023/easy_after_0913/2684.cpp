#include <iostream>
#include <string>
using namespace std;

string s;
string arr[8] = {"TTT", "TTH", "THT", "THH", "HTT", "HTH", "HHT", "HHH"};
int answer[8];
void init() { cin >> s; }

void solve() {
    for (int i = 0; i < 8; i++) {
        int cnt = 0;
        int pos = 0;
        while (s.find(arr[i],pos) != string::npos) {
            cnt++;
            pos = s.find(arr[i], pos)+1;
            if (cnt == 40)
                break;
        }
        answer[i] = cnt;
    }
    for (int i = 0; i < 8; i++) {
        cout << answer[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}