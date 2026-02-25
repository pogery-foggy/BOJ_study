#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
string A, B;
void init() {
   cin >> A >> B;
}

// 생각보다 나에겐 이게 더 중요할지도
// 롤링 dp로 해야함
vector<int> prefix(int as, int ae, int bs, int be) {
   int m = be - bs;
   vector<int> cur(m+1, 0), prev(m+1, 0);
   // dp배열을 두줄만으로 해결하는 것
   // prev 이전행에서 의 값, cur 현재 행에서의 값
   for(int i = as; i < ae; i++){ // [as,ae)인거 명심
      cur[0] = 0;
      for(int j = 1; j <= m; j++){
         if(A[i] == B[bs + j - 1]){ 
            //dp[i][j] = dp[i-1][j-1] + 1;
            cur[j] = prev[j - 1] + 1;
         }
         else{
            //dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            cur[j] = max(prev[j], cur[j-1]);
         }
      }
      prev = cur;
   }
   return prev;
}
// reverse쓰고 함수 하나로 합쳐도 되긴하는데 공부하는거니까
// reverse쓰지 않고 역으로 보기
vector<int> suffix(int as, int ae, int bs, int be) {
      int m = be - bs;
   vector<int> cur(m+1, 0), prev(m+1, 0);
   for(int i = ae-1; i >= as; i--){ // 뒤집었으니 [ae,as)를 (ae,as]로 해야하는거 명심
      cur[0] = 0;
      for(int j = 1; j <= m; j++){
         if(A[i] == B[be - j]){ // 뒤집었으니까 j에다가 -1을 한번 더해야하는데 원래 -1해야하니까
            cur[j] = prev[j - 1] + 1;
         }
         else{
            cur[j] = max(prev[j], cur[j-1]);
         }
      }
      prev = cur;
   }
   return prev;
}
// [as, ae), [bs,be) 한번 [as,ae], [bs,be]도 짜볼까
string hirschberg(int as, int ae, int bs, int be) {
   int n = ae - as;
   int m = be - bs;
   if (!n || !m) return "";

   // base
   if (n == 1) { // A가 한글자라 A에 대한 B 겹치는거
      char ch = A[as];
      for (int i = bs; i < be; i++) {
         if (B[i] == ch) {
            return string(1, ch);
         }
      }
      // 없으면
      return "";
   }

   int amid = as + (n >> 1);
   // 이제 k를 찾을거임. a앞과 b,a뒤와 b를 매칭해서 가장 많이 나오는 k
   vector<int> lk = prefix(as, amid, bs, be);
   vector<int> rk = suffix(amid, ae, bs, be);

   int maxi = -1;
   int maxk = 0;
   for (int k = 0; k <= m; k++) {
      int value = lk[k] + rk[m - k];  // 나중에는 그냥 a로 쓰자
      if (value > maxi) {
         maxi = value;
         maxk = k;
      }
   }

   int bmid = bs + maxk;
   // 2사분면 + 4사분면
   return hirschberg(as, amid, bs, bmid) + hirschberg(amid, ae, bmid, be);
   
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
   return 0;
}