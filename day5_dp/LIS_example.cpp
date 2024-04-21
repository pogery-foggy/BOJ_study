#include <cstdio>
#include <iostream>

using namespace std;

int lis[100];
int pre[100];
int a[50];
int answer = 0;
int ans[100];
int n; // 입력
void DP() {
    int last = 0, len = 1;
    for (int i = 0; i < n; i++) {
        lis[i] = 1;
        pre[i] = -1;

        for (int j = 0; j < i; j++) {
            if (a[j] > a[i])
                continue;

            if (lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
                pre[i] = j;
                if (answer < lis[i])
                    last = i, answer = lis[i];
            }
        }
    }
}

void printArray(int pos) {
    if (pos < 0)
        return;
    printArray(pre[pos]);

    printf("%d ", a[pos]);
    /*loop문*/
    for (int src = pos, i = 0; src >= 0; src = pre[src])
        ans[i++] = src;

    for (int i = lis[n - 1] - 1; i >= 0; i--)
        printf("%d ", a[ans[i]]);
}

int main() { return 0; }