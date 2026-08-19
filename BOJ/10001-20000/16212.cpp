#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> arr;
int N;
void init() {
    cin >> N;
    arr.resize(N);
    for(auto &a : arr){
        cin >> a;
    }
    sort(arr.begin(), arr.end());
}

void solve() {
    for(auto a : arr){
        cout << a << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}