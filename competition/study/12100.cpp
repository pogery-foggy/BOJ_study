#include <iostream>
#include <vector>
#define MAX_N 20
using namespace std;
int N, answer;

vector<int> merge_one_line(vector<int> line){
    vector<int> ret(N, 0);
    int cur = 0; // 위치
    int last = 0;   // 마지막
    for(auto x : line){
        if(x == 0) continue;
        if(last == 0) last = x;
        else if(last == x){
            ret[cur++] = last * 2;
            last = 0;
        }
        else{
            ret[cur++] = last;
            last = x;
        }
    }
    // 마지막처리
    ret[cur] = last;
    return ret;
}

vector<vector<int>> left(vector<vector<int>> original){
    vector<vector<int>> cpy(N,vector<int>(N,0));
    for(int i = 0; i < N; i++){
        cpy[i] = merge_one_line(original[i]);
    }
    return cpy;
}

vector<vector<int>> right(vector<vector<int>> original){
    vector<vector<int>> cpy(N, vector<int>(N,0));
    // 뒤집어서 계산하고 다시 뒤집어서 넣기
    for(int i = 0; i < N; i++){
        vector<int> data(N);
        for(int j = 0; j < N; j++){
            data[j] = original[i][N-1-j];
        }

        data = merge_one_line(data);
        for(int j = 0; j < N; j++){
            cpy[i][N-1-j] = data[j];
        }
    }
    return cpy;
}

vector<vector<int>> down(vector<vector<int>> original){
    // 세로 후 뒤집어서 계산하고 다시 뒤집어서 세로로 넣기
    vector<vector<int>> cpy(N, vector<int>(N,0));
    for(int j = 0; j < N; j++){
        vector<int> data(N);
        for(int i = 0; i < N; i++){
            data[i] = original[N-1-i][j];
        }

        data = merge_one_line(data);
        for(int i = 0; i < N; i++){
            cpy[N-1-i][j] = data[i];
        }
    }
    return cpy;
}

vector<vector<int>> up(vector<vector<int>> original){
    // 세로로 계산하고 넣기
    vector<vector<int>> cpy(N,vector<int>(N,0));
    for(int j = 0; j < N; j++){
        vector<int> data(N);
        for(int i = 0; i < N; i++){
            data[i] = original[i][j];
        }

        data = merge_one_line(data);
        for(int i = 0; i < N; i++){
            cpy[i][j] = data[i];
        }
    }
    return cpy;
}

void dfs(int depth, vector<vector<int>> map){
    if(depth == 6){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                answer = answer > map[i][j] ? answer : map[i][j];
            }
        }
        return; 
    }
    // l=1 r=10 d=100 u=1000 움직였을때 map이 똑같으면 수직인 움직임에 대해 정지움직임은 dfs안돌려도 됨. 
    // 근데 구현귀찮으니 하지말자 네이브하게가자
    dfs(depth+1, left(map));
    dfs(depth+1, right(map));
    dfs(depth+1, down(map));
    dfs(depth+1, up(map));
}

void solve() {
    cin >> N;
    vector<vector<int>> map(N,vector<int>(N,0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> map[i][j];
        }
    } 
    dfs(1, map);
    cout << answer;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}