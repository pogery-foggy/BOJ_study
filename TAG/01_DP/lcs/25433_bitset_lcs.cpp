#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long ull;
struct Bitset {
    ull block[782];
    void set(int pos) { block[pos >> 6] |= (1ULL << (pos & 63)); }
    void clear() {for (int i = 0; i < 782; i++) block[i] = 0;}
    void shift() {
        for (int i = 781; i >= 0; i--) {
            bool carry = ((block[i] >> 63) & 1 ? true : false);
            block[i] <<= 1;
            if (carry)
                block[i + 1] |= 1;
        }
        block[0] |= 1;
    }
    Bitset operator&(const Bitset &t) const {
        Bitset c;
        for (int i = 0; i < 782; i++) {
            c.block[i] = block[i] & t.block[i];
        }
        return c;
    }
    Bitset operator|(const Bitset &t) const {
        Bitset c;
        for (int i = 0; i < 782; i++) {
            c.block[i] = block[i] | t.block[i];
        }
        return c;
    }
    Bitset operator^(const Bitset &t) const {
        Bitset c;
        for (int i = 0; i < 782; i++) {
            c.block[i] = block[i] ^ t.block[i];
        }
        return c;
    }
    Bitset operator-(const Bitset &t) const {
        Bitset c;
        bool carry = 0;                 
        for (int i = 0; i < 782; i++) { 
            c.block[i] = block[i] - t.block[i];
            if (carry)
                c.block[i]--;
            carry = (block[i] < t.block[i] || ((block[i] == t.block[i]) & carry));
        }
        return c;
    }
    size_t count() {
        size_t total = 0;
        for (int i = 0; i < 782; i++) {
            total += __builtin_popcountll(block[i]);
        }
        return total;
    }
};
string A, B;
char X, Y;
size_t LCS(string s1, string s2) {
	Bitset alpha[26], candidat, previou;

	for (int k = 0; k < 26; k++) alpha[k].clear();
	candidat.clear();
	previou.clear();
    int sz = (int)s1.size();
	for (int i = 0; i < sz; i++) {
		alpha[s1[i] - 'a'].set(i);
	}

	for (auto a : s2) {
		candidat = previou | alpha[a - 'a'];
		previou.shift();
		previou = candidat ^ (candidat & (candidat - previou));
	}
	return previou.count();
}

void init(){
    cin >> A >> B;
    cin >> X >> Y;
}

string removing(string s, char rem){
    string t;
    t.reserve(s.size());
    for(char a : s)
        if(a != rem) 
            t.push_back(a);
    return t;
}

int prime(int x){
    if(x < 2) return -1;
    vector<bool> is_prime(x+1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= x; i++) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= x; j += i) 
            is_prime[j] = false;
    }

    for(int i = x; i >= 2; i--) 
        if(is_prime[i]) return i;
    return -1;
}

void solve() {
    int walla = A.find(X);
    int wallb = B.find(X);
    string AL = A.substr(0, walla);
    string AR = A.substr(walla + 1);
    string BL = B.substr(0, wallb);
    string BR = B.substr(wallb + 1);
    AL = removing(AL, Y);
    AR = removing(AR, Y);
    BL = removing(BL, Y);
    BR = removing(BR, Y);

    int L = LCS(AL,BL);
    int R = LCS(AR,BR);
    int x = L + 1 + R;
    cout << prime(x);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}