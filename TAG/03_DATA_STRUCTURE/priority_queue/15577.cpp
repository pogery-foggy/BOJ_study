#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<double> arr;
int N;
double answer;

bool compare(double a, double b) { return a > b; }

void init() {
    cin >> N;
    arr.resize(N);
    for (auto &a : arr) {
        cin >> a;
    }
    sort(arr.begin(), arr.end(), compare);
    answer = arr.back();
    arr.pop_back();
}

void solve() {
    while(!arr.empty()){
        double temp1 = arr.back();
        arr.pop_back();
        answer += temp1;
        answer /= 2.0;
    }

    cout << fixed;
    cout.precision(6);
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}