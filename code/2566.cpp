#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,pair<int,int>>> arr;

void init() {
    int a;
    for(int i = 1 ; i < 10; i++){
        for(int j = 1; j <10 ; j++){
            cin >> a;
            arr.push_back(make_pair(a,make_pair(i,j)));
        }
    }
}

void solve() {
    sort(arr.begin(),arr.end());
    cout << arr[80].first << "\n";
    cout << arr[80].second.first << " " << arr[80].second.second << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}