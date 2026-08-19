#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;
struct Bitset{
    ull block[33];
    void set(int pos){block[pos>>6] |= (1ULL << (pos&63));}
    void clear() {for (int i = 0; i < 33; i++) block[i] = 0;}
    void shift(){
        for(int i = 32; i >= 0 ; i--){
            bool carry = ((block[i] >> 63)&1 ? true : false);
            block[i] <<= 1;
            if(carry && i + 1 < 33) block[i+1] |= 1;   // 오버플로우 방지를 그냥
        }
        block[0] |= 1;
    }
    Bitset operator&(const Bitset &t) const{  
        Bitset c;
        for(int i = 0; i < 33; i++){
            c.block[i] = block[i] & t.block[i];
        }
        return c;
    }
    Bitset operator|(const Bitset &t) const{
        Bitset c;
        for(int i = 0; i < 33; i++){
            c.block[i] = block[i] | t.block[i];
        }
        return c;
    }
    Bitset operator^(const Bitset &t) const{
        Bitset c;
        for(int i = 0; i < 33; i++){
            c.block[i] = block[i] ^ t.block[i];
        }
        return c;
    }
    Bitset operator-(const Bitset &t) const{
        // carry 주의
        Bitset c;
        bool carry = 0; 
        for(int i = 0; i < 33; i++){ 
            c.block[i] = block[i] - t.block[i];
            if(carry)
                c.block[i]--;
            carry = (block[i] < t.block[i] || ((block[i] == t.block[i])&carry));

        }
        return c;
    }
    size_t count(){
        size_t total = 0;
        for(int i = 0; i < 33; i++){
            total += __builtin_popcountll(block[i]);
        }
        return total;
    }
};
string s1, s2;
// 만든거 lcs라는 함수로 합치기
size_t LCS(int s) {
	Bitset alpha[26], candidat, previou;

	for (int k = 0; k < 26; k++) alpha[k].clear();
	candidat.clear();
	previou.clear();
    int sz = (int)s1.size();
	for (int i = 0; i < sz; i++) {
        int idx = (s+i) % sz;
		alpha[s1[idx] - 'a'].set(i);
	}

	for (auto a : s2) {
		candidat = previou | alpha[a - 'a'];
		previou.shift();
		previou = candidat ^ (candidat & (candidat - previou));
	}

	return previou.count();
}
void init(){
    cin >> s1 >> s2;
}
void solve() {
    size_t ans = 0;
    size_t sz = s1.size(); // 절반이상 돌리면 의미없음
    for (int i = 0; i < sz; i++)
        ans = max(ans, LCS(i));
    reverse(s1.begin(), s1.end());
    for (int i = 0; i < sz; i++)
        ans = max(ans, LCS(i));
    cout << ans;
}
// 기존
// Bitset alpha[26], candidat, previou; //candidate, previous
// string s1,s2;
// void init(){
//     cin >> s1 >> s2;
//     for(int i = 0; i < s1.size(); i++){
//         alpha[s1[i] - 'A'].set(i);
//     }
// }
// void solve(){
//     for(auto a:s2){
//         candidat = previou | alpha[a - 'A'];
//         previou.shift();
//         previou = candidat ^ (candidat & (candidat-previou));
//     }
//     cout << previou.count();
// }

int main() {
    init();
    solve();
    return 0;
}