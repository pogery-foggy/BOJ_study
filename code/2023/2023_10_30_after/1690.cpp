#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> arr;
int lamp[2001];
int N, M, arr_size;

void init() {
    cin >> N >> M;
    arr.resize(N);
    for(int i = 0 ; i <N; i++){
        int a;
        cin >> a;
        arr[i].resize(a);
        for(int j = 0 ; j < a ;j++){
            cin >> arr[i][j];
            lamp[arr[i][j]]+=1;
        }
    }
}

bool check(int x,int* cpy){
    for(auto a : arr[x]){
        if(cpy[a] - 1 <=0)
            return false;
    }
    return true;
}

int solve() {
    for(int i = 0 ; i < N; i++){
        if(check(i,lamp))
            return 1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}