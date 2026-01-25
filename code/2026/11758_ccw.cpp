#include <iostream>

using namespace std;

int x1, x2, x3, y1, y2, y3;
/* ab벡터 x ac벡터 = a->b->c의 각도 , 0이면 일직선, 양수면 반시계, 음수면 시계*/
/* 왜 양수면 반시계일까? a를 기준으로 왼쪽으로 돌아가면 마이너스여야하는거 아닐까?*/
void init() { cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3; }

void solve() {
    /* ab벡터는 b-a, ac벡터는 c-a
    따라서 신발끈 공식에 의해 x2가 먼저 나오는 이유는 a->b->c라서
    (x3-x1)...이 아님!
    (x2-x1)(y3-y1)-(x3-x1)(y2-y1);
    */
    int sign = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    if (sign == 0)
        cout << 0;
    else if (sign > 0)
        cout << 1;
    else
        cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}