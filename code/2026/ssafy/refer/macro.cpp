#include <iostream>
#include <queue>
#define MAX_N 20
#define NOTFIND 0
using namespace std;
typedef pair<int, pair<int,int>> piii;
int N;
int dy[] = {-1,0,0,1}; // 순서중요 
int dx[] = {0,-1,1,0};
int map[MAX_N][MAX_N];
int sy,sx, level = 2, exp = 0;
void init() {
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> map[i][j];
            if(map[i][j] == 9){
                sy = i;
                sx = j;
                map[i][j] = 0;
            }
        }
    }
}

bool is_valid(int y,int x){
    if(y<0 || N<=y) return false;
    if(x<0 || N<=x) return false;
    return true;
}

int bfs(int yy, int xx){
    queue<piii> q;
    bool is_visit[MAX_N][MAX_N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            is_visit[i][j] = 0;
        }
    }

    q.push({0,{yy,xx}});
    is_visit[yy][xx] = true;
    // 2. 거리중에서 제일 위 왼쪽 따로 구해야 함
    int dist = 0;
    int miny = -1;
    int minx = -1;

    while(!q.empty()){
        int y = q.front().second.first;
        int x = q.front().second.second;
        int t = q.front().first;
        q.pop();
        // 1. 이러면 안된다.
        // 8 8 8 8 1
        // 8 8 8 8 0
        // 0 0 9 0 0
        // 0 8 8 8 8
        // 1 8 8 8 8 이러면 왼쪽 아래거부터 탐색하게 된다.
        // if(map[y][x] && map[y][x] < level){
        //     sy = y;
        //     sx = x;
        //     map[y][x] = 0;
        //     return t;
        // }
        // 2. 직접 갱신해줘야함 
        // 찾았을 때 부분이랑 bfs 끝부분 바꿔야함
        // 최적 index 찾고, index 0 만들고 sy sx 갱신하고 return else -1
        if(dist && t > dist) break; // 찾았고 더 멀리가야하면 종료
        if(map[y][x] && map[y][x] < level){
            if(!dist){
                dist = t;
                miny = y;
                minx = x;
            }
            else{
                if(y<miny || (y==miny && x<minx)){
                    miny = y;
                    minx = x;
                }
            }
            continue; // t+1 볼필요 없음
        }
        if(dist) continue;

        for(int i = 0; i < 4; i++){
            int ny = dy[i] + y;
            int nx = dx[i] + x;
            if(!is_valid(ny,nx)) continue;
            if(is_visit[ny][nx]) continue;
            if(map[ny][nx] > level) continue;
            q.push({t+1,{ny,nx}});
            is_visit[ny][nx] = true;
        }
    }

    if(!dist) return -1;
    else{
        sy = miny;
        sx = minx;
        map[sy][sx] = 0;
        return dist;
    }
}

int solve() {
    int t = 0;
    int a = 0;
    while(1){
        // cout << sx+1 <<" " << sy+1 << "\n";
        int e = bfs(sy,sx);
        if(e == -1) break;
        t += e;
        // cout << t << ":t\n";
        exp ++;
        if(exp==level){
            exp = 0;
            level++;
        }
        a++;
    }
    return t;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    cout << solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}