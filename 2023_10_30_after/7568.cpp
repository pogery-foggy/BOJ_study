

#include <iostream>
#include <utility>

using namespace std;
int N, grade;
pair<int, int> arr[50];
void init() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i].first >> arr[i].second;
}

void solve() {
    for (int i = 0; i < N; i++) {
        grade = 1;
        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;
            if (arr[i].first < arr[j].first && arr[i].second < arr[j].second)
                grade++;
        }
        cout << grade << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}