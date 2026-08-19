#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int contry[1001];
vector<pair<int, pair<int, int>>> arr;
int N;
bool comp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) { return a.first > b.first; }
int main() {
    cin >> N;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        int c, n, s;
        cin >> c >> n >> s;
        arr[i] = {s, {c, n}};
    }
    sort(arr.begin(), arr.end(), comp);
    int ans = 0;
    for (int i = 0; ans < 3; i++) {
        int c = arr[i].second.first;
        int n = arr[i].second.second;
        int s = arr[i].first;
        if (++contry[c] >= 3)
            continue;
        else {
            cout << c << " " << n << "\n";
            ans++;
        }
    }
}