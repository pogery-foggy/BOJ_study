#include <iostream>

using namespace std;

int pac(int x) {
    int answer = 1;
    for (int i = x; i > 0; i--)
        answer *= i;
    return answer;
}

int main() {
    int N, result, K;
    cin >> N >> K;
    result = pac(N) / (pac(K) * pac(N - K));
    cout << result;
}