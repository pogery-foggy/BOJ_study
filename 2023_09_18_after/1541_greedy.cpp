#include <iostream>
#include <string>

using namespace std;

string user_in, n;
int answer;
bool is_minus;

void init() { cin >> user_in; 
n = "";}

void solve() {
    for (int i = 0; i <= user_in.size(); i++) {
        if (user_in[i] == '+' || user_in[i] == '-' || i == user_in.size()) {
            if (is_minus)
                answer -= stoi(n);
            else
                answer += stoi(n);
            n = "";
        } else
            n += user_in[i];

        if (user_in[i] == '-')
            is_minus = true;
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