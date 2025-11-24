#include <iostream>
#define MAX_N 501
using namespace std;
int arr[MAX_N];
int N;

void init(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
}
void solve(){
    int answer = 0;
    int st = 0;
    for(int i = 0;i < N - 2; i++){
        // a[k] - a[k+1] = -1 * (a[k+1] - a[k+2])
        if(arr[i] == arr[i+2]){
            st++;
        }
        else st = 0;
        answer = answer > st ? answer : st;
    }
    // 존재하지 않는 경우 없음.
    cout << answer+2 << "\n";
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	std::ios::sync_with_stdio(false);
	cin >> T;
	for (test_case = 1; test_case <= T; test_case++)
	{
		cout << "#" << test_case << " ";
		init();
        solve();
	}

	return 0; // 정상종료시 반드시 0을 리턴해야 합니다.
}
