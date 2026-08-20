#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// bitset LCS 랑 히르쉬버그 합체하기
// bitset lcs가변으로 바꿔야함 어떻게? 나누기
typedef unsigned long long ull;

string A, B;

struct Bitset {
    int blocks; // 블럭길이
    int n;
    vector<ull> block;

    Bitset() : blocks(0), n(0) {}

    // m+63 / 64 필요한 만큼만
    void init(int bits) {
        n = bits;
        blocks = (n + 63) >> 6;
        block.assign(blocks, 0);
    }

    void set(int pos){ block[pos >> 6] |= (1ULL << (pos & 63)); }
    void clear(){for(int i = 0; i < block.size(); i++) block[i] = 0; }
    void shift(){
        for(int i = blocks-1; i >= 0 ; i--){
            bool carry = ((block[i] >> 63)&1 ? true : false);
            block[i] <<= 1;
            if(carry && i + 1 < blocks) block[i+1] |= 1;
        }
        block[0] |= 1;
    }

    Bitset operator&(const Bitset &t) const {
        Bitset c;
        c.init(n);
        for (int i = 0; i < blocks; i++){
            c.block[i] = block[i] & t.block[i];
        } 
        return c;
    }

    Bitset operator|(const Bitset &t) const {
        Bitset c;
        c.init(n);
        for (int i = 0; i < blocks; i++){ 
            c.block[i] = block[i] | t.block[i];
        }
        return c;
    }

    Bitset operator^(const Bitset &t) const {
        Bitset c;
        c.init(n);
        for (int i = 0; i < blocks; i++){
            c.block[i] = block[i] ^ t.block[i];
        }
        return c;
    }

    Bitset operator-(const Bitset &t) const {
        Bitset c;
        c.init(n);
        bool carry = 0;
        for(int i = 0; i < blocks; i++){ 
            c.block[i] = block[i] - t.block[i];
            if(carry)
                c.block[i]--;
            carry = (block[i] < t.block[i] || ((block[i] == t.block[i]) &carry));

        }
        return c;
    }

    size_t count(){
        size_t total = 0;
        for (int i = 0; i < blocks; i++){
            total += __builtin_popcountll(block[i]);
        }
        return total;
    }
};

// dp 복구
vector<int> bitset_to_k(const Bitset &t, int m) {
    vector<int> out(m + 1, 0);
    int cur = 0, pos = 1;
    for (int i = 0; i < t.blocks; i++) {
        ull w = t.block[i];
        for (int b = 0; b < min(64, m - (i << 6)); b++) {
            if (w & (1ULL << b)) cur++;
            out[pos++] = cur;
        }
    }
    return out;
}

vector<int> prefix(int as, int ae, int bs, int be) {
    int m = be - bs;
    if (m == 0) return vector<int>(1, 0);

    Bitset alpha[26], candidat, previou;
    
    for (int k = 0; k < 26; k++) alpha[k].init(m);
    candidat.init(m);
    previou.init(m);

    for (int k = 0; k < 26; k++) alpha[k].clear();
    candidat.clear();
    previou.clear();

    for (int j = 0; j < m; j++) {
        alpha[B[bs + j] -'A'].set(j);
    }
    
    for (int i = as; i < ae; i++) {
        candidat = previou | alpha[A[i] -'A'];
        previou.shift();
        previou = candidat ^ (candidat & (candidat - previou));
    }

    // 복구해서 lk값리턴
    return bitset_to_k(previou, m);
}

vector<int> suffix(int as, int ae, int bs, int be) {
    int m = be - bs;
    if (m == 0) return vector<int>(1, 0);

    Bitset alpha[26], candidat, previou;

    for (int k = 0; k < 26; k++) alpha[k].init(m);
    candidat.init(m);
    previou.init(m);

    for (int k = 0; k < 26; k++) alpha[k].clear();
    candidat.clear();
    previou.clear();

    for (int j = 0; j < m; j++) {
        alpha[B[be - 1 - j] - 'A'].set(j);
    }

    for (int i = ae - 1; i >= as; i--) {
        candidat = previou | alpha[A[i] -'A'];
        previou.shift();
        previou = candidat ^ (candidat & (candidat - previou));
    }

    return bitset_to_k(previou, m);
}

string hirschberg(int as, int ae, int bs, int be) {
    int n = ae - as;
    int m = be - bs;
    if (!n || !m) return "";

    if (n == 1) {
        char ch = A[as];
        for (int i = bs; i < be; i++) {
            if (B[i] == ch) {
                return string(1, ch);
            }
        }
        return "";
    }

    int amid = as + (n >> 1);
    vector<int> lk = prefix(as, amid, bs, be);
    vector<int> rk = suffix(amid, ae, bs, be);

    int maxi = -1;
    int maxk = 0;
    for (int k = 0; k <= m; k++) {
        int value = lk[k] + rk[m - k];
        if (value > maxi) {
            maxi = value;
            maxk = k;
        }
    }

    int bmid = bs + maxk;
    return hirschberg(as, amid, bs, bmid) + hirschberg(amid, ae, bmid, be);
}

void init() {
    cin >> A >> B;
}

void solve() {
    string answer = hirschberg(0, A.size(), 0, B.size());
    cout << answer.size() << "\n" << answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}