#include <iostream>
#include <string>

using namespace std;

int N, M, U, V;
char texture[402][402], map[201][201], is_visit[201][201];
string method;
void init() {
    cin >> N >> M;
    cin >> U >> V;
    for (int i = 0; i < U; i++) {
        for (int j = 0; j < V; j++) {
            cin >> texture[i][j];
            map[i][j] = texture[i][j];
            is_visit[i][j] = true;
        }
    }
    cin >> method;
}

void solve() {

    if (method == "clamp-to-edge") {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (is_visit[i][j])
                    continue;
                if (i < U)
                    map[i][j] = texture[i][V - 1];
                else if (j < V)
                    map[i][j] = texture[U - 1][j];
                else
                    map[i][j] = texture[U - 1][V - 1];
            }
        }
    } else if (method == "repeat") {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                map[i][j] = texture[i % U][j % V];
            }
        }
    } else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int a = i % (2 * U);
                int b = j % (2 * V);
                if (a >= U)
                    a = U * 2 - a - 1;
                if (b >= V)
                    b = V * 2 - b - 1;
                map[i][j] = texture[a][b];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << map[i][j];
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}