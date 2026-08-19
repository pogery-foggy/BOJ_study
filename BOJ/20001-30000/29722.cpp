#include <iostream>
#include <string>
using namespace std;

string s, change, answer;
int year, month, day, N, total, ny, nm, nd;
void init() {
    cin >> s;
    change = "";
    change += s[0];
    change += s[1];
    change += s[2];
    change += s[3];
    year = stoi(change);
    change = "";
    change += s[5];
    change += s[6];
    month = stoi(change);
    change = "";
    change += s[8];
    change += s[9];
    day = stoi(change);
    cin >> N;
}

void solve() {
    day += N;
    while(day > 30){
        day -= 30;
        month ++;
        if(month > 12){
            month = 1;
            year++;
        }
    }

    printf("%04d-%02d-%02d\n", year, month, day);
}

int main() {
    // ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}