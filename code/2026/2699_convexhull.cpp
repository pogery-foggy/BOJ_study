#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
// 시작점 바꿔야함.
struct Point {
    long long x, y;
};
vector<Point> stars;
int N;

long long ccw(Point a, Point b, Point c) {
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}

long long dist(Point a, Point b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool compare(Point a, Point b) {
    // 이건 시계방향으로 돌거
    long long direction = ccw(stars[0], a, b);
    if (direction > 0)
        return false; // 반시계 b
    if (direction < 0)
        return true;                              // 시계 a
    return dist(stars[0], a) < dist(stars[0], b); // ccw가 0이면 일직선이라 더 가까운게 우선순위
}

void init() {
    stars.clear();
    cin >> N;
    stars.resize(N);
    long long minx = 21, maxy = -21;
    for (auto &a : stars) {
        cin >> a.x >> a.y;
    }
    // 시작점 0을 찾는 거 가장 아래있고, 그 중에서 가장 왼쪽에 있는거
    int si = 0;
    for (int i = 1; i < N; i++) {
        if (stars[i].y > stars[si].y || (stars[i].y == stars[si].y && stars[i].x < stars[si].x))
            si = i;
    }
    Point temp = stars[0];
    stars[0] = stars[si];
    stars[si] = temp;

    // 두번째 점을 찾기 위한 정렬 + 나머지 점들은 p0과 p1기준으로 각도 크기에 따라 정렬됨
    sort(stars.begin() + 1, stars.end(), compare);
}

void solve() {
    vector<Point> convex;
    convex.push_back(stars[0]);
    convex.push_back(stars[1]);
    for (int i = 2; i < N; i++) {    // 3번재 부터 끝까지
        while (convex.size() >= 2) { // 돌릴 수 있을 떄까지
            Point a = convex[convex.size() - 2];
            Point b = convex[convex.size() - 1];
            // 문제에서는 양끝점만 포함하랬음 그래서 0 포함안함
            if (ccw(a, b, stars[i]) < 0)
                break;
            else
                convex.pop_back();
        }
        convex.push_back(stars[i]);
    }
    cout << convex.size() << "\n";
    for (auto a : convex) {
        cout << a.x << " " << a.y << "\n";
    }
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