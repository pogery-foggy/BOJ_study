#include <iostream>
#include <vector>
using namespace std;
int main() {
    int K, user_in, i, total = 0;
    vector<int> arr;
    cin >> K;
    for (i = 0; i < K; i++) {
        cin >> user_in;
        if (user_in == 0) {
            arr.pop_back();
        } else {
            arr.push_back(user_in);
        }
    }

    for (i = 0; i < arr.size(); i++) {
        total += arr[i];
    }
    cout << total;
    return 0;
}