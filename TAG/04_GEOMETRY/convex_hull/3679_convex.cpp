#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct Point {
    long long x, y;
    int id;
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
    long long direction = ccw(stars[0], a, b);
    if (direction > 0)
        return true; 
    if (direction < 0)
        return false;            
    return dist(stars[0], a) < dist(stars[0], b);
}

void init() {
    stars.clear();
    cin >> N;
    stars.resize(N);
    
    for(int i = 0; i < N; i++){
        cin >> stars[i].x >> stars[i].y;
        stars[i].id = i;
    }
    int si = 0;
    for (int i = 1; i < N; i++) {
        if (stars[i].x < stars[si].x || (stars[i].x == stars[si].x && stars[i].y < stars[si].y))
            si = i;
    }
    Point temp = stars[0];
    stars[0] = stars[si];
    stars[si] = temp;

    sort(stars.begin() + 1, stars.end(), compare);
}

void solve() {

    int rev = N-1;
    while(ccw(stars[0], stars[N-1], stars[--rev]) == 0){;}
    reverse(stars.begin()+rev+1,stars.end());

    cout << stars[0].id;
    for(int i = 1; i < N; i++){
        cout << " " << stars[i].id;
    }cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for(int testcase = 0; testcase < T; testcase++){
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}