#include <iostream>

using namespace std;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int N;
char map[51][51];
void init() {
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];
}

bool is_valid(int y, int x) {
    if (x < 0 || x >= N)
        return false;
    if (y < 0 || y >= N)
        return false;
    return true;
}
void swap(int y, int x, int ny, int nx) {
    char temp = map[y][x];
    map[y][x] = map[ny][nx];
    map[ny][nx] = temp;
}

int check() {
    int maxi = 1;
    for (int i = 0; i < N; i++) {
        char s = map[i][0];
        int cnt = 1;
        for (int j = 1; j < N; j++) {
            if (s != map[i][j]) {
                maxi = maxi > cnt ? maxi : cnt;
                s = map[i][j];
                cnt = 1;
            } else
                cnt++;
        }
        maxi = maxi > cnt ? maxi : cnt;
    }
    for (int i = 0; i < N; i++) {
        char s = map[0][i];
        int cnt = 1;
        for (int j = 1; j < N; j++) {
            if (s != map[j][i]) {
                maxi = maxi > cnt ? maxi : cnt;
                s = map[j][i];
                cnt = 1;
            } else
                cnt++;
        }
        maxi = maxi > cnt ? maxi : cnt;
    }
    return maxi;
}

void solve() {

    // 브루트포스인건 확실한데 어떻게?
    // 인접한 타일이 다르면 바꿔보고 전부 탐색? 비효율적이긴한데
    // 다 다르다는 가정하에 (4 * 4(모서리) + 3 * (N-2) (엣지) 4 * (N-2)(N-2))/2 = 4768
    // 뒤집을 때마다 모든 줄을 확인해야하니 50 * 50 * 4768 == 11 920 000
    int answer = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x = j;
            int y = i;
            for (int k = 0; k < 4; k++) {
                int ny = y + dy[k];
                int nx = x + dx[k];
                if (!is_valid(ny, nx))
                    continue;
                // 나누기 2 안해도 시간은 안터진다. 비효율적인 visit배열말고 방법도 안떠오른다.
                if (map[y][x] == map[ny][nx])
                    continue;
                swap(y, x, ny, nx);
                int fnd = check();
                answer = answer > fnd ? answer : fnd;
                swap(y, x, ny, nx); // 원상복구
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