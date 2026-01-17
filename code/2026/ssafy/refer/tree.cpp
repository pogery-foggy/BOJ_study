#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> tree;
int N, maxi;
bool comp(int a, int b) { return a > b; }
void init() {
    tree.clear();
    cin >> N;
    tree.resize(N);
    for (auto &a : tree) {
        cin >> a;
    }
    sort(tree.begin(), tree.end(), comp);
    maxi = tree[0];
}

int solve() {
    /* max와의 차이는 2의 길이와 1로 이루어져있고
        2는 1 두개로 이루어져 있음.
        그리고 2를 분해해서 2와 1의 균형을 최대한 맞춰야함
        그리고 둘이 같은만큼 뺴고
        그냥 더 많은 쪽에 맞춤 1은 -1, 2로끝나면 두배해야함, 같으면 두배
    */
    int two = 0, one = 0;
    for (auto a : tree) {
        two += (maxi - a) / 2;
        one += (maxi - a) % 2;
    }
    // 예외 애초에 1이 훨씬 많았을경우
    while (!(two - one == 0 || two - one == 1 || two - one == -1) && two > one) {
        two -= 1;
        one += 2;
    }
    if(one > two){ //퐁당퐁
        return one *2 -1;
    }
    else { //퐁당 같을때와 two가 더 많을때 똑같음
        return two*2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int testcase = 0; testcase < T; testcase++) {
        init();
        cout << "#" << testcase + 1 << " " << solve() << "\n";
    }
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}