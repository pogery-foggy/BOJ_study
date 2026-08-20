#include <iostream>
#include <algorithm>
#define MAX_N 1000100
using namespace std;
/*
B B  B   3B
B B' B   2B + C
B B' B'   B + 2C
만약 B < C 라면 3B < 2B + C < B + 2C
만약 B > C 라면 3B > 2B + C > B + 2C

B <= C 라면 그냥 B로 다 사면 됨
B > C라면 일단 묶음이 무조건 이득
그러면 앞에서부터 사면 되는데
3개부터 살때 반례
1 2 1 1 
그럼 언제 2개?
arr[i+1] > arr[i+2] 일때.

이때 
1 2
  2 3
그러면 arr[i+1]-arr[i+2]만큼을 사야하는거
*/

long long answer;
long long N,B,C;
long long arr[MAX_N];
void init() {
    cin >> N >> B >> C;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
}

void solve() {
    if(B<=C){
        for(int i = 0; i < N; i++)
            answer += B * arr[i];
    }else{
        for(int i = 0; i < N; i++){
            if(arr[i+1] <= arr[i+2]){
                // 3
                long long three = min(arr[i], min(arr[i+1], arr[i+2]));
                answer += three * (B + 2*C);
                for(int j = i; j < i+3; j++){
                    arr[j] -= three;
                }
                // 2
                long long two = min(arr[i], arr[i+1]);
                answer += two * (B + C);
                for(int j = i; j < i+2; j++){
                    arr[j] -= two;
                }
                // 1
                answer += B * arr[i];
                arr[i] = 0;
            }
            else{
                // 2
                long long two = min(arr[i], arr[i+1] - arr[i+2]);
                answer += two * (B + C);
                for(int j = i; j < i+2; j++){
                    arr[j] -= two;
                }
                // 3
                long long three = min(arr[i], min(arr[i+1], arr[i+2]));
                answer += three * (B + 2*C);
                for(int j = i; j < i+3; j++){
                    arr[j] -= three;
                }
                // 1
                answer += B * arr[i];
                arr[i] = 0;
            }
        }
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