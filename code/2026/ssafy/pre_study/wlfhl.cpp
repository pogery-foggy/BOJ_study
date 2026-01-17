#include <iostream>
#include <queue>
using namespace std;
int N, sx, sy, ex, ey;
char wlfhl[300][300];
int map[300][300], is_visit[300][300];
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

bool is_valid(int y, int x) {
    if (x < 0 || N <= x)
        return false;
    if (y < 0 || N <= y)
        return false;
    return true;
}

void surround_plus(int y, int x) {
    for (int i = 0; i < 8; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if(!is_valid(ny,nx)) continue;
        map[ny][nx]+=1;
    }
}
void init() {
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            map[i][j] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> wlfhl[i][j];
            if (wlfhl[i][j] == '*') {
                map[i][j] = -9;
                is_visit[i][j] = true;
                surround_plus(i, j);
            } else
                is_visit[i][j] = false;
        }
    }
}

void bfs(int y, int x){
    queue<pair<int,int>> q;
    q.push({y,x});
    is_visit[y][x] = true;
    while(!q.empty()){
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();
        for(int i = 0; i < 8; i++){
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            if(!is_valid(ny,nx)) continue;
            if(is_visit[ny][nx]) continue;
            if(map[ny][nx] == 0){
                q.push({ny,nx});
            }
            is_visit[ny][nx] = true;
        }
    }
}

int solve() {
    int cnt = 0;
    
    for(int i =0; i < N; i++){
        for(int j = 0; j <N; j++){
            if(is_visit[i][j]) continue;
            if(map[i][j] != 0) continue;
            cnt++;
            bfs(i,j);
        }
    }
    for(int i =0; i < N; i++){
        for(int j = 0; j <N; j++){
            if(!is_visit[i][j]) cnt++;
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
        init();
        cout << "#" << testcase << " " << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}