#include <iostream>
#include <queue>
#include <vector>
#define MAX_N 301
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
bool is_water[301];
int arr[301], N, p[MAX_N], cost, mini = 99999999, s = -1;
priority_queue<piii, vector<piii>, greater<piii>> pq;
vector<priority_queue<piii, vector<piii>, greater<piii>>> edge;
// 간선추가할때는 물 연결 안되어 있으면 추가하기
void init() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        mini = mini < arr[i] ? mini : arr[i];
        s = mini < arr[i] ? s : i;
        p[i] = i;
    }
    cost += mini; // 시작
    edge.resize(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int c;
            cin >> c;
            if (i > j) {
                edge[i].push({j,{c,arr[j]});
                    edge[j].push({i, c});
            }
            }
        }
    }

    void solve() {}

    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        init();
        solve();
        return 0; // 정상종료시 반드시 0을 리턴해야합니다.
    }