#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, min, max, user_in;
    vector<int> arr;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> user_in;
        arr.push_back(user_in);
    }
    sort(arr.begin(), arr.end());
    min = arr[0];
    max = arr[arr.size() - 1];

    cout << min << " " << max << "\n";
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}