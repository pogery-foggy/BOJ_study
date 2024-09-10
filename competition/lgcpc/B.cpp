#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> one,two;
long long N,K;
void init() {
    cin >> N >> K;
    one.clear();
    two.clear();
    vector<int> temp;
    temp.resize(N);
    for(auto &a : temp){
        cin >> a;
    }
    for(auto a : temp){
        int w;
        cin >> w;
        if(a==1){
            one.push_back(w);
        }
        else{
            two.push_back(w);
        }
    }
    sort(one.begin(), one.end());
    sort(two.begin(), two.end());
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        solve();
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}