#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

priority_queue<pair<double,pair<int,int>>> pq;
int p[101], N;
pair<double, double> arr[101];

void init() {
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i].first >> arr[i].second;
        p[i] = i;
    }
    for(int i = 0 ; i < N-1; i++){
        for(int j = i + 1; j < N; j++){
            int x1 = arr[i].first;
            int y1 = arr[i].second;
            int x2 = arr[j].first;
            int y2 = arr[j].second;
            int dx = pow(x2-x1,2.0);
            int dy = pow(y2-y1,2.0);
            pq.push({-sqrt(dx+dy),{i,j}});
        }
    }
}

int find_parent(int x){
    if(p[x] == x) return x;
    return p[x] = find_parent(p[x]);
}

void union_parent(int a, int b){
    a = find_parent(a);
    b = find_parent(b);
    p[a] = b;
}

void solve() {
    int cnt = 0;
    double answer = 0;
    while(cnt < N-1){
        double c = -pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        u = find_parent(u);
        v = find_parent(v);
        if(u == v) continue;
        answer += c;
        union_parent(u, v);
        cnt++;
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