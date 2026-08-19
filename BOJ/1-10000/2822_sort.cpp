#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int,int>> arr(8);
vector<int> answer;
int sum;
void init() {
    for(int i = 0 ; i <8; i++){
        int a;
        cin >> a;
        arr[i] = make_pair(a,i+1);
    }
    sort(arr.begin(), arr.end());
}

void solve() {
    for(int i = 3; i <8;i++){
        sum += arr[i].first;
        answer.push_back(arr[i].second);
    }
    
    sort(answer.begin(), answer.end());

    cout << sum << "\n";
    for(int i = 0 ; i <5 ; i++){
        cout << answer[i] <<" ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}