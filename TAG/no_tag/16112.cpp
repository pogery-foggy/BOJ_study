#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> exp;
int N,K;
long long answer;

void init() {
    cin >> N >> K;
    exp.resize(N);
    for(auto &a: exp){
        cin >> a;
    }
    sort(exp.begin(),exp.end());
}
// 100 200 300 400
// 200 300 400
// 300 400
void solve() {
    for(int i = 1, act = 1; i < N; i++){
        answer += exp[i] * act;
        if(act<K) act++;
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