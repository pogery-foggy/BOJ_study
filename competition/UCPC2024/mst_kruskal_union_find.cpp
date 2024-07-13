/*
1. 서로 같은 부모를 갖는지 판단해주는 함수
bool SameParent(int x, int y)    // 노드 x와 y가 서로 같은 부모를 갖는지 아닌지 판단해주는 함수
{   
    x = Find_Parent(x);        // 노드 x의 부모 찾기
    y = Find_Parent(y);        // 노드 y의 부모 찾기
    if(x == y) return true;      // 두 부모가 같은 부모라면, true를 반환
    else return false;         // 두 부모가 서로 다른 부모라면, false를 반환
}
2. 1번 과정을 위해서, 부모를 찾는 find함수
int Find_Parent(int x)    // 노드 x의 부모를 찾는 함수
{
    if (Parent[x] == x) return x;
    else return Parent[x] = Find_Parent(Parent[x]);
}
3. 서로 다른 부모일 경우, 두 개의 노드를 연결해주는 union 함수
void Union(int x, int y)     // 노드 x와 y를 합쳐주는 함수
{
    x = Find_Parent(x);    // 먼저 x의 부모를 찾고
    y = Find_Parent(y);    // y의 부모를 찾아준다.
    if (x != y)            // 만약 두 노드의 부모가 서로 다르다면
    {
        Parent[y] = x;    // 어느 한쪽 노드의 부모를 연결되는 다른 한쪽 노드로 설정해버림.
    }// 이 과정을 통해 노드 x의 부모도 x, 노드 y의 부모도 x로 부모가 같아진다 !
}
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int N, bridge, parrent[1001];
vector<pair<long long, pair<long long, long long>>> edges;
long long answer, x[1001], y[1001];
double E;

int root(int node) {
    if (parrent[node] == node)
        return node;
    return parrent[node] = root(parrent[node]);
}

void union_root(int a, int b) {
    int root1 = root(a);
    int root2 = root(b);

    if (root1 != root2)
        parrent[root1] = root2;
}

void kruskal() {
    for (auto node : edges) {
        int a = node.second.first;
        int b = node.second.second;

        if (root(a) != root(b)) {
            union_root(a, b);
            answer += node.first;
            bridge++;
        }

        if (bridge == N - 1)
            break;
    }
}

void init() {
    cin >> N;
    edges.clear();
    for (int i = 0; i < N; i++) {
        parrent[i] = i;
        cin >> x[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> y[i];
    }
    cin >> E;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            long long dist = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
            edges.push_back({dist, {i, j}});
        }

    sort(edges.begin(), edges.end());

    answer = 0;
    bridge = 0;
}

void solve() {
    kruskal();
    double temp = E * answer;
    answer = round(temp);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        init();
        solve();
        cout.precision(0);
        cout << fixed;
        cout << "#" << test_case << " " << answer << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}