#include <cmath>
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    double w, h, answer;
    cin >> w >> h;
    answer = (w + h) - sqrt(w * w + h * h);

    printf("%.6lf\n", answer);
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}