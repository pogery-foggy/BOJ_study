#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<pair<int, int>> arr;

    int cnt = 1;
    for (int i = 0; i < 9; i++) {
        int user_in;
        cin >> user_in;
        arr.push_back({user_in, cnt++});
    }

    sort(arr.begin(), arr.end());
    cout << arr[8].first << "\n" << arr[8].second;
}