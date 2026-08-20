#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point
{
    long long x,y;
};
vector<Point> stars;
int N;

long long ccw(Point a, Point b, Point c){
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    return x1*y2 - x2*y1;
}

long long dist(Point a, Point b){
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}
bool compare(Point a, Point b){
    long long direction = ccw(stars[0], a, b);
    if(direction > 0) return true;
    if(direction < 0) return false; 
    return dist(stars[0], a) < dist(stars[0], b); 
}

void init() {
    cin >> N;
    stars.resize(N);
    long long minx = 40001, maxy = -40001;
    for(auto &a: stars){
        cin >> a.x >> a.y;
    }
    int si = 0;
    for(int i = 1; i < N; i++){
        if(stars[i].y < stars[si].y || (stars[i].y == stars[si].y && stars[i].x < stars[si].x))
            si = i;
    }
    Point temp = stars[0];
    stars[0] = stars[si];
    stars[si] = temp;

    sort(stars.begin()+1, stars.end(), compare);
}

void solve() {
    vector<Point> convex;
    convex.push_back(stars[0]);
    convex.push_back(stars[1]);
    for(int i = 2; i < N; i++){ 
        while(convex.size() >= 2){ 
            Point a = convex[convex.size()-2];
            Point b = convex[convex.size()-1];
            if(ccw(a,b,stars[i]) > 0) break;  
            else convex.pop_back();
        }
        convex.push_back(stars[i]);
    }
    
    int m = convex.size();
    if (m < 3) { 
        cout << 0;
        return;
    }

    long long total = 0;
    for(int i = 0; i < m; i++){
        int j = (i + 1) % m;
        total += convex[i].x * convex[j].y - convex[i].y * convex[j].x;
    } //x1 * y2 - y1 * x2 신발끈

    double area = fabs((double)total) / 2.0;
    long long cows = (long long)floor(area / 50.0);

    cout << cows;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
