#include <iostream>
#include <stdio.h>

// i& ( 1 << j ) i의 j번째 비트가 1인지 아닌지를 의미한다.
void printSubsets(char arr[], int n) {
    for (int i = 0; i < (1 << n); ++i) {
        printf("{");
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j))
                printf("%c ", arr[j]);
        }
        printf("}\n");
    }
}

int main(void) {
    char data[] = {'A', 'B', 'C', 'D'};
    printSubsets(data, 4);
    return 0;
}