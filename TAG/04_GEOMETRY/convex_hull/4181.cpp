#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct Point {
    long long x, y;
};
vector<Point> stars;
int N, nN;

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
    stars.reserve(N);
    
    long long minx = 21, maxy = -21;
    for(int i = 0; i < N; i++){
        int x, y;
        char flag;
        cin >> x >> y >> flag;
        if(flag == 'Y'){
            stars.push_back({x,y});
            nN++;
        }
    }
    int si = 0;
    for (int i = 1; i < nN; i++) {
        if (stars[i].x < stars[si].x || (stars[i].x == stars[si].x && stars[i].y < stars[si].y))
            si = i;
    }
    Point temp = stars[0];
    stars[0] = stars[si];
    stars[si] = temp;

    sort(stars.begin() + 1, stars.end(), compare);
}

void solve() {

    int rev = nN-1;
    while(ccw(stars[0], stars[nN-1], stars[--rev]) == 0){;}
    reverse(stars.begin()+rev+1,stars.end());

    cout << stars.size() << "\n";
    for (auto a : stars) {
        cout << a.x << " " << a.y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}