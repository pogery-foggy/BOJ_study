#include <iostream>
#include <vector>
using namespace std;
vector<int> happy_number;
int is_happy[10000];
bool visit[10000];
int sum;
void init() {}

int find_happy(int cur) {
    int ret = cur;
    if (cur == 1)
        return is_happy[cur] = 1;
    if (visit[cur])
        return is_happy[cur];
    visit[cur] = true;
    int new_cur = 0;
    while (cur > 0) {
        int power = cur % 10;
        new_cur += power * power;
        cur /= 10;
    }
    return is_happy[ret] = find_happy(new_cur);
}

int solve(int value) {
    int result = find_happy(value);
    if (result == 1) {
        happy_number.push_back(value);
        return 1;
    }
    return 0;
}

int main() {
    int T = 9999;
    init();
    for (int testcase = 1; testcase <= T; testcase++) {
        solve(testcase);
    }
    int cnt = 0;
    int sum = 0;
    for (int i = 1; i <= T; i++) {
        if (is_happy[i] == 1) {
            cnt++;
            sum += i;
        }
    }
    long long answer = (long long)cnt * (long long)sum;
    // cout << "1~9999 범위의 행복 수는 " << cnt << "개이고 총합은 " << sum << "입니다.\n";
    cout << answer << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}