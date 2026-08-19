#include <iostream>
#include <string>
using namespace std;

string s;
int ahdma, wkdma, ahdmastack, wkdmastack, flag;
char ago;
void init() {
    cin >> s;
    ahdmastack = 0;
    wkdmastack = 0;
    ahdma = 0;
    wkdma = 0;
    flag = 1;
    ago = '5';
}

string solve() {
    for (auto a : s) {
        if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u') {
            if (ago == a) {
                if (a == 'a' || a == 'i' || a == 'u') {
                    flag = 0;
                } else {
                    ago = a;
                    ahdma++;
                    wkdmastack = 0;
                    ahdmastack++;
                    if (ahdmastack == 3)
                        flag = 0;
                }
            } else {
                ago = a;
                ahdma++;
                wkdmastack = 0;
                ahdmastack++;
                if (ahdmastack == 3)
                    flag = 0;
            }
        } else {
            wkdma++;
            wkdmastack++;
            ahdmastack = 0;
            if (ago == a)
                flag = 0;
            ago = a;
            if (wkdmastack == 3)
                flag = 0;
        }
    }
    if (ahdma == 0)
        flag = 0;

    if (flag)
        return s + "> is";
    else
        return s + "> is not";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (1) {
        init();
        if (s == "end")
            break;
        cout << "<" << solve() << " acceptable.\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}