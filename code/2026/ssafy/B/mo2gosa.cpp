#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

#define MAX_N 50000
#define MAX_M 50000
#define MAX_LEN 11

using namespace std;

struct Player{
    int l,r;
};

Player player[MAX_N+1];

struct Order{
    int cur;
    int alive;

    void init(int cnt){
        // cnt개 원형으로 만들기.
        for (int i = 1; i <= cnt; i++){
            player[i].l = (i == 1 ? cnt : i-1);
            player[i].r = (i == cnt ? 1 : i + 1);
        }
    }

    void erase(int x){
        int l = player[x].l;
        int r = player[x].r;
        player[l].r = r;
        player[r].l = l;
        alive--;
    }

    void set_s(int s){
        cur = s;
    }

    void next_cur() {
        cur = player[cur].r;
    }
    int get_cur(){
        return cur;
    }
};

int n, m;

Order gamer;
set<string> words[26];
vector<string> round_used; // 라운드에서 사용한단어
unordered_map<string,bool> total_used;  // 전체사용한단어

void init(int N, int M, char mWords[][MAX_LEN])
{
    n = N; m = M;
    for(int i = 0; i < 26; i++) 
        words[i].clear();
    round_used.clear();
    total_used.clear();

    gamer.init(N);
    for(int i = 0; i < M; i++){
        int s = mWords[i][0] - 'a';
        words[s].insert(mWords[i]);
    }
}

int playRound(int mID, char mCh)
{
    gamer.set_s(mID);
    round_used.clear();
    int ch = mCh - 'a';
    
    while(true){
        int cur = gamer.get_cur();

        if(words[ch].empty()){
            gamer.erase(cur);

            for(string s : round_used){
                reverse(s.begin(), s.end());
                if(total_used[s] == 1) continue; // 사용했으면
                words[s[0] - 'a'].insert(s);
            }
            round_used.clear();
            return cur;
        }

        string s = *words[ch].begin();
        words[ch].erase(words[ch].begin());

        round_used.push_back(s);
        total_used[s] = 1;

        ch = s.back()-'a';
        gamer.next_cur();
    }
	return -1;
}