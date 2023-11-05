#include <iostream>
#include <string>
using namespace std;

int arr[26];
int ret1, ret2, N;
string s1, s2;
void init() {
    cin >> N;
    for (int i = 0; i < N / 2; i++) {
        char a;
        cin >> a;
        s1.push_back(a);
    }
    if (N % 2) {
        char a;
        cin >> a;
    }
    for (int i = 0; i < N / 2; i++) {
        char a;
        cin >> a;
        s2.push_back(a);
    }
}

string solve() {
    for(auto a : s1){
        arr[a-'a']++;
    }
    for(auto a : s2){
        arr[a-'a']++;
    }
    for(int i = 0; i <26; i++){
        if(arr[i]%2) return "No";
    }
    return "Yes";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}