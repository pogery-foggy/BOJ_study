#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> man, hat;
int N;

void init() {
    man.clear();
    hat.clear();
    cin >> N;
    man.resize(N);
    hat.resize(N);
    for (auto &a : man)
        cin >> a;
    for (auto &a : hat)
        cin >> a;
    sort(man.begin(), man.end());
    sort(hat.begin(), hat.end());
}

bool in_area(int x, int y) {
    if (-3 <= x - y && x - y <= 3)
        return true;
    else
        return false;
}

int solve() {
    // 그리디, 투포인터인가
    // 정렬 후, 앞사람부터 가장 앞에 있는 모자를 쓸 수 있는지 판단.
    // 쓸 수 있다면, 사람++, 모자++
    // 쓸 수 없다면, 사람이 더 클경우 모자++
    //               모자가 더 클 경우 사람++
    // 어느 한쪽이 끝나기 전까지 계속 돌림
    //
    // 첫번째 사람이 가장 가까운 모자를 쓰지 않는다고 하자.
    // 그러면 하나씩 밀리게 되고 마지막 사람은 모자를 쓰지 못한다.
    // 이게 아닌거 같은데
    // 귀류법으로 증명이 가능한가? 아니면 그리디가 아닌것인가?
    int m = 0, h = 0;
    int cnt = 0;
    while (m < N && h < N) {
        if (in_area(man[m], hat[h])) {
            m++;
            h++;
            cnt++;
        } else {
            if (man[m] > hat[h]) {
                h++;
            } else {
                m++;
            }
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        cout << "#" << testcase + 1 << " " << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}