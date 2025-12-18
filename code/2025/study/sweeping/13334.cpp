#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
pair<int, int> lines[100000];
vector<pair<int, int>> dots;
int N, D, answer;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        lines[i].first = a;
        lines[i].second = b;
    }
    cin >> D;
    for (int i = 0; i < N; i++) {
        if (lines[i].second - lines[i].first > D) {
            continue;
        }
        dots.push_back({lines[i].first, 1});       // +1? -1?
        dots.push_back({lines[i].second - D, -1}); // 끝점이 먼저오게 하려면 -1이고 빼야함
    }
    sort(dots.begin(), dots.end());
}
// 끝점에서 D를 뺀 값을 추가
// 만약 끝점-D 가 시작점 보다 앞에 있다면
// 선분 L이 품을 수 있는 선,
// 그리고 시작점을 만나는 순간, 그 선분은 L이 품을 수 없는 선이 된 것.
// 겹치면 끝점 먼저 계산해야함
// 큰 핵심은 우선순위 큐와 같다. L or R좌표로 정렬한뒤 R or L좌표를 보는 것
// 끝점 - D도 포함하고 정렬해야함.
// 정수쌍이 D를 넘는 것을 포함해도 될까? 될거같음 어차피 +1 -1 음.. 안되나. 될것같음 음수만 조심하면. 안됨.
void solve() {
    int cur = 0, cnt = 0;
    for (int i = 0; i < dots.size(); i++) {
        cnt -= dots[i].second;
        answer = max(answer, cnt);
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