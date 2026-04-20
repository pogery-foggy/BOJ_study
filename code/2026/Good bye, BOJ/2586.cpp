#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_N 200001
using namespace std;
typedef long long ll;

int P, F;
int pump[MAX_N], truck[MAX_N];
int cur, mini, maxi;
vector<int> pos[MAX_N * 2];
// 비슷한듯 다르다. 하지만 어찌보면 같다.
// 펌프가 나오면 넣고 level++, 소방차면 --level 하고 넣음 
void init(){
    cin >> P >> F;
    for(int i = 0; i < P; i++) cin >> pump[i];
    for(int i = 0; i < F; i++) cin >> truck[i];

    cur = mini = maxi = P+F;
    int i = 0, j = 0;
    while(i < P || j < F){
        // 같은 좌표면 펌프를 먼저 처리
        if(j == F || (i < P && pump[i] <= truck[j])){
            pos[cur].push_back(pump[i]);
            maxi = max(maxi, cur);
            cur++;
            i++;
        }
        else{
            cur--;
            pos[cur].push_back(truck[j]);
            mini = min(mini, cur);
            j++;
        }
    }
}

void solve(){

    ll answer = 0;

    for(int lv = mini; lv <= maxi; lv++){
        auto &v = pos[lv];
        if(v.size() == 0) continue;

        ll cost = 0;
        for(int k = 1; k < v.size(); k += 2){
            cost += 1LL * v[k] - v[k - 1];
        }
        if((v.size() & 1) == 0){
            answer += cost;
            continue;
        }
        ll best = cost;
        for(int k = v.size() - 1; k >= 2; k -= 2){
            cost += 1LL * v[k] - 2LL * v[k - 1] + v[k - 2];
            best = min(best, cost);
        }
        answer += best;
    }

    cout << answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}